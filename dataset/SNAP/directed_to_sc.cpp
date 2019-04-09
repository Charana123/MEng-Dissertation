#include "../../src/gp_utils.hpp"
#include <chrono>
#include "omp.h"
using namespace std;
namespace bip = boost::interprocess;

unsigned long filesize(const char* filename)
{
    std::ifstream in(filename, std::ios::ate | std::ios::binary);
    return static_cast<unsigned long>(in.tellg());
}

void read_set(int b, std::ifstream **infiles, unsigned long *tcsi, vector<unsigned long>* tcs){
    string line;
    if(getline(*infiles[b], line)){
        char *cline = new char[line.length() + 1];
        strcpy(cline, line.c_str());
        unsigned long i = std::stoul(std::strtok(cline, " \t"));
        tcsi[b] = i;
        for(char *s; (s = std::strtok(NULL, " \t")) != NULL; ){
            tcs[b].push_back(std::stoul(s));
        }
        delete[] cline;
    }
};
/* int filesize(const char* filename){ */
/*     std::ifstream infile(filename); */
/*     infile.ignore(std::numeric_limits<std::streamsize>::max()); */
/*     return infile.gcount(); */
/* } */

/* size_t filesize(const char* filename){ */
/*     struct stat sb; */
/*     stat(filename, &sb); */
/*     return (size_t) sb.st_size; */
/* } */

struct Edge {
    unsigned long s;
    unsigned long d;
};

void time(string name, std::function<void()> func){
    auto t1 = chrono::high_resolution_clock::now();
    func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    cout << endl;
}

const int ts = 28;
size_t thunk = 5242880000; // 5 gigabytes
//size_t thunk = 1073741824; // 1 gigabyte
//size_t thunk = 52428800; // 50 megabytes
int main(int argc, char** argv){

    // arguments
    const string inpath = string("/mnt/storage/scratch/an15739/") + string(argv[1]);
    const string outpath = string("/mnt/storage/scratch/an15739/") + string(argv[2]);
    //const string inpath = string(argv[1]);
    //const string outpath = string(argv[2]);
    size_t fs = filesize(inpath.c_str());
    int blocks = fs/thunk + ((fs % thunk > 0) ? 1 : 0);
    cout << "blocks: " << blocks << endl;
    int largest = 0;

    time("read, parsed and wrote sets of block to file", [&]() -> void{
    for(int block = 0; block < blocks; block++){
        // memory mapped file
        bip::file_mapping mapping(inpath.c_str(), bip::read_only);
        bip::mapped_region mapped_rgn(mapping, bip::read_only, thunk*block, (block != blocks - 1) ? thunk : fs%thunk);
        cout << "block: " << block << "here3" << endl;
        char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
        size_t const mmap_size = mapped_rgn.get_size();
        imemstream mmifs(mmaped_data, mmap_size);
        cout << "block: " << block << "here4" << endl;

        unsigned long blargest = 0;
        unsigned long bsmallest = static_cast<unsigned long>(-1);
        cout << "block: " << block << "here5" << endl;
        vector<Edge>* edges = new vector<Edge>();
        /* time("sequential - reading file and parsing to edges", [&]() -> void{ */
            for(string line; getline(mmifs, line); ){
                boost::trim(line);
                if(line.size() == 0) continue;
                char *cline = new char[line.length() + 1];
                strcpy(cline, line.c_str());
                char* cs = std::strtok(cline, " \t");
                unsigned long s = stoul(cs);
                char* cd = std::strtok(NULL, " \t");
                if(cd == NULL || strcmp(cd, "\0") == 0) continue;
                unsigned long d = stoul(cd);
                delete[] cline;
                if(s > blargest) blargest = s;
                if(s < bsmallest) bsmallest = s;
                edges->push_back(Edge{s, d});
            }
        /* }); */
        cout << "block: " << block << "here" << endl;
        if(blargest > largest) largest = blargest;

    //    const unsigned long block = edges->size() / ts;
    //    Edge* edges_data = edges->data();
    //    vector<unsigned long>** sets = new vector<unsigned long>*[ts]();
    //    time("sequential - edges to sets", [&]() -> void{
    //        #pragma omp parallel for
    //        for(int t = 0; t < ts; t++){
    //            sets[t] = new vector<unsigned long>[largest+1]();
    //            for(int i = block * t; i < block * (t+1); i++){
    //                sets[t][(edges_data+i)->s].push_back((edges_data+i)->d);
    //                if(!(directed == 1)) sets[t][(edges_data+i)->d].push_back((edges_data+i)->s);
    //            }
    //        }
    //        for(int i = block * ts; i < edges->size(); i++){
    //            sets[0][(edges_data+i)->s].push_back((edges_data+i)->d);
    //            if(!(directed == 1)) sets[0][(edges_data+i)->d].push_back((edges_data+i)->s);
    //        }
    //    });

        Edge* edges_data = edges->data();
        cout << "block: " << block << "here0" << endl;
        vector<unsigned long>* sets = new vector<unsigned long>[blargest-bsmallest+1]();
        cout << "block: " << block << "here0.1" << endl;
        /* time("sequential - edges to sets", [&]() -> void{ */
            for(int i = 0; i < edges->size(); i++){
                sets[(edges_data+i)->s-bsmallest].push_back((edges_data+i)->d);
            }
        /* }); */
        edges_data = nullptr;
        delete edges;
        cout << "block: " << block << "here1" << endl;

        /* time("sequential - write sets to file", [&]() -> void{ */
            remove(outpath.c_str());
            std::ofstream outfile(outpath + "." + to_string(block));
            for(unsigned long i = 0; i < blargest-bsmallest+1; i++){
                if(sets[i].size() > 0){
                    outfile << i+bsmallest << "\t";
                    for(unsigned long v : sets[i]) outfile << v << " ";
                    outfile << endl;
                }
            }
        /* }); */
        delete[] sets;
        cout << "block: " << block << "here2" << endl;

        /* const unsigned long block = largest / ts; */
        /* const unsigned long block_remain = largest % ts; */
        /* time("parallel - write sets to files", [&]() -> void{ */
        /*     #pragma omp parallel for */
        /*     for(int t = 0; t < ts; t++){ */
        /*         std::ofstream outfile(outpath + "." + to_string(t)); */
        /*         for(unsigned long i = t * block; i < (t+1) * block + (t == ts-1) ? block_remain : 0; i++){ */
        /*             /1* outfile << "i[" << i << "]" << " "; *1/ */
        /*             if(sets[i].size() > 0){ */
        /*                 for(unsigned long v : sets[i]) outfile << v << " "; */
        /*                 outfile << endl; */
        /*             } */
        /*         } */
        /*     } */
        /* }); */

        /* time("sequential - dump files to file", [&]() -> void{ */
        /*     remove(outpath.c_str()); */
        /*     std::ofstream outfile(outpath); */
        /*     for(int t = 0; t < ts; t++){ */
        /*         std::ifstream infile(outpath + "." + to_string(t), std::ios_base::binary); */
        /*         outfile << infile.rdbuf(); */
        /*         remove((outpath + "." + to_string(t)).c_str()); */
        /*     } */
        /* }); */
    }
    });

//    time("find largest", [&]() -> void{
//        bip::file_mapping mapping(inpath.c_str(), bip::read_only);
//        bip::mapped_region mapped_rgn(mapping, bip::read_only);
//        char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
//        size_t const mmap_size = mapped_rgn.get_size();
//        imemstream mmifs(mmaped_data, mmap_size);
//        for(string line; getline(mmifs, line); ){
//            boost::trim(line);
//            if(line.size() == 0) continue;
//            char *cline = new char[line.length() + 1];
//            strcpy(cline, line.c_str());
//            char* cs = std::strtok(cline, " \t");
//            unsigned long s = stoul(cs);
//            char* cd = std::strtok(NULL, " \t");
//            delete[] cline;
//            if(cd == NULL || strcmp(cd, "\0") == 0) continue;
//            unsigned long d = stoul(cd);
//            if(directed == 1) {
//                if(s > largest) largest = s;
//            }
//            else {
//                if(max(s, d) > largest) largest = max(s, d);
//            }
//        }
//    });

    time("merge files", [&]() -> void{
        // Preprocess
        unsigned long* tcsi = new unsigned long[blocks];
        vector<unsigned long>* tcs = new vector<unsigned long>[blocks]();
        std::ifstream** infiles = new std::ifstream*[blocks];
        for(int b = 0; b < blocks; b++) infiles[b] = new std::ifstream(outpath + "." + to_string(b));
        for(int b = 0; b < blocks; b++) read_set(b, infiles, tcsi, tcs);

        // Compute
        unsigned long csi = 0;
        vector<unsigned long>* cs = new vector<unsigned long>();
        std::ofstream outfile(outpath);
        for(int csi = 0; csi < largest + 1; csi++){
            for(int b = 0; b < blocks; b++) if(tcsi[b] == csi) {
                //Include subset into set
                cs->insert(cs->end(), tcs[b].begin(), tcs[b].end());
                tcs[b].clear();
                //Read next set
                read_set(b, infiles, tcsi, tcs);
            }
            if(cs->size() > 0){
                outfile << csi << "\t";
                for(unsigned long v : *cs) outfile << v << " ";
                outfile << endl;
                cs->clear();
            }
        }

        // Clean up
        for(int b = 0; b < blocks; b++) {
            //remove((outpath + "." + to_string(b)).c_str());
            delete infiles[b];
        }
        delete[] infiles;
        delete[] tcsi;
        delete[] tcs;
        delete cs;

    });
}


























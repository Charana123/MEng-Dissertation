#include "../../src/gp_utils.hpp"
#include <chrono>
#include "omp.h"
using namespace std;
namespace bip = boost::interprocess;

unsigned long filesize(const char* filename)
{
    std::ifstream in(filename, std::ios::ate | std::ios::binary);
    return in.tellg();
}

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
int main(int argc, char** argv){

    // arguments
    const string inpath = string("/mnt/storage/scratch/an15739/") + string(argv[1]);
    const string outpath = string("/mnt/storage/scratch/an15739/") + string(argv[2]);
    const int directed = stoi(argv[3]);

    // memory mapped file
    bip::file_mapping mapping(inpath.c_str(), bip::read_only);
    bip::mapped_region mapped_rgn(mapping, bip::read_only);
    char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
    size_t const mmap_size = mapped_rgn.get_size();
    imemstream mmifs(mmaped_data, mmap_size);

    unsigned long largest = 0;
    vector<Edge>* edges = new vector<Edge>();
    time("sequential - reading file and parsing to edges", [&]() -> void{
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
            if(directed == 1) { if(s > largest) largest = s; }
            else { if(max(s, d) > largest) largest = max(s, d); }
            edges->push_back(Edge{s, d});
        }
    });

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
    vector<unsigned long>* sets = new vector<unsigned long>[largest+1]();
    time("sequential - edges to sets", [&]() -> void{
        for(int i = 0; i < edges->size(); i++){
            sets[(edges_data+i)->s].push_back((edges_data+i)->d);
            if(!(directed == 1)) sets[(edges_data+i)->d].push_back((edges_data+i)->s);
        }
    });

    const unsigned long block = largest / ts;
    const unsigned long block_remain = largest % ts;
    time("parallel - write sets to files", [&]() -> void{
        #pragma omp parallel for
        for(int t = 0; t < ts; t++){
            std::ofstream outfile(outpath + "." + to_string(t));
            for(unsigned long i = t * block; i < (t+1) * block + (t == ts-1) ? block_remain : 0; i++){
                /* outfile << "i[" << i << "]" << " "; */
                if(sets[i].size() > 0){
                    for(unsigned long v : sets[i]) outfile << v << " ";
                    outfile << endl;
                }
            }
        }
    });

    time("sequential - dump files to file", [&]() -> void{
        remove(outpath.c_str());
        std::ofstream outfile(outpath);
        for(int t = 0; t < ts; t++){
            std::ifstream infile(outpath + "." + to_string(t), std::ios_base::binary);
            outfile << infile.rdbuf();
            remove((outpath + "." + to_string(t)).c_str());
        }
    });
}



























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

int main(int argc, char** argv){
    time("graph to set-cover", [&]() -> void{
        const int ts = 28;
        string outpath = string(argv[1]);
        string inpath = string(argv[2]);
        int directed = stoi(argv[3]);
        bip::file_mapping mapping(inpath.c_str(), bip::read_only);
        unsigned long file_size = filesize(inpath.c_str());
        unsigned long thread_block = file_size / ts;
        unsigned long block_remain = file_size % ts;

        unsigned long tlargest[ts] = {0};
        unsigned long largest = 0;
        vector<Edge>* tedges = new vector<Edge>[ts]();
        vector<unsigned long>** sets = new vector<unsigned long>*[ts]();
        #pragma omp parallel for
        for(int t = 0; t < ts; t++){
            bip::mapped_region mapped_rgn(mapping, bip::read_only, t * thread_block, thread_block + (t == ts-1 ? block_remain : 0));
            char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
            size_t const mmap_size = mapped_rgn.get_size();

            imemstream mmifs(mmaped_data, mmap_size);
            for(string line; getline(mmifs, line); ){
                boost::trim(line);
                char *cline = new char[line.length() + 1];
                /* cout << "[-" << line << "]" << endl; */
                if(line.size() == 0) continue;
                strcpy(cline, line.c_str());
                const char* cs = std::strtok(cline, " \t");
                /* cout << string(cs) << endl; */
                unsigned long s = stoul(cs);
                const char* cd = std::strtok(NULL, " \t");
                if(cd == NULL) continue;
                /* cout << string(cd) << endl; */
                /* cout << "===" << endl; */
                unsigned long d = stoul(cd);
                delete[] cline;
                if(directed == 1) { if(s > tlargest[t]) tlargest[t] = s; }
                else { if(max(s, d) > tlargest[t]) tlargest[t] = max(s, d); }
                tedges[t].push_back(Edge{s, d});
            }
        }
        for(int t = 0; t < ts; t++) if(tlargest[t] > largest) largest = tlargest[t];
        /* cout << "here" << endl; */
        #pragma omp parallel for
        for(int t = 0; t < ts; t++){
            sets[t] = new vector<unsigned long>[largest+1]();
            /* cout << "here1" << endl; */
            for(Edge& e : tedges[t]){
                sets[t][e.s].push_back(e.d);
                if(!(directed == 1)) sets[t][e.d].push_back(e.s);
            }
        }
        #pragma omp parallel for
        for(int t = 0; t < ts; t++){
            const unsigned long block = largest / ts;
            std::ofstream outfile(outpath + "." + to_string(t));
            for(unsigned long i = t * block; i < (t+1) * block; i++){
                /* outfile << "i[" << i << "]" << " "; */
                for(int t = 0; t < ts; t++) {
                    for(unsigned long v : sets[t][i]){
                        outfile << v << " ";
                    }
                }
                outfile << endl;
            }
        }
        remove(outpath.c_str());
        std::ofstream outfile(outpath);
        for(int t = 0; t < ts; t++){
            std::ifstream infile(outpath + "." + to_string(t), std::ios_base::binary);
            outfile << infile.rdbuf();
            remove((outpath + "." + to_string(t)).c_str());
        }
    });
}



























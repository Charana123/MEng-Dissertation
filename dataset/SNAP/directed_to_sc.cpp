#include "../../src/gp_utils.hpp"
using namespace std;
namespace bip = boost::interprocess;

vector<string>* read_file(string filename)
{
    bip::file_mapping mapping(filename.c_str(), bip::read_only);
    bip::mapped_region mapped_rgn(mapping, bip::read_only);
	char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
	size_t const mmap_size = mapped_rgn.get_size();

	imemstream mmistream(mmaped_data, mmap_size);
	vector<string>* lines = new vector<string>();
	for(string line; getline(mmistream, line);){
		lines->push_back(line);
	}
	return lines;
}

int filesize(const char* filename)
{
    std::ifstream in(filename, std::ios::ate | std::ios::binary);
    return static_cast<int>(in.tellg());
}

struct Edge {
    unsigned long s;
    unsigned long d;
};

int main(int argc, char** argv){
    const int ts = 28;
    string outpath = string(argv[1]);
    string inpath = string(argv[2]);
    int directed = stoi(argv[3]);
    bip::file_mapping mapping(inpath.c_str(), bip::read_only);
    int file_size = filesize(inpath.c_str());
    int page_size = file_size / ts;
    int page_remain = file_size % ts;

    unsigned long largest = -1;
    vector<Edge>* tedges = new vector<Edge>[ts]();
    vector<unsigned long>** sets = new vector<unsigned long>*[ts]();
    for(int t = 0; t < ts; t++){
        bip::mapped_region mapped_rgn(mapping, bip::read_only, t * page_size, page_size + (t == ts ? page_remain : 0));
        char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
        size_t const mmap_size = mapped_rgn.get_size();

        imemstream mmifs(mmaped_data, mmap_size);
        for(string line; getline(mmifs, line); ){
            boost::trim(line);
            boost::tokenizer<> tok(line);
            unsigned long s = stoi(*tok.begin());
            unsigned long d = stoi(*(++tok.begin()));
            if(directed) { if(s > largest) largest = s; }
            else { if(max(s, d) > largest) largest = max(s, d); }
            tedges[t].push_back(Edge{s, d});
        }
        sets[t] = new vector<unsigned long>[largest]();
        for(Edge& e : tedges[t]){
            sets[t][e.s].push_back(e.d);
        }
        const unsigned long block = largest / ts;
        std::ofstream outfile(outpath + "." + to_string(t));
        for(unsigned long i = t * block; i < (t+1) * block; i++){
            for(int t = 1; t < ts; t++) {
                for(int v : sets[t][i]){
                    outfile << v << " ";
                }
            }
            outfile << endl;
        }
    }
    std::ofstream outfile(outpath);
    for(int t = 0; t < ts; t++){
        std::ifstream infile(outpath + "." + to_string(t), std::ios_base::binary);
        outfile << infile.rdbuf();
        remove((outpath + "." + to_string(t)).c_str());
    }
}



























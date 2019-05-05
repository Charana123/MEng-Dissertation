#include "sc_utils.hpp"

using namespace boost;
namespace bip = boost::interprocess;
vector<string>* read_lines(string filename, size_t t, const size_t ts, const size_t fs, const size_t block)
{
    bip::file_mapping mapping(filename.c_str(), bip::read_only);
    bip::mapped_region mapped_rgn(mapping, bip::read_only, t*block, (t != ts-1) ? block : block+(fs%block));
    char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
    size_t const mmap_size = mapped_rgn.get_size();
    imemstream mmifs(mmaped_data, mmap_size);

	imemstream mmistream(mmaped_data, mmap_size);
    vector<string>* lines = new vector<string>();
	for(string line; getline(mmistream, line);){
        lines->push_back(line);
	}
    return lines;
}

unsigned long filesize(const char* filename)
{
    std::ifstream in(filename, std::ios::ate | std::ios::binary);
        return static_cast<unsigned long>(in.tellg());
}

int main(int argc, char** argv){
    string filename = string(argv[1]);
    const size_t ts = std::stoi(argv[2]);

    const size_t fs = filesize(filename.c_str());
    const size_t block = fs/ts;

    for(size_t t = 12; t < ts; t++){
        ofstream out(filename + "." + to_string(ts) + "." + to_string(t));
        vector<string>* lines = read_lines(filename, t, ts, fs, block);
        for(string& line : *lines){
            out << line << endl;
        }
        delete lines;
    }
}

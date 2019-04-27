#include "sc_utils.hpp"

using namespace boost;
namespace bip = boost::interprocess;
vector<string>* read_lines(string filename)
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



int main(int argc, char** argv){
    string filename = string(argv[1]);
    unsigned long ts = std::stoi(argv[2]);
    vector<string>* lines = read_lines(filename);

    unsigned long per_file = lines->size()/ts;
    /* #pragma omp parallel for */
    for(unsigned long t = 0; t < ts; t++){
        ofstream out(filename + "." + to_string(ts) + "." + to_string(t));
        for(unsigned long i = (lines->size()/ts)*t; i < (lines->size()/ts)*(t+1) + (t == ts-1 ? (lines->size() % ts) : 0); i++){
            out << (*lines)[i] << endl;
        }
    }
}

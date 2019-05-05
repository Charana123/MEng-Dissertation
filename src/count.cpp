#include "sc_utils.hpp"
#include <string>

using namespace std;
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
	for(string line; getline(mmistream, line); ){
        lines->push_back(line);
	}
    return lines;
}

int main(int argc, char** argv){
    string filename = string(argv[1]);
    vector<string>* lines = read_lines(filename);
    unsigned long count = 0;
    for(string line : *lines){
        if(line.compare("hammer") == 0) count++;
    }
    cout << "count: " << count << endl;
}

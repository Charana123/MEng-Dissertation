#include "sc_utils.hpp"

using namespace boost;
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

map<int, Set>* get_sets(vector<string>* lines){
    map<int, Set>* sets = new map<int, Set>();
    int counter = 0;
	for(auto& line: *lines){
		set<int> vertices;
		boost::tokenizer<> tokens(line);
		for(auto& token : tokens){
			vertices.insert(std::stoi(token));
		}
		(*sets)[counter] = {vertices, counter};
        counter++;
	}
    return sets;
}

set<int>* get_universe(map<int, Set>* sets){
    set<int>* universe = new set<int>();
    for(auto& e: *sets){
        Set& s = e.second;
        universe->insert(s.vertices.begin(), s.vertices.end());
    }
    return universe;
}

SetCoverInput* read_sci(string filename)
{
    vector<string>* lines = read_file(filename);
    map<int, Set>* sets = get_sets(lines);
    set<int>* universe = get_universe(sets);
	return new SetCoverInput{sets, universe};
}











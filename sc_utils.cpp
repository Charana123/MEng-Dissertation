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

vector<Set*>* get_sets(vector<string>* lines){
    vector<Set*>* sets = new vector<Set*>();
    int counter = 0;
	for(string& line: *lines){
		Set* s = new Set{{}, counter};
		boost::tokenizer<> tokens(line);
		for(auto& token : tokens){
			s->vertices.insert(std::stoi(token));
		}
        sets->push_back(s);
        counter++;
	}
    return sets;
}

set<int>* get_universe(vector<Set*>* sets){
    set<int>* universe = new set<int>();
    for(Set* s: *sets){
        universe->insert(s->vertices.begin(), s->vertices.end());
    }
    return universe;
}

SetCoverInput* read_sci(string filename)
{
    vector<string>* lines = read_file(filename);
    vector<Set*>* sets = get_sets(lines);
    set<int>* universe = get_universe(sets);
	return new SetCoverInput{sets, universe};
}











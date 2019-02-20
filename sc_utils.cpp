#include "sc_utils.hpp"

map<int, Set> read_sets(string filename)
{
    /* auto f = map_file("one.txt", length); */
    bip::file_mapping mapping(filename.c_str(), bip::read_only);
    bip::mapped_region mapped_rgn(mapping, bip::read_only);
	char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
	size_t const mmap_size = mapped_rgn.get_size();

	imemstream mmistream(mmaped_data, mmap_size);
    map<int, Set> sets;
	for(string line; getline(mmistream, line);){
		set<int> vertices;
		boost::trim(*line);
		boost::tokenizer<> tok(*line);
		for(auto beg=tok.begin(); beg!=tok.end();++beg){
			vertices.insert(std::stoi(*beg));
		}
        Set set = {vertices, counter};
		sets[counter] = set;
        counter++;
	}
	return sets;
}

for(string line; getline(ifs, line); ){
    Set* s = parse_line(line);
    delete s;
}

Set* parse_line(string line){
    boost::tokenizer<> tok(line);
    Set* s = new Set();
    for(auto beg=tok.begin(); beg!=tok.end(); ++beg){
        s->vertices.insert(std::stoi(*beg));
    }
    s->i = counter++;
    return s;
}

Set get_universe(map<int, Set> sets){
    Set universe = {{}, -1};
    for(auto e: sets){
        Set& set = e.second;
        std::set_difference(set.vertices.begin(), set.vertices.end(), universe.vertices.begin(), universe.vertices.end(), std::inserter(universe.vertices, universe.vertices.end()));
    }
    return universe;
}




















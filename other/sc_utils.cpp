#include "sc_utils.hpp"

map<int, Set> get_sets(vector<string> lines){
    map<int, Set> sets;
    int counter = 0;
	for(auto line=lines.begin(); line!=lines.end(); ++line){
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

Set get_universe(map<int, Set> sets){
    Set universe = {{}, -1};
    for(auto e: sets){
        Set& set = e.second;
        std::set_difference(set.vertices.begin(), set.vertices.end(), universe.vertices.begin(), universe.vertices.end(), std::inserter(universe.vertices, universe.vertices.end()));
    }
    return universe;
}


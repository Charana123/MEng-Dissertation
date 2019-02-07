#include "utils.hpp"

bool operator==(const Set& a1, const Set& a2)
{
    if(a1.vertices == a2.vertices && a1.i == a2.i) return true;
    else return false;
}

std::ostream& operator<<(std::ostream& o, const Set& s){
    o << "{ k:" << s.i << "," << s.vertices << " }";
    return o;
}

vector<string> read_file(string filename)
{
    /* auto f = map_file("one.txt", length); */
    bip::file_mapping mapping(filename.c_str(), bip::read_only);
    bip::mapped_region mapped_rgn(mapping, bip::read_only);
	char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
	size_t const mmap_size = mapped_rgn.get_size();

	imemstream mmistream(mmaped_data, mmap_size);
	vector<string> lines;
	for(string line; getline(mmistream, line);){
		lines.push_back(line);
	}
	return lines;
}

map<int, Set> get_sets(vector<string> lines){
    map<int, Set> sets;
    int counter = 0;
	for(auto line=lines.begin(); line!=lines.end(); ++line){
		// TODO:: Replace split for tokenizer (its significantly more memory efficient and faster)
		set<int> vertices;
		boost::trim(*line);
		boost::tokenizer<> tok(*line);
		for(auto beg=tok.begin(); beg!=tok.end();++beg){
			vertices.insert(std::stoi(*beg));
		}
        Set set = {vertices, counter};
		/* boost::trim(*line); */
		/* vector<string> vertices; */
		/* boost::split(vertices, *line, boost::is_any_of(" ")); */
		/* vector<int> set(vertices.size()); */
		/* transform(vertices.begin(), vertices.end(), set.begin(), [](string str) -> int { return std::stoi(str); }); */
		sets[counter] = set;
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

SetCoverInput read_problem(string filename)
{
    vector<string> lines = read_file(filename);
    map<int, Set> sets = get_sets(lines);
    Set universe = get_universe(sets);
	return {sets, universe};
}









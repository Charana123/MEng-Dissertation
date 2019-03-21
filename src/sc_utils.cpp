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

/* vector<Set*>* get_sets(vector<string>* lines){ */
/*     vector<Set*>* m = new vector<Set*>(129613600); */
/* 	for(string& line: *lines){ */
/* 		boost::tokenizer<> tokens(line); */
/*         vector<int> temp; */
/* 		for(auto& token : tokens) temp.push_back(std::stoi(token)); */
/*         /1* cout << temp << endl; *1/ */
/*         int set_size = temp.size(); */
/*         for(int i = 0; i < set_size; i++) { */
/*             int s = temp[i]; */
/*             if((*m)[s] == nullptr) (*m)[s] = new Set{{}, s}; */
/*             for(int j = 0; j < i; j++) (*m)[s]->vertices.push_back(temp[j]); */
/*             for(int j = i+1; j < set_size; j++) (*m)[s]->vertices.push_back(temp[j]); */
/*         } */
/* 	} */
/*     vector<Set*>* sets = new vector<Set*>(); */
/*     int counter = 0; */
/*     for(Set* e : *m) { */
/*         if(e != nullptr) { */
/*             e->i = counter++; */
/*             sets->push_back(e); */
/*         } */
/*     } */
/*     cout << *(*sets)[0] << endl; */
/*     return sets; */
/* } */

/* vector<Set*>* get_sets(vector<string>* lines){ */
/*     vector<Set*>* sets = new vector<Set*>(); */
/*     int counter = -1; */
/*     int prev_s = -1; */
/* 	for(string& line: *lines){ */
/* 		boost::tokenizer<> tokens(line); */
/*         int s = std::stoi(*tokens.begin()); */
/*         int d = std::stoi(*(++tokens.begin())); */
/*         /1* cout << "(" << s << "," << d << ")" << endl; *1/ */
/*         if(s == prev_s) (*sets)[counter]->vertices.push_back(d); */
/*         else { */
/*             /1* if(counter != -1) cout << (*sets)[counter]->vertices << endl; *1/ */
/*             Set* sett = new Set{{d}, s}; */
/*             prev_s = s; */
/*             sets->push_back(sett); */
/*             counter++; */
/*         } */
/* 	} */
/*     /1* cout << "counter: " << counter << endl; *1/ */
/*     return sets; */
/* } */

struct set_compare {
    bool operator() (const Set* s1, const Set* s2) const {
        return s1->vertices.size() > s2->vertices.size();
    }
};

vector<Set>* get_sets(vector<string>* lines){
    /* multiset<Set, set_compare>* sets = new multiset<Set*, set_compare>(); */
    vector<Set>* sets = new vector<Set>(lines->size());
    int counter = 0;
	for(string& line: *lines){
        (*sets)[counter].i = counter;
		boost::tokenizer<> tokens(line);
		for(auto& token : tokens) (*sets)[counter].vertices.push_back(std::stoi(token));
        counter++;
	}

    return sets;
}

void get_universe(vector<Set>* sets, vector<int>* universe, int* m, int* avg, int* median, int* largest, int* M){
    *m = 0;
    *M = 0;
    *median = 0; *largest = 0;
    vector<int> set_sizes = {};
    set<int> universe_s;
    for(Set& s : *sets){
        (*m)++;
        *M += s.vertices.size();
        set_sizes.push_back(s.vertices.size());
        if(s.vertices.size() > *largest) *largest = s.vertices.size();
        universe_s.insert(s.vertices.begin(), s.vertices.end());
    }
    universe->insert(universe->end(), universe_s.begin(), universe_s.end());
    *avg = *M/(*m);
    std::nth_element(set_sizes.begin(), set_sizes.begin() + set_sizes.size()/2, set_sizes.end());
    *median = set_sizes[set_sizes.size()/2];
}

SetCoverInput* read_sci(string filename)
{
    vector<string>* lines = read_file(filename);
    vector<Set>* sets = get_sets(lines);
    vector<int>* universe = new vector<int>();
    int m, avg, median, largest, M;
    get_universe(sets, universe, &m, &avg, &median, &largest, &M);
    int n = universe->size();
	return new SetCoverInput{sets, universe, m, n, avg, median, largest, M};
}











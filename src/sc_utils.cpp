#include "sc_utils.hpp"

using namespace boost;
namespace bip = boost::interprocess;

vector<Set>* read_sets(string filename)
{
    bip::file_mapping mapping(filename.c_str(), bip::read_only);
    bip::mapped_region mapped_rgn(mapping, bip::read_only);
	char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
	size_t const mmap_size = mapped_rgn.get_size();

	imemstream mmistream(mmaped_data, mmap_size);

    vector<Set>* sets = new vector<Set>();
    unsigned long counter = 0;
	for(string line; getline(mmistream, line);){
        sets->push_back(Set{{}, counter});
        Set& sett = sets->at(sets->size()-1);
        sett.i = counter++;
        char* cline = new char[line.size() + 1];
        strcpy(cline, line.c_str());
        char* cs = strtok_r(cline, " \t", &cline);
        sett.vertices.push_back(stoul(cs));
        for(; (cs = strtok_r(NULL, " \t", &cline)) != NULL; ){
            sett.vertices.push_back(stoul(cs));
        }
        delete[] cline;
	}
    return sets;
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

void get_universe(vector<Set>* sets, vector<unsigned long>* universe, unsigned long* m, unsigned long* avg, unsigned long* largest, unsigned long* M){
    *m = 0;
    *M = 0;
    *largest = 0;
    unsigned long maxx = 0;
    Set* sets_data = sets->data();
    for(unsigned long i = 0; i < sets->size(); i++){
        (*m)++;
        (*M)+= (sets_data+i)->vertices.size();
        if((sets_data+i)->vertices.size() > *largest) *largest = (sets_data+i)->vertices.size();
        unsigned long c_maxx = *std::max_element((sets_data+i)->vertices.begin(), (sets_data+i)->vertices.end());
        if(c_maxx > maxx) maxx = c_maxx;
    }
    *avg = *M/(*m);

    bool* covered = new bool[maxx+1]();
    for(unsigned long i = 0; i < sets->size(); i++){
        for(unsigned long v : (sets_data+i)->vertices) covered[v] = 1;
    }
    for(unsigned long i = 0; i < maxx+1; i++) if(covered[i] == 1) universe->push_back(i);
    delete[] covered;
}

#include <chrono>
void summarise(string name, std::function<void()> func){
    auto t1 = chrono::high_resolution_clock::now();
    func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "===========" << endl;
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
}

SetCoverInput* read_sci(string filename)
{
    vector<Set>* sets;
    summarise("read sets", [&]() -> void{
        sets = read_sets(filename);
    });
    vector<unsigned long>* universe = new vector<unsigned long>();
    unsigned long m, avg, largest, M;
    get_universe(sets, universe, &m, &avg, &largest, &M);
    unsigned long n = universe->size();
	return new SetCoverInput{sets, universe, m, n, avg, largest, M};
}











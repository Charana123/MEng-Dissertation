#include "greedy.hpp"

map<int, vector<Set*>>* computeInvertedIndex(SetCoverInput* sci){
    map<int, vector<Set*>>* inverted_index = new map<int, vector<Set*>>();
    for(Set& s : *sci->sets){
        for(int v : s.vertices) (*inverted_index)[v].push_back(&s);
    }
    return inverted_index;
}

vector<vector<Set*>>* computePQUEUE(SetCoverInput* sci){
    vector<vector<Set*>>* pqueue = new vector<vector<Set*>>(sci->n + 1);
    for(Set& s : *sci->sets){
        (*pqueue)[s.vertices.size()].push_back(&s);
    }
    return pqueue;
}

// greedy3 - update cardinality, list of lists to find best
vector<int>* greedy_impl3(SetCoverInput* sci, map<int, vector<Set*>>* inverted_index, vector<vector<Set*>>* pqueue){
    // Globals
    vector<int>* sol = new vector<int>(); //list of indices of chosen sets

    int ncovered = 0;
    int max_elem = *std::max_element(sci->universe->begin(), sci->universe->end());
    vector<int> covered(max_elem+1, 0);

    vector<int> cardinality;
    for(Set s : *sci->sets) cardinality.push_back(s.vertices.size());
    vector<int> changes(sci->m);
    int topp = sci->n - 1;
    while((*pqueue)[topp].size() == 0) topp--;

    while(ncovered < sci->n){
        Set* T = (*pqueue)[topp].back();
        (*pqueue)[topp].pop_back();
        sol->push_back(T->i);

        // Element covered in universe
        for(int v : T->vertices){
            if(covered[v] == 1) continue;
            else {
                ncovered++;
                covered[v] = 1;
                // Remove element from all existing sets
                for(Set* s : (*inverted_index)[v]) {
                    changes[s->i] += 1;
                }
            }
        }

        for(int i = 0; i < sci->m; i++){
            if(changes[i] > 0) {
                Set* s = &(*sci->sets)[i];
                auto pos = std::remove((*pqueue)[cardinality[i]].begin(), (*pqueue)[cardinality[i]].end(), s);
                if(pos != (*pqueue)[cardinality[i]].end()) (*pqueue)[cardinality[i]].erase(pos);
                cardinality[i] -= changes[i];
                changes[i] = 0;
                (*pqueue)[cardinality[i]].push_back(s);
            }
        }
        while((*pqueue)[topp].size() == 0 && topp > -1) topp--;
    }

    return sol;
}

// greedy2 - update cardinality, pass to find best
vector<int>* greedy_impl2(SetCoverInput* sci, map<int, vector<Set*>>* inverted_index){
    // Globals
    vector<int>* sol = new vector<int>(); //list of indices of chosen sets

    int ncovered = 0;
    int max_elem = *std::max_element(sci->universe->begin(), sci->universe->end());
    vector<int> covered(max_elem+1, 0);
    vector<CardinalitySet> csets(sci->m);
    for(Set& s : *sci->sets)  csets[s.i] = {s.i, (int)s.vertices.size()};
    while(ncovered < sci->n){
        CardinalitySet T = *std::max_element(csets.begin(), csets.end(), [](CardinalitySet& s1, CardinalitySet& s2) -> bool{
            return s1.cardinality < s2.cardinality;
        });
        sol->push_back(T.i);

        // Element covered in universe
        Set bs = (*sci->sets)[T.i];
        for(int v : bs.vertices){
            if(covered[v] == 1) continue;
            else {
                ncovered++;
                covered[v] = 1;
                // Remove element from all existing sets
                for(Set* s : (*inverted_index)[v]) {
                    csets[s->i].cardinality--;
                }
            }
        }
    }

    return sol;
}


// greedy1 - update sets, pass to find best
vector<int>* greedy_impl1(SetCoverInput* sci, map<int, vector<Set*>>* inverted_index){
    // Globals
    vector<int>* sol = new vector<int>(); //list of indices of chosen sets

    int covered = 0;
    while(covered < sci->n){
        Set T = *std::max_element(sci->sets->begin(), sci->sets->end(), [](Set& s1, Set& s2) -> bool{
            return s1.vertices.size() < s2.vertices.size();
        });
        sol->push_back(T.i);

        // Element covered in universe
        covered += T.vertices.size();
        for(int v : T.vertices){
            // Remove element from all existing sets
            for(Set* s : (*inverted_index)[v]) {
                auto pos = std::remove(s->vertices.begin(), s->vertices.end(), v);
                if(pos != s->vertices.end()) s->vertices.erase(pos);
            }
        }
    }

    return sol;
}


vector<int>* greedy(SetCoverInput* sci, int type){
    if(type == 1) {
        map<int, vector<Set*>>* inverted_index = computeInvertedIndex(sci);
        return greedy_impl1(sci, inverted_index);
    }
    if(type == 2) {
        map<int, vector<Set*>>* inverted_index = computeInvertedIndex(sci);
        return greedy_impl2(sci, inverted_index);
    }
    if(type == 3) {
        map<int, vector<Set*>>* inverted_index = computeInvertedIndex(sci);
        vector<vector<Set*>>* pqueue = computePQUEUE(sci);
        return greedy_impl3(sci, inverted_index, pqueue);
    }
}










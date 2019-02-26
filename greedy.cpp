#include "greedy.hpp"

map<int, vector<Set*>>* computeInvertedIndex(SetCoverInput* sci){
    map<int, vector<Set*>>* inverted_index = new map<int, vector<Set*>>();
    for(Set* s : *sci->sets){
        for(int v : s->vertices) (*inverted_index)[v].push_back(s);
    }
    return inverted_index;
}

SetCoverOutput* greedy_impl(SetCoverInput* sci, map<int, vector<Set*>>* inverted_index){
    // Globals
    set<int>* Sigma = new set<int>(); //list of indices of chosen sets

    // Compute universe
    set<int> universe;
    for(Set* s : *sci->sets) universe.insert(s->vertices.begin(), s->vertices.end());
    set<int>* C = new set<int>(universe); //list of covered vertices

    while(universe.size() > 0){
        sort(sci->sets->begin(), sci->sets->end(), [](Set* s1, Set* s2) -> bool{
            return s1->vertices.size() < s2->vertices.size();
        });
        Set T = *sci->sets->back();
        sci->sets->pop_back();
        Sigma->insert(T.i);

        for(int v : T.vertices){
            // Remove element from all existing sets
            for(Set* s : (*inverted_index)[v]) s->vertices.erase(v);
            // Element covered in universe
            universe.erase(v);
        }
    }

    return new SetCoverOutput{Sigma, C};
}


SetCoverOutput* greedy(SetCoverInput* set_cover_input){
    map<int, vector<Set*>>* inverted_index = computeInvertedIndex(set_cover_input);
    return greedy_impl(set_cover_input, inverted_index);
}










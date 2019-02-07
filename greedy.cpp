#include "greedy.hpp"

map<int, vector<Set*>> computeInvertedIndex(SetCoverInput* set_cover_input){
    map<int, vector<Set*>> inverted_index;
    for(auto& e : set_cover_input->sets){
        Set& s = e.second;
        for(int vertex : s.vertices){
            inverted_index[vertex].push_back(&s);
        }
    }
    return inverted_index;
}

vector<tuple<int, int>> computeCardinality(SetCoverInput* set_cover_input){

    vector<tuple<int, int>> set_cardinality;
    for(auto e : set_cover_input->sets){
        Set& s = e.second;
        set_cardinality.push_back({s.i, s.vertices.size()});
    }
    return set_cardinality;
}

SetCoverOutput greedy_impl(SetCoverInput* set_cover_input, map<int, vector<Set*>> inverted_index){

    // Globals
    set<int> Sigma; //list of indices of chosen sets

    // Compute universe
    set<int> universe;
    for(auto e : set_cover_input->sets) {
        Set s = e.second;
        universe.insert(s.vertices.begin(), s.vertices.end());
    }
    Set C = {universe, -1}; //list of covered vertices

    while(universe.size() > 0){
        vector<tuple<int, int>> set_cardinality = computeCardinality(set_cover_input);
        sort(set_cardinality.begin(), set_cardinality.end(), [](tuple<int, int> t1, tuple<int, int> t2) -> bool{ return get<1>(t1) > get<1>(t2); });
        int T_i = get<0>(set_cardinality[0]);
        Sigma.insert(T_i);
        Set T = set_cover_input->sets[T_i];

        for(int v : T.vertices){
            // Remove element from all existing sets
            for(Set* s : inverted_index[v]){
                s->vertices.erase(v);
            }
            // Element covered in universe
            universe.erase(v);
        }
    }

    return {Sigma, C};
}


SetCoverOutput greedy(SetCoverInput set_cover_input){
    map<int, vector<Set*>> inverted_index = computeInvertedIndex(&set_cover_input);
    return greedy_impl(&set_cover_input, inverted_index);
}










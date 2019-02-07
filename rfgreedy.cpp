#include "rfgreedy.hpp"

SetCoverOutput rfgreedy(SetCoverInput set_cover_input, float q){

    // Globals
    set<int> Sigma; //list of indices of chosen sets

    // Compute universe
    Set universe = {{}, -1};
    for(auto e : set_cover_input.sets) {
        Set s = e.second;
        universe.vertices.insert(s.vertices.begin(), s.vertices.end());
    }
    Set C = universe; //list of covered vertices

    // Reduce to sets
    vector<Set> sets;
    for(auto e : set_cover_input.sets) sets.push_back(e.second);

    make_heap(sets.begin(), sets.end(), [](Set s1, Set s2) -> bool{
        return s1.vertices.size() > s2.vertices.size();
    });

    while(universe.vertices.size() > 0){

        Set T = sets[0];
        int s = T.vertices.size();

        Set diff = {{}, -1};
        set_intersection(T.vertices.begin(), T.vertices.end(), universe.vertices.begin(), universe.vertices.end(), inserter(diff.vertices, diff.vertices.end()));
        int s_prime = diff.vertices.size();

        if (q * s_prime > s){
            pop_heap(sets.begin(), sets.end(), [](Set s1, Set s2) -> bool{
                return s1.vertices.size() > s2.vertices.size();
            });
            sets.pop_back();

            Sigma.insert(T.i);
            for(int v : T.vertices) universe.vertices.erase(v);
        }
        else {
            sets[0] = diff;
            make_heap(sets.begin(), sets.end(), [](Set s1, Set s2) -> bool{
                return s1.vertices.size() > s2.vertices.size();
            });
        }
    }

    return {Sigma, C};
}












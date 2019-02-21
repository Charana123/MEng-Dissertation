#include "rfgreedy.hpp"

SetCoverOutput rfgreedy(SetCoverInput set_cover_input, float q){
    assert(q > 1);

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

    std::function<bool(Set, Set)> max_heap_compare = [](Set s1, Set s2) -> bool{
        return s1.vertices.size() < s2.vertices.size();
    };
    make_heap(sets.begin(), sets.end(), max_heap_compare);

    cout << "universe size: " << universe.vertices.size() << endl;
    while(universe.vertices.size() > 0){

        Set T = sets[0];
        int s = T.vertices.size();

        Set diff = {{}, T.i};
        set_intersection(T.vertices.begin(), T.vertices.end(), universe.vertices.begin(), universe.vertices.end(), inserter(diff.vertices, diff.vertices.end()));
        int s_prime = diff.vertices.size();

        if (q * s_prime > s){
            cout << "T: " << T.vertices << endl;
            cout << "s: " << s << endl;

            pop_heap(sets.begin(), sets.end(), max_heap_compare);
            sets.pop_back();

            Sigma.insert(T.i);
            for(int v : T.vertices) universe.vertices.erase(v);
            cout << "universe size: " << universe.vertices.size() << endl;
        }
        else {
            sets[0] = diff;
            make_heap(sets.begin(), sets.end(), max_heap_compare);
        }
    }

    return {Sigma, C};
}












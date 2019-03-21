#include "naive.hpp"


vector<int>* naive(SetCoverInput* sci){
    // sort sets by size
    sort(sci->sets->begin(), sci->sets->end(), [](Set s1, Set s2) -> bool{
        return s1.vertices.size() > s2.vertices.size();
    });

    // choose a set if it contains an uncovered element while all elements are not covered
    int max_elem = *std::max_element(sci->universe->begin(), sci->universe->end());
    vector<int> covered(max_elem+1, 0);
    int covered_num = 0;
    vector<int>* sol = new vector<int>();
    for(Set s : *sci->sets){
        if(covered_num == sci->n) break;
        int covered_num_s = 0;
        for(int v : s.vertices) {
            covered_num_s += covered[v];
            covered[v] = 1;
        }
        if(covered_num_s < s.vertices.size()) {
            sol->push_back(s.i);
            covered_num += s.vertices.size() - covered_num_s;
        }
    }

    return sol;
}

#include "pgreedy.hpp"

void greedy_pass(ProgressiveGreedyInput& pgin, int threshold, set<int>& sol, set<int>& covered){
    for(Set s; pgin.stream.get_next_set(s) != -1; s = {}){
        /* cout << "s: " << s << endl; */
        set<int> diff;
        set_difference(s.vertices.begin(), s.vertices.end(),
                covered.begin(), covered.end(),
                std::inserter(diff, diff.end()));
        /* cout << "covered: " << covered << endl; */
        /* cout << "diff: " << diff << endl; */
        if(diff.size() >= threshold){
            sol.insert(s.i);
            covered.insert(diff.begin(), diff.end());
        }
    }
    pgin.stream.reset();
}

void progressive_greedy_naive(ProgressiveGreedyInput& pgin, int p, ProgressiveGreedyOutput& pgout){

    assert(p >= 1);
    for(int j = 1; j <= p; j++){
        cout << "exponent: " << 1 - (float)j/p << endl;
        float threshold = pow(pgin.n, 1 - (float)j/p);
        /* cout << "threshold: " << threshold << endl; */
        greedy_pass(pgin, threshold, pgout.sol, pgout.covered);
    }
    /* cout << "solution size: " << pgout.sol.size() << endl; */
}






























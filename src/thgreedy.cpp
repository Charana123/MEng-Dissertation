#include "thgreedy.hpp"

set<int>* threshold_greedy_pass(ThresholdGreedyInput* tgi, int threshold){

    set<int>* sol = new set<int>();
    map<int, bool> covered;
    for(Set* s; (s = tgi->stream->get_next_set()) != nullptr; ){
        set<int> diff;
        for(int i : s->vertices) if(!covered[i]) diff.insert(i);
        if(diff.size() >= threshold){
            sol->insert(s->i);
            for(int i : diff) covered[i] = true;
        }
    }
    tgi->stream->reset();
    return sol;
}

set<int>* threshold_greedy(ThresholdGreedyInput* tgi){

    int passes = log2f(tgi->n);
    set<int>* best_sol;
    int best_sol_size = std::numeric_limits<int>::max();
    for(int i = 0; i < passes; i++){
        int threshold = pow(2, i);
        cout << "threshold: " << threshold << endl;
        set<int>* sol = threshold_greedy_pass(tgi, threshold);
        cout << "sol.size(): " << sol->size() << endl;
        if(sol->size() <= best_sol_size){
            best_sol = sol;
            best_sol_size = sol->size();
        }
    }
    return best_sol;
}











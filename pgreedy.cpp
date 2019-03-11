#include "pgreedy.hpp"

void greedy_pass(ProgressiveGreedyInput* pgin, int threshold, vector<int>* covered, set<int>* sol){
    for(Set* s; (s = pgin->stream->get_next_set()) != nullptr; ){
        vector<int> diff;
        for(int v : s->vertices) if((*covered)[v] == 0) diff.push_back(v);
        if(diff.size() >= threshold){
            sol->insert(s->i);
            for(int v : diff) (*covered)[v] = 1;
        }
    }
    pgin->stream->reset();
}

/* void rand_pass(ProgressiveGreedyInput* pgin, int sample_size, ProgressiveGreedyOutput* pgout){ */

/*     unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); */
/*     vector<int> sample_m; */
/*     sample_m.insert(sample_m.begin(), pgin->universe->begin(), pgin->universe->end()); */
/*     shuffle(sample_m.begin(), sample_m.end(), std::default_random_engine(seed)); */
/*     sample_m.erase(sample_m.begin() + sample_size, sample_m.end()); */
/*     sort(sample_m.begin(), sample_m.end(), std::less<int>()); */

/*     pgout->sol.insert(sample_m.begin(), sample_m.end()); */
/*     for(Set* s; (s = pgin->stream->get_next_set()) != nullptr; ){ */
/*         if(s->i == sample_m.back()) { */
/*             for(int i : s->vertices) pgout->covered[i] = true; */
/*             sample_m.pop_back(); */
/*         } */
/*     } */
/*     pgin->stream->reset(); */
/* } */

set<int>* progressive_greedy_naive(ProgressiveGreedyInput* pgin, int p){

    assert(p >= 1);
    int max_elem = *std::max_element(pgin->universe->begin(), pgin->universe->end());
    set<int>* sol = new set<int>();
    vector<int>* covered = new vector<int>(max_elem);
    /* rand_pass(pgin, 2500, pgout); */
    vector<int> precomp;
    precomp.push_back(1); precomp.push_back(pow(pgin->n, (float)1/p));
    for(int j = 2; j < p+1; j++) precomp[j] = precomp[j-1] * precomp[j-1];
    for(int j = p; j >= 0; j--){
        greedy_pass(pgin, precomp[j], covered, sol);
    }
    return sol;
}






























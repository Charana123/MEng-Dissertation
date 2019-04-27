#include "pgreedy.hpp"

void greedy_pass(ProgressiveGreedyInput* pgin, unsigned long threshold, vector<bool>* covered, unordered_set<unsigned long>* sol){
    for(Set* s; (s = pgin->stream->get_next_set()) != nullptr; ){
        vector<unsigned long> diff;
        for(unsigned long v : s->vertices) {
            if(!(*covered)[v]) diff.push_back(v);
        }
        if(diff.size() >= threshold){
            sol->insert(s->i);
            for(unsigned long v : diff) (*covered)[v] = true;
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

unordered_set<unsigned long>* progressive_greedy_naive(ProgressiveGreedyInput* pgin, unsigned long p){
    cout << "started" << endl;
    assert(p >= 1);
    unsigned long max_elem = *std::max_element(pgin->universe->begin(), pgin->universe->end());
    unordered_set<unsigned long>* sol = new unordered_set<unsigned long>();
    vector<bool>* covered = new vector<bool>(max_elem + 1, false);
    /* rand_pass(pgin, 2500, pgout); */
    vector<float> precomp;
    precomp.push_back(1); precomp.push_back(pow(pgin->n, (float)1/p));
    for(unsigned long j = 2; j < p+1; j++) precomp[j] = precomp[j-1] * precomp[1];
    for(unsigned long j = p; j != static_cast<unsigned long>(-1); j--){
        greedy_pass(pgin, precomp[j], covered, sol);
    }
    return sol;
}






























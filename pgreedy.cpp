#include "pgreedy.hpp"

void greedy_pass(ProgressiveGreedyInput* pgin, int threshold, ProgressiveGreedyOutput* pgout){
    for(Set* s; (s = pgin->stream->get_next_set()) != nullptr; ){
        set<int> diff;
        for(int i : s->vertices){
            if(!pgout->covered[i]) diff.insert(i);
        }
        if(diff.size() >= threshold){
            pgout->sol.insert(s->i);
            for(int i : diff) pgout->covered[i] = true;
        }
    }
    pgin->stream->reset();
}

void rand_pass(ProgressiveGreedyInput* pgin, int sample_size, ProgressiveGreedyOutput* pgout){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    vector<int> sample_m;
    sample_m.insert(sample_m.begin(), pgin->universe->begin(), pgin->universe->end());
    shuffle(sample_m.begin(), sample_m.end(), std::default_random_engine(seed));
    sample_m.erase(sample_m.begin() + sample_size, sample_m.end());
    sort(sample_m.begin(), sample_m.end(), std::less<int>());

    pgout->sol.insert(sample_m.begin(), sample_m.end());
    for(Set* s; (s = pgin->stream->get_next_set()) != nullptr; ){
        if(s->i == sample_m.back()) {
            for(int i : s->vertices) pgout->covered[i] = true;
            sample_m.pop_back();
        }
    }
    pgin->stream->reset();
}

void progressive_greedy_naive(ProgressiveGreedyInput* pgin, int p, ProgressiveGreedyOutput* pgout){

    assert(p >= 1);
    /* rand_pass(pgin, 2500, pgout); */
    for(int j = 1; j <= p; j++){
        float threshold = pow(pgin->n, 1 - (float)j/p);
        greedy_pass(pgin, threshold, pgout);
    }
}






























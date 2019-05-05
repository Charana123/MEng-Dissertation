#include "set-sampling.hpp"

vector<unsigned long>* SimpleSetCover(SSSCInput* sssci, vector<unsigned long>* sampled_universe, unsigned long max_elem){
    vector<bool> sample_covered(max_elem+1, false);
    for(unsigned long v : *sampled_universe) sample_covered[v] = true;
    //Project set-system to sampled universe
    vector<Set>* reduced_sets = new vector<Set>();
    Set* s;
    for(size_t i = 0; (s = sssci->stream->get_next_set()) != nullptr; i++){
        reduced_sets->push_back(Set{{}, s->i});
        for(unsigned long v : s->vertices) if(sample_covered[v]) (*reduced_sets)[i].vertices.push_back(v);
    }
    sssci->stream->reset();
    //Compute reduced offline set-covering
	SetCoverInput sci = SetCoverInput{reduced_sets, sampled_universe, sssci->m, sampled_universe->size(), 0, 0, 0};
    vector<unsigned long>* sol = greedy(&sci);
    /* cout << "sol.size(): " << sol->size() << endl; */
    delete reduced_sets;
    return sol;
}

vector<unsigned long>* ISS(SSSCInput* sssci, unsigned long max_elem, float prob, unsigned long set_threshold){

    //Randomly sample sets c.k.p sets
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_real_distribution<float> distribution(0.0,1.0);
    if(prob >= 1.0) {
        cout << "over-estimation of OPT" << endl;
        return nullptr;
    }

    vector<unsigned long>* sol = new vector<unsigned long>();
    vector<bool> covered(max_elem+1, false);
    vector<unsigned long> T(max_elem+1, 0);
    vector<unsigned long> sampled_universe;
    for(Set* s; (s = sssci->stream->get_next_set()) != nullptr; ){
        for(unsigned long v : s->vertices) T[v]++;
        if(distribution(gen) < prob) {
            sol->push_back(s->i);
            for(unsigned long v : s->vertices) if(!covered[v]){
                covered[v] = true;
                sampled_universe.push_back(v);
            }
        }
    }
    sssci->stream->reset();
    /* cout << "sets sampled: " << sol->size() << endl; */
    /* cout << "sampled_universe.size(): " << sampled_universe.size() << endl; */

    //Compute whether all uncovered elements belong to atmost (m.logn)/pk sets
    vector<unsigned long> remaining_universe;
    for(unsigned long v : *sssci->universe) if(!covered[v]) remaining_universe.push_back(v);
    /* cout << "threshold of how many sets should contain an uncovered element: " << set_threshold << endl; */
    for(unsigned long v : remaining_universe){
        if(T[v] > set_threshold) {
            cout << "set sampling failed" << endl;
            return nullptr;
        }
    }
    vector<unsigned long>* sol_remainder = SimpleSetCover(sssci, &remaining_universe, max_elem);
    sol->insert(sol->end(), sol_remainder->begin(), sol_remainder->end());
    /* cout << "sol_final.size(): " << sol->size() << endl; */
    return sol;
}

/* vector<unsigned long>* SetSampling(SSSCInput* sssci){ */
/*     float p = logf(sssci->n) + 1; */
/*     float c = 5; */
/*     unsigned long guesses = log2f(sssci->n); */

/*     vector<unsigned long>* best_sol = nullptr; */
/*     unsigned long best_sol_size = std::numeric_limits<unsigned long>::max();; */
/*     unsigned long best_opt = 0; */
/*     size_t max_elem = *std::max_element(sssci->universe->begin(), sssci->universe->end()); */
/*     for(unsigned long i = 1; i <= guesses; i++){ */
/*         cout << endl; */
/*         cout << "iteration: " << i << endl; */

/*         unsigned long opt = powf(2, i); */
/*         float prob = (c * opt * p) / sssci->m; */
/*         unsigned long set_threshold = (sssci->m * logf(sssci->n)) / (p * opt); */
/*         vector<unsigned long>* sol = ISS(sssci, max_elem, prob, set_threshold); */
/*         if(sol == nullptr) continue; */
/*         if (sol->size() < best_sol_size) { */
/*             best_sol = sol; */
/*             best_sol_size = sol->size(); */
/*             best_opt = opt; */
/*         } */
/*     } */
/*     return best_sol; */
/* } */

vector<unsigned long>* SetSampling(SSSCInput* sssci, float L){
    size_t max_elem = *std::max_element(sssci->universe->begin(), sssci->universe->end());
    unsigned long c = 2;
    float prob = L / sssci->m;
    /* cout << "prob: " << prob << endl; */
    unsigned long set_threshold = (sssci->m * c * logf(sssci->n)) / L;
    vector<unsigned long>* sol = ISS(sssci, max_elem, prob, set_threshold);
    return sol;
}


//implement the assadi algorithm
//get the recursive demain to work
//show that set sampling works well for large values of OPT












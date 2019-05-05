#include "element-sampling.hpp"

vector<unsigned long>* SimpleSetCover(SSSCInput* sssci, unsigned long max_elem){
    cout << "here4" << endl;
    //Project set-system to sampled universe
    vector<bool> covered(max_elem + 1, false);
    for(unsigned long v : *sssci->universe) covered[v] = true;
    vector<Set>* reduced_sets = new vector<Set>();
    Set* s;
    for(size_t i = 0; (s = sssci->stream->get_next_set()) != nullptr; i++){
        reduced_sets->push_back(Set{{}, s->i});
        for(unsigned long v : s->vertices) if(covered[v]) (*reduced_sets)[i].vertices.push_back(v);
    }
    sssci->stream->reset();
    cout << "here5" << endl;
    //Compute reduced offline set-covering
	SetCoverInput sci = SetCoverInput{reduced_sets, sssci->universe, sssci->m, sssci->universe->size(), 0, 0, 0};
    vector<unsigned long>* sol = greedy(&sci);
    cout << "here6" << endl;
    delete reduced_sets;
    return sol;
}

vector<unsigned long>* REC(SSSCInput* sssci, float k, float c, float p, float logm, float n_delta, size_t max_elem){
    /* float k = sssci->universe->size() / (c * c * p * n_delta * logm); */

    //Base case
    if(sssci->universe->size() < n_delta){
        return SimpleSetCover(sssci, max_elem);
    }

    float memory_bound = sqrt(p * sssci->universe->size() * k * logm);
    unsigned long sample_size = c * memory_bound;
    /* cout << "sample_size: " << sample_size << endl; */
    vector<unsigned long> sampled_universe;
    sample(sssci->universe->begin(), sssci->universe->end(),
        std::inserter(sampled_universe, sampled_universe.begin()), sample_size,
        std::mt19937{std::random_device{}()});
    SSSCInput sampled_sssci{sssci->stream, &sampled_universe, sssci->n, sssci->m};
    vector<unsigned long>* sol_sample = REC(&sampled_sssci, k, c, p, logm, n_delta, max_elem);
    /* cout << "sol_sample: " << sol_sample->size() << endl; */

    if(sol_sample != nullptr){
        //Iterate over the set stream, projecting the sets, solve the set covering using Lazy-Greedy
        vector<bool> covered(max_elem+1, false);
        sort(sol_sample->begin(), sol_sample->end(), std::less<unsigned long>());
        unsigned long i = 0;
        for(Set* s; (s = sssci->stream->get_next_set()) != nullptr; ){
            unsigned long si = (*sol_sample)[i];
            if(s->i == si) {
                for(unsigned long v : s->vertices) covered[v] = true;
                i++;
            }
        }
        sssci->stream->reset();
        vector<unsigned long> remaining_universe;
        for(unsigned long v : *sssci->universe) if(!covered[v]) remaining_universe.push_back(v);

        vector<unsigned long>* sol_remainder = nullptr;
        /* cout << "remaining_universe: " << remaining_universe.size() << endl; */
        /* cout << "remaining_size: " << memory_bound << endl; */
        if(remaining_universe.size() <= memory_bound){
            cout << "here" << endl;
            REC(sssci, k, c, p, logm, n_delta, max_elem);
        }
        if(sol_remainder == nullptr) {
            delete sol_sample;
            return nullptr;
        }
        else {
            sol_sample->insert(sol_sample->end(), sol_remainder->begin(), sol_remainder->end());
            delete sol_remainder;
            return sol_sample;
        }
    }
    else return nullptr;
}

vector<unsigned long>* ElementSampling(SSSCInput* sssci, float delta){
    float p = logf(sssci->n) + 1;
    float c = 10;
    float logm = log2f(sssci->m);
    float n_delta = powf(sssci->n, delta);
    float max_k = sssci->n / (p * logm);
    size_t max_elem = *std::max_element(sssci->universe->begin(), sssci->universe->end());
    unsigned long iterations = 10;
    for(unsigned long i = 1; i <= iterations; i++){
        float k = ((float)max_k/iterations) * i;
        vector<unsigned long>* sol;
        if((sol = REC(sssci, k, c, p, logm, n_delta, max_elem)) != nullptr) return sol;
    }
}

//implement the assadi algorithm
//get the recursive demain to work
//show that set sampling works well for large values of OPT












#include "rssc.hpp"

int p = 1.05;
set<int>* simple_sample_set_cover(Set* universe, Stream* stream){

    map<int, Set*> sets;
    while(Set* s; (s=stream->get_next_set()) != nullptr; ){ sets[s.i] = s; }

    SetCoverInput* sci = new {sets, universe};
    map<int, vector<Set>>* ktoCollection = OrderBySubCollection(sci, p);
    SetCoverOuput* sco = DFG(ktoCollection, p);
    return sco->Sigma;
}

//rho is the approximation factor of the offline algorithm
float get_rho(float n){
    return p * log(n);
}

vector<int>* get_random_sample_idx(int sample_size, int size){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    vector<int>* sample_idx = new boost::irange(1, universe.size());
    sample_idx->erase(sample_size, sample_idx.size());
    std::sort(sample_idx->begin(), sample_idx->end(), [](int a1, int a2) -> { return a1 < a2; });
    return sample_idx;
}

set<int>* recursive_sample_set_cover(RSSCInput* rssc_input){
    float rho = get_rho(rssc_input->universe.size());
    float k = rssc_input->universe.size() / pow(rssc_input->c, 2) * rho * pow(rssc_input->n, rssc_input->accuracy_delta * log(rssc_input->m);

    // Base case
    // Element sampling is repeated until O(m.n^delta) space is required to compute offline.
    if rssc_input->universe.size() <= pow(rssc_input->n, accuracy_delta){
        return simple_sample_set_cover(rssc_input->universe, rssc_input->stream);
    }

    // Case 1, handling OPT(universe, sets) > k via "set sampling" module
    int set_sample_size = rssc_input->c * k * get_rho(rssc_input->n);
    vector<int>* S_rnd_idx = get_random_sample_idx(c1_sample_size, rssc_input->m);
    map<int, int> element_to_count;
    vector<int> covered_elements_of_S_rnd;
    for(Set* s; (s = get_next_set()) != nullptr; ) {
        if (s->i == S_rnd_idx->back()) {
            S_rnd_idx->pop_back();
            covered_elements_of_S_rnd.insert(s->begin(), s->end());
        }
        for(int e : s->vertices) element_to_count[e]++;
    }
    vector<int> uncovered_elements_of_S_rnd;
    set_difference(rssc_input->universe->vertices.begin(), rssc_input->universe->vertices.end(),
            covered_elements_of_S_rnd.begin(), covered_elements_of_S_rnd.end(), uncovered_elements_of_S_rnd.begin());
    float c1_threshold = (m * log(rssc_input->n))/k;

    set<int>* S_rnd = nullptr;
    if(all_of(uncovered_elements_of_S_rnd.begin(), uncovered_elements_of_S_rnd.end(),
            [c1_threshold, &element_to_count](int e) -> {return element_to_count[e] < c1_threshold; })){
        S_rnd  = simple_sample_set_cover()
    }
    else {
        return nullptr;
    }

    // Case 2, handling OPT(universe, sets) < k via "element sampling" module
    int element_sample_size = rssc_input->c * sqrt(rho * rssc_input->universe->size() * k * log(rssc_input->m);
    vector<int>* U_smp_idx = get_random_sample_idx(element_sample_size, rssc_input->m);
    Set* U_smp = new Set();
    for(int i: *S_smp_idx) { U_smp.insert(rssc_input->universe[i]); }

    RSSCInput* rssc_input_smp = new RSSCInput(*rssc_input);
    rssc_input_c2->universe = U_smp;
    set<int>* S_smp = recursive_sample_set_cover(rssc_input_smp);

    vector<int>* sample_idx = new boost::irange(1, universe.size());
    vector<int> U_rem_idx;
    set_difference(sample_idx.begin(), sample_idx.end(),
        U_smp_idx.begin(), U_smp_idx.end(), U_rem_idx.begin());

    set<int>* S_rem;
    if (U_rem_idx->vertices.size() <= rssc_input->universe->vertices.size() / rssc_input->c * pow(n, accuracy_delta/2)){
        Set* U_rem = new Set();
        for(int i : U_rem_idx) { U_rem.insert(rssc_input->universe[i]); }
        RSSCInput* rssc_input_rem = new RSSCInput(*rssc_input);
        rssc_input_rem->universe = U_rem;
        S_rem = recursive_sample_set_cover(rssc_input_rem);
    }
    else {
        return nullptr;
    }

    return nullptr;
}
















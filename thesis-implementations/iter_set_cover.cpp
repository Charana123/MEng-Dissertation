#include "iter_set_cover.hpp"

vector<int>* random_sample(int sample_size, Set& universe){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    vector<int>* S = new boost::irange(1, universe.size());
    shuffle (S->begin(), S->end(), std::default_random_engine(seed));
    S->erase(sample_size, S->size());

    transform(S->begin(), S->end(), S->begin(), [&universe](int i) -> {
        return universe.vertices[i];
    });
    return S;
}

float p = 1.05;
//rho is the approximation factor of the offline algorithm
float get_rho(float n){
    return p * log(n);
}

set<int>* iter_set_cover(IterSetCoverInput* isci){
    int n = eci->universe->vertices.size();
    int log_n = log2f(n);

    // Run in parallel invocations of the algorithm for k \in {1...log n}
    vector<set<int>> Sols = {};
    #pragma omp parallel for
    for(int i = 1; i < log_n; i++){
        Stream* stream = stream->;

        // For k = 2^iteration
        int k = pow(2, i);
        set<int> Sol;
        // Iterate 1/delta for each guess of k ~ OPT
        int repeat = 1/delta_cover;

        int S_size = isci->c * get_rho(isci->n) * k * pow(isci->n, isci->accuracy_delta) * log(isci->m) * log(isci->n);
        for(int i = 0; i < repeat; i++){
            random_sample(S_size, 
        }
    }
    return nullptr;
}


#include "iter_set_cover.hpp"

set<int> random_sample(int sample_size, Set& universe){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    vector<int> i = boost::irange(1, universe.size());
    i.erase(sample_size, i.size());

    shuffle (i.begin(), i.end(), std::default_random_engine(seed));
    transform(i.begin(), i.end(), i.begin(), [&universe](int i) -> {
        return universe.vertices[i];
    });
    return i;
}

EdgeCoverOutput* iterSetCover(EdgeCoverInput* eci){
    int n = eci->universe->vertices.size();
    int log_n = log2f(n);

    vector<set<int>> Sols = {};
    #pragma omp parallel for
    for(int i = 1; i < log_n; i++){

        int k = pow(2, i);
        set<int> Sol;
        int repeat = 1/delta_cover;
        for(int i = 0; i < repeat; i++){
            random_sample(
        }
    }
    return nullptr;
}


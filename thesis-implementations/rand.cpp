#include "rand.hpp"

void rand(RI* ri, RO* ro){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    vector<int>* S = new boost::irange(1, universe.size());
    shuffle (S->begin(), S->end(), std::default_random_engine(seed));
    S->erase(sample_size, S->size());

    for(Set* s; (s = ri->stream->get_next_set()) != nullptr; ){
        s->
    }
}

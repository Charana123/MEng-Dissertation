#ifndef ASSADI_MP
#define ASSADI_MP

#include "sc_utils.hpp"
#include "ssc_utils.hpp"
#include <map>
#include <random>

struct AssadiMP
{
    int epsilon;
    // iterations of element sampling
    // The alpha constant regulates size of element samples to maintain a constant
    // 1 - 1/m^2 probability of a successfull element sampling
    // A larger alpha (more iterations) generates smaller samples
    int alpha;

    Stream* stream;
    int m;
    set<int>* universe;
    int n;
};

set<int>* Algorithm1(AssadiMP* assadiMP, int opt_tilda);
int assadiMP(AssadiMP* assadiMP);

#endif

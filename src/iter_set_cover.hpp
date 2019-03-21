#ifndef ITER_SET_COVER_H
#define ITER_SET_COVER_H
// Set Cover Utilities

#include "ssc_utils.hpp"
/* #include "omp.h" */
#include <random>

// Recursive Sample Set Cover
struct IterSetCoverInput
{
    Stream* stream;
    set<int>* universe;
    int n;
    int m;
    float accuracy_delta; // Controls the number of passes and thereby the space and approximation ratio
    int c; // Controls the accuracy of the randomized sample being a delta-cover
};

set<int>* iter_set_cover(IterSetCoverInput* isci);

#endif

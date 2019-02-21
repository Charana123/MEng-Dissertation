#ifndef ITER_SET_COVER_H
#define ITER_SET_COVER_H
// Set Cover Utilities

#include "ec_utils.hpp"
#include <omp.h>

// Recursive Sample Set Cover
struct IterSetCoverInput
{
    Stream* stream;
    int n;
    int m;
    Set* universe;
    float accuracy_delta; // Controls the number of passes, space and approximation ratio
    float c; // Controls the accuracy of the randomized sample being a delta-cover
};

set<int>* iter_set_cover(IterSetCoverInput* isci);

#endif

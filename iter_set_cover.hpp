#ifndef ITER_SET_COVER_H
#define ITER_SET_COVER_H
// Set Cover Utilities

#include "ec_utils.hpp"
#include <omp.h>

struct EdgeCoverOutput
{
    std::set<int> Sigma;
};

EdgeCoverOutput* iterSetCover(EdgeCoverInput* eci);

#endif

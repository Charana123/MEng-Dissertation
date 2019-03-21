#ifndef RAND_H
#define RAND_H

#include "ssc_utils.hpp"
#include <boost/range/irange.hpp>
#include <random>

struct RI
{
    Stream* stream;
    int n;
};

struct RO
{
    set<int> sol;
    map<int, bool> covered;
};

void rand(RI* ri, RO* ro);

#endif

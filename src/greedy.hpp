#ifndef GREEDY_H_
#define GREEDY_H_

#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>
#include <iterator>
#include "sc_utils.hpp"

struct CardinalitySet{
    unsigned long i;
    unsigned long cardinality;
};

vector<unsigned long>* greedy(SetCoverInput* sci);

#endif

#ifndef GREEDY_H_
#define GREEDY_H_

#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>
#include <iterator>
#include "sc_utils.hpp"

struct CardinalitySet{
    int i;
    int cardinality;
};

vector<int>* greedy(SetCoverInput* sci, int type);

#endif

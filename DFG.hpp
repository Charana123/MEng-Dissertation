#ifndef SET_COVER_H_
#define SET_COVER_H_

#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>
#include <iterator>
#include "utils.hpp"

struct SetCoverOutput {
    std::set<int> Sigma;
    Set C;
};

SetCoverOutput DFG(string filename, float p);

#endif

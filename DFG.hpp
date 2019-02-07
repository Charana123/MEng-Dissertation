#ifndef DFG_H_
#define DFG_H_

#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>
#include <iterator>
#include "utils.hpp"


map<int, vector<Set>> OrderBySubCollection(SetCoverInput set_cover_input, float p);
SetCoverOutput DFG(map<int, vector<Set>> ktoCollection, float p);

#endif

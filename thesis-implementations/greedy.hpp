#ifndef GREEDY_H_
#define GREEDY_H_

#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>
#include <iterator>
#include "sc_utils.hpp"

SetCoverOutput* greedy(SetCoverInput* set_cover_input);
SetCoverOutput* greedy_impl(SetCoverInput* set_cover_input, map<int, vector<Set*>>* inverted_index);
map<int, vector<Set*>>* computeInvertedIndex(SetCoverInput* set_cover_input);

#endif

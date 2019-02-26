#ifndef DFG_H_
#define DFG_H_

#include "sc_utils.hpp"

map<int, vector<Set*>>* OrderBySubCollection(SetCoverInput* sci, float p);
SetCoverOutput* DFG(map<int, vector<Set>>* ktoCollection, float p);

#endif

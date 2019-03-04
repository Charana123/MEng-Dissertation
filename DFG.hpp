#ifndef DFG_H_
#define DFG_H_

#include "sc_utils.hpp"

void OrderBySubCollection(SetCoverInput* sci, float p, vector<float>* p_pow_k, vector<vector<Set*>>* ktoCollection);
vector<int>* DFG(SetCoverInput* sci, float p);

#endif

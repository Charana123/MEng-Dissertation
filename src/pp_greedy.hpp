#ifndef PP_GREEDY_H_
#define PP_GREEDY_H_

#include "DFG.hpp"
#include "sssc.hpp"
#include "boost/range/algorithm/remove_if.hpp"
#include <chrono>

vector<unsigned long>* compose(SSSCInput* sssci, string pp_alg, string type);
#endif

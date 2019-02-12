#ifndef SC_UTILS_H_
#define SC_UTILS_H_
// Set Cover Utilities

#include "gp_utils.hpp"

using namespace std;

struct SetCoverInput
{
    map<int, Set> sets;
    Set universe;
};

struct SetCoverOutput {
    std::set<int> Sigma;
    Set C;
};

SetCoverInput read_sci(string filename);

#endif

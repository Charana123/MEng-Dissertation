#ifndef SC_UTILS_H_
#define SC_UTILS_H_
// Set Cover Utilities

#include "gp_utils.hpp"

using namespace std;

struct SetCoverInput
{
    vector<Set*>* sets;
    vector<int>* universe;
    int m;
    int n;
    int avg;
};

struct SetCoverOutput {
    set<int>* Sigma;
    set<int>* C;
};

SetCoverInput* read_sci(string filename);

#endif

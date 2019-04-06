#ifndef SC_UTILS_H_
#define SC_UTILS_H_
// Set Cover Utilities

#include "gp_utils.hpp"

using namespace std;

struct SetCoverInput
{
    vector<Set>* sets;
    vector<unsigned long>* universe;
    unsigned long m;
    unsigned long n;
    unsigned long avg;
    unsigned long median;
    unsigned long largest;
    unsigned long M;
};

struct PSetCoverInput
{
    vector<Set*>* sets;
    vector<unsigned long>* universe;
    unsigned long m;
    unsigned long n;
    unsigned long avg;
    unsigned long median;
    unsigned long largest;
    unsigned long M;
};

struct SetCoverOutput {
    set<unsigned long>* Sigma;
    set<unsigned long>* C;
};

SetCoverInput* read_sci(string filename);

#endif

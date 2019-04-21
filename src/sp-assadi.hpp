#ifndef SINGLE_ASSADI_H
#define SINGLE_ASSADI_H

#include "ssc_utils.hpp"
#include <algorithm>
#include <random>
#include <map>
#include <chrono>

using namespace std;

struct SPAInput
{
    Stream* stream;
    vector<unsigned long>* universe;
    unsigned long n;
    unsigned long m;
};

vector<unsigned long>* single_sublinear(SPAInput* ssi, unsigned long alpha);
#endif

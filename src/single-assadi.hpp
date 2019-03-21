#ifndef SINGLE_ASSADI_H
#define SINGLE_ASSADI_H

#include "ssc_utils.hpp"
#include <algorithm>
#include <random>
#include <map>
#include <chrono>

using namespace std;

struct SSInput
{
    Stream* stream;
    vector<int>* universe;
    int n;
    int m;
};

vector<int>* single_sublinear(SSInput* ssi, int alpha);
#endif

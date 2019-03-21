#ifndef THGREEDY_H
#define THGREEDY_H

#include "ssc_utils.hpp"

using namespace std;

struct ThresholdGreedyInput
{
    Stream* stream;
    set<int>* universe;
    int n;
    int m;
};

set<int>* threshold_greedy(ThresholdGreedyInput* tgi);
#endif

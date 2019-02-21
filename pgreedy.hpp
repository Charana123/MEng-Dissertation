#ifndef PGREEDY_H
#define PGREEDY_H

#include "ssc_utils.hpp"
#include <algorithm>
#include <random>
#include <map>
#include <chrono>

using namespace std;

struct ProgressiveGreedyInput
{
    Stream* stream;
    set<int>* universe;
    int n;
    int m;
};

struct ProgressiveGreedyOutput
{
    set<int> sol;
    map<int, bool> covered;
};

void progressive_greedy_naive(ProgressiveGreedyInput* pgin, int p, ProgressiveGreedyOutput* pgout);
#endif

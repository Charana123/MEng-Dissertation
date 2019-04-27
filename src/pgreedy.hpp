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
    vector<unsigned long>* universe;
    unsigned long n;
    unsigned long m;
};

unordered_set<unsigned long>* progressive_greedy_naive(ProgressiveGreedyInput* pgin, unsigned long p);
#endif

#ifndef PGREEDY_H
#define PGREEDY_H

#include "ssc_utils.hpp"
#include <algorithm>

using namespace std;

struct ProgressiveGreedyInput
{
    Stream& stream;
    int n;
};

struct ProgressiveGreedyOutput
{
    set<int> sol;
    set<int> covered;
};

void progressive_greedy_naive(ProgressiveGreedyInput& pgin, int p, ProgressiveGreedyOutput& pgout);
void greedy_pass(ProgressiveGreedyInput& pgin, int threshold, set<int>& sol, set<int>& covered);
#endif

#ifndef SSSC_H_
#define SSSC_H_

#include "ssc_utils.hpp"
#include <cmath>

using HyperEdge = Set;

struct SSSCInput
{
    Stream* stream;
    Set* universe;
};

set<int>* sssc(SSSCInput* eci);

class UnweightedCover {
    public:
        UnweightedCover();
        void run(HyperEdge* he);
        void get(map<int, int>* eid, vector<tuple<int, int>>* eff);
    private:
        map<int, set<int>> eid;
        vector<tuple<int, int>> eff;
};

#endif

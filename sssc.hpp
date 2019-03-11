#ifndef SSSC_H_
#define SSSC_H_

#include "ssc_utils.hpp"
#include <map>
#include <cmath>
#include <random>

using HyperEdge = Set;

struct SSSCInput
{
    Stream* stream;
    vector<int>* universe;
    int n;
    int m;
    int avg;
};

unordered_set<int>* sssc(SSSCInput* sssci);
unordered_set<int>* capture(SSSCInput* sssci);
unordered_set<int>* randomized_sssc(SSSCInput* sssci);
unordered_set<int>* threshold_randomized_sssc(SSSCInput* sssci);

class UnweightedCover {
    public:
        UnweightedCover(SSSCInput* sssci) {
            this->max_elem = *std::max_element(sssci->universe->begin(), sssci->universe->end());
            this->ceid = new vector<int>(max_elem, -1);
            this->ceff = new vector<int>(max_elem, 0);
            this->eid = new vector<int>(max_elem, -1);
            this->eff = new vector<int>(max_elem, 0);
        };
        int max_elem;
        void run(HyperEdge* he);
        void randomized_run(HyperEdge* he, float p);
        void threshold_randomized_run(HyperEdge* he, int threshold);
        void capture(HyperEdge* he);
        vector<int> *ceid, *ceff, *eid, *eff;
};

// lookup effectivity for vertices, sort, find i, transform to vertices

#endif

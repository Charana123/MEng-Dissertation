#ifndef SSSC_SIMD_H_
#define SSSC_SIMD_H_

#include "ssc_utils.hpp"
#include <map>
#include <cmath>
#include <random>
/* #include "omp.h" */

using HyperEdge = Set;

struct SSSCInput
{
    Stream* stream;
    vector<int>* universe;
    int n;
    int m;
};

set<int>* sssc(SSSCInput* sssci);

class UnweightedCover {
    public:
        UnweightedCover(SSSCInput* sssci) {
            /* this->ceid = new vector<int>(sssci->n); */
            /* this->ceff = new vector<int>(sssci->n); */
            /* this->eid = new vector<int>(sssci->n); */
            /* this->eff = new vector<int>(sssci->n); */
            for(int v : *sssci->universe){
                (*this->eff)[v] = 0;
                (*this->ceff)[v] = 0;
            }
        };
        void run(HyperEdge* he);
        void randomized_run(HyperEdge* he, float p);
        void capture(const HyperEdge* he);
        vector<int>* ceid;
        vector<int>* ceff;
        vector<int>* eid;
        vector<int>* eff;
        /* vector<int>* ceid; */
        /* vector<int>* ceff; */
        /* vector<int>* eid; */
        /* vector<int>* eff; */
};

// lookup effectivity for vertices, sort, find i, transform to vertices

#endif

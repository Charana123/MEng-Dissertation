#ifndef SSSC_H_
#define SSSC_H_

#include "ssc_utils.hpp"
#include <map>
#include <cmath>
#include <random>
#include <numeric>

using HyperEdge = Set;

struct SSSCInput
{
    Stream* stream;
    vector<unsigned long>* universe;
    unsigned long n;
    unsigned long m;
    unsigned long avg;
};

unordered_set<unsigned long>* sssc(SSSCInput* sssci);
unordered_set<unsigned long>* capture(SSSCInput* sssci);
/* unordered_set<unsigned long>* randomized_sssc(SSSCInput* sssci); */
/* unordered_set<unsigned long>* threshold_randomized_sssc(SSSCInput* sssci); */

class UnweightedCover {
    public:
        UnweightedCover(SSSCInput* sssci) {
            this->max_elem = *std::max_element(sssci->universe->begin(), sssci->universe->end());
            this->ceid = new vector<unsigned long>(max_elem, static_cast<unsigned long>(-1));
            this->ceff = new vector<unsigned long>(max_elem, 0);
            this->eid = new vector<unsigned long>(max_elem, static_cast<unsigned long>(-1));
            this->eff = new vector<unsigned long>(max_elem, 0);
            this->ben = new vector<unsigned long>(max_elem, 0);
            this->ben1 = new vector<unsigned long>(max_elem, 0);
        };
        unsigned long max_elem;
        void run(HyperEdge* he);
        void mrun(HyperEdge* he);
        void randomized_run(HyperEdge* he, float p);
        void threshold_randomized_run(HyperEdge* he, unsigned long threshold);
        void capture(HyperEdge* he);
        vector<unsigned long> *ceid, *ceff, *eid, *eff, *ben, *ben1;
};

// lookup effectivity for vertices, sort, find i, transform to vertices










#endif

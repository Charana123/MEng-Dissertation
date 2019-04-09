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

struct PSSSCInput
{
    POfflineStream** streams;
    vector<unsigned long>* universe;
    unsigned long n;
    unsigned long m;
};

unordered_set<unsigned long>* sssc(SSSCInput* sssci);
unordered_set<unsigned long>* capture(SSSCInput* sssci);
unordered_set<unsigned long>* capture(PSSSCInput* psssci, int ts);
/* unordered_set<unsigned long>* randomized_sssc(SSSCInput* sssci); */
/* unordered_set<unsigned long>* threshold_randomized_sssc(SSSCInput* sssci); */

class CaptureCover {
    public:
        CaptureCover(vector<unsigned long>* universe){
            /* cout << *universe << endl; */
            this->max_elem = *std::max_element(universe->begin(), universe->end());
            this->ceid = new vector<unsigned long>(max_elem, static_cast<unsigned long>(-1));
            this->ceff = new vector<unsigned long>(max_elem, 0);
        }
        ~CaptureCover(){
            delete ceid;
            delete ceff;
        }
        void capture(HyperEdge* he);

        unsigned long max_elem;
        vector<unsigned long> *ceid, *ceff;
};

class SSSCCover {
    public:
        SSSCCover(vector<unsigned long>* universe) {
            this->max_elem = *std::max_element(universe->begin(), universe->end());
            this->eid = new vector<unsigned long>(max_elem, static_cast<unsigned long>(-1));
            this->eff = new vector<unsigned long>(max_elem, 0);
            /* this->ben = new vector<unsigned long>(max_elem, 0); */
            /* this->ben1 = new vector<unsigned long>(max_elem, 0); */
        };
        ~SSSCCover(){
            delete eid;
            delete eff;
        }
        void run(HyperEdge* he);
        void mrun(HyperEdge* he);
        void randomized_run(HyperEdge* he, float p);
        void threshold_randomized_run(HyperEdge* he, unsigned long threshold);

        // Variables
        unsigned long max_elem;
        vector<unsigned long> *eid, *eff;
        vector<unsigned long> *ben, *ben1;
};

// Parallel UnweightedCover
class PUC {
    public:
        PUC(vector<unsigned long>* universe, int ts) {
            this->max_elem = *std::max_element(universe->begin(), universe->end());
            this->ceids = new unsigned long*[ts];
            this->ceffs = new unsigned long*[ts];
            for(int t = 0; t < ts; t++){
                this->ceffs[t] = new unsigned long[this->max_elem];
                this->ceids[t] = new unsigned long[this->max_elem];
                std::fill_n(this->ceids[t], this->max_elem, static_cast<unsigned long>(-1));
            }
            this->fceid = new unsigned long[this->max_elem];
        };
        unsigned long max_elem;
        void capture(HyperEdge* he, int t);
        unsigned long **ceids, **ceffs, *fceid;
};

// lookup effectivity for vertices, sort, find i, transform to vertices










#endif

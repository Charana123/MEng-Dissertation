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
    /* POfflineStream** streams; */
    OnlineStream** streams;
    vector<unsigned long>* universe;
    unsigned long n;
    unsigned long m;
};

unordered_set<unsigned long>* sssc(SSSCInput* sssci, string type);
unordered_set<unsigned long>* sssc(PSSSCInput* psssci, int ts);
unordered_set<unsigned long>* capture(SSSCInput* sssci);
unordered_set<unsigned long>* capture(PSSSCInput* psssci, int ts);
/* unordered_set<unsigned long>* randomized_sssc(SSSCInput* sssci); */
unordered_set<unsigned long>* threshold_randomized_sssc(SSSCInput* sssci, unsigned long largest, unsigned long avg);

class SSSCCover {
    public:
        SSSCCover(vector<unsigned long>* universe) {
            this->max_elem = *std::max_element(universe->begin(), universe->end());
            cout << "max_elem: " << max_elem << endl;
            this->eid = new vector<unsigned long>(max_elem+1, static_cast<unsigned long>(-1));
            this->eff = new vector<unsigned long>(max_elem+1, 0);
            this->ben = new vector<unsigned long>(max_elem+1, 0);
            this->ben1 = new vector<unsigned long>(max_elem+1, 0);
        };
        ~SSSCCover(){
            delete eid;
            delete eff;
            delete ben;
            delete ben1;
        }
        void run(HyperEdge* he);
        void mrun1(HyperEdge* he);
        void mrun2(HyperEdge* he);
        void mrun3(HyperEdge* he);
        /* void randomized_run(HyperEdge* he, float p); */
        void threshold_randomized_run(HyperEdge* he, unsigned long threshold);

        // Variables
        unsigned long max_elem;
        vector<unsigned long> *eid, *eff;
        vector<unsigned long> *ben, *ben1;
};

class RCover {
    public:
        RCover(vector<unsigned long>* universe) {
            this->max_elem = *std::max_element(universe->begin(), universe->end());
            this->eid = new vector<unsigned long>(max_elem+1, static_cast<unsigned long>(-1));
            this->eff = new vector<unsigned long>(max_elem+1, 0);
            this->ceid = new vector<unsigned long>(max_elem+1, static_cast<unsigned long>(-1));
            this->ceff = new vector<unsigned long>(max_elem+1, 0);
        };
        ~RCover(){
            delete eid;
            delete ceid;
            delete eff;
            delete ceff;
        }
        void threshold_randomized_run(HyperEdge* he, unsigned long threshold);
        void capture(HyperEdge* he);
        unsigned long max_elem;
        vector<unsigned long> *eid, *eff, *ceid, *ceff;
};


class PCover {
    public:
        PCover(vector<unsigned long>* universe, int ts) {
            this->max_elem = *std::max_element(universe->begin(), universe->end());
            this->eids = new vector<unsigned long>*[ts]();
            this->effs = new vector<unsigned long>*[ts]();
            for(int t = 0; t < ts; t++){
                this->effs[t] = new vector<unsigned long>(this->max_elem + 1, 0);
                this->eids[t] = new vector<unsigned long>(this->max_elem + 1, static_cast<unsigned long>(-1));
            }
        };
        unsigned long max_elem;
        void run(HyperEdge* he, int t);
        vector<unsigned long> **eids, **effs;
};

class CaptureCover {
    public:
        CaptureCover(vector<unsigned long>* universe){
            /* cout << *universe << endl; */
            this->max_elem = *std::max_element(universe->begin(), universe->end());
            this->ceid = new vector<unsigned long>(max_elem+1, static_cast<unsigned long>(-1));
            this->ceff = new vector<unsigned long>(max_elem+1, 0);
        }
        ~CaptureCover(){
            delete ceid;
            delete ceff;
        }
        void capture(HyperEdge* he);

        unsigned long max_elem;
        vector<unsigned long> *ceid, *ceff;
};

// Parallel UnweightedCover
class PCaptureCover {
    public:
        PCaptureCover(vector<unsigned long>* universe, int ts) {
            this->max_elem = *std::max_element(universe->begin(), universe->end());
            this->ceids = new unsigned long*[ts]();
            this->ceffs = new unsigned long*[ts]();
            for(int t = 0; t < ts; t++){
                this->ceffs[t] = new unsigned long[this->max_elem+1];
                this->ceids[t] = new unsigned long[this->max_elem+1];
                std::fill_n(this->ceids[t], this->max_elem+1, static_cast<unsigned long>(-1));
            }
            this->fceid = new unsigned long[this->max_elem+1];
            std::fill_n(this->fceid, this->max_elem+1, static_cast<unsigned long>(-1));
        };
        unsigned long max_elem;
        void capture(HyperEdge* he, int t);
        unsigned long **ceids, **ceffs, *fceid;
};

// lookup effectivity for vertices, sort, find i, transform to vertices










#endif

#ifndef SSSC_H_
#define SSSC_H_

#include "ssc_utils.hpp"
#include <map>
#include <cmath>

using HyperEdge = Set;

struct SSSCInput
{
    Stream* stream;
    set<int>* universe;
};

map<int,int>* sssc(SSSCInput* sssci);

class UnweightedCover {
    public:
        UnweightedCover(SSSCInput* sssci) {
            for(int v : *sssci->universe){
                (*eff)[v] = 0;
            }
        };
        void run(HyperEdge* he);
        map<int,int>* eid = new map<int,int>();
        map<int,int>* eff = new map<int,int>();
};

// lookup effectivity for vertices, sort, find i, transform to vertices

#endif

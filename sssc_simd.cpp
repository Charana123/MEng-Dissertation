#include "sssc_simd.hpp"
using namespace std;

void UnweightedCover::capture(const HyperEdge* he){
    int eff = he->vertices.size();
    for(int i = 0; i < eff; i++){
        int v = he->vertices[i];
        if(eff > (*ceff)[v]){
            (*ceid)[v] = he->i;
            (*ceff)[v] = eff;
        }
    }
}

set<int>* sssc(SSSCInput* sssci){

    UnweightedCover cover(sssci);
    for(const HyperEdge* he; (he = sssci->stream->get_next_set()) != nullptr; ){
        cover.capture(he);
    }
    set<int>* sol = new set<int>();
    sol->insert(cover.ceid->begin(), cover.ceid->end());

    return sol;
}













#include "sssc.hpp"
using namespace std;

//take it as a set, take the set, update the count, check <= root n
//for taken sets, append to collection, find difference with universe, collect
void UnweightedCover::run(HyperEdge* he){
    vector<int> s;
    s.insert(s.begin(), he->vertices.begin(), he->vertices.end());
    map<int,int>* eff = this->eff;
    sort(s.begin(), s.end(), [&eff](int v1, int v2) -> bool{
        return (*eff)[v1] < (*eff)[v2];
    });
    int i = s.size() - 1;
    for(; i >= 0 && (i + 1) < 2*(*eff)[s[i]]; i--) {}

    for(int j = 0; j <= i; j++){
        int v = s[j];
        this->eid->at(v) = he->i;
        this->eff->at(v) = i + 1;
    }
}

map<int,int>* sssc(SSSCInput* sssci){

    UnweightedCover cover(sssci);
    for(HyperEdge* he; (he = sssci->stream->get_next_set()) != nullptr; ){
        cover.run(he);
    }
    sssci->stream->reset();

    map<int,int>* eid  = cover.eid;
    map<int,int>* eff = cover.eff;

    /* vector<int> universe; */
    /* universe.insert(universe.begin(), sssci->universe->vertices.begin(), sssci->universe->vertices.end()); */
    /* sort(sssci->universe->vertices.begin(), sssci->universe->vertices.end(), [&eff](int v1, int v2) -> bool{ return eff[v1] < eff[v2]; }); */
    /* int root_n = sqrt(sssci->universe->vertices.size()); */
    /* if(eff[root_n] == eff[root_n+1]){ */
    /*     while(eff[root_n - 1] == eff[root_n]) root_n--; */
    /*     root_n--; */
    /* } */
    /* for(int i = 0; i < root_n; i++) eid->erase(universe[i]); */
    return eid;
}













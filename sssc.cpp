#include "sssc.hpp"

void UnweightedCover::get(map<int, int>* eid, vector<tuple<int, int>>* eff){
    /* *eid = this->eid; */
    *eff = this->eff;
}

//take it as a set, take the set, update the count, check <= root n
//for taken sets, append to collection, find difference with universe, collect
void UnweightedCover::run(HyperEdge* he){
    int lev_t = ceil(log2f(he->vertices.size()));
    for(int v : he->vertices){
        /* this->eid[v] = he->i; */
        this->eff.push_back({v, lev_t});
    }
}

set<int>* sssc(SSSCInput* sssci){

    UnweightedCover cover;
    for(HyperEdge* he; (he = sssci->stream->get_next_set()) != nullptr; ){
        cover.run(he);
    }
    map<int, int> *eid = new map<int, int>();
    vector<tuple<int, int>> *eff = new vector<tuple<int, int>>();
    cover.get(eid, eff);
    sort(eff->begin(), eff->begin(), [](auto t1, auto t2) -> bool{
        return get<1>(t1) > get<1>(t2);
    });
    for(auto& t : *eff){

    }
    return nullptr;
}













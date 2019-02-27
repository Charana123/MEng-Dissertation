#include "sssc.hpp"
using namespace std;

void UnweightedCover::randomized_run(HyperEdge* he, float p){

    int set_size = he->vertices.size();
    int sample_size = set_size * p;
    if(sample_size == 0) sample_size = set_size;
    int samples = set_size / sample_size;

    vector<int> he_sample;
    sample(he->vertices.begin(), he->vertices.end(),
            std::inserter(he_sample, he_sample.begin()), sample_size,
            std::mt19937{std::random_device{}()});
    map<int,int>* eff = this->eff;
    sort(he_sample.begin(), he_sample.end(), [&eff](int v1, int v2) -> bool{
        return (*eff)[v1] < (*eff)[v2];
    });
    int i = sample_size - 1;
    for(; i >= 0 && (i*samples + 1) < 2*(*eff)[he_sample[i]]; i--) {}
    if(i == -1) return;
    int threshold_effectivity = (*eff)[he_sample[i]];
    set<int> T;
    for(int v : he->vertices) if((*eff)[v] <= threshold_effectivity) T.insert(v);
    int eff_t = T.size();

    for(int v : T){
        (*this->eid)[v] = he->i;
        (*this->eff)[v] = eff_t;
    }
}

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
        (*this->eid)[v] = he->i;
        (*this->eff)[v] = i + 1;
    }
}

void UnweightedCover::capture(HyperEdge* he){
    int eff = he->vertices.size();
    for(int v : he->vertices){
        if(eff > (*this->ceff)[v]){
            (*this->ceid)[v] = he->i;
            (*this->ceff)[v] = eff;
        }
    }
}

map<int,int>* sssc(SSSCInput* sssci){

    UnweightedCover cover(sssci);
    for(HyperEdge* he; (he = sssci->stream->get_next_set()) != nullptr; ){
        /* cover.run(he); */
        /* cover.randomized_run(he, 0.1); */
        cover.capture(he);
    }
    sssci->stream->reset();

    /* map<int,int>* feid = new map<int, int>(); */
    /* for(auto& e : *cover.eff){ */
    /*     if(e.second == 0) (*feid)[e.first] = (*cover.ceid)[e.first]; */
    /*     else (*feid)[e.first] = (*cover.eid)[e.first]; */
    /* } */

    /* vector<int> universe; */
    /* universe.insert(universe.begin(), sssci->universe->vertices.begin(), sssci->universe->vertices.end()); */
    /* sort(sssci->universe->vertices.begin(), sssci->universe->vertices.end(), [&eff](int v1, int v2) -> bool{ return eff[v1] < eff[v2]; }); */
    /* int root_n = sqrt(sssci->universe->vertices.size()); */
    /* if(eff[root_n] == eff[root_n+1]){ */
    /*     while(eff[root_n - 1] == eff[root_n]) root_n--; */
    /*     root_n--; */
    /* } */
    /* for(int i = 0; i < root_n; i++) eid->erase(universe[i]); */
    return cover.ceid;
}













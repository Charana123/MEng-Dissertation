#include "sssc.hpp"
using namespace std;

void UnweightedCover::randomized_run(HyperEdge* he, float p){

    int set_size = he->vertices.size();
    int sample_size = set_size * p;
    if(sample_size == 0) sample_size = set_size;
    int samples = set_size / sample_size;

    vector<int> he_sample(he->vertices.begin(), he->vertices.begin() + sample_size);
    /* vector<int> he_sample; */
    /* sample(he->vertices.begin(), he->vertices.end(), */
    /*         std::inserter(he_sample, he_sample.begin()), sample_size, */
    /*         std::mt19937{std::random_device{}()}); */
    vector<int>* eff = this->eff;
    sort(he_sample.begin(), he_sample.end(), [&eff](int v1, int v2) -> bool{
        return (*eff)[v1] < (*eff)[v2];
    });
    int i = sample_size - 1;
    for(; i >= 0 && (i*samples + 1) < 2*(*eff)[he_sample[i]]; i--) {}
    if(i == -1) return;
    int threshold_effectivity = (*eff)[he_sample[i]];
    vector<int> T;
    for(int v : he->vertices) if((*eff)[v] <= threshold_effectivity) T.push_back(v);
    int eff_t = T.size();

    for(int v : T){
        (*this->eid)[v] = he->i;
        (*this->eff)[v] = eff_t;
    }
}

void UnweightedCover::threshold_randomized_run(HyperEdge* he, int threshold){

    int set_size = he->vertices.size();
    int sample_size = threshold < set_size && threshold > 0 ? threshold : set_size;
    int samples = set_size / sample_size;

    vector<int> he_sample(he->vertices.begin(), he->vertices.begin() + sample_size);
    /* vector<int> he_sample; */
    /* sample(he->vertices.begin(), he->vertices.end(), */
    /*         std::inserter(he_sample, he_sample.begin()), threshold, */
    /*         std::mt19937{std::random_device{}()}); */
    vector<int>* eff = this->eff;
    sort(he_sample.begin(), he_sample.end(), [&eff](int v1, int v2) -> bool{
        return (*eff)[v1] < (*eff)[v2];
    });
    int i = sample_size - 1;
    for(; i >= 0 && (i*samples + 1) < 2*(*eff)[he_sample[i]]; i--) {}
    if(i == -1) return;
    int threshold_effectivity = (*eff)[he_sample[i]];
    vector<int> T;
    for(int v : he->vertices) if((*eff)[v] <= threshold_effectivity) T.push_back(v);
    int eff_t = T.size();

    for(int v : T){
        (*this->eid)[v] = he->i;
        (*this->eff)[v] = eff_t;
    }
}

void UnweightedCover::run(HyperEdge* he){

    vector<int>* eff = this->eff;
    sort(he->vertices.begin(), he->vertices.end(), [&eff](int v1, int v2) -> bool{
        return (*eff)[v1] < (*eff)[v2];
    });
    int i = he->vertices.size() - 1;
    for(; i >= 0 && (i + 1) < 2*(*eff)[he->vertices[i]]; i--) {}

    for(int j = 0; j <= i; j++){
        int v = he->vertices[j];
        (*this->eid)[v] = he->i;
        (*this->eff)[v] = i + 1;
        (*this->ceff)[v] = he->vertices.size();
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

set<int>* sssc(SSSCInput* sssci, float p){

    UnweightedCover cover(sssci);
    for(HyperEdge* he; (he = sssci->stream->get_next_set()) != nullptr; ){
        cover.run(he);
        /* cover.randomized_run(he, p); */
        /* cover.threshold_randomized_run(he, p * sssci->avg); */
        /* cover.capture(he); */
    }
    sssci->stream->reset();

    /* for(int i : *sssci->universe){ */
    /*     if((*cover.eid)[i] == -1 && (*cover.ceid)[i] != -1) { */
    /*         (*cover.eid)[i] = (*cover.ceid)[i]; */
    /*     } */
    /* } */

    set<int>* sol = new set<int>();
    for(int v : *cover.eid) if(v != -1) sol->insert(v);
    return sol;
}









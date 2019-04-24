#include "sssc.hpp"
#include "omp.h"
using namespace std;

/* void UnweightedCover::randomized_run(HyperEdge* he, float p){ */

/*     unsigned long set_size = he->vertices.size(); */
/*     unsigned long sample_size = set_size * p; */
/*     if(sample_size == 0) sample_size = set_size; */
/*     unsigned long samples = set_size / sample_size; */

/*     vector<unsigned long> he_sample(he->vertices.begin(), he->vertices.begin() + sample_size); */
/*     /1* vector<unsigned long> he_sample; *1/ */
/*     /1* sample(he->vertices.begin(), he->vertices.end(), *1/ */
/*     /1*         std::inserter(he_sample, he_sample.begin()), sample_size, *1/ */
/*     /1*         std::mt19937{std::random_device{}()}); *1/ */
/*     vector<unsigned long>* eff = this->eff; */
/*     sort(he_sample.begin(), he_sample.end(), [&eff](unsigned long v1, unsigned long v2) -> bool{ */
/*         return (*eff)[v1] < (*eff)[v2]; */
/*     }); */
/*     unsigned long i = sample_size - 1; */
/*     for(; i >= 0 && (i*samples + 1) < 2*(*eff)[he_sample[i]]; i--) {} */
/*     if(i == -1) return; */
/*     unsigned long threshold_effectivity = (*eff)[he_sample[i]]; */
/*     vector<unsigned long> T; */
/*     for(unsigned long v : he->vertices) if((*eff)[v] <= threshold_effectivity) T.push_back(v); */
/*     unsigned long eff_t = T.size(); */

/*     for(unsigned long v : T){ */
/*         (*this->eid)[v] = he->i; */
/*         (*this->eff)[v] = eff_t; */
/*     } */
/* } */

void SSSCCover::mrun1(HyperEdge* he){

    vector<unsigned long>* eff = this->eff;
    sort(he->vertices.begin(), he->vertices.end(), [&eff](unsigned long v1, unsigned long v2) -> bool{
        return (*eff)[v1] < (*eff)[v2];
    });
    unsigned long i = he->vertices.size() - 1;
    unsigned long benefit;
    for(; i != static_cast<unsigned long>(-1); i--) {
        if((i+1) > (*eff)[he->vertices[i]]) {
            benefit = he->vertices.size() - i - 1;
            break;
		}
        else if((i+1) == (*eff)[he->vertices[i]]){
            benefit = he->vertices.size() - i - 1;
            if(benefit > (*this->ben)[he->vertices[i]]) break;
        }
    }

    if(i ==  static_cast<unsigned long>(-1)) return;
    for(unsigned long j = 0; j <= i; j++){
        unsigned long v = he->vertices[j];
        (*this->eid)[v] = he->i;
        (*this->eff)[v] = i + 1;
        (*this->ben)[v] = benefit;
    }
}

void SSSCCover::mrun2(HyperEdge* he){

    vector<unsigned long>* eff = this->eff;
    sort(he->vertices.begin(), he->vertices.end(), [&eff](unsigned long v1, unsigned long v2) -> bool{
        return (*eff)[v1] < (*eff)[v2];
    });
    unsigned long i = he->vertices.size() - 1;
    unsigned long benefit; double benefit1;
    for(; i != static_cast<unsigned long>(-1); i--) {
        if((i+1) > (*eff)[he->vertices[i]]) {
            //cout << "i: " << i << endl;
            //for(auto itr=he->vertices.begin()+i+1; itr<he->vertices.end(); itr++) cout << *itr << " ";
            //cout << endl;
            for(auto itr = he->vertices.begin() + i + 1; itr < he->vertices.end(); itr++) cout << *itr << endl;
            benefit1  = std::accumulate(he->vertices.begin() + i + 1, he->vertices.end(), 0.0,
                [&eff](float acc, unsigned long v) -> float {
                    //cout << "acc: " << (float)acc << endl;
                    //cout << "v: " << v << endl;
                    return acc + (float)1/(*eff)[v];
                }
            );
            cout << "benefit1: " << benefit1 << endl;
            benefit = he->vertices.size() - i - 1;
            break;
		}
        else if((i+1) == (*eff)[he->vertices[i]]){
            benefit1  = std::accumulate(he->vertices.begin() + i + 1, he->vertices.end(), 0.0,
                [&eff](float acc, unsigned long v) -> float {
                    return acc + (float)1/(*eff)[v];
                }
            );
            benefit = he->vertices.size() - i - 1;
            if(benefit > (*this->ben)[he->vertices[i]]) break;
            if(benefit == (*this->ben)[he->vertices[i]] && benefit1 > (*this->ben1)[he->vertices[i]]) break;
        }
    }

    if(i ==  static_cast<unsigned long>(-1)) return;
    for(unsigned long j = 0; j <= i; j++){
        unsigned long v = he->vertices[j];
        (*this->eid)[v] = he->i;
        (*this->eff)[v] = i + 1;
        (*this->ben)[v] = benefit;
        (*this->ben1)[v] = benefit1;
    }
}

void SSSCCover::run(HyperEdge* he){
    vector<unsigned long>* eff = this->eff;
    sort(he->vertices.begin(), he->vertices.end(), [&eff](unsigned long v1, unsigned long v2) -> bool{
        return (*eff)[v1] < (*eff)[v2];
    });
    unsigned long i = he->vertices.size() - 1;
    /* for(; i != static_cast<unsigned long>(-1) && (i + 1) < 2*(*eff)[he->vertices[i]]; i--) {} */
    for(; i != static_cast<unsigned long>(-1) && (i + 1) <= (*eff)[he->vertices[i]]; i--) {}

    if(i ==  static_cast<unsigned long>(-1)) return;
    for(unsigned long j = 0; j <= i; j++){
        unsigned long v = he->vertices[j];
        (*this->eid)[v] = he->i;
        (*this->eff)[v] = i + 1;
    }
}

unordered_set<unsigned long>* sssc(SSSCInput* sssci, string type){

    SSSCCover cover(sssci->universe);
    if(type.compare("run") == 0){
        for(HyperEdge* he; (he = sssci->stream->get_next_set()) != nullptr; ){
            cover.run(he);
        }
    }
    else if(type.compare("mrun1") == 0){
        for(HyperEdge* he; (he = sssci->stream->get_next_set()) != nullptr; ){
            cover.mrun1(he);
        }
    }
    else if(type.compare("mrun2") == 0){
        for(HyperEdge* he; (he = sssci->stream->get_next_set()) != nullptr; ){
            cover.mrun2(he);
        }
    }
    sssci->stream->reset();

    unordered_set<unsigned long>* sol = new unordered_set<unsigned long>();
    for(unsigned long v : *cover.eid) if(v != static_cast<unsigned long>(-1)) sol->insert(v);
    return sol;
}


void PCover::run(HyperEdge* he, int t){
    vector<unsigned long>** effs = this->effs;
    sort(he->vertices.begin(), he->vertices.end(), [&effs, &t](unsigned long v1, unsigned long v2) -> bool{
        return (*effs[t])[v1] < (*effs[t])[v2];
    });
    unsigned long i = he->vertices.size() - 1;
    for(; i != static_cast<unsigned long>(-1) && (i + 1) < 2*(*effs[t])[he->vertices[i]]; i--) {}

    if(i ==  static_cast<unsigned long>(-1)) return;
    for(unsigned long j = 0; j <= i; j++){
        unsigned long v = he->vertices[j];
        (*this->eids[t])[v] = he->i;
        (*this->effs[t])[v] = i + 1;
    }
}


unordered_set<unsigned long>* sssc(PSSSCInput* psssci, int ts){

    PCover cover(psssci->universe, ts);
    #pragma omp parallel for
    for(int t = 0; t < ts; t++){
        for(HyperEdge* he; (he = psssci->streams[t]->get_next_set())!= nullptr; ){
            cover.run(he, t);
        }
        psssci->streams[t]->reset();
    }

    for(int t = 1; t < ts; t++){
        vector<unsigned long> sv;
        for(int v = 0; v < cover.max_elem + 1; v++) sv.push_back(v);
        sort(sv.begin(), sv.end(), [&](unsigned long v1, unsigned long v2) -> bool {
            return (*cover.eids[t])[v1] < (*cover.eids[t])[v2];
        });

        unsigned long i = 0;
        while(i < sv.size()){
            vector<unsigned long> s;
            unsigned long eff, id;
            s.push_back(sv[i]);
            eff = (*cover.effs[t])[sv[i]]; id = (*cover.eids[t])[sv[i]];
            if(id == static_cast<unsigned long>(-1)) break;
            for(i++; (*cover.eids[t])[sv[i]] == id && i < sv.size(); i++) s.push_back(sv[i]);
            vector<bool> s_removed(s.size(), false);
            unsigned long eff_after = eff;
            while(eff_after != eff){
                eff = eff_after;
                for(unsigned long j = 0; j < s.size(); j++) {
                    if(s_removed[j] != true){
                        if(eff_after < (*cover.effs[0])[s[j]]){
                            eff_after--;
                            s_removed[j] = true;
                        }
                    }
                }
            }
            for(unsigned long j = 0; j < s.size(); j++){
                if(s_removed[j] != true) {
                    (*cover.eids[0])[s[j]] = (*cover.eids[t])[s[j]];
                    (*cover.effs[0])[s[j]] = eff_after;
                }
            }
        }
    }

    unordered_set<unsigned long>* sol = new unordered_set<unsigned long>();
    for(unsigned long i = 0; i < cover.max_elem + 1; i++){
        if((*cover.eids[0])[i] != static_cast<unsigned long>(-1)){
            sol->insert((*cover.eids[0])[i]);
        }
    }
    return sol;
}

void CaptureCover::capture(HyperEdge* he){
    unsigned long eff = he->vertices.size();
    for(unsigned long v : he->vertices){
        if(eff > (*this->ceff)[v]){
            (*this->ceid)[v] = he->i;
            (*this->ceff)[v] = eff;
        }
    }
}

unordered_set<unsigned long>* capture(SSSCInput* sssci){

    CaptureCover cover(sssci->universe);
    for(HyperEdge* he; (he = sssci->stream->get_next_set()) != nullptr; ){
        cover.capture(he);
    }
    sssci->stream->reset();

    unordered_set<unsigned long>* sol = new unordered_set<unsigned long>();
    for(unsigned long v : *cover.ceid) if(v != static_cast<unsigned long>(-1)) sol->insert(v);
    return sol;
}

void PCaptureCover::capture(HyperEdge* he, int t){
    unsigned long eff = he->vertices.size();
    for(unsigned long v : he->vertices){
        if(eff > this->ceffs[t][v]){
            this->ceids[t][v] = he->i;
            this->ceffs[t][v] = eff;
        }
    }
}

unordered_set<unsigned long>* capture(PSSSCInput* psssci, int ts){

    PCaptureCover pcc(psssci->universe, ts);
    /* cout << "here2" << endl; */
    #pragma omp parallel for
    for(int t = 0; t < ts; t++){
        for(HyperEdge* he; (he = psssci->streams[t]->get_next_set())!= nullptr; ){
            pcc.capture(he, t);
        }
        psssci->streams[t]->reset();
    }
    #pragma omp parallel for
    for(int t = 0; t < ts; t++){
        for(unsigned long i = (pcc.max_elem/ts) * t; i < (pcc.max_elem/ts) * (t+1); i++){
            unsigned long max_ceff = 0; unsigned long max_ceid;
            for(int t = 0; t < ts; t++){
                if(pcc.ceffs[t][i] > max_ceff) {
                    max_ceff = pcc.ceffs[t][i];
                    max_ceid = pcc.ceids[t][i];
                }
            }
            pcc.fceid[i] = max_ceid;
        }
    }

    unordered_set<unsigned long>* sol = new unordered_set<unsigned long>();
    for(unsigned long i = 0; i < pcc.max_elem; i++){
        if(pcc.fceid[i] != static_cast<unsigned long>(-1)){
            sol->insert(pcc.fceid[i]);
        }
    }
    return sol;
}

/* unordered_set<int>* randomized_sssc(SSSCInput* sssci){ */

/*     UnweightedCover cover(sssci); */
/*     float p = 0.25; */
/*     for(HyperEdge* he; (he = sssci->stream->get_next_set()) != nullptr; ){ */
/*         cover.randomized_run(he, p); */
/*         cover.capture(he); */
/*     } */
/*     sssci->stream->reset(); */

/*     for(int i : *sssci->universe){ */
/*         if((*cover.eid)[i] == -1 && (*cover.ceid)[i] != -1) { */
/*             (*cover.eid)[i] = (*cover.ceid)[i]; */
/*         } */
/*     } */

/*     unordered_set<int>* sol = new unordered_set<int>(); */
/*     for(int v : *cover.eid) if(v != -1) sol->insert(v); */
/*     return sol; */
/* } */

void RCover::capture(HyperEdge* he){
    unsigned long eff = he->vertices.size();
    for(unsigned long v : he->vertices){
        if(eff > (*this->ceff)[v]){
            (*this->ceid)[v] = he->i;
            (*this->ceff)[v] = eff;
        }
    }
}

void RCover::threshold_randomized_run(HyperEdge* he, unsigned long threshold){

    unsigned long sample_size = threshold < he->vertices.size() && threshold > 0 ? threshold : he->vertices.size();
    float fraction = he->vertices.size() / sample_size;

    /* vector<unsigned long> he_sample(he->vertices.begin(), he->vertices.begin() + sample_size); */
    // Stage 1
    vector<unsigned long>* he_sample;
    if(sample_size < he->vertices.size()){
        he_sample = new vector<unsigned long>();
        sample(he->vertices.begin(), he->vertices.end(),
            std::inserter(*he_sample, he_sample->begin()), threshold,
            std::mt19937{std::random_device{}()});
    }
    else {
        he_sample = &he->vertices;
    }

    // Stage 2
    vector<unsigned long>* eff = this->eff;
    sort(he_sample->begin(), he_sample->end(), [&eff](unsigned long v1, unsigned long v2) -> bool{
        return (*eff)[v1] < (*eff)[v2];
    });
    unsigned long i = sample_size - 1;
    for(; i != static_cast<unsigned long>(-1) && (i*fraction + 1) <= (*eff)[(*he_sample)[i]]; i--) {}

    // Stage 3
    if(i == static_cast<unsigned long>(-1)) return;
    if(threshold < he->vertices.size()){
        unsigned long threshold_effectivity = (*eff)[(*he_sample)[i]];
        vector<unsigned long> T;
        for(unsigned long v : he->vertices) if((*eff)[v] <= threshold_effectivity) T.push_back(v);
        unsigned long eff_t = T.size();
        for(unsigned long v : T){
            (*this->eid)[v] = he->i;
            (*this->eff)[v] = eff_t;
        }
    }
    else {
        for(unsigned long j = 0; j <= i; j++){
            unsigned long v = he->vertices[j];
            (*this->eid)[v] = he->i;
            (*this->eff)[v] = i + 1;
        }
    }
}

unordered_set<unsigned long>* threshold_randomized_sssc(SSSCInput* sssci, unsigned long largest){

    RCover cover(sssci->universe);
    unsigned long threshold = 0.25 * largest;
    cout << "threshold: " << threshold << endl;
    for(HyperEdge* he; (he = sssci->stream->get_next_set()) != nullptr; ){
        cover.threshold_randomized_run(he, threshold);
        cover.capture(he);
    }
    sssci->stream->reset();

    for(unsigned long v : *sssci->universe){
        if((*cover.eid)[v] == static_cast<unsigned long>(-1) && (*cover.ceid)[v] != static_cast<unsigned long>(-1)) {
            (*cover.eid)[v] = (*cover.ceid)[v];
        }
    }

    unordered_set<unsigned long>* sol = new unordered_set<unsigned long>();
    for(unsigned long v : *cover.eid) if(v != static_cast<unsigned long>(-1)) sol->insert(v);
    return sol;
}







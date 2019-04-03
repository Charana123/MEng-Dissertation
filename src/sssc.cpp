#include "sssc.hpp"
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

/* void UnweightedCover::threshold_randomized_run(HyperEdge* he, unsigned long threshold){ */

/*     unsigned long set_size = he->vertices.size(); */
/*     unsigned long sample_size = threshold < set_size && threshold > 0 ? threshold : set_size; */
/*     unsigned long samples = set_size / sample_size; */

/*     vector<unsigned long> he_sample(he->vertices.begin(), he->vertices.begin() + sample_size); */
/*     /1* vector<unsigned long> he_sample; *1/ */
/*     /1* sample(he->vertices.begin(), he->vertices.end(), *1/ */
/*     /1*         std::inserter(he_sample, he_sample.begin()), threshold, *1/ */
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

void UnweightedCover::mrun(HyperEdge* he){

    vector<unsigned long>* eff = this->eff;
    sort(he->vertices.begin(), he->vertices.end(), [&eff](unsigned long v1, unsigned long v2) -> bool{
        return (*eff)[v1] < (*eff)[v2];
    });
    unsigned long i = he->vertices.size() - 1;
    unsigned long benefit;
    double benefit1;
    float prob = 1;
    for(; i >= 0; i--) {
        /* if((i+1) > (*eff)[he->vertices[i]]) break; */
        if((i+1) > (*eff)[he->vertices[i]]) {
            /* benefit1  = std::reduce(he->vertices.begin() + i, he->vertices.end(), 0.0, */
            /*     [&eff](unsigned long v1, unsigned long v2) -> float { */
            /*         return (1/(*eff)[v1] + 1/(*eff)[v2]); */
            /*     } */
            /* ); */
            /* benefit = benefit1/(he->vertices.size() - i) * prob + he->vertices.size() - i; */
            benefit = he->vertices.size() - i;
            break;
		}
        else if((i+1) == (*eff)[he->vertices[i]]){
            /* benefit1  = std::reduce(he->vertices.begin() + i, he->vertices.end(), 0.0, */
                /* [&eff](unsigned long v1, unsigned long v2) -> float { */
                /*     return (1/(*eff)[v1] + 1/(*eff)[v2]); */
                /* } */
            /* ); */
            /* benefit = benefit1/(he->vertices.size() - i) * prob + he->vertices.size() - i; */
            benefit = he->vertices.size() - i;
            // compare the additional benefit of the current set to the previous effective set
            // if the subset cover is of the same size.
            if(benefit > (*this->ben)[he->vertices[i]] || (benefit == (*this->ben)[he->vertices[i]] && benefit1 > (*this->ben1)[he->vertices[i]])){
                break;
            }
        }
    }

    for(unsigned long j = 0; j <= i; j++){
        unsigned long v = he->vertices[j];
        (*this->eid)[v] = he->i;
        (*this->eff)[v] = i + 1;
        (*this->ben)[v] = benefit;
        /* (*this->ben1)[v] = benefit1; */
    }
}

void UnweightedCover::run(HyperEdge* he){
    /* cout << "started" << endl; */
    vector<unsigned long>* eff = this->eff;
    sort(he->vertices.begin(), he->vertices.end(), [&eff](unsigned long v1, unsigned long v2) -> bool{
        return (*eff)[v1] < (*eff)[v2];
    });
    /* cout << "here" << endl; */
    unsigned long i = he->vertices.size() - 1;
    for(; i != static_cast<unsigned long>(-1) && (i + 1) < 2*(*eff)[he->vertices[i]]; i--) {}
    /* cout << "here1" << endl; */

    if(i ==  static_cast<unsigned long>(-1)) return;
    for(unsigned long j = 0; j <= i; j++){
        unsigned long v = he->vertices[j];
        (*this->eid)[v] = he->i;
        (*this->eff)[v] = i + 1;
    }
    /* cout << "ended" << endl; */
}

void UnweightedCover::capture(HyperEdge* he){
    unsigned long eff = he->vertices.size();
    for(unsigned long v : he->vertices){
        if(eff > (*this->ceff)[v]){
            (*this->ceid)[v] = he->i;
            (*this->ceff)[v] = eff;
        }
    }
}

unordered_set<unsigned long>* capture(SSSCInput* sssci){

    UnweightedCover cover(sssci);
    for(HyperEdge* he; (he = sssci->stream->get_next_set()) != nullptr; ){
        cover.capture(he);
    }
    sssci->stream->reset();

    unordered_set<unsigned long>* sol = new unordered_set<unsigned long>();
    for(unsigned long v : *cover.ceid) if(v != static_cast<unsigned long>(-1)) sol->insert(v);
    return sol;
}

unordered_set<unsigned long>* sssc(SSSCInput* sssci){

    UnweightedCover cover(sssci);
    for(HyperEdge* he; (he = sssci->stream->get_next_set()) != nullptr; ){
        cover.run(he);
    }
    /* cout << "after" << endl; */
    sssci->stream->reset();

    unordered_set<unsigned long>* sol = new unordered_set<unsigned long>();
    for(unsigned long v : *cover.eid) if(v != static_cast<unsigned long>(-1)) sol->insert(v);
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


/* unordered_set<int>* threshold_randomized_sssc(SSSCInput* sssci){ */

/*     UnweightedCover cover(sssci); */
/*     for(HyperEdge* he; (he = sssci->stream->get_next_set()) != nullptr; ){ */
/*         cover.threshold_randomized_run(he, 0.25 * sssci->avg); */
/*         cover.capture(he); */
/*     } */
/*     sssci->stream->reset(); */

/*     for(int i : *sssci->universe){ */
/*         if((*cover.eid)[i] == -1 && (*cover.ceid)[i] != -1) { */
/*             (*cover.eid)[i] = (*cover.ceid)[i]; */
/*         } */
/*     } */

/*     unordered_set<int>* sol = new unordered_set<int>(); */
/*     for(unsigned long v : *cover.eid) if(v != -1) sol->insert(v); */
/*     return sol; */
/* } */







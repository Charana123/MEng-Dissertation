#include "assadiMP.hpp"
using namespace std;

#include "DFG.hpp"
set<int>* offline(SetCoverInput* sci, int p){
    map<int, vector<Set>>* ktoCollection = OrderBySubCollection(sci, p);
    SetCoverOutput* sco = DFG(ktoCollection, p);
    return sco->Sigma;
}

set<int>* Algorithm1(AssadiMP* assadiMP, int opt_tilda){

    int threshold = assadiMP->n/(assadiMP->epsilon * opt_tilda);

    set<int>* universe = new set<int>();
    universe->insert(assadiMP->universe->begin(), assadiMP->universe->end());
    set<int>* sol = new set<int>();

    //Threshold set sampling
    for(Set* s; (s = assadiMP->stream->get_next_set()) != nullptr; ){
        if(s->vertices.size() > threshold){
            sol->insert(s->i);
            for(int v : s->vertices) universe->erase(v);
        }
    }

    float p = 16 * opt_tilda * log(assadiMP->m) / pow(assadiMP->n, 1 - assadiMP->alpha);
    int sample_size = p * assadiMP->n;
    //Iterative element sampling
    set<int>* U_smpl = new set<int>();
    for(int j = 1; j <= assadiMP->alpha; j++){

        U_smpl->clear();
        sample(universe->begin(), universe->end(),
                std::inserter(*U_smpl, U_smpl->begin()), sample_size,
                std::mt19937{std::random_device{}()});
        map<int, bool> sampled;
        for(int v : *U_smpl) sampled[v] = true;
        for(Set* s; (s = assadiMP->stream->get_next_set()) != nullptr; ){
            Set* projected_set = new Set{{}, s->i};
            for(int v : s->vertices) if(sampled[v]) projected_set->vertices.insert(v);
        }
        /* offline */

        map<int, Set>* sets = new map<int, Set>();


        /* SetCoverInput* sci = */
        /* offline( */

    }

    return sol;
}

int assadiMP(AssadiMP* assadiMP){

    int guesses = log2f(n)/assadiMP->epsilon;
    for(int i = 0; i < guesses; i++){
        int opt_tilda = powf(2, i)/(assadiMP->epsilon) * i;
        Algorithm1(assadiMP, opt_tilda);
    }
}








#include "assadiMP.hpp"
using namespace std;

/* #include "DFG.hpp" */
/* set<int>* offline(SetCoverInput* sci, double p){ */
/*     map<int, vector<Set*>>* ktoCollection = OrderBySubCollection(sci, p); */
/*     SetCoverOutput* sco = DFG(ktoCollection, p); */
/*     return sco->Sigma; */
/* } */

#include "greedy.hpp"
set<int>* offline(SetCoverInput* sci){
    SetCoverOutput* sco = greedy(sci);
    return sco->Sigma;
}

set<int>* Algorithm1(AssadiMPInput* assadiMPInput, int opt_tilda){
    /* cout << "opt_tilda: " << opt_tilda << endl; */
    /* cout << "epsilon * opt_tilda: " << assadiMPInput->epsilon * opt_tilda << endl; */
    unsigned long threshold = assadiMPInput->n/(assadiMPInput->epsilon * opt_tilda);
    /* cout << "threshold: " << threshold << endl; */

    set<int>* universe = new set<int>();
    universe->insert(assadiMPInput->universe->begin(), assadiMPInput->universe->end());
    set<int>* sol = new set<int>();

    //Threshold set sampling
    for(Set* s; (s = assadiMPInput->stream->get_next_set()) != nullptr; ){
        if(s->vertices.size() >= threshold){
            sol->insert(s->i);
            for(int v : s->vertices) universe->erase(v);
        }
    }
    assadiMPInput->stream->reset();
    cout << *sol << endl;

    /* cout << opt_tilda << " " << log2f(assadiMPInput->m) << " " << powf(assadiMPInput->n, (float)1/assadiMPInput->alpha - 1) << endl; */
    float p = 16 * opt_tilda * log2f(assadiMPInput->m) * powf(assadiMPInput->n, (float)1/assadiMPInput->alpha - 1);
    cout << "p: " << p << endl;
    int sample_size = p * universe->size();
    //Iterative element sampling
    set<int>* U_smpl = new set<int>();
    for(int j = 1; j <= assadiMPInput->alpha && universe->size() > 0; j++){

        // 3)a) randomly sample O(n^{1/alpha})
        U_smpl->clear();
        /* cout << "universe->size(): " << universe->size() << endl; */
        /* cout << "sample_size: " << sample_size << endl; */
        sample(universe->begin(), universe->end(),
                std::inserter(*U_smpl, U_smpl->begin()), sample_size,
                std::mt19937{std::random_device{}()});
        /* cout << "U_smpl.size(): " << U_smpl->size() << endl; */

        // 3)b) Store the projection S' = S \union U_smpl over the stream
        // Compute a partial cover over the sample, append the partial cover
        map<int, bool> sampled;
        for(int v : *U_smpl) sampled[v] = true;
        vector<Set*>* sets = new vector<Set*>();
        for(Set* s; (s = assadiMPInput->stream->get_next_set()) != nullptr; ){
            Set* projected_set = new Set{{}, s->i};
            for(int v : s->vertices) if(sampled[v]) projected_set->vertices.insert(v);
            sets->push_back(projected_set);
        }
        assadiMPInput->stream->reset();
        SetCoverInput* sci = new SetCoverInput{sets, U_smpl};
        set<int>* partial_sol = offline(sci);
        sol->insert(partial_sol->begin(), partial_sol->end());

        // 3)c) Remove elements of sets of partial cover
        vector<int> partial_sol_v(partial_sol->begin(), partial_sol->end());
        sort(partial_sol_v.begin(), partial_sol_v.end(), std::greater<int>());
        for(Set* s; (s = assadiMPInput->stream->get_next_set()) != nullptr; ){
            if(s->i == partial_sol_v.back()) {
                partial_sol_v.pop_back();
                for(int v : s->vertices) universe->erase(v);
            }
        }
        assadiMPInput->stream->reset();
    }

    return sol;
}

set<int>* assadiMP(AssadiMPInput* assadiMPInput){

    /* cout << "n: " << assadiMPInput->n << endl; */
    /* cout << "m: " << assadiMPInput->m << endl; */

    int guesses = log2f(assadiMPInput->n)/assadiMPInput->epsilon;
    /* cout << "guesses: " << guesses << endl; */
    set<int>* best_sol = nullptr; int best_sol_size = std::numeric_limits<int>::max();;
    for(int i = 1; i <= guesses; i++){
        int opt_tilda = powf(2, i * assadiMPInput->epsilon);
        set<int>* sol = Algorithm1(assadiMPInput, opt_tilda);
        if (sol->size() < best_sol_size) {
            best_sol = sol;
            best_sol_size = sol->size();
        }
    }
    return best_sol;
}








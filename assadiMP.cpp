#include "assadiMP.hpp"
using namespace std;

#include "DFG.hpp"
set<int>* offline(SetCoverInput* sci, double p){
    map<int, vector<Set*>>* ktoCollection = OrderBySubCollection(sci, p);
    SetCoverOutput* sco = DFG(ktoCollection, p);
    return sco->Sigma;
}

set<int>* Algorithm1(AssadiMPInput* assadiMPInput, int opt_tilda){

    cout << assadiMPInput->n << endl;
    cout << opt_tilda << endl;
    cout << assadiMPInput->epsilon * opt_tilda << endl;
    int threshold = assadiMPInput->n/(assadiMPInput->epsilon * opt_tilda);
    cout << "here2" << endl;

    set<int>* universe = new set<int>();
    universe->insert(assadiMPInput->universe->begin(), assadiMPInput->universe->end());
    set<int>* sol = new set<int>();

    //Threshold set sampling
    for(Set* s; (s = assadiMPInput->stream->get_next_set()) != nullptr; ){
        if(s->vertices.size() > threshold){
            sol->insert(s->i);
            for(int v : s->vertices) universe->erase(v);
        }
    }
    assadiMPInput->stream->reset();

    float p = 16 * opt_tilda * logf(assadiMPInput->m) / powf(assadiMPInput->n, 1 - 1/assadiMPInput->alpha);
    cout << "p: " << p << endl;
    cout << "here3" << endl;
    int sample_size = p * assadiMPInput->n;
    //Iterative element sampling
    set<int>* U_smpl = new set<int>();
    for(int j = 1; j <= assadiMPInput->alpha; j++){

        cout << "here4" << endl;
        // 3)a) randomly sample O(n^{1/alpha})
        U_smpl->clear();
        sample(universe->begin(), universe->end(),
                std::inserter(*U_smpl, U_smpl->begin()), sample_size,
                std::mt19937{std::random_device{}()});

        cout << "here5" << endl;
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
        cout << "here6" << endl;
        SetCoverInput* sci = new SetCoverInput{sets, U_smpl};
        set<int>* partial_sol = offline(sci, 1.05);
        sol->insert(partial_sol->begin(), partial_sol->end());

        cout << "here5" << endl;
        // 3)c) Remove elements of sets of partial cover
        for(Set* s; (s = assadiMPInput->stream->get_next_set()) != nullptr; ){
            partial_sol->erase(partial_sol->begin());
            universe->erase(s->vertices.begin(), s->vertices.end());
        }
    }

    return sol;
}

set<int>* assadiMP(AssadiMPInput* assadiMPInput){

    int guesses = log2f(assadiMPInput->n)/assadiMPInput->epsilon;
    cout << "here" << endl;
    set<int>* best_sol;
    int sol_size = 0;
    int i = 1;
    /* for(int i = 1; i <= guesses; i++){ */
        int opt_tilda = powf(2, i)/(assadiMPInput->epsilon) * i;
        cout << "here1" << endl;
        set<int>* sol = Algorithm1(assadiMPInput, opt_tilda);
        if (sol->size() > sol_size) best_sol = sol;
    /* } */
    return best_sol;
}








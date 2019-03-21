#include "single-assadi.hpp"
#include "DFG.hpp"

vector<int>* single_sublinear(SSInput* ssi, int alpha){
    int m = (float)ssi->m/alpha;
    if(ssi->m % alpha > 0) m++;
    vector<unordered_set<int>>* vertices = new vector<unordered_set<int>>(m);
    vector<Set>* sets = new vector<Set>(m);

    Set* s = nullptr;
    for(int i = 0; i < alpha; i++){
        for(int j = 0; j < m && (s = ssi->stream->get_next_set()) != nullptr; j++){
            (*vertices)[j].insert(s->vertices.begin(), s->vertices.end());
        }
    }
    for(int i = 0; i < m; i++){
        (*sets)[i].i = i;
        (*sets)[i].vertices.insert((*sets)[i].vertices.end(),
            (*vertices)[i].begin(), (*vertices)[i].end());
    }
    ssi->stream->reset();
    SetCoverInput* sci = new SetCoverInput{sets, ssi->universe, m, ssi->n, 0, 0, 0, 0};
    return DFG(sci, 1.05);
}

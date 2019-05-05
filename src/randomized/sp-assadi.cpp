#include "sp-assadi.hpp"

vector<unsigned long>* single_sublinear(SPAInput* ssi, unsigned long alpha){
    unsigned long m = ((float)ssi->m/alpha);
    if(ssi->m % alpha > 0) m++;
    cout << "ssi->m: " << ssi->m << endl;
    cout << "m: " << m << endl;
    vector<unordered_set<unsigned long>>* vertices = new vector<unordered_set<unsigned long>>(m);
    vector<Set>* sets = new vector<Set>();

    Set* s = nullptr;
    for(unsigned long i = 0; i < alpha; i++){
        for(unsigned long j = 0; j < m && (s = ssi->stream->get_next_set()) != nullptr; j++){
            (*vertices)[j].insert(s->vertices.begin(), s->vertices.end());
        }
    }
    ssi->stream->reset();
    for(unsigned long i = 0; i < m; i++){
        sets->push_back(Set{{}, i});
        (*sets)[i].vertices.insert((*sets)[i].vertices.end(),
            (*vertices)[i].begin(), (*vertices)[i].end());
    }
    SetCoverInput* sci = new SetCoverInput{sets, ssi->universe, m, ssi->n, 0, 0, 0};
    return DFG(sci, 1.05);
}

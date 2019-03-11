#include "greedy.hpp"

vector<int>* greedy_impl(SetCoverInput* sci, int max_elem){
    //list of indices of chosen sets
    vector<int>* sol = new vector<int>();
    vector<vector<Set*>*> pqueue(sci->n, nullptr);
    vector<int> setIndexToSetCardinality(sci->m);
    vector<bool> covered(max_elem + 1);

    Set* s = sci->sets->data();
    for(int i = 0; i < sci->m; i++){
        int set_size = (s+i)->vertices.size();
        if(pqueue[set_size] == nullptr) pqueue[set_size] = new vector<Set*>();
        pqueue[set_size]->push_back(s+i);
        setIndexToSetCardinality[(s+i)->i] = set_size;
    }

    int topp = sci->n - 1;
    while(pqueue[topp] == nullptr) topp--;

    bool all_covered = true;
    for(int v : *sci->universe) if(!covered[v]) all_covered = false;
    while(!all_covered){
        //Get set with the highest number of uncovered elements and include it in the solution
        Set* T = pqueue[topp]->back();
        if(pqueue[topp]->size() > 1) pqueue[topp]->pop_back();
        else pqueue[topp] = nullptr;

        Set* diff = new Set{{}, T->i};
        for(int v : T->vertices) if(!covered[v]) diff->vertices.push_back(v);
        if(diff->vertices.size() == T->vertices.size()){
            sol->push_back(T->i);
            for(int v : T->vertices) covered[v] = true;
        }
        else {
            int new_size = diff->vertices.size();
            if(pqueue[new_size] == nullptr) pqueue[new_size] = new vector<Set*>();
            pqueue[new_size]->push_back(diff);
        }
        while(pqueue[topp] == nullptr && --topp > -1) {};
        if(topp == -1) break;
        all_covered = true;
        for(int v : *sci->universe) if(!covered[v]) all_covered = false;
    }

    return sol;
}


vector<int>* greedy(SetCoverInput* sci){
    int max_elem = *std::max_element(sci->universe->begin(), sci->universe->end());
    return greedy_impl(sci, max_elem);
}






#include "greedy.hpp"

struct SSet : public Set {
    SSet(vector<unsigned long> vertices, unsigned long i)
        : Set(vertices, i) {}
};

vector<unsigned long>* greedy_impl(SetCoverInput* sci, unsigned long max_elem){
    //list of indices of chosen sets
    vector<unsigned long>* sol = new vector<unsigned long>();
    vector<vector<Set*>*> pqueue(sci->n, nullptr);
    vector<bool> covered(max_elem + 1, false);

    Set* s = sci->sets->data();
    for(unsigned long i = 0; i < sci->m; i++){
        unsigned long set_size = (s+i)->vertices.size();
        if(pqueue[set_size] == nullptr) pqueue[set_size] = new vector<Set*>();
        pqueue[set_size]->push_back(s+i);
    }

    unsigned long topp = sci->n - 1;
    while(pqueue[topp] == nullptr) topp--;

    unsigned long num_covered = 0;
    while(num_covered != sci->n){
        //Get set with the highest number of uncovered elements and include it in the solution
        Set* T = pqueue[topp]->back();
        if(pqueue[topp]->size() > 1) pqueue[topp]->pop_back();
        else {
            delete pqueue[topp];
            pqueue[topp] = nullptr;
        }

        Set* diff = new SSet{{}, T->i};
        for(unsigned long v : T->vertices) if(!covered[v]) diff->vertices.push_back(v);
        if(diff->vertices.size() == T->vertices.size()){
            sol->push_back(T->i);
            for(unsigned long v : T->vertices) {
                covered[v] = true;
                num_covered++;
            }
        }
        else {
            unsigned long new_size = diff->vertices.size();
            if(pqueue[new_size] == nullptr) pqueue[new_size] = new vector<Set*>();
            pqueue[new_size]->push_back(diff);
        }
        if(SSet* Ts = dynamic_cast<SSet*>(T)) delete Ts;
        while(pqueue[topp] == nullptr && --topp != static_cast<unsigned long>(-1)) {};
        if(topp == static_cast<unsigned long>(-1)) break;
    }

    return sol;
}


vector<unsigned long>* greedy(SetCoverInput* sci){
    unsigned long max_elem = *std::max_element(sci->universe->begin(), sci->universe->end());
    return greedy_impl(sci, max_elem);
}






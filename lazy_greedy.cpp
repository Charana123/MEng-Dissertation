#include "greedy.hpp"

vector<int>* greedy_impl(SetCoverInput* sci, int max_elem){
    //list of indices of chosen sets
    vector<int>* sol = new vector<int>();
    vector<vector<Set*>*> pqueue(sci->n);
    vector<int> setIndexToSetCardinality(sci->m);
    vector<bool> covered(max_elem + 1);
    Set* s = sci->sets->data();

    int topp = 0;
    for(int i = 0; i < sci->m; i++){
        int set_size = (s+i)->vertices.size();
        if(set_size > topp) topp = set_size;
        if(pqueue[set_size] == nullptr) pqueue[set_size] = new vector<Set*>();
        pqueue[set_size]->push_back(s+i);
        setIndexToSetCardinality[(s+i)->i] = set_size;
    }

    bool all_covered = true;
    for(int v : *sci->universe) if(!covered[v]) all_covered = false;
    cout << "here1" << endl;
    while(!all_covered){
        cout << "here2" << endl;
        //Get set with the highest number of uncovered elements and include it in the solution
        Set* T = (*pqueue[topp])[0];

        int covered_elements = true;
        for(int v : T->vertices) if(covered[v]) covered_elements += 1;
        cout << "here3" << endl;
        if(covered_elements == 0){
            cout << "here5.1" << endl;
            sol->push_back(T->i);
            for(int v : T->vertices) covered[v] = true;
            cout << "here5.2" << endl;
        }
        else {
            cout << "here4.2" << endl;
            Set* si = nullptr;
            vector<Set*>* clist = pqueue[setIndexToSetCardinality[T->i]];
            int clist_size = clist->size();
            cout << "here4.3" << endl;
            for(int j = 0; j < clist_size; j++){
                if(T->i == (*clist)[j]->i) {
                    cout << "here4.3.1" << endl;
                    si = s;
                    clist->erase(clist->begin() + j);
                    break;
                }
            }

            cout << "here4.4" << endl;
            int new_size = T->vertices.size() - covered_elements;
            setIndexToSetCardinality[T->i] = new_size;
            cout << "here4.5" << endl;
            if(pqueue[setIndexToSetCardinality[T->i]] == nullptr) pqueue[setIndexToSetCardinality[T->i]] = new vector<Set*>();
            pqueue[setIndexToSetCardinality[T->i]]->push_back(si);
            cout << "here4.6" << endl;
        }
        while(pqueue[topp] == nullptr) topp--;
        all_covered = true;
        for(int v : *sci->universe) if(!covered[v]) all_covered = false;
    }

    return sol;
}


vector<int>* greedy(SetCoverInput* sci){
    int max_elem = *std::max_element(sci->universe->begin(), sci->universe->end());
    return greedy_impl(sci, max_elem);
}






#include "greedy.hpp"

vector<vector<int>>* computeInvertedIndex(SetCoverInput* sci, int max_elem){
    vector<vector<int>>* inverted_index = new vector<vector<int>>(max_elem + 1);
    Set* s = sci->sets->data();
    for(int i = 0; i < sci->m; i++){
        for(int v : (s+i)->vertices) {
            /* cout << "v: " << v << ", s: " << (s+i)->i << endl; */
            (*inverted_index)[v].push_back((s+i)->i);
        }
    }
    return inverted_index;
}

vector<int>* greedy_impl(SetCoverInput* sci, vector<vector<int>>* inverted_index, int max_elem){
    //list of indices of chosen sets
    vector<int>* sol = new vector<int>();
    //list of lists, mapping number of uncovered elements to a list of sets
    vector<vector<Set*>*> pqueue(sci->n);
    //maps set index to a pointer to that set
    vector<Set*> setIndexToSet(sci->m);
    //maps set index to number of uncovered elements
    vector<int> setIndexToSetCardinality(sci->m);
    //maps set index to number of elements to decrement from number of uncovered elements
    vector<int> setIndexToUpdateCount(sci->m);
    vector<bool> covered(max_elem + 1);
    Set* s = sci->sets->data();

    cout << "here2" << endl;
    int topp = 0;
    for(int i = 0; i < sci->m; i++){
        int set_size = (s+i)->vertices.size();
        if(set_size > topp) topp = set_size;
        if(pqueue[set_size] == nullptr) pqueue[set_size] = new vector<Set*>();
        pqueue[set_size]->push_back(s+i);
        setIndexToSet[(s+i)->i] = (s+i);
        setIndexToSetCardinality[(s+i)->i] = set_size;
    }

    cout << "here3" << endl;
    bool all_covered = true;
    for(int v : *sci->universe) if(!covered[v]) all_covered = false;
    while(!all_covered){
        cout << "here4" << endl;
        //Get set with the highest number of uncovered elements and include it in the solution
        Set* T = (*pqueue[topp])[0];
        sol->push_back(T->i);
        cout << "here4.1" << endl;
        for(int v : T->vertices) {
            if(!covered[v]){
                cout << "here4.2" << endl;
                /* cout << "v: " << v << endl; */
                //Include uncovered elements of set in cover
                covered[v] = true;
                cout << "here4.3" << endl;
                //increase update count for sets containing uncovered elements of chosen set
                for(int i : (*inverted_index)[v]) {
                    cout << "here4.4" << endl;
                    /* cout << "i: " << i << endl; */
                    setIndexToUpdateCount[i]++;
                }
                cout << "here4.5" << endl;
            }
        }
        cout << "here5" << endl;

        //For every set whose cardinality is reduced, perform the update
        for(int i = 0; i < sci->m; i++){
            cout << "here5.1" << endl;
            if(setIndexToUpdateCount[i]){
            cout << "here5.2" << endl;
                Set* si = nullptr;
                vector<Set*>* clist = pqueue[setIndexToSetCardinality[i]];
                cout << "set: " << i << endl;
                for(Set* s: *clist) cout << *s << endl;
                int clist_size = clist->size();
            cout << "here5.2" << endl;
                for(int j = 0; j < clist_size; j++){
                    if(i == (*clist)[j]->i) {
                        si = s;
                        clist->erase(clist->begin() + j);
                        break;
                    }
                }
            cout << "here5.3" << endl;
            cout << "si: " << si << endl;
                setIndexToSetCardinality[i] -= setIndexToUpdateCount[i];
                if(pqueue[setIndexToSetCardinality[i]] == nullptr) pqueue[setIndexToSetCardinality[i]] = new vector<Set*>();
                pqueue[setIndexToSetCardinality[i]]->push_back(si);
            }
        }
        setIndexToUpdateCount.clear();
        while(pqueue[topp] == nullptr) topp--;
        all_covered = true;
        for(int v : *sci->universe) if(!covered[v]) all_covered = false;
    }

    return sol;
}


vector<int>* greedy(SetCoverInput* sci){
    int max_elem = *std::max_element(sci->universe->begin(), sci->universe->end());
    vector<vector<int>>* inverted_index = computeInvertedIndex(sci, max_elem);
    return greedy_impl(sci, inverted_index, max_elem);
}










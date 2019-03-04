#include "DFG.hpp"
using namespace std;
using namespace boost;

void OrderBySubCollection(SetCoverInput* sci, float p, vector<float>* p_pow_k, vector<vector<Set*>>* ktoCollection){

    Set* s = sci->sets->data();
    p_pow_k->push_back(1);
    for(int i = 0; i < sci->m; i++){
        for(int k = 0; ; k++){
            if(p_pow_k->size() <= k + 1) {
                p_pow_k->push_back(powf(p,k+1));
            }
            if ((s+i)->vertices.size() >= (*p_pow_k)[k] && (s+i)->vertices.size() < (*p_pow_k)[k+1]){
                if(k + 1 > ktoCollection->size()) ktoCollection->resize(k+1);
                (*ktoCollection)[k].push_back(s+i);
                break;
            }
        }
    }
}

// Disk Friendly Greedy
vector<int>* DFG_impl(SetCoverInput* sci, vector<float>* p_pow_k, vector<vector<Set*>>* ktoCollection, float p)
{
    // Globals
    vector<int>* sol = new vector<int>(); //list of indices of chosen sets
    int max_elem = *std::max_element(sci->universe->begin(), sci->universe->end());
    vector<bool> covered(max_elem);

    for(int k = ktoCollection->size()-1; k > 0; k--){
        for (Set *s: (*ktoCollection)[k]){
            Set* diff = new Set{{}, s->i};
            for(int v : s->vertices) if(!covered[v]) diff->vertices.push_back(v);

            if(diff->vertices.size() >= (*p_pow_k)[k]) {
                sol->push_back(s->i);
                for(int v : diff->vertices) covered[v] = true;
            }
            else{
                for(int k_prime = k-1; k_prime >= 0; k_prime--){
                    if (diff->vertices.size() >= (*p_pow_k)[k_prime] && diff->vertices.size() < (*p_pow_k)[k_prime+1]){
                        (*ktoCollection)[k_prime].push_back(diff);
                        break;
                    }
                }
            }
        }
    }

    for(Set* s: (*ktoCollection)[0]){
        vector<int> diff;
        for(int v : s->vertices) if(!covered[v]) diff.push_back(v);
        if(diff.size() == 1) {
            sol->push_back(s->i);
            covered[diff[0]] = true;
        }
    }
    return sol;
}

vector<int>* DFG(SetCoverInput* sci, float p = 1.05){
    vector<float>* p_pow_k = new vector<float>();
    vector<vector<Set*>>* ktoCollection = new vector<vector<Set*>>();
    OrderBySubCollection(sci, p, p_pow_k, ktoCollection);
    return DFG_impl(sci, p_pow_k, ktoCollection, p);
}




















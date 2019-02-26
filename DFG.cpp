#include "DFG.hpp"
using namespace std;
using namespace boost;

map<int, vector<Set*>>* OrderBySubCollection(SetCoverInput* sci, float p = 1.05){

    map<int, vector<Set*>>* ktoCollection = new map<int, vector<Set*>>();
    for(Set* s : *sci->sets){
        for(int k = 0; ; k++){
            if (s->vertices.size() >= pow(p, k) && s->vertices.size() < pow(p, k+1)){
                (*ktoCollection)[k].push_back(s);
                break;
            }
        }
    }
    return ktoCollection;
}

// Disk Friendly Greedy
SetCoverOutput* DFG(map<int, vector<Set*>>* ktoCollection, float p = 1.05)
{
    // Globals
    set<int>* Sigma = new set<int>(); //list of indices of chosen sets
    set<int>* C = new set<int>(); //list of covered vertices

    set<int, std::less<int>> keys;
    for(auto const& e : *ktoCollection) keys.insert(e.first);
    int K = max(*keys.end(), *keys.begin());
    for(int k = K; k > 0; k--){
        for (Set *s: (*ktoCollection)[k]){
            Set diff = {{}, -1};
            set_difference(s->vertices.begin(), s->vertices.end(), C->begin(), C->end(), inserter(diff.vertices, diff.vertices.end()));

            if(diff.vertices.size() >= pow(p, k)){
                Sigma->insert(s->i);
                C->insert(diff.vertices.begin(), diff.vertices.end());
            }

            else{
                for(int k_prime = K; k_prime >= 0; k_prime--){
                    if (diff.vertices.size() >= pow(p, k_prime) && diff.vertices.size() < pow(p, k_prime+1)){
                        diff.i = s->i;
                        (*ktoCollection)[k_prime]->push_back(diff);
                        break;
                    }
                }
            }
        }
    }

    for(Set set: (*ktoCollection)[0]){
        Set diff = {{}, -1};
        set_difference(set.vertices.begin(), set.vertices.end(), C->begin(), C->end(), inserter(diff.vertices, diff.vertices.end()));

        if(diff.vertices.size() == 1){
            Sigma->insert(set.i);
            C->insert(diff.vertices.begin(), diff.vertices.end());
        }
    }
    return new SetCoverOutput{Sigma, C};
}






















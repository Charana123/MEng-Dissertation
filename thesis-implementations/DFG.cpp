#include "DFG.hpp"
using namespace std;
using namespace boost;

map<int, vector<Set>>* OrderBySubCollection(SetCoverInput* set_cover_input, float p = 1.05){

    map<int, Set> collection = set_cover_input->sets;
    Set universe = set_cover_input->universe;

    map<int, vector<Set>> ktoCollection = new {};
    for(auto e : collection){
        Set s = e.second;
        for(int k = 0; ; k++){
            if (s.vertices.size() >= pow(p, k) && s.vertices.size() < pow(p, k+1)){
                ktoCollection[k].push_back(s);
                break;
            }
        }
    }
    return ktoCollection;
}

// Disk Friendly Greedy
SetCoverOutput* DFG(map<int, vector<Set>>* ktoCollection, float p = 1.05)
{
    // Globals
    set<int> Sigma; //list of indices of chosen sets
    Set C = {{}, -1}; //list of covered vertices

    set<int, std::less<int>> keys;
    for(auto const& e : *ktoCollection) keys.insert(e.first);
    int K = max(*keys.end(), *keys.begin());
    for(int k = K; k > 0; k--){
        for (Set set: ktoCollection[k]){
            Set diff = {{}, -1};
            set_difference(set.vertices.begin(), set.vertices.end(), C.vertices.begin(), C.vertices.end(), inserter(diff.vertices, diff.vertices.end()));

            if(diff.vertices.size() >= pow(p, k)){
                Sigma.insert(set.i);
                C.vertices.insert(diff.vertices.begin(), diff.vertices.end());
            }

            else{
                for(int k_prime = K; k_prime >= 0; k_prime--){
                    if (diff.vertices.size() >= pow(p, k_prime) && diff.vertices.size() < pow(p, k_prime+1)){
                        diff.i = set.i;
                        ktoCollection[k_prime].push_back(diff);
                        break;
                    }
                }
            }
        }
    }

    for(Set set: ktoCollection[0]){
        Set diff = {{}, -1};
        set_difference(set.vertices.begin(), set.vertices.end(), C.vertices.begin(), C.vertices.end(), inserter(diff.vertices, diff.vertices.end()));

        if(diff.vertices.size() == 1){
            Sigma.insert(set.i);
            C.vertices.insert(diff.vertices.begin(), diff.vertices.end());
        }
    }
    return new {Sigma, C};
}






















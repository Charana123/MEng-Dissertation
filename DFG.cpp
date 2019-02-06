#include "set_cover.hpp"
using namespace std;
using namespace boost;

SetCoverOutput DFG(string filename, float p = 1.05)
{
    // Globals
    set<int> Sigma; //list of indices of chosen sets
    Set C = {{}, -1}; //list of covered vertices

    //Read and parse set S
	SetCoverInput set_cover_input = read_problem(filename);
    cout << "finished reading" << endl;
    vector<Set> collection = set_cover_input.sets;
    Set universe = set_cover_input.universe;

    // Order sets by subcollection
    map<int, vector<Set>> ktoCollection;
    for(Set s : collection){
        for(int k = 0; ; k++){
            if (s.vertices.size() >= std::pow(p, k) && s.vertices.size() < std::pow(p, k+1)){
                ktoCollection[k].push_back(s);
                break;
            }
        }
    }

    //Algorithm
    vector<int> keys;
    for(auto const& e : ktoCollection) keys.push_back(e.first);
    int K = *max_element(keys.begin(), keys.end());
    for(int k = K; k > 0; k--){
        for (Set set: ktoCollection[k]){
            cout << "k:" << k << "-" << set.i << endl;
            Set diff = {{}, -1};
            std::set_difference(set.vertices.begin(), set.vertices.end(), C.vertices.begin(), C.vertices.end(), std::inserter(diff.vertices, diff.vertices.end()));

            if(diff.vertices.size() >= pow(p, k)){
                Sigma.insert(set.i);
                C.vertices.insert(diff.vertices.begin(), diff.vertices.end());
            }

            else{
                for(int k_prime = 0; ; k_prime++){
                    if (diff.vertices.size() >= std::pow(p, k_prime) && diff.vertices.size() < std::pow(p, k_prime+1)){
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
        std::set_difference(set.vertices.begin(), set.vertices.end(), C.vertices.begin(), C.vertices.end(), std::inserter(diff.vertices, diff.vertices.end()));

        if(diff.vertices.size() == 1){
            Sigma.insert(set.i);
            C.vertices.insert(diff.vertices.begin(), diff.vertices.end());
        }
    }
    cout << "end" << endl;
    return {Sigma, C};
}






















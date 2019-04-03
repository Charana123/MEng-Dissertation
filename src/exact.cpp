#include "exact.hpp"
#include <string>
#include <chrono>

using namespace std;

bool evaluate_combination(SetCoverInput* sci, char* combination)
{
    vector<char> covered(sci->n, 0);
    int ncovered = 0;
    for(int i = 0; i < sci->m; i++){
        if(combination[i] == 1) {
            for(int v : sci->sets->at(i).vertices){
                if(covered[v] == 0) {
                    covered[v] = 1;
                    ncovered++;
                }
            }
        }
    }
    if(sci->n == ncovered) return true;
    else return false;
}

int exact(SetCoverInput* sci){
    unsigned long combinations = std::pow(2, sci->m);
    char* combination = new char[sci->m];
    for(int i = 0; i < combinations; i++){
        cout << "i: " << i << endl;
        // Count the number of 1's
        int size = 0;
        for(int j = 0; j < sci->m; j++) if(combination[sci->m-j-1] == 1) size++;
        // Compute whether to reset
        bool all_last = true;
        for(int j = 0; j < size; j++){
            if(combination[sci->m-j-1] == 0) all_last = false;
        }
        // if all_last, set all (size + 1) bits to 1
        // then evaluate the combination
        if (all_last || size == 0){
            for(int j = 0; j < size + 1; j++) combination[j] = 1;
            if(evaluate_combination(sci, combination)) return size + 1;
        }
        // if not all_last, move last bit that isn't at its last position, one step foward
        // then evaluate the combination
        else{
            for(int j = 0; j < sci->m; j++) if(combination[sci->m-j-1] == 1){
                if(j == 0 || combination[sci->m-j] == 1) continue;
                else{
                    combination[sci->m-j-1] = 0;
                    combination[sci->m-j] = 1;
                    break;
                }
            }
            if(evaluate_combination(sci, combination)) return size;
        }
    }
    return -1;
}





















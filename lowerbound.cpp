#include "sc_utils.hpp"

void compute_lowerbound(string filename){

    SetCoverInput* sci = read_sci("./dataset/FIMI/" + filename + ".dat");

    // Compute universe
    set<int> universe;
    for(Set* s : *sci->sets) universe.insert(s->vertices.begin(), s->vertices.end());

    // Sort sets by size
    sort(sci->sets->begin(), sci->sets->end(), [](Set* s1, Set* s2) -> bool{
        return s1->vertices.size() < s2->vertices.size();
    });
    set<int> covered_universe;
    int sol_size = -1;
    for(Set* s : *sci->sets){
        covered_universe.insert(s->vertices.begin(), s->vertices.end());
        if(covered_universe.size() == universe.size()) {
            sol_size = s->i;
            break;
        }
    }
    cout << "file: " << filename + ".dat" << endl;
    cout << "solution size: " << sol_size << endl;
}

int main(int argc, char** argv){
    /* string filename = string(argv[1]); */
    vector<string> files = {"test", "chess", "pumsb", "retail", "kosarak"};
    for(string filename : files) compute_lowerbound(filename);
}


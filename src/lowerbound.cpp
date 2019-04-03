#include "sc_utils.hpp"

int compute_lowerbound(SetCoverInput* sci){

    // Sort sets by size
    sort(sci->sets->begin(), sci->sets->end(), [](Set& s1, Set& s2) -> bool{
        return s1.vertices.size() < s2.vertices.size();
    });
    int i = 0;
    for(int size = 0; i < sci->m; i++){
        Set& s = sci->sets->at(i);
        size += s.vertices.size();
        if(size >= sci->n) break;
    }
    return i;
}

int main(int argc, char** argv){
    /* string filename = string(argv[1]); */
    vector<string> files = {"test", "chess", "pumsb", "retail", "kosarak"};
    for(string filename : files) {
        SetCoverInput* sci = read_sci("../implementations/dataset/FIMI/" + filename + ".dat");
        /* SetCoverInput* sci = read_sci(filename); */
        int lowerbound = compute_lowerbound(sci);
        cout << "lowerbound: " << lowerbound << endl;
    }
}


#include "sc_utils.hpp"
#include "functional"

bool compare(const Set& s1, const Set& s2){
    return s1.vertices.size() > s2.vertices.size();
}

int compute_lowerbound(SetCoverInput* sci){
    cout << "computing lowerbound" << endl;

    // Sort sets by size
    vector<unsigned long> sizes;
    for(Set& s : *sci->sets) sizes.push_back(s.vertices.size());
    sort(sizes.begin(), sizes.end(), std::greater<unsigned long>());
    unsigned long i = 0;
    unsigned long size = 0;
    for(unsigned long csize : sizes){
        size += csize; i++;
        if(size >= sci->n) break;
    }
    return i;
}

int main(int argc, char** argv){
    string filepath = string(argv[1]);
    //vector<string> files = {"test", "chess", "pumsb", "retail", "kosarak"};
    //for(string filename : files) {
        //SetCoverInput* sci = read_sci("../implementations/dataset/FIMI/" + filename + ".dat");
        SetCoverInput* sci = read_sci(filepath);
        /* SetCoverInput* sci = read_sci(filename); */
        int lowerbound = compute_lowerbound(sci);
        cout << "lowerbound: " << lowerbound << endl;
    //}
}


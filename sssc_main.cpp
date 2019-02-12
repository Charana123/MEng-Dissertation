#include "sssc.hpp"
#include "ec_utils.hpp"
#include <functional>

using namespace std;

int main(){
    EdgeCoverInput* eci = read_eci("./dataset/chess.dat");
    HyperEdge* he = eci->hyperedges->get_next_hyperedge();
    if (he == nullptr) cout << "nullptr" << endl;
    /* EdgeCoverOutput* eco = sssc(eci); */
}





















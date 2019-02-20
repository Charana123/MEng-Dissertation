#include "pgreedy.hpp"


int main(){
    Stream stream("./dataset/chess.dat");
    cout << "created stream" << endl;
    Set universe = {{}, -1};
    stream.get_universe(universe);
    cout << "get universe" << endl;
    int n = universe.vertices.size();

    ProgressiveGreedyInput pgin = {stream, n};
    int p = 1;
    ProgressiveGreedyOutput pgout;
    progressive_greedy_naive(pgin, p, pgout);

    cout << "solution.size: " << pgout.sol.size() << endl;
}

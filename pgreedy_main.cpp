#include "pgreedy.hpp"


int main(){
    Stream stream("./dataset/chess.dat");
    Set universe = {{}, -1};
    stream.get_universe(universe);
    int n = universe.vertices.size();

    cout << "before" << endl;
    ProgressiveGreedyInput pgin = {stream, n};
    cout << "after" << endl;
    int p = 10;
    ProgressiveGreedyOutput pgout;
    progressive_greedy_naive(pgin, p, pgout);

    cout << "solution.size: " << pgout.sol.size() << endl;
}

#include "pgreedy.hpp"
#include <sys/types.h>
#include <unistd.h>

void summarise(string name, std::function<void()> func){
    auto t1 = chrono::high_resolution_clock::now();
    func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "===========" << endl;
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    cout << endl;
}

int main(int argc, char** argv){
	string filename = string(argv[1]);
    Stream* stream = new Stream("./dataset/" + filename + ".dat");
    set<int>* universe = new set<int>();
    int m;
    stream->get_universe(universe, &m);
    int n = universe->size();
    ProgressiveGreedyInput pgin = {stream, universe, n, m};

    summarise("p = 1", [&pgin]() -> void{
        ProgressiveGreedyOutput pgout;
        progressive_greedy_naive(&pgin, 1, &pgout);
    });

	/* pid_t pid = getpid(); */
    /* ofstream results(filename + ".res." + to_string(pid)); */
    /* for(int p = 1; p < 20; p+=1){ */
        /* ProgressiveGreedyOutput pgout; */
        /* progressive_greedy_naive(&pgin, p, &pgout); */
        /* cout << p << " " << pgout.sol.size() << " " << endl; */
        /* results << p << " " << pgout.sol.size() << " " << endl; */
    /* } */
}

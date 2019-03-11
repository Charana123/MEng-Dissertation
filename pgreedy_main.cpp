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
	/* string filename = string(argv[1]); */
	vector<string> files = {"test", "chess", "retail", "pumsb", "kosarak"};
	/* vector<string> files = {"webdocs"}; */
	for(string filename : files){
        Stream* stream = new OfflineStream("./dataset/FIMI/" + filename + ".dat");
        vector<int>* universe = new vector<int>();
        int m, avg, M;
        stream->get_universe(universe, &m, &avg, &M);
        int n = universe->size();
        ProgressiveGreedyInput pgin = {stream, universe, n, m};

        int passes = 1; //log2f(n);
        summarise(filename + ".dat", [&]() -> void{
            set<int>* sol = progressive_greedy_naive(&pgin, passes);
            cout << "Solution size: " << sol->size() << endl;
        });
	}

	/* pid_t pid = getpid(); */
    /* ofstream results(filename + ".res." + to_string(pid)); */
    /* for(int p = 1; p < 20; p+=1){ */
        /* ProgressiveGreedyOutput pgout; */
        /* progressive_greedy_naive(&pgin, p, &pgout); */
        /* cout << p << " " << pgout.sol.size() << " " << endl; */
        /* results << p << " " << pgout.sol.size() << " " << endl; */
    /* } */
}

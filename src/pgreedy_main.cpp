#include "pgreedy.hpp"
#include <sys/types.h>
#include <unistd.h>

void summarise(string name, int passes, ofstream* outfile, std::function<unordered_set<int>*()> func){
    auto t1 = chrono::high_resolution_clock::now();
    unordered_set<int>* sol = func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "===========" << endl;
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    /* cout << "Solution size: " << sol->size() << endl; */
    *outfile << passes << " " << sol->size() << " " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << endl;
    cout << endl;
}

int main(){
	/* string filename = string(argv[1]); */
	/* vector<string> files = {"test", "chess", "retail", "pumsb", "kosarak"}; */
	vector<string> files = {"webdocs"};
	for(string filename : files){
        Stream* stream = new OfflineStream("../dataset/FIMI/" + filename + ".dat");
        vector<int>* universe = new vector<int>();
        int m, M, avg, median, largest;
        stream->get_universe(universe, &m, &avg, &median, &largest, &M);
        int n = universe->size();
        ProgressiveGreedyInput pgin = {stream, universe, n, m};

        ofstream* outfile = new ofstream("../pg_results/" + filename + ".res", std::fstream::out);
        int max_passes = log(n);
        cout << "max_passes: " << max_passes << endl;
        for(int passes = 11; passes < max_passes; passes++){
            cout << "passes: " << passes << endl;
            summarise(filename + ".dat", passes, outfile, [&]() -> unordered_set<int>*{
                return progressive_greedy_naive(&pgin, passes);
            });
        }
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

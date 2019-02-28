#include "thgreedy.hpp"
#include <chrono>

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
	for(string filename : files){
        Stream* stream = new Stream("./dataset/FIMI/" + filename + ".dat");
        set<int>* universe = new set<int>();
        int m;
        stream->get_universe(universe, &m);
        int n = universe->size();
        ThresholdGreedyInput tgi = {stream, universe, n, m};

        summarise(filename + ".dat", [&]() -> void{
            set<int>* sol = threshold_greedy(&tgi);
            cout << "Solution size: " << sol->size() << endl;
        });
	}
}

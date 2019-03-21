#include "greedy.hpp"
#include "pgreedy.hpp"
#include "DFG.hpp"
#include "sssc.hpp"
#include <chrono>

using namespace std;

void summarise(string name, std::function<vector<int>*()> func){
    auto t1 = chrono::high_resolution_clock::now();
    vector<int>* sol = func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "===========" << endl;
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    cout << "Solution size: " << sol->size() << endl;
    cout << endl;
}

void summarise(string name, std::function<unordered_set<int>*()> func){
    auto t1 = chrono::high_resolution_clock::now();
    unordered_set<int>* sol = func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "===========" << endl;
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    cout << "Solution size: " << sol->size() << endl;
    cout << endl;
}


int main(int argc, char** argv){
	string filename = string(argv[1]);
    OfflineStream* offline_stream = new OfflineStream(filename);
    SetCoverInput* sci = offline_stream->sci;
    Stream* stream = offline_stream;
    vector<int>* universe = new vector<int>();
    int m, avg, M;
    stream->get_universe(universe, &m, &avg, &M);
    int n = universe->size();

    /* summarise("lazy greedy", [&]() -> vector<int>*{ */
    /*     return greedy(sci); */
    /* }); */

    summarise("DFG", [&]() -> vector<int>*{
        float p = 1.05;
        return DFG(sci, p);
    });

    summarise("capture", [&]() -> unordered_set<int>*{
        SSSCInput sssci = {stream, universe, n, m, avg};
        return capture(&sssci);
    });

    summarise("sssc", [&]() -> unordered_set<int>*{
        SSSCInput sssci = {stream, universe, n, m, avg};
        return sssc(&sssci);
    });

    summarise("randomized sssc", [&]() -> unordered_set<int>*{
        SSSCInput sssci = {stream, universe, n, m, avg};
        return randomized_sssc(&sssci);
    });

    /* summarise("randomized sssc", [&]() -> unordered_set<int>*{ */
    /*     SSSCInput sssci = {stream, universe, n, m, avg}; */
    /*     return threshold_randomized_sssc(&sssci); */
    /* }); */

    summarise("pg", [&]() -> unordered_set<int>*{
        ProgressiveGreedyInput pgin = {stream, universe, n, m};
        int passes = 1;
        return progressive_greedy_naive(&pgin, passes);
    });
}






















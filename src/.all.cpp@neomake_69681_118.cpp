#include "greedy.hpp"
#include "pgreedy.hpp"
#include "DFG.hpp"
#include "sssc.hpp"
#include <chrono>

using namespace std;

void summarise(string name, std::function<vector<unsigned long>*()> func){
    auto t1 = chrono::high_resolution_clock::now();
    vector<unsigned long>* sol = func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "===========" << endl;
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    cout << "Solution size: " << sol->size() << endl;
    cout << endl;
}

void summarise(string name, std::function<unordered_set<unsigned long>*()> func){
    auto t1 = chrono::high_resolution_clock::now();
    unordered_set<unsigned long>* sol = func();
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
	int streaming_only = std::stoi(string(argv[2]));
    Stream* stream;
    if(streaming_only == 1) stream = new OnlineStream(filename);
    else stream = new OfflineStream(filename);
    vector<unsigned long>* universe = new vector<unsigned long>();
    unsigned long m, M, avg, largest;
    stream->get_universe(universe, &m, &avg, &largest, &M);
    unsigned long n = universe->size();

    cout << "==============" << endl;
    cout << "n: " << n << endl;
    cout << "m: " << m << endl;
    cout << "M: " << M << endl;
    cout << "avg: " << avg << endl;
    cout << "largest: " << largest << endl;
    cout << "==============" << endl;

    if(streaming_only == 0){
        OfflineStream* offline_stream = static_cast<OfflineStream*>(stream);
        SetCoverInput* sci = offline_stream->sci;
        summarise("DFG", [&]() -> vector<unsigned long>*{
            float p = 1.05;
            return DFG(sci, p);
        });
    }

    summarise("capture", [&]() -> unordered_set<unsigned long>*{
        SSSCInput sssci = {stream, universe, n, m, avg};
        return capture(&sssci);
    });

    summarise("sssc", [&]() -> unordered_set<unsigned long>*{
        SSSCInput sssci = {stream, universe, n, m, avg};
        return sssc(&sssci);
    });

    /* summarise("randomized sssc", [&]() -> unordered_set<int>*{ */
    /*     SSSCInput sssci = {stream, universe, n, m, avg}; */
    /*     return randomized_sssc(&sssci); */
    /* }); */

    /* summarise("randomized sssc", [&]() -> unordered_set<int>*{ */
    /*     SSSCInput sssci = {stream, universe, n, m, avg}; */
    /*     return threshold_randomized_sssc(&sssci); */
    /* }); */

    /* summarise("pg", [&]() -> unordered_set<int>*{ */
    /*     ProgressiveGreedyInput pgin = {stream, universe, n, m}; */
    /*     int passes = 1; */
    /*     return progressive_greedy_naive(&pgin, passes); */
    /* }); */
}






















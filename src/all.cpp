#include "greedy.hpp"
#include "pgreedy.hpp"
#include "DFG.hpp"
#include "sssc.hpp"
#include "pp_greedy.hpp"
#include "rss.hpp"
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
    cout << "before" << endl;
    auto t1 = chrono::high_resolution_clock::now();
    unordered_set<unsigned long>* sol = func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "===========" << endl;
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    cout << "Solution size: " << sol->size() << endl;
    cout << endl;
    cout << "after" << endl;
}

int main(int argc, char** argv){
	string filename = string(argv[1]);
	int streaming_only = std::stoi(string(argv[2]));
	string alg = string(argv[3]);

    if(!(alg.compare("DFG") == 0
        || alg.compare("pp") == 0
        || alg.compare("LSH") == 0
        || alg.compare("PLSH") == 0
        || alg.compare("Rosen") == 0
        || alg.compare("all") == 0
        || alg.compare("LSH-DFG") == 0
        || alg.compare("Rosen-DFG") == 0)){
        cout << "could not find: " << alg << endl;
        abort();
    }

    Stream* stream;
    if(streaming_only == 1) stream = new OnlineStream(filename);
    else stream = new OfflineStream(filename);
    cout << "Created stream" << endl;
    vector<unsigned long>* universe = new vector<unsigned long>();
    unsigned long m, M, avg, largest;
    stream->get_universe(universe, &m, &avg, &largest, &M);
    cout << "Computed universe" << endl;
    unsigned long n = universe->size();

    cout << "==============" << endl;
    cout << "n: " << n << endl;
    cout << "m: " << m << endl;
    cout << "M: " << M << endl;
    cout << "avg: " << avg << endl;
    cout << "largest: " << largest << endl;
    cout << "==============" << endl;

    if(alg.compare("DFG") == 0 || alg.compare("all") == 0){
        if(streaming_only == 0){
            OfflineStream* offline_stream = static_cast<OfflineStream*>(stream);
            SetCoverInput* sci = offline_stream->sci;
            summarise("DFG", [&]() -> vector<unsigned long>*{
                float p = 1.05;
                return DFG(sci, p);
            });
        }
    }

    if(alg.compare("PLSH") == 0 || alg.compare("all") == 0){
        summarise("capture", [&]() -> unordered_set<unsigned long>*{
            SSSCInput sssci = {stream, universe, n, m, avg};
            return capture(&sssci);
        });
    }

    if(alg.compare("LSH") == 0 || alg.compare("all") == 0){
        summarise("capture", [&]() -> unordered_set<unsigned long>*{
            SSSCInput sssci = {stream, universe, n, m, avg};
            return capture(&sssci);
        });
    }

    if(alg.compare("Rosen") == 0 || alg.compare("all") == 0){
        summarise("sssc", [&]() -> unordered_set<unsigned long>*{
            SSSCInput sssci = {stream, universe, n, m, avg};
            return sssc(&sssci, string("run"));
        });
    }

    if(alg.compare("RobustRosen") == 0 || alg.compare("all") == 0){
        summarise("sssc", [&]() -> unordered_set<unsigned long>*{
            SSSCInput sssci = {stream, universe, n, m, avg};
            return sssc(&sssci, string("mrun1"));
        });
    }

    if(alg.compare("Rosen-DFG") == 0 || alg.compare("all") == 0 || alg.compare("pp") == 0){
        if(alg.compare("all") == 0 || alg.compare("pp") == 0){
            vector<string> types = {"run", "mrun1"};
            for(string type : types){
                summarise("Rosen-DFG-" + type, [&]() -> vector<unsigned long>*{
                    SSSCInput sssci = {stream, universe, n, m, avg};
                    return compose(&sssci, string("Rosen"), type);
                });
            }
        }
        else{
            string type = string(argv[4]);
            if(type.compare("run") == 0 || type.compare("mrun1") == 0 || type.compare("mrun2") == 0) {
                summarise("Rosen-DFG-" + type, [&]() -> vector<unsigned long>*{
                    SSSCInput sssci = {stream, universe, n, m, avg};
                    return compose(&sssci, string("Rosen"), type);
                });
            }
            if(type.compare("mrun") == 0){
                for(string type: {"mrun1", "mrun2"}){
                    summarise("Rosen-DFG-" + type, [&]() -> vector<unsigned long>*{
                        SSSCInput sssci = {stream, universe, n, m, avg};
                        return compose(&sssci, string("Rosen"), type);
                    });
                }
            }
        }
    }

    if(alg.compare("LSH-DFG") == 0 || alg.compare("all") == 0 || alg.compare("pp") == 0){
        summarise("LSH-DFG", [&]() -> vector<unsigned long>*{
            SSSCInput sssci = {stream, universe, n, m, avg};
            return compose(&sssci, string("LSH"), string("invalid"));
        });
    }

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






















#include "set-sampling.hpp"
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
    if(sol == nullptr) cout << "INVALID" << endl;
    else cout << "Solution size: " << sol->size() << endl;
    delete sol;
    cout << endl;
}

int main(int argc, char** argv){
	string filename = string(argv[1]);

    /* Stream* stream = new OnlineStream(filename); */
    Stream* stream = new OfflineStream(filename);
    vector<unsigned long>* universe = new vector<unsigned long>();
    unsigned long m, M, avg, largest;
    stream->get_universe(universe, &m, &avg, &largest, &M);
    unsigned long n = universe->size();
    SSSCInput sssci = {stream, universe, n, m, avg};

    /* float L = log2f(n); */
    float L = sqrt(n);
    /* float L = sqrt(n) * log2f(n); */
    /* float L = n; */
    summarise(filename + ".dat", [&]() -> vector<unsigned long>*{
        vector<unsigned long>* sol = SetSampling(&sssci, L);
        return sol;
    });
}


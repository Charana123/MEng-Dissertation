#include "sssc.hpp"
#include <chrono>

using namespace std;

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

void check(SSSCInput* sssci, unordered_set<unsigned long>* sol){
    vector<unsigned long> v;
    v.insert(v.begin(), sol->begin(), sol->end());
    sort(v.begin(), v.end(), std::greater<unsigned long>());

    set<unsigned long> actual_universe;
    for(HyperEdge* he; (he = sssci->stream->get_next_set()) != nullptr; ){
        if(he->i == v.back()) {
            actual_universe.insert(he->vertices.begin(), he->vertices.end());
            v.pop_back();
        }
    }
    cout << actual_universe.size() << endl;
    cout << sssci->universe->size() << endl;
    vector<unsigned long> diff;
    set_difference(sssci->universe->begin(), sssci->universe->end(), actual_universe.begin(), actual_universe.end(), std::inserter(diff, diff.end()));
    cout << diff << endl;
}

void parr(string filename){
    POfflineStream** streams = get_streams(filename, 28);
    cout << "here" << endl;
    vector<unsigned long>* universe = new vector<unsigned long>();
    unsigned long m, M, avg, median, largest;
    streams[0]->get_universe(universe, &m, &avg, &median, &largest, &M);
    unsigned long n = universe->size();
    PSSSCInput psssci = {streams, universe, n, m};
    cout << "here1" << endl;
    summarise(filename + ".dat", [&]() -> unordered_set<unsigned long>*{
        unordered_set<unsigned long>* sol = capture(&psssci, 28);
        return sol;
    });

}

void seqq(string filename){
    /* Stream* stream = new OfflineStream(filename); */
    Stream* stream = new OfflineStream("../dataset/FIMI/" + filename + ".dat");
    vector<unsigned long>* universe = new vector<unsigned long>();
    unsigned long m, M, avg, median, largest;
    stream->get_universe(universe, &m, &avg, &median, &largest, &M);
    unsigned long n = universe->size();
    SSSCInput sssci = {stream, universe, n, m, avg};

    /* cout << filename << endl; */
    /* cout << "==============" << endl; */
    /* cout << "n: " << n << endl; */
    /* cout << "m: " << m << endl; */
    /* cout << "M: " << M << endl; */
    /* cout << "avg: " << avg << endl; */
    /* cout << "median: " << median << endl; */
    /* cout << "largest: " << largest << endl; */
    /* cout << "==============" << endl; */

    summarise(filename + ".dat", [&]() -> unordered_set<unsigned long>*{
        unordered_set<unsigned long>* sol = sssc(&sssci);
        return sol;
    });
    summarise(filename + ".dat", [&]() -> unordered_set<unsigned long>*{
        unordered_set<unsigned long>* sol = capture(&sssci);
        return sol;
    });
}

int main(int argc, char** argv){
	string filename = string(argv[1]);
	vector<string> files = {"test", "chess", "retail", "pumsb", "kosarak", "webdocs"};
	for(string filename : files){
        /* parr(filename); */
        seqq(filename);
	}
}













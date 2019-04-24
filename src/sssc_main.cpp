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
    delete sol;
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

void parrstream(string filename){
}

void parr(string filename, int ts){
    POfflineStream** streams = get_streams("../dataset/FIMI/" + filename + ".dat", ts);
    cout << "here" << endl;
    vector<unsigned long>* universe = new vector<unsigned long>();
    unsigned long m, M, avg, largest;
    streams[0]->get_universe(universe, &m, &avg, &largest, &M);
    unsigned long n = universe->size();
    PSSSCInput psssci = {streams, universe, n, m};
    cout << "here1" << endl;

    /* summarise(filename + ".dat", [&]() -> unordered_set<unsigned long>*{ */
    /*     unordered_set<unsigned long>* sol = capture(&psssci, ts); */
    /*     return sol; */
    /* }); */

    summarise(filename + ".dat", [&]() -> unordered_set<unsigned long>*{
        unordered_set<unsigned long>* sol = sssc(&psssci, ts);
        return sol;
    });
}

void seqq(string filename){
    /* Stream* stream = new OfflineStream(filename); */
    Stream* stream = new OfflineStream("../dataset/FIMI/" + filename + ".dat");
    vector<unsigned long>* universe = new vector<unsigned long>();
    unsigned long m, M, avg, largest;
    stream->get_universe(universe, &m, &avg, &largest, &M);
    unsigned long n = universe->size();
    SSSCInput sssci = {stream, universe, n, m, avg};

    /* cout << filename << endl; */
    /* cout << "==============" << endl; */
    /* cout << "n: " << n << endl; */
    /* cout << "m: " << m << endl; */
    /* cout << "M: " << M << endl; */
    /* cout << "avg: " << avg << endl; */
    /* cout << "largest: " << largest << endl; */
    /* cout << "==============" << endl; */

    summarise(filename + ".dat", [&]() -> unordered_set<unsigned long>*{
        unordered_set<unsigned long>* sol = sssc(&sssci, string("run"));
        return sol;
    });
    /* summarise(filename + ".dat", [&]() -> unordered_set<unsigned long>*{ */
    /*     unordered_set<unsigned long>* sol = capture(&sssci); */
    /*     return sol; */
    /* }); */
    summarise(filename + ".dat", [&]() -> unordered_set<unsigned long>*{
        unordered_set<unsigned long>* sol = threshold_randomized_sssc(&sssci, largest);
        return sol;
    });
}

#include "rss.hpp"
int main(int argc, char** argv){
	/* string filename = string(argv[1]); */
    /* int ts = stoi(argv[2]); */
	vector<string> files = {"test", "chess", "retail", "pumsb", "kosarak", "webdocs"};
	for(string filename : files){
        /* parrstream(filename); */
        /* parr(filename, ts); */
        seqq(filename);
	}

    /* size_t peakSize = getPeakRSS(); */
    /* cout << "peakSize: " << peakSize << endl; */
    /* size_t currentSize = getCurrentRSS(); */
    /* cout << "currentSize: " << currentSize << endl; */
}













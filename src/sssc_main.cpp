#include "sssc.hpp"
#include <chrono>

using namespace std;

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

void check(SSSCInput* sssci, unordered_set<int>* sol){
    vector<int> v;
    v.insert(v.begin(), sol->begin(), sol->end());
    sort(v.begin(), v.end(), std::greater<int>());

    set<int> actual_universe;
    for(HyperEdge* he; (he = sssci->stream->get_next_set()) != nullptr; ){
        if(he->i == v.back()) {
            actual_universe.insert(he->vertices.begin(), he->vertices.end());
            v.pop_back();
        }
    }
    cout << actual_universe.size() << endl;
    cout << sssci->universe->size() << endl;
    vector<int> diff;
    set_difference(sssci->universe->begin(), sssci->universe->end(), actual_universe.begin(), actual_universe.end(), std::inserter(diff, diff.end()));
    cout << diff << endl;
}

int main(int argc, char** argv){
	string filename = string(argv[1]);
	/* vector<string> files = {"test", "chess", "retail", "pumsb", "kosarak", "webdocs"}; */
	/* vector<string> files = {"chess"}; */
	/* for(string filename : files){ */
        /* Stream* stream = new OfflineStream("../dataset/FIMI/" + filename + ".dat"); */
        Stream* stream = new OfflineStream("/Users/charana/Documents/thesis/papers/SCL/SPMF/" + filename);
        /* Stream* stream = new OfflineStream("/Users/charana/Documents/thesis/implementations/other/" + filename); */
        vector<int>* universe = new vector<int>();
        int m, M, avg, median, largest;
        stream->get_universe(universe, &m, &avg, &median, &largest, &M);
        int n = universe->size();
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

        summarise(filename + ".dat", [&]() -> unordered_set<int>*{
            unordered_set<int>* sol = sssc(&sssci);
            return sol;
        });
        summarise(filename + ".dat", [&]() -> unordered_set<int>*{
            unordered_set<int>* sol = capture(&sssci);
            return sol;
        });
	/* } */
}













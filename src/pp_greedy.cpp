#include "DFG.hpp"
#include "sssc.hpp"
#include "boost/range/algorithm/remove_if.hpp"
#include <chrono>

vector<int>* compose(OfflineStream* stream){

    vector<int>* universe = new vector<int>();
    int m, M, avg, median, largest;
    stream->get_universe(universe, &m, &avg, &median, &largest, &M);
    int n = universe->size();
    SSSCInput sssci = {stream, universe, n, m, avg};

    unordered_set<int>* sol = sssc(&sssci);
    vector<int> chosen(m, 0);
    for(int sid: *sol) chosen[sid] = 1;
    /* vector<Set>* sets = stream->sci->sets; */
    /* sets->erase( */
    /*     std::remove_if(sets->begin(), sets->end(), [&chosen](Set& s) -> bool{ */
    /*         return chosen[s.i] == 0; */
    /*     }), */
    /*     sets->end() */
    /* ); */
    vector<Set>* sets = new vector<Set>();
    for(Set* s; (s = sssci.stream->get_next_set()) != nullptr; ){
        if(chosen[s->i]) sets->push_back(*s);
    }

    int proj_m = sol->size();
    SetCoverInput* sci = new SetCoverInput{sets, universe, proj_m, n, -1, -1, -1, -1};
    vector<int>* final_sol = DFG(sci, 1.01);
    return final_sol;
}

void summarise(string name, std::function<vector<int>*()> func){
    auto t1 = chrono::high_resolution_clock::now();
    vector<int>* sol = func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "===========" << endl;
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    cout << "Solution size: " << sol->size() << endl;
}

int main(int argc, char** argv){
	vector<string> files = {"test", "chess", "retail", "pumsb", "kosarak", "webdocs"};
	/* vector<string> files = {"test"}; */
	for(string filename : files){
        cout << "filename: " << filename << endl;
        OfflineStream* stream = new OfflineStream("../dataset/FIMI/" + filename + ".dat");
        summarise(filename + ".dat", [&]() -> vector<int>*{
            vector<int>* sol = compose(stream);
            return sol;
        });
	}
}












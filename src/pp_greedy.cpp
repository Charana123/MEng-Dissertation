#include "DFG.hpp"
#include "sssc.hpp"
#include "boost/range/algorithm/remove_if.hpp"
#include <chrono>

vector<unsigned long>* compose(OfflineStream* stream){

    vector<unsigned long>* universe = new vector<unsigned long>();
    unsigned long m, M, avg, largest;
    stream->get_universe(universe, &m, &avg, &largest, &M);
    unsigned long n = universe->size();
    SSSCInput sssci = {stream, universe, n, m, avg};

    unordered_set<unsigned long>* sol = sssc(&sssci);
    vector<bool> chosen(m, 0);
    for(unsigned long sid: *sol) chosen[sid] = true;
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

    unsigned long proj_m = sol->size();
    SetCoverInput* sci = new SetCoverInput{sets, universe, proj_m, n, 0, 0, 0};
    vector<unsigned long>* final_sol = DFG(sci, 1.05);
    return final_sol;
}

void summarise(string name, std::function<vector<unsigned long>*()> func){
    auto t1 = chrono::high_resolution_clock::now();
    vector<unsigned long>* sol = func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "===========" << endl;
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    cout << "Solution size: " << sol->size() << endl;
}

int main(int argc, char** argv){
    string filename = string(argv[1]);
	/* vector<string> files = {"test", "chess", "retail", "pumsb", "kosarak", "webdocs"}; */
	/* vector<string> files = {"test"}; */
	/* for(string filename : files){ */
        cout << "filename: " << filename << endl;
        OfflineStream* stream = new OfflineStream("../dataset/FIMI/" + filename + ".dat");
        summarise(filename + ".dat", [&]() -> vector<unsigned long>*{
            return compose(stream);
        });
	/* } */
}












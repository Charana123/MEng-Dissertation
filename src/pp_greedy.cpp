#include "DFG.hpp"
#include "sssc.hpp"
#include <chrono>

vector<int>* compose(OfflineStream* stream){

    vector<int>* universe = new vector<int>();
    int m, avg, M;
    stream->get_universe(universe, &m, &avg, &M);
    int n = universe->size();
    SSSCInput sssci = {stream, universe, n, m, avg};


    unordered_set<int>* sol = sssc(&sssci);
    /* cout << "sol: " << sol->size() << endl; */
    vector<Set>* sets = stream->sci->sets;
    vector<Set>* projected_sets = new vector<Set>();
    for(int sid : *sol) projected_sets->push_back((*sets)[sid]);
    /* cout << *sets << endl; */
    /* cout << *projected_sets << endl; */

    int proj_m = sol->size();
    SetCoverInput* sci = new SetCoverInput{projected_sets, universe, proj_m, n, avg, M};
    vector<int>* final_sol = DFG(sci, 1.05);
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
	for(string filename : files){
        cout << "filename: " << filename << endl;
        OfflineStream* stream = new OfflineStream("../dataset/FIMI/" + filename + ".dat");
        summarise(filename + ".dat", [&]() -> vector<int>*{
            vector<int>* sol = compose(stream);
            return sol;
        });
	}
}












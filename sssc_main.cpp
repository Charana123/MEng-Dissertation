#include "sssc.hpp"
#include <chrono>

using namespace std;

void summarise(string name, std::function<void()> func){
    auto t1 = chrono::high_resolution_clock::now();
    func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "===========" << endl;
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    cout << endl;
}

int main(int argc, char** argv){
	// string filename = string(argv[1]);
	/* vector<string> files = {"test", "chess", "retail", "pumsb", "kosarak"}; */
    vector<string> files = {"webdocs"};
	for(string filename : files){
		Stream* stream = new Stream("./dataset/FIMI/" + filename + ".dat");
		set<int>* universe = new set<int>();
		int m;
		stream->get_universe(universe, &m);
		int n = universe->size();
		SSSCInput sssci = {stream, universe};

		/* map<int,int>* eid = sssc(&sssci); */
		/* set<int> sol; */
		/* for(auto e : *eid) sol.insert(e.second); */
		/* cout << sol.size() << endl; */

		/* vector<int> v; */
		/* v.insert(v.begin(), sol.begin(), sol.end()); */
		/* sort(v.begin(), v.end(), std::greater<int>()); */

		/* set<int> actual_universe; */
		/* for(HyperEdge* he; (he = stream->get_next_set()) != nullptr; ){ */
		/*     if(he->i == v.back()) { */
		/*         actual_universe.insert(he->vertices.begin(), he->vertices.end()); */
		/*         v.pop_back(); */
		/*     } */
		/* } */
		/* cout << actual_universe.size() << endl; */
		/* cout << universe->size() << endl; */
		/* vector<int> diff; */
		/* set_difference(universe->begin(), universe->end(), actual_universe.begin(), actual_universe.end(), std::inserter(diff, diff.end())); */
		/* cout << diff << endl; */

		summarise(filename + ".dat", [&sssci]() -> void{
			map<int,int>* eid = sssc(&sssci);
			set<int> sol;
			for(auto e : *eid) sol.insert(e.second);
            /* cout << sol << endl; */
			cout << "Solution size: " << sol.size() << endl;
		});
	}
}






















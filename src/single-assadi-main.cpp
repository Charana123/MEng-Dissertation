#include "single-assadi.hpp"

void summarise(string name, int alpha, std::function<vector<int>*()> func){
    auto t1 = chrono::high_resolution_clock::now();
    vector<int>* sol = func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "===========" << endl;
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;

    cout << "Solution size: " << sol->size() * alpha << endl;
    cout << endl;
}

int main(){
	/* string filename = string(argv[1]); */
	vector<string> files = {"test", "chess", "retail", "pumsb", "kosarak", "webdocs"};
	/* vector<string> files = {"test"}; */
	/* vector<string> files = {"webdocs"}; */
	for(string filename : files){
        Stream* stream = new OfflineStream("../dataset/FIMI/" + filename + ".dat");
        vector<int>* universe = new vector<int>();
        int m, M, avg, median, largest;
        stream->get_universe(universe, &m, &avg, &median, &largest, &M);
        int n = universe->size();
        SSInput ssi = {stream, universe, n, m};

        /* int alpha = sqrt(n); */
        /* int alpha = sqrt(n) / log(n); */
        int alpha = log(n);
        summarise(filename + ".dat", alpha, [&]() -> vector<int>*{
            return single_sublinear(&ssi, alpha);
        });
	}
}














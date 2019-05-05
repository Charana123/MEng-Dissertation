#include "sp-assadi.hpp"

void summarise(string name, unsigned long alpha, std::function<vector<unsigned long>*()> func){
    auto t1 = chrono::high_resolution_clock::now();
    vector<unsigned long>* sol = func();
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
        vector<unsigned long>* universe = new vector<unsigned long>();
        unsigned long m, M, avg, largest;
        stream->get_universe(universe, &m, &avg, &largest, &M);
        unsigned long n = universe->size();
        SPAInput ssi = {stream, universe, n, m};

        /* unsigned long alpha = sqrt(n); */
        /* unsigned long alpha = sqrt(n) / log(n); */
        unsigned long alpha = log(n);
        summarise(filename + ".dat", alpha, [&]() -> vector<unsigned long>*{
            return single_sublinear(&ssi, alpha);
        });

        // log(n.log(n)) < sqrt(n)
	}
}














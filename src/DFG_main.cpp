#include "DFG.hpp"
#include <string>
#include <chrono>

using namespace std;
float p = 1.05;

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

	/* string filename = string(argv[1]); */
	vector<string> files = {"test", "chess", "retail", "pumsb", "kosarak", "webdocs"};
    for(string filename : files){
        SetCoverInput* sci = read_sci("../dataset/FIMI/" + filename + ".dat");
        cout << "here" << endl;
        /* SetCoverInput* sci = read_sci("/Users/charana/Documents/thesis/papers/SCL/SPMF/" + filename); */
        summarise(filename + ".dat", [&]() -> vector<unsigned long>*{
            return DFG(sci, p);
        });
    }
}

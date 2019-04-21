#include "DFG.hpp"
#include <string>
#include <chrono>

using namespace std;
/* float p = 1.1; */
/* float p = 1.05; */
float margin = 0.05;

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
	vector<string> files = {"test", "chess", "retail", "pumsb", "kosarak", "webdocs"};
    for(string filename : files){
        SetCoverInput* sci = read_sci("../dataset/FIMI/" + filename + ".dat");
        /* for(int i = 0; i < 10; i++){ */
            /* margin = margin / 2; */
            summarise(filename + ", p: " + to_string(1.0+margin), [&]() -> vector<unsigned long>*{
                return DFG(sci, 1.0+margin);
            });
        /* } */
    }
}

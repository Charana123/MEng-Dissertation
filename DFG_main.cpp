#include "DFG.hpp"
#include <string>
#include <chrono>

using namespace std;
float p = 2;

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

	string filename = string(argv[1]);
    SetCoverInput* sci = read_sci("./dataset/FIMI/" + filename + ".dat");
    summarise("test.dat", [&]() -> void{
        vector<int>* sol = DFG(sci, p);
        cout << "Solution size: " << sol->size() << endl;
    });
}

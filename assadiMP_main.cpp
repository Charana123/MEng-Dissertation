#include "assadiMP.hpp"
#include <string>
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

	string filename = string(argv[1]);
    Stream* stream = new Stream("./dataset/FIMI/" + filename + ".dat");
    set<int>* universe = new set<int>();
    int m;
    stream->get_universe(universe, &m);
    int n = universe->size();
    int epsilon = 1;
    int alpha = 5;
    AssadiMPInput* assadiMPInput = new AssadiMPInput{epsilon, alpha, stream, m, universe, n};
    summarise("test.dat", [&]() -> void{
        set<int>* sol = assadiMP(assadiMPInput);
        cout << "Solution size: " << sol->size() << endl;
    });
}

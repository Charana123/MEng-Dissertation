#include "rfgreedy.hpp"
#include <iostream>
#include <string>
#include <chrono>

using namespace std;
float p = 1.05;

void summarise(string name, std::function<SetCoverOutput()> func){
    auto t1 = chrono::high_resolution_clock::now();
    SetCoverOutput sco = func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "===========" << endl;
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    cout << "universe size: " << sco.C.vertices.size() << endl;
    cout << "solution size: " << sco.Sigma.size() << endl;
    cout << endl;
}

float q = 1.05;
int main(){

    SetCoverInput sci = read_problem("./dataset/test.dat");
    summarise("test.dat", [&]() -> SetCoverOutput{
        return rfgreedy(sci, q);
    });

    sci = read_problem("./dataset/chess.dat");
    summarise("chess.dat", [&]() -> SetCoverOutput{
        return rfgreedy(sci, q);
    });

    sci = read_problem("./dataset/pumsb.dat");
    summarise("pumsb.dat", [&]() -> SetCoverOutput{
        return rfgreedy(sci, q);
    });

    sci = read_problem("./dataset/kosarak.dat");
    summarise("kosarak.dat", [&]() -> SetCoverOutput{
        return rfgreedy(sci, q);
    });

}








#include "DFG.hpp"
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

int main(){

    SetCoverInput test_sci = read_problem("./dataset/test.dat");
    map<int, vector<Set>> ktoCollection = OrderBySubCollection(test_sci, p);
    summarise("test.dat", [&]() -> SetCoverOutput{
        return DFG(ktoCollection, p);
    });

    SetCoverInput chess_sci = read_problem("./dataset/chess.dat");
    ktoCollection = OrderBySubCollection(chess_sci, p);
    summarise("chess.dat", [&]() -> SetCoverOutput{
        return DFG(ktoCollection, p);
    });

    SetCoverInput pumsb_sci = read_problem("./dataset/pumsb.dat");
    ktoCollection = OrderBySubCollection(pumsb_sci, p);
    summarise("pumsb.dat", [&]() -> SetCoverOutput{
        return DFG(ktoCollection, p);
    });

    SetCoverInput kosarak_sci = read_problem("./dataset/kosarak.dat");
    ktoCollection = OrderBySubCollection(kosarak_sci, p);
    summarise("kosarak.dat", [&]() -> SetCoverOutput{
        return DFG(ktoCollection, p);
    });

}








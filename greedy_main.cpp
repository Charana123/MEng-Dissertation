#include "greedy.hpp"
#include <iostream>
#include <string>
#include <chrono>

using namespace std;
float p = 1.05;

void summarise(string name, std::function<SetCoverOutput*()> func){
    auto t1 = chrono::high_resolution_clock::now();
    SetCoverOutput* sco = func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "===========" << endl;
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    cout << "universe size: " << sco->C->size() << endl;
    cout << "solution size: " << sco->Sigma->size() << endl;
    cout << endl;
}

int main(){

    /* SetCoverInput* sci = read_sci("./dataset/test.dat"); */
    /* summarise("test.dat", [&]() -> SetCoverOutput*{ */
    /*     return greedy(sci); */
    /* }); */

    SetCoverInput* sci = read_sci("./dataset/chess.dat");
    /* summarise("chess.dat", [&]() -> SetCoverOutput*{ */
    greedy(sci);
    /* }); */

    /* sci = read_sci("./dataset/retail.dat"); */
    /* summarise("retail.dat", [&]() -> SetCoverOutput*{ */
    /*     return greedy(sci); */
    /* }); */

    /* sci = read_sci("./dataset/pumsb.dat"); */
    /* summarise("pumsb.dat", [&]() -> SetCoverOutput*{ */
    /*     return greedy(sci); */
    /* }); */

    /* sci = read_sci("./dataset/kosarak.dat"); */
    /* summarise("kosarak.dat", [&]() -> SetCoverOutput*{ */
    /*     return greedy(sci); */
    /* }); */

}








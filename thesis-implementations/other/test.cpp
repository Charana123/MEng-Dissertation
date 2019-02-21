#include <fstream>
#include <string>
#include <chrono>
#include "../gp_utils.hpp"

using namespace std;
string file_path = "../dataset/kosarak.dat";

int counter = 0;
void parse_line(string line, Set& s){
    boost::tokenizer<> tok(line);
    for(auto beg=tok.begin(); beg!=tok.end(); ++beg){
        s.vertices.insert(std::stoi(*beg));
    }
    s.i = counter++;
}

void time(string name, std::function<void()> func){
    auto t1 = chrono::high_resolution_clock::now();
    func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "===========" << endl;
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    cout << endl;
}

int main(){
    time("input file stream", []() -> void{
        std::ifstream ifs(file_path);
        for(string line; getline(ifs, line); ){
            Set s;
            parse_line(line, s);
            /* delete s; */
        }
    });
}

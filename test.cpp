#include "ssc_utils.hpp"
#include <chrono>

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
    summarise("time read: " + filename, [&]() -> void{
        for(Set* s; (s = stream->get_next_set()) != nullptr; ){
        }
    });
}

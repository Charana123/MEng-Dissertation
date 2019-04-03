#include "exact.hpp"
#include <string>
#include <chrono>

using namespace std;
float p = 1.05;

void summarise(string name, std::function<int()> func){
    auto t1 = chrono::high_resolution_clock::now();
    int optimal_solution_size = func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "===========" << endl;
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    cout << "Optimal Solution: " << optimal_solution_size << endl;
}

int main(int argc, char** argv){

	string filename = string(argv[1]);
	/* vector<string> files = {"test", "chess", "retail", "pumsb", "kosarak", "webdocs"}; */
    /* for(string filename : files){ */
        SetCoverInput* sci = read_sci(filename);
        /* SetCoverInput* sci = read_sci(filepath); */
        summarise(filename + ".dat", [&]() -> int{
            return exact(sci);
        });
    /* } */
}

#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <omp.h>
#include <functional>
#include <chrono>

using namespace std;

void summarise(string name, std::function<void()> func){
    auto t1 = chrono::high_resolution_clock::now();
    func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    cout << endl;
}

int main(int argc, char** argv){

    const string outpath = string(argv[1]);
    const unsigned long N = stoi(string(argv[2]));
    const float density = stof(string(argv[3]));

    summarise("generate graph", [=]() -> void{
        // Randomness
        vector<unsigned long>* S = new vector<unsigned long>[N];
        const unsigned long block = N / 28;
        #pragma omp parallel for
        for(int t = 0; t < 28; t++){
            std::random_device dev;
            std::mt19937 gen(dev());
            std::uniform_real_distribution<float> real_distribution(0.0, 1.0);

            for(unsigned long i = t * block; i < (t+1)*block; i++){
                for(unsigned long j = 0; j < N; j++){
                    if(real_distribution(gen) < density) S[i].push_back(j);
                }
            }
        }
        std::ofstream outfile(outpath);
        for(int i = 0; i < N; i++){
            int J = (S+i)->size();
            for(int j = 0; j < J; j++){
                outfile << (S+i)->at(j) << " ";
            }
            outfile << endl;
        }
    });
}











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
    cout << density << endl;

    summarise("generate graph", [=]() -> void{
        // Randomness
        const unsigned long block = N / 28;
        #pragma omp parallel for
        for(int t = 0; t < 28; t++){
            std::random_device dev;
            std::mt19937 gen(dev());
            std::uniform_real_distribution<float> real_distribution(0.0, 1.0);

            std::ofstream outfile(outpath + "." + to_string(t));
            vector<unsigned long> s;
            for(unsigned long i = t * block; i < (t+1)*block; i++){
                for(unsigned long j = 0; j < N; j++){
                    if(real_distribution(gen) < density) s.push_back(j);
                }
                int J = s.size();
                if(J == 0) continue;
                for(int j = 0; j < J; j++) outfile << s.at(j) << " ";
                s.clear();
                outfile << endl;
            }
        }

        // Merge files
        std::ofstream outfile(outpath);
        for(int t = 0; t < 28; t++){
            std::ifstream infile(outpath + "." + to_string(t), std::ios_base::binary);
            outfile << infile.rdbuf();
            remove((outpath + "." + to_string(t)).c_str());
        }
    });
}



















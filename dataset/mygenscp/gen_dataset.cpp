#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <omp.h>

using namespace std;

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  if ( !v.empty() ) {
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, " "));
  }
  return out;
}

int main(int argc, char** argv){

    string outpath = string(argv[1]);
    unsigned long long N = stoi(string(argv[2]));
    float density = stof(string(argv[3]));

    // Randomness
    std::random_device dev;
    /* std::mt19937 gen(dev()); */
    std::default_random_engine gen(dev());
    std::uniform_real_distribution<float> real_distribution(0.0, 1.0);

    std::ofstream outfile(outpath);
    for(unsigned long i = 0; i < N; i++){
        vector<vector<unsigned long>> S;
        for(unsigned long j = 0; j < N; j++){
            if(real_distribution(gen) < density) s.push_back(j);
        }
    }
    outfile << s << endl;
}











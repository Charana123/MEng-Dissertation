#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <fstream>

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
    unsigned long long M = stoi(string(argv[3]));
    float density = stof(string(argv[4]));
    int significance = stoi(string(argv[5]));

    // Randomness
    std::random_device dev;
    std::mt19937 gen(dev());
    unsigned long long maxi = std::pow(10, significance);
    std::uniform_int_distribution<unsigned long long> int_distribution(0, maxi-1);


    std::ofstream outfile(outpath);
    unsigned long long threshold = density * maxi;
    for(unsigned long i = 0; i < M; i++){
        vector<unsigned long> s;
        for(unsigned long j = 0; j < N; j++){
            if(int_distribution(gen) < threshold) s.push_back(j);
        }
        outfile << s << endl;
    }
}












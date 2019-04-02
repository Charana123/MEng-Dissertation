#include <string>
#include <vector>
#include <random>
#include <algorithm>
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
    unsigned long N = stoi(string(argv[2]));
    unsigned long M = stoi(string(argv[3]));
    float density = stof(string(argv[4]));

    // Randomness
    std::random_device dev;
    std::mt19937 gen(dev());
    std::normal_distribution<unsigned long> guassian(density * N, 2);

    std::ofstream outfile(outpath);
    std::vector<unsigned long > universe;
    for(int i = 0; i < N; i++) universe.push_back(i);
    for(unsigned long i = 0; i < M; i++){
        vector<unsigned long> s;
        std::sample(universe.begin(), universe.end(), std::back_inserter(s), guassian(gen), gen);
        outfile << s << endl;
    }
}












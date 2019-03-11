#include <string>
#include <boost/range/irange.hpp>
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

unsigned long gig_to_elements = 2.5 * pow(10, 8);
int main(int argc, char** argv){

    float gigs = stof(string(argv[1]));
    float avg = stoi(string(argv[2]));
    string out_filename = string(argv[3]);


    unsigned long m, n, M;
    M = gigs * gig_to_elements;
    m = n = M/avg;

    vector<unsigned long> universe;
    for(unsigned long i = 0; i < n; i++) universe.push_back(i);

    // Randomness
    std::random_device dev;
    /* std::mt19937 rng(dev()); */
    std::default_random_engine rng(dev());
    std::uniform_int_distribution<unsigned long> dist_n(0,n-1);
    std::uniform_int_distribution<int> dist_avg(1,avg);

    std::ofstream outfile;
    outfile.open(out_filename);

    for(unsigned long i = 0; i < m-1; i++){
        int size = dist_avg(rng);
        vector<unsigned long> s;
        for(int i = 0; i < size; i++) {
            unsigned long v = dist_n(rng);
            s.push_back(v);
        }
        outfile << s << endl;
    }
}










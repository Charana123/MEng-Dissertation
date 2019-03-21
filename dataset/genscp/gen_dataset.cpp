#include <string>
#include <boost/range/irange.hpp>
#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  if ( !v.empty() ) {
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, " "));
  }
  return out;
}

static unsigned long x=123456789, y=362436069, z=521288629;
//period 2^96-1
unsigned long xorshf96(void) {
    unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;

    return z;
}

int main(int argc, char** argv){

    unsigned long long n = stoll(string(argv[1]));
    unsigned long long m = stoi(string(argv[2]));
    float density = stof(string(argv[3]));
    unsigned long long avg = n * density;
    unsigned long long noise = n * (density * 0.1);
    string fout = string(argv[4]);

    vector<unsigned long> universe;
    for(unsigned long i = 0; i < n; i++) universe.push_back(i);

    // Randomness
    std::random_device dev;
    /* std::mt19937 rng(dev()); */
    std::default_random_engine rng(dev());
    std::uniform_int_distribution<unsigned long long> dist_avg(avg-noise, avg+noise);
    std::vector<unsigned long long> covered(n);

    std::ofstream out;
    out.open(fout);

    out << n << " " << m << endl;
    for(unsigned long long i = 0; i < m-1; i++){
        int size = dist_avg(rng);
        vector<unsigned long long> s;
        /* cout << "here" << endl; */
        /* std::shuffle(universe.begin(), universe.end(), rng); */
        /* s.insert(s.begin(), universe.begin(), universe.begin()+size); */
        std::sample(universe.begin(), universe.end(), std::back_inserter(s), size, rng);
        for(int v : s) covered[v] = 1;
        out << s << endl;
    }

    std::vector<unsigned long long> s;
    for(int i = 0; i < n; i++) if(covered[i] == 0) s.push_back(i);
    if(s.size() > 0) out << s << endl;
}











#include "iter_set_cover.hpp"


int main(int argc, char** argv){
	string filename = string(argv[1]);
    Stream* stream = new Stream("./dataset/FIMI/" + filename + ".dat");
    set<int>* universe = new set<int>();
    int m;
    stream->get_universe(universe, &m);
    cout << "m: " << m << endl;
    int n = universe->size();
    int c = 10;
    float accuracy_delta = 0.1;
    IterSetCoverInput* isci = new IterSetCoverInput{stream, universe, n, m, accuracy_delta, c};

    /* int k = 1; */
    /* int sample_size = c * log2f(n) * k * powf(n, accuracy_delta) * log2f(n) * log2f(m); */
    /* cout << "n: " << n << endl; */
    /* cout << isci->c << " " << log2f(n) << " " << k << " " << powf(isci->n, isci->accuracy_delta) << " " << log2f(isci->n) << " " << log2f(isci->m) << " " << endl; */
    /* cout << "sample_size: " << sample_size << endl; */
    /* unsigned long threshold = sample_size / k; */
    /* cout << "threshold: " << threshold << endl; */

    set<int>* sol = iter_set_cover(isci);
    /* cout << *sol << endl; */
    cout << "solution size: " << sol->size() << endl;

    vector<int> v;
    v.insert(v.begin(), sol->begin(), sol->end());
    sort(v.begin(), v.end(), std::greater<int>());
    set<int> actual_universe;
    for(Set* s; (s = stream->get_next_set()) != nullptr; ){
        if(s->i == v.back()) {
            actual_universe.insert(s->vertices.begin(), s->vertices.end());
            v.pop_back();
        }
    }
    cout << actual_universe.size() << endl;
    stream->get_universe(universe, &m);
    cout << universe->size() << endl;

}

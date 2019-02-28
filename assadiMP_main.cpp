#include "assadiMP.hpp"
#include <string>
#include <chrono>

using namespace std;

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
    /* vector<string> files = {"test", "chess", "pumsb", "retail", "kosarak"}; */
    /* for(string filename : files){ */
        Stream* stream = new Stream("./dataset/FIMI/" + filename + ".dat");
        set<int>* universe = new set<int>();
        int m;
        stream->get_universe(universe, &m);
        int n = universe->size();
        int epsilon = 1;
        int alpha = 3;
        AssadiMPInput* assadiMPInput = new AssadiMPInput{epsilon, alpha, stream, m, universe, n};
        summarise(filename + ".dat", [&]() -> void{
            set<int>* sol = assadiMP(assadiMPInput);
            cout << "Solution size: " << sol->size() << endl;
        });
    /* } */

	/* string filename = string(argv[1]); */
    /* int epsilon = 1; */
    /* int alpha = 1; */
    /* for(int i = 0; i < 5; i+=4){ */
        /* epsilon += i; */
        /* for(int j = 0; j < 5; j+=4){ */
            /* alpha += j; */

            /* cout << "epsilon: " << epsilon << "alpha: " << alpha << endl; */
            /* Stream* stream = new Stream("./dataset/FIMI/" + filename + ".dat"); */
            /* set<int>* universe = new set<int>(); */
            /* int m; */
            /* stream->get_universe(universe, &m); */
            /* int n = universe->size(); */
            /* AssadiMPInput* assadiMPInput = new AssadiMPInput{epsilon, alpha, stream, m, universe, n}; */
            /* summarise(filename + ".dat", [&]() -> void{ */
                /* set<int>* sol = assadiMP(assadiMPInput); */
                /* cout << "Solution size: " << sol->size() << endl; */
            /* }); */
        /* } */
    /* } */

    /* cout << m << " " << n << endl; */
    /* int i = 1; */
    /* int opt_tilda = powf(2, i * assadiMPInput->epsilon); */
    /* cout << "opt_tilda: " << opt_tilda << endl; */
    /* float p = 16 * opt_tilda * logf(assadiMPInput->m) * powf(assadiMPInput->n, 1/assadiMPInput->alpha - 1); */
    /* cout << "p: " << p << endl; */
    /* int sample_size = p * n; */
}























#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "prettyprint.hpp"
#include "sc_utils.hpp"
#include "DFG.hpp"
#include <boost/range/irange.hpp>

using namespace std;
float p = 2;

/* TEST_CASE("test.dat", "" ) { */
/*     SetCoverInput* sci = read_sci("./dataset/FIMI/test.dat"); */

/*     vector<float>* p_pow_k = new vector<float>(); */
/*     vector<vector<Set*>>* ktoCollection = new vector<vector<Set*>>(); */
/*     OrderBySubCollection(sci, p, p_pow_k, ktoCollection); */
/*     /1* SECTION("covered vertices equals universe"){ *1/ */
/*     /1*     map<int, vector<Set>> actual_ktoCollection; *1/ */
/*     /1*     actual_ktoCollection[1].push_back({{1,2}, 0}); *1/ */
/*     /1*     actual_ktoCollection[2].push_back({{2,3,4,5}, 1}); *1/ */
/*     /1*     actual_ktoCollection[3].push_back({{6, 7, 8, 9, 10, 11, 12, 13}, 2}); *1/ */
/*     /1*     actual_ktoCollection[2].push_back({{1, 3, 5, 7, 9, 11, 13}, 3}); *1/ */
/*     /1*     actual_ktoCollection[2].push_back({{2, 4, 6, 8, 10, 12, 13}, 4}); *1/ */
/*     /1*     REQUIRE(*ktoCollection ==  actual_ktoCollection); *1/ */
/*     /1* } *1/ */

/*     vector<int>* sol = DFG(sci, p); */

/*     set<int> actual_universe; */
/*     auto rg = boost::irange(1, 14); */
/*     actual_universe.insert(rg.begin(), rg.end()); */

/*     SECTION("covered vertices equals universe"){ */
/*         REQUIRE(*sco->C == actual_universe); */
/*     } */

/*     SECTION("chosen sets cover universe"){ */
/*         set<int> universe; */
/*         for(int i : *sco->Sigma) universe.insert((*sci->sets)[i].vertices.begin(), (*sci->sets)[i].vertices.end()); */
/*         REQUIRE(universe ==  actual_universe); */
/*     } */
/* } */


TEST_CASE("pumsb.dat", "" ) {
    SetCoverInput* sci = read_sci("./dataset/FIMI/kosarak.dat");
    vector<int>* sol = DFG(sci, p);

    SECTION("chosen sets cover universe"){
        set<int> actual_universe_s;
        for(int i : *sol) actual_universe_s.insert((*sci->sets)[i].vertices.begin(), (*sci->sets)[i].vertices.end());
        vector<int> actual_universe(actual_universe_s.begin(), actual_universe_s.end());
        REQUIRE(*sci->universe == actual_universe);
    }
}

/* int main(){ */
/*     /1* SetCoverInput chess_scp = read_problem("./dataset/test.dat"); *1/ */
    /* for(Set set : chess_scp.sets){ */
/*     /1*     for(int vertex: set.vertices) cout << vertex; *1/ */
/*     /1*     cout << "-" << set.i << endl; *1/ */
/*     /1* } *1/ */

/*     SetCoverInput test_sci = read_problem("./dataset/test1.dat"); */
/*     map<int, vector<Set>> ktoCollection = OrderBySubCollection(test_sci.sets, 2); */
/*     cout << ktoCollection << endl; */
/* } */











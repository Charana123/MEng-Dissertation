#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "prettyprint.hpp"
#include "sc_utils.hpp"
#include "DFG.hpp"
#include <boost/range/irange.hpp>

using namespace std;
float p = 2;

TEST_CASE("test.dat", "" ) {
    SetCoverInput* sci = read_sci("./dataset/FIMI/test.dat");

    map<int, vector<Set>>* ktoCollection = OrderBySubCollection(sci, p);
    SECTION("covered vertices equals universe"){
        map<int, vector<Set>> actual_ktoCollection;
        actual_ktoCollection[1].push_back({{1,2}, 0});
        actual_ktoCollection[2].push_back({{2,3,4,5}, 1});
        actual_ktoCollection[3].push_back({{6, 7, 8, 9, 10, 11, 12, 13}, 2});
        actual_ktoCollection[2].push_back({{1, 3, 5, 7, 9, 11, 13}, 3});
        actual_ktoCollection[2].push_back({{2, 4, 6, 8, 10, 12, 13}, 4});
        REQUIRE(*ktoCollection ==  actual_ktoCollection);
    }

    SetCoverOutput* sco = DFG(ktoCollection, p);

    set<int> actual_universe;
    auto rg = boost::irange(1, 14);
    actual_universe.insert(rg.begin(), rg.end());

    SECTION("covered vertices equals universe"){
        REQUIRE(*sco->C == actual_universe);
    }

    SECTION("chosen sets cover universe"){
        set<int> universe;
        for(int i : *sco->Sigma) universe.insert((*sci->sets)[i].vertices.begin(), (*sci->sets)[i].vertices.end());
        REQUIRE(universe ==  actual_universe);
    }
}


TEST_CASE("pumsb.dat", "" ) {
    SetCoverInput* sci = read_sci("./dataset/FIMI/pumsb.dat");

    map<int, vector<Set>>* ktoCollection = OrderBySubCollection(sci, p);
    SetCoverOutput* sco = DFG(ktoCollection, p);

    SECTION("chosen sets cover universe"){
        set<int> universe;
        for(int i : *sco->Sigma) universe.insert((*sci->sets)[i].vertices.begin(), (*sci->sets)[i].vertices.end());
        REQUIRE(universe == *sco->C);
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











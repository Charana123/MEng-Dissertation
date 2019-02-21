#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "prettyprint.hpp"
#include "utils.hpp"
#include "greedy.hpp"
#include <boost/range/irange.hpp>

using namespace std;
float p = 1.05;

TEST_CASE("test.dat", "" ) {
    SetCoverInput sci = read_problem("./dataset/test.dat");
    SetCoverOutput sco = greedy(sci);

    set<int> actual_universe;
    auto rg = boost::irange(1, 14);
    actual_universe.insert(rg.begin(), rg.end());

    SECTION("covered vertices equals universe"){
        REQUIRE(sco.C.vertices ==  actual_universe);
    }

    SECTION("chosen sets cover universe"){
        set<int> universe;
        cout << "Sigma: " << sco.Sigma << endl;
        for(int i : sco.Sigma) universe.insert(sci.sets[i].vertices.begin(), sci.sets[i].vertices.end());
        REQUIRE(universe ==  actual_universe);
    }
}


TEST_CASE("pumsb.dat", "" ) {
    SetCoverInput sci = read_problem("./dataset/chess.dat");
    SetCoverOutput sco = greedy(sci);

    SECTION("chosen sets cover universe"){
        set<int> universe;
        for(int i : sco.Sigma) universe.insert(sci.sets[i].vertices.begin(), sci.sets[i].vertices.end());
        REQUIRE(universe ==  sco.C.vertices);
    }
}




#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "utils.hpp"
#include "DFG.hpp"
#include <boost/range/irange.hpp>

using namespace std;

/* TEST_CASE( "utils", "" ) { */
/*     SetCoverInput chess_sci = read_problem("./dataset/test.dat"); */

/*     SECTION("univere calculation"){ */
/*         set<int> actual_universe; */
/*         boost::push_back(actual_universe, boost::irange(1, 6)); */
/*         REQUIRE(chess_sci.universe.vertices ==  actual_universe); */
/*     } */

/*     SECTION("sets calculation"){ */
/*         vector<Set> actual_sets; */
/*         actual_sets.push_back({{1,2,3}, 0}); */
/*         actual_sets.push_back({{2,4}, 1}); */
/*         actual_sets.push_back({{3,4}, 2}); */
/*         actual_sets.push_back({{4,5}, 3}); */
/*         REQUIRE(chess_sci.sets == actual_sets); */
/*     } */
/* } */

TEST_CASE( "set_cover", "" ) {
    SetCoverOutput test_sco = DFG("./dataset/chess.dat", 2);

    SECTION("covered vertices equals universe"){
        set<int> actual_universe;
        auto rg = boost::irange(1, 76);
        actual_universe.insert(rg.begin(), rg.end());
        REQUIRE(test_sco.C.vertices ==  actual_universe);
    }

    /* SECTION("optimal solution found"){ */
    /*     vector<int> opt_sol = {0,3}; */
    /*     REQUIRE(test_sco.Sigma == opt_sol); */
    /* } */
}

/* int main(){ */
/*     SetCoverInput chess_scp = read_problem("./dataset/test.dat"); */
/*     for(Set set : chess_scp.sets){ */
/*         for(int vertex: set.vertices) cout << vertex; */
/*         cout << "-" << set.i << endl; */
/*     } */

/* } */

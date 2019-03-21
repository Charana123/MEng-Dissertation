#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "prettyprint.hpp"
#include "ssc_utils.hpp"
#include "pgreedy.hpp"
#include <boost/range/irange.hpp>

TEST_CASE("test.dat", "" ) {

    // Test - read and store sets from stream, compare all sets
    Stream stream("./dataset/test.dat");

    vector<Set> original_sets;
    original_sets.push_back({{1, 2}, 0});
    original_sets.push_back({{2, 3, 4, 5}, 1});
    original_sets.push_back({{6, 7, 8, 9, 10, 11, 12, 13}, 2});
    original_sets.push_back({{1, 3, 5, 7, 9, 11, 13}, 3});
    original_sets.push_back({{2, 4, 6, 8, 10, 12, 13}, 4});

    vector<Set> actual_sets;
    SECTION("sets"){

        for(Set s; stream.get_next_set(s) != -1; s = {}){
            actual_sets.push_back(s);
        }
        stream.reset();

        REQUIRE(actual_sets == original_sets);
    }

    SECTION("m"){
        int actual_m = stream.get_m();
        int original_m = original_sets.size();
        stream.reset();
        REQUIRE(actual_m == original_m);
    }

    SECTION("universe"){
        set<int> original_universe;
        auto rg = boost::irange(1, 14);
        original_universe.insert(rg.begin(), rg.end());

        Set actual_universe;
        stream.get_universe(actual_universe);
        stream.reset();
        REQUIRE(actual_universe.vertices == original_universe);
    }
}












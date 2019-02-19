#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "prettyprint.hpp"
#include "pgreedy.hpp"
#include <boost/range/irange.hpp>

TEST_CASE("test.dat", "" ) {

    // Test - read and store sets from stream, compare all sets
    Stream stream("./dataset/chess.dat");
    Set original_universe = {{}, -1};
    stream.get_universe(original_universe);
    int n = original_universe.vertices.size();

    ProgressiveGreedyInput pgin = {stream, n};
    int p = 10;

    ProgressiveGreedyOutput pgout;
    progressive_greedy_naive(pgin, p, pgout);

    REQUIRE(pgout.covered == original_universe.vertices);
}












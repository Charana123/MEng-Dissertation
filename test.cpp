#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "prettyprint.hpp"
#include "utils.hpp"
#include "DFG.hpp"
#include <boost/range/irange.hpp>

using namespace std;
float p = 1.05;

TEST_CASE("test.dat", "" ) {
    SetCoverInput test_sci = read_problem("./dataset/test.dat");

    map<int, vector<Set>> ktoCollection = OrderBySubCollection(test_sci, 2);
    SECTION("covered vertices equals universe"){
        map<int, vector<Set>> actual_ktoCollection;
        actual_ktoCollection[1].push_back({{1,2}, 0});
        actual_ktoCollection[2].push_back({{2,3,4,5}, 1});
        actual_ktoCollection[3].push_back({{6, 7, 8, 9, 10, 11, 12, 13}, 2});
        actual_ktoCollection[2].push_back({{1, 3, 5, 7, 9, 11, 13}, 3});
        actual_ktoCollection[2].push_back({{2, 4, 6, 8, 10, 12, 13}, 4});
        REQUIRE(ktoCollection ==  actual_ktoCollection);
    }

    ktoCollection = OrderBySubCollection(test_sci, p);
    SetCoverOutput test_sco = DFG(ktoCollection, p);

    set<int> actual_universe;
    auto rg = boost::irange(1, 14);
    actual_universe.insert(rg.begin(), rg.end());

    SECTION("covered vertices equals universe"){
        REQUIRE(test_sco.C.vertices ==  actual_universe);
    }

    SECTION("chosen sets cover universe"){
        set<int> universe;
        for(int i : test_sco.Sigma) universe.insert(test_sci.sets[i].vertices.begin(), test_sci.sets[i].vertices.end());
        REQUIRE(universe ==  actual_universe);
    }
}


TEST_CASE("pumsb.dat", "" ) {
    SetCoverInput pumsb_sci = read_problem("./dataset/pumsb.dat");

    map<int, vector<Set>> ktoCollection = OrderBySubCollection(pumsb_sci, p);
    SetCoverOutput pumsb_sco = DFG(ktoCollection, p);

    SECTION("chosen sets cover universe"){
        set<int> universe;
        for(int i : pumsb_sco.Sigma) universe.insert(pumsb_sci.sets[i].vertices.begin(), pumsb_sci.sets[i].vertices.end());
        REQUIRE(universe ==  pumsb_sco.C.vertices);
    }
}

/* int main(){ */
/*     /1* SetCoverInput chess_scp = read_problem("./dataset/test.dat"); *1/ */
/*     /1* for(Set set : chess_scp.sets){ *1/ */
/*     /1*     for(int vertex: set.vertices) cout << vertex; *1/ */
/*     /1*     cout << "-" << set.i << endl; *1/ */
/*     /1* } *1/ */

/*     SetCoverInput test_sci = read_problem("./dataset/test1.dat"); */
/*     map<int, vector<Set>> ktoCollection = OrderBySubCollection(test_sci.sets, 2); */
/*     cout << ktoCollection << endl; */
/* } */











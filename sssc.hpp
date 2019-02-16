#ifndef SSSC_H_
#define SSSC_H_

#include "ec_utils.hpp"
#include <cmath>

using HyperEdge = Set;

struct SSSCInput
{
    Stream* stream;
    Set* universe;
    float epsilon_cover;
    std::function<int(set<int>&)> b; // vertex benefits
    std::function<int(set<int>&)> c; // edge costs
};

struct SSSCOutput {
    function<int(int)>* cover_certificate;
};

SSSCOutput* sssc(SSSCInput* eci);

class Cover {
    public:
        Cover(function<int(set<int>&)>& b, function<int(set<int>&)>& c)
            : b(b), c(c){};
        void run(HyperEdge* he);
        void get(function<int(int)>* eid, function<int(int)>* eff);
    private:
        map<int, int> eid_m = {};
        map<int, int> eff_m = {};
        function<int(set<int>&)>& b;
        function<int(set<int>&)>& c;
};

#endif

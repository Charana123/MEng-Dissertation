#ifndef SSC_UTILS_H_
#define SSC_UTILS_H_

#include "gp_utils.hpp"

using namespace boost;
namespace bip = boost::interprocess;

class Stream {
    public:
        Stream(string filename);
        Set* get_next_set();
        void get_universe(set<int>* universe, int* m);
        void reset();
    private:
        bip::file_mapping mapping;
        bip::mapped_region mapped_rgn;
        imemstream mmistream;
        int counter = 0;
};

#endif

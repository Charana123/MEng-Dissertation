#ifndef MULTI_ASSADI_H
#define MULTI_ASSADI_H

#include "sc_utils.hpp"
#include "ssc_utils.hpp"
#include <map>
#include <random>

struct MAInput
{
    Stream* stream;
    vector<int>* universe;
    int n;
    int m;
};

/* struct */
/* { */
/*     int epsilon; */
/*     // iterations of element sampling */
/*     // The alpha constant regulates size of element samples to maintain a constant */
/*     // 1 - 1/m^2 probability of a successfull element sampling */
/*     // A larger alpha (more iterations) generates smaller samples */
/*     int alpha; */

/*     Stream* stream; */
/*     int m; */
/*     set<int>* universe; */
/*     int n; */
/* }; */

vector<int>* Algorithm1(MAInput* ma_input, int opt_tilda);
vector<int>* assadiMP(MAInput* ma_input);

#endif

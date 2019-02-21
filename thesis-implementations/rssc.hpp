#ifndef RSSC_H_
#define RSSC_H_

#include "ec_utils.hpp"
#include <cmath>

// Recursive Sample Set Cover
struct RSSCInput
{
    Stream* stream;
    int n;
    int m;
    Set* universe;
    float accuracy_delta; // Controls the number of passes, space and approximation ratio
    float c; // Controls the accuracy of the randomized sample being a delta-cover
};

RSSCOutput* recursive_sample_set_cover(RSSCInput* rssc_input){
RSSCOutput* simple_sample_set_cover(RSSCInput* rssc_input){

#endif

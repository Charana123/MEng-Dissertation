#include "sssc.hpp"
#include <iostream>
#include <vector>
#include "prettyprint.hpp"
#include <stdlib.h>

#define type int
/* #define ALIGN 32 */

using namespace std;
int main(){
    /* int* a = (int*)_mm_malloc(100*sizeof(int), ALIGN); */
    /* int* b = (int*)_mm_malloc(100*sizeof(int), ALIGN); */
    /* int* c = (int*)_mm_malloc(100*sizeof(int), ALIGN); */
    /* int a[100], b[100], c[100]; */

    /* #pragma vector aligned */
    /* #pragma simd vectorlengthfor(type) */
    /* for(int i = 0; i < 100; i++){ */
    /*     c[i] = a[i] * b[i]; */
    /* } */

    /* vector<int> vec(std::begin(c), std::end(c)); */
    /* cout << vec << endl; */


    /* const HyperEdge* __restrict__ he = new Set{{0,1,2,3,4,5,6}, -1}; */
    /* map<int,int>* __restrict__ ceid = new map<int,int>(); */
    /* map<int,int>* __restrict__ ceff = new map<int,int>(); */

    /* int eff = he->vertices.size(); */
    /* #pragma vector aligned vecremainder */
    /* #pragma simd vectorlengthfor(int) */
    /* for(int v : he->vertices){ */
    /*     if(eff > (*ceff)[v]){ */
    /*         (*ceid)[v] = he->i; */
    /*         (*ceff)[v] = eff; */
    /*     } */
    /* } */

    /* cout << *ceid << endl; */
}


















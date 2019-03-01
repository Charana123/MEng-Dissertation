#include <stdlib.h>

#define type int
#define ALIGN 32

int main(){
    int* a = (int*)_mm_malloc(100*sizeof(int), ALIGN);
    int* b = (int*)_mm_malloc(100*sizeof(int), ALIGN);
    int* c = (int*)_mm_malloc(100*sizeof(int), ALIGN);

    #pragma vector algined
    #pragma simd vectorlengthfor(int)
    for(int i = 0; i < 100; i++){
        c[i] = a[i] * b[i];
    }
}

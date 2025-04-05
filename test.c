#include "fil.h"

#include <stdio.h>

#define PASS(test) (printf("Test passed: %s:%d:%s: %s\n", __FILE__, __LINE__, __func__, #test))
#define FAIL(test) (fprintf(stderr, "Test failed: %s:%d:%s: %s\n", __FILE__, __LINE__, __func__, #test))
#define ASSERT(test) ({\
    if ((!(test)))\
        FAIL(#test);\
    else\
        PASS(#test);\
})\

void Fil_resize_test()
{
    Fil fil = {0};
    Fil_resize(&fil, FIL_RESIZE_FACTOR);
    ASSERT(fil.capacity == FIL_DEFAULT_CAPACITY * FIL_RESIZE_FACTOR);
    unsigned long cap = fil.capacity;
    Fil_resize(&fil, FIL_RESIZE_FACTOR);
    ASSERT(fil.capacity == cap * FIL_RESIZE_FACTOR);
}


int main(void)
{
    Fil_resize_test();
    return 0;
}
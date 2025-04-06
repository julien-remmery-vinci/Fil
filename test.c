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

void Fil_macro_test()
{
    ASSERT(FIL_MIN(1, 2) == 1);
    ASSERT(FIL_MAX(1, 2) == 2);
}

void Fil_resize_test()
{
    Fil fil = {0};
    
    ASSERT(Fil_resize(NULL, FIL_RESIZE_FACTOR) & FIL_ERR_PARAM);
    ASSERT(Fil_resize(&fil, 0) & FIL_ERR_PARAM);

    unsigned long new_cap = fil.capacity * FIL_RESIZE_FACTOR;
    Fil_resize(&fil, new_cap);
    ASSERT(fil.capacity == new_cap);
}

void Fil_len_test()
{
    ASSERT(Fil_len(NULL) == 0);
    ASSERT(Fil_len("Test") == 4);
}

void Fil_cmp_test()
{
    ASSERT(Fil_cmp("Hello, world!", "Hello, world!") == 0);
    ASSERT(Fil_cmp("Hello, world!", "Hello, Belgium!") != 0);
}

void Fil_cpy_test()
{
    char hello[13] = "Hello";
    Fil_cpy(hello + 5, ", world!");
    ASSERT(Fil_cmp(hello, "Hello, world!") == 0);
}

void Fil_append_test()
{
    Fil fil = {0};
    const char *hello = "Hello, world!";

    Fil_append(&fil, hello);
    ASSERT(Fil_cmp(fil.string, hello) == 0);
    ASSERT(fil.len == Fil_len(hello) + 1);
    ASSERT(fil.capacity == Fil_len(hello) + 1);
}

int main(void)
{
    Fil_macro_test();
    Fil_resize_test();
    Fil_len_test();
    Fil_cmp_test();
    Fil_cpy_test();
    Fil_append_test();
    return 0;
}
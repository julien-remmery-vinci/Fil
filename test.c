#include "fil.h"

#include <stdio.h>

#define PRINT_FIL(fil) (printf("Cap: %lu, Len: %lu, String: %s\n", (fil).capacity, (fil).len, (fil).string))
#define PRINT_POINTER(ptr) (printf("%s: %p\n", #ptr, ptr))

#define PASS(test) (printf("Test passed: %s:%d:%s: %s\n", __FILE__, __LINE__, __func__, #test))
#define FAIL(test) (fprintf(stderr, "Test failed: %s:%d:%s: %s\n", __FILE__, __LINE__, __func__, #test))
#define ASSERT(test) \
    do { \
        if (!(test)) \
            FAIL(test); \
        else \
            PASS(test); \
    } while (0)

void Fil_macro_test(void);
void Fil_resize_test(void);
void Fil_len_test(void);
void Fil_cmp_test(void);
void Fil_cpy_test(void);
void Fil_append_test(void);
void Fil_merge_test(void);
void Fil_fstr_test(void);
void Fil_lstr_test(void);
void Fil_istr_test(void);
void Fil_fchr_test(void);
void Fil_lchr_test(void);
void Fil_ichr_test(void);
void Fil_replacef_test(void);
void Fil_replacea_test(void);
void Fil_replacel_test(void);
void Fil_replacei_test(void);

int main(void)
{
    Fil_macro_test();
    Fil_resize_test();
    Fil_len_test();
    Fil_cmp_test();
    Fil_cpy_test();
    Fil_append_test();
    Fil_merge_test();
    Fil_fstr_test();
    Fil_lstr_test();
    Fil_istr_test();
    Fil_fchr_test();
    Fil_lchr_test();
    Fil_ichr_test();
    Fil_replacef_test();
    Fil_replacea_test();
    Fil_replacel_test();
    Fil_replacei_test();
    return 0;
}


void Fil_macro_test(void)
{
    ASSERT(FIL_MIN(1, 2) == 1);
    ASSERT(FIL_MAX(1, 2) == 2);
}

void Fil_resize_test(void)
{
    Fil fil = {0};
    
    ASSERT(Fil_resize(NULL, FIL_RESIZE_FACTOR) & FIL_ERR_PARAM);
    ASSERT(Fil_resize(&fil, 0) & FIL_ERR_PARAM);

    unsigned long new_cap = fil.capacity * FIL_RESIZE_FACTOR;
    Fil_resize(&fil, new_cap);
    ASSERT(fil.capacity == new_cap);
}

void Fil_len_test(void)
{
    ASSERT(Fil_len(NULL) == 0);
    ASSERT(Fil_len("Test") == 4);
}

void Fil_cmp_test(void)
{
    ASSERT(Fil_cmp(NULL, "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_cmp("Hello", NULL) & FIL_ERR_PARAM);
    ASSERT(Fil_cmp("Hello, world!", "Hello, world!") == 0);
    ASSERT(Fil_cmp("Hello, world!", "Hello, Belgium!") != 0);
    ASSERT(Fil_cmp("Hello", "Hello!") != 0);
}

void Fil_cpy_test(void)
{
    char hello[13] = "Hello";
    Fil_cpy(hello + 5, ", world!");
    ASSERT(Fil_cmp(hello, "Hello, world!") == 0);
}

void Fil_append_test(void)
{
    Fil fil = {0};
    const char *hello = "Hello, world!";

    Fil_append(&fil, hello);
    ASSERT(Fil_cmp(fil.string, hello) == 0);
    ASSERT(fil.len == Fil_len(hello));

    Fil_free(&fil);
}

void Fil_merge_test(void)
{
    Fil dest = {0};
    Fil src = {0};
    const char *hello = "Hello, world!";

    Fil_append(&dest, "Hello");
    Fil_append(&src, ", world!");
    Fil_merge(&dest, &src);
    ASSERT(Fil_cmp(dest.string, hello) == 0);
    ASSERT(dest.len == Fil_len(hello));

    Fil_free(&dest);
    Fil_free(&src);
}

void Fil_fstr_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "Hello, world!world");
    
    const char *ptr = Fil_fstr(&fil, "world");
    ASSERT(ptr != NULL);
    ASSERT(Fil_cmp(ptr, "world!world") == 0);
}

void Fil_lstr_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "Hello, worldworld!");

    const char *ptr = Fil_lstr(&fil, "world");
    ASSERT(ptr != NULL);
    ASSERT(Fil_cmp(ptr, "world!") == 0);
}

void Fil_istr_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "Hello, world!world!world!");
    
    const char *ptr = Fil_istr(&fil, "world", 2);
    ASSERT(ptr != NULL);
    ASSERT(Fil_cmp(ptr, "world!world!") == 0);
}

void Fil_fchr_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "Hello, world!");

    const char *ptr = Fil_fchr(&fil, ',');
    ASSERT(ptr == fil.string + 5);
}
void Fil_lchr_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "Hello! world!");

    const char *ptr = Fil_lchr(&fil, '!');
    ASSERT(ptr == fil.string + 12);
}
void Fil_ichr_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "Hello! world!");

    const char *ptr = Fil_ichr(&fil, '!', 2);
    ASSERT(ptr == fil.string + 12);
}

void Fil_replacef_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "foo bar bar baz");

    ASSERT(Fil_replacef(NULL, "Test", "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_replacef(&fil, NULL, "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_replacef(&fil, "Test", NULL) & FIL_ERR_PARAM);
    ASSERT(Fil_replacef(&fil, "Test", "Hello") & FIL_ERR_SEQNOTFOUND);

    Fil_replacef(&fil, "bar", "Hello, world!");
    ASSERT(Fil_cmp(fil.string, "foo Hello, world! bar baz") == 0);
}

void Fil_replacea_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "foo bar bar baz");

    ASSERT(Fil_replacea(NULL, "Test", "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_replacea(&fil, NULL, "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_replacea(&fil, "Test", NULL) & FIL_ERR_PARAM);
    ASSERT(Fil_replacea(&fil, "Test", "Hello") & FIL_ERR_SEQNOTFOUND);

    Fil_replacea(&fil, "bar", "Hello, world!");
    ASSERT(Fil_cmp(fil.string, "foo Hello, world! Hello, world! baz") == 0);
}

void Fil_replacel_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "foo bar bar baz");

    ASSERT(Fil_replacel(NULL, "Test", "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_replacel(&fil, NULL, "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_replacel(&fil, "Test", NULL) & FIL_ERR_PARAM);
    ASSERT(Fil_replacel(&fil, "Test", "Hello") & FIL_ERR_SEQNOTFOUND);

    Fil_replacel(&fil, "bar", "Hello, world!");
    ASSERT(Fil_cmp(fil.string, "foo bar Hello, world! baz") == 0);
}

void Fil_replacei_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "foo bar bar bar baz");

    ASSERT(Fil_replacei(NULL, "Test", 1, "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_replacei(&fil, NULL, 1, "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_replacei(&fil, "Test", 1, NULL) & FIL_ERR_PARAM);
    ASSERT(Fil_replacei(&fil, "Test", 0, "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_replacei(&fil, "Test", 1, "Hello") & FIL_ERR_SEQNOTFOUND);

    Fil_replacei(&fil, "bar", 2, "Hello, world!");
    ASSERT(Fil_cmp(fil.string, "foo bar Hello, world! bar baz") == 0);
}
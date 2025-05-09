#include "fil.h"

#include <stdio.h>

#define PRINT_FIL(fil) (printf("Cap: %lu, Len: %lu, String: %s\n", (fil).capacity, (fil).len, (fil).string))
#define PRINT_POINTER(ptr) (printf("%s: %p\n", #ptr, ptr))

#define PASS(test) (printf("\tTest passed: %s:%d:%s: %s\n", __FILE__, __LINE__, __func__, #test))
#define FAIL(test) (fprintf(stderr, "\tTest failed: %s:%d:%s: %s\n", __FILE__, __LINE__, __func__, #test))
#define ASSERT(test) \
    do { \
        if (!(test)) \
            FAIL(test); \
        else \
            PASS(test); \
    } while (0)

#define TEST(func) (printf("Running test: %s\n", #func));(func())

void Fil_macro_test(void);
void Fil_resize_test(void);
void Fil_len_test(void);
void Fil_cmp_test(void);
void Fil_cpy_test(void);
void Fil_append_test(void);
void Fil_merge_test(void);
void Fil_sfstr_test(void);
void Fil_slstr_test(void);
void Fil_sistr_test(void);
void Fil_sfchr_test(void);
void Fil_slchr_test(void);
void Fil_sichr_test(void);
void Fil_rfstr_test(void);
void Fil_rastr_test(void);
void Fil_rlstr_test(void);
void Fil_ristr_test(void);
void Fil_read_from_file_test(void);
void Fil_write_to_file_test(void);

int main(void)
{
    TEST(Fil_macro_test);
    TEST(Fil_resize_test);
    TEST(Fil_len_test);
    TEST(Fil_cmp_test);
    TEST(Fil_cpy_test);
    TEST(Fil_append_test);
    TEST(Fil_merge_test);
    TEST(Fil_sfstr_test);
    TEST(Fil_slstr_test);
    TEST(Fil_sistr_test);
    TEST(Fil_sfchr_test);
    TEST(Fil_slchr_test);
    TEST(Fil_sichr_test);
    TEST(Fil_rfstr_test);
    TEST(Fil_rastr_test);
    TEST(Fil_rlstr_test);
    TEST(Fil_ristr_test);
    TEST(Fil_read_from_file_test);
    TEST(Fil_write_to_file_test);
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
    ASSERT(Fil_cmp("Hello, world!", "Hello, world!") == FIL_CEQ);
    ASSERT(Fil_cmp("Hello, world!", "Hello, Belgium!") != FIL_CEQ);
    ASSERT(Fil_cmp("Hello", "Hello!") != FIL_CEQ);
}

void Fil_cpy_test(void)
{
    char hello[13] = "Hello";
    Fil_cpy(hello + 5, ", world!");
    ASSERT(Fil_cmp(hello, "Hello, world!") == FIL_CEQ);
}

void Fil_append_test(void)
{
    Fil fil = {0};
    const char *hello = "Hello, world!";

    Fil_append(&fil, hello);
    ASSERT(Fil_cmp(fil.string, hello) == FIL_CEQ);
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
    ASSERT(Fil_cmp(dest.string, hello) == FIL_CEQ);
    ASSERT(dest.len == Fil_len(hello));

    Fil_free(&dest);
    Fil_free(&src);
}

void Fil_sfstr_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "Hello, world!world");
    
    const char *ptr = Fil_sfstr(&fil, "world");
    ASSERT(ptr != NULL);
    ASSERT(Fil_cmp(ptr, "world!world") == FIL_CEQ);
}

void Fil_slstr_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "Hello, worldworld!");

    const char *ptr = Fil_slstr(&fil, "world");
    ASSERT(ptr != NULL);
    ASSERT(Fil_cmp(ptr, "world!") == FIL_CEQ);
}

void Fil_sistr_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "Hello, world!world!world!");
    
    const char *ptr = Fil_sistr(&fil, "world", 2);
    ASSERT(ptr != NULL);
    ASSERT(Fil_cmp(ptr, "world!world!") == FIL_CEQ);
}

void Fil_sfchr_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "Hello, world!");

    const char *ptr = Fil_sfchr(&fil, ',');
    ASSERT(ptr == fil.string + 5);
}

void Fil_slchr_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "Hello! world!");

    const char *ptr = Fil_slchr(&fil, '!');
    ASSERT(ptr == fil.string + 12);
}

void Fil_sichr_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "Hello! world!");

    const char *ptr = Fil_sichr(&fil, '!', 2);
    ASSERT(ptr == fil.string + 12);
}

void Fil_rfstr_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "foo bar bar baz");

    ASSERT(Fil_rfstr(NULL, "Test", "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_rfstr(&fil, NULL, "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_rfstr(&fil, "Test", NULL) & FIL_ERR_PARAM);
    ASSERT(Fil_rfstr(&fil, "Test", "Hello") & FIL_ERR_SEQNOTFOUND);

    Fil_rfstr(&fil, "bar", "Hello, world!");
    ASSERT(Fil_cmp(fil.string, "foo Hello, world! bar baz") == FIL_CEQ);
}

void Fil_rastr_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "foo bar bar baz");

    ASSERT(Fil_rastr(NULL, "Test", "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_rastr(&fil, NULL, "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_rastr(&fil, "Test", NULL) & FIL_ERR_PARAM);
    ASSERT(Fil_rastr(&fil, "Test", "Hello") & FIL_ERR_SEQNOTFOUND);

    Fil_rastr(&fil, "bar", "Hello, world!");
    ASSERT(Fil_cmp(fil.string, "foo Hello, world! Hello, world! baz") == FIL_CEQ);
}

void Fil_rlstr_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "foo bar bar baz");

    ASSERT(Fil_rlstr(NULL, "Test", "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_rlstr(&fil, NULL, "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_rlstr(&fil, "Test", NULL) & FIL_ERR_PARAM);
    ASSERT(Fil_rlstr(&fil, "Test", "Hello") & FIL_ERR_SEQNOTFOUND);

    Fil_rlstr(&fil, "bar", "Hello, world!");
    ASSERT(Fil_cmp(fil.string, "foo bar Hello, world! baz") == FIL_CEQ);
}

void Fil_ristr_test(void)
{
    Fil fil = {0};
    Fil_append(&fil, "foo bar bar bar baz");

    ASSERT(Fil_ristr(NULL, "Test", 1, "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_ristr(&fil, NULL, 1, "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_ristr(&fil, "Test", 1, NULL) & FIL_ERR_PARAM);
    ASSERT(Fil_ristr(&fil, "Test", 0, "Hello") & FIL_ERR_PARAM);
    ASSERT(Fil_ristr(&fil, "Test", 1, "Hello") & FIL_ERR_SEQNOTFOUND);

    Fil_ristr(&fil, "bar", 2, "Hello, world!");
    ASSERT(Fil_cmp(fil.string, "foo bar Hello, world! bar baz") == FIL_CEQ);
}


void Fil_read_from_file_test()
{
    const char *file_path = "tests/read_from_file.txt";
    Fil fil = {0};
    Fil_read_from_file(&fil, file_path);
    ASSERT(Fil_read_from_file(NULL, file_path) & FIL_ERR_PARAM);
    ASSERT(Fil_read_from_file(&fil, NULL) & FIL_ERR_PARAM);
    ASSERT(Fil_cmp(fil.string, "Hello, World!") == FIL_CEQ);
}
void Fil_write_to_file_test()
{

}

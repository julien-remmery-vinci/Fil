/*
MIT License

Copyright (c) 2025 Julien Remmery

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "fil.h"

#include <stdlib.h>

int Fil_resize(Fil *fil, int new_cap)
{
    if (!fil || new_cap <= 0) return FIL_ERR_PARAM;

    char *tmp = realloc(fil->string, new_cap);
    if (!tmp) return FIL_ERR_MEMORY;
    fil->string = tmp;
    fil->capacity = new_cap;
    return 0;
}

unsigned long Fil_len(const char *str)
{
    if (!str) return 0;

    const char *tmp = str;

    while (*tmp)
    {
        ++tmp;
    }
    return tmp - str;
}

unsigned long Fil_cpy(char *dest, const char *src)
{
    if (!dest || !src) return FIL_ERR_PARAM;

    while (*src)
    {
        *dest++ = *src++;
    }
    return 0;
}

unsigned long Fil_cmp(char *s1, const char *s2)
{
    if (!s1 ||!s2) return FIL_ERR_PARAM;

    while(*s1 || *s2)
    {
        if (*s1++ != *s2++)
        {
            return 1;
        }
    }
    return 0;
}

int Fil_append(Fil *fil, const char *str)
{
    if (!fil || !str) return FIL_ERR_PARAM;

    unsigned long str_len = Fil_len(str);
    unsigned long new_len = fil->len + str_len + 1; 

    if (new_len > fil->capacity)
    {
        if (Fil_resize(fil, FIL_MAX(new_len, fil->capacity * FIL_RESIZE_FACTOR)))
        {
            return FIL_ERR_MEMORY;
        }
    }
    Fil_cpy(fil->string + fil->len, str);
    fil->string[new_len] = 0;
    fil->len = new_len;
    return 0;
}

int Fil_merge(Fil *dest, Fil *src)
{
    return FIL_NOT_IMPLEMENTED;
}

int Fil_replacef(Fil *fil, const char *seq)
{
    return FIL_NOT_IMPLEMENTED;
}

int Fil_replacea(Fil *fil, const char *seq)
{
    return FIL_NOT_IMPLEMENTED;
}

int Fil_replacei(Fil *fil, const char *seq, unsigned int index)
{
    return FIL_NOT_IMPLEMENTED;
}

void* Fil_searchf(Fil *fil, const char *seq)
{
    return ((void*)0);
}

void* Fil_searchl(Fil *fil, const char *seq)
{
    return ((void*)0);
}

void* Fil_searchi(Fil *fil, const char *seq, unsigned int index)
{
    return ((void*)0);
}
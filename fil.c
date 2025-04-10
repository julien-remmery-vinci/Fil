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

void Fil_free(Fil *fil)
{
    free(fil->string);
}

int Fil_resize(Fil *fil, unsigned long new_cap)
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
    return (unsigned long)(tmp - str);
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

unsigned long Fil_cmp(const char *s1, const char *s2)
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
    unsigned long new_len = fil->len + str_len; 

    if (new_len + 1 > fil->capacity)
    {
        if (Fil_resize(fil, FIL_MAX(new_len + 1, fil->capacity * FIL_RESIZE_FACTOR)))
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
    if (!dest || !src) return FIL_ERR_PARAM;

    unsigned long new_len = dest->len + src->len; 

    if (new_len + 1 > dest->capacity)
    {
        if (Fil_resize(dest, FIL_MAX(new_len + 1, dest->capacity * FIL_RESIZE_FACTOR)))
        {
            return FIL_ERR_MEMORY;
        }
    }
    Fil_cpy(dest->string + dest->len, src->string);
    dest->string[new_len] = 0;
    dest->len = new_len;
    return FIL_NOT_IMPLEMENTED;
}

int Fil_replacef(Fil *fil, const char *s1, const char *s2)
{
    if (!fil || !s1 || !s2) return FIL_ERR_PARAM;

    const char *found = Fil_searchf(fil, s1);
    if (!found) return FIL_ERR_SEQNOTFOUND;

    unsigned long s1_len = Fil_len(s1);
    unsigned long s1_start = (unsigned long)(found - fil->string);
    unsigned long s2_len = Fil_len(s2);
    unsigned long new_len = (fil->len - s1_len) + s2_len;

    if (new_len + 1 > fil->capacity)
    {
        if (Fil_resize(fil, FIL_MAX(new_len + 1, fil->capacity * FIL_RESIZE_FACTOR)))
        {
            return FIL_ERR_MEMORY;
        }
    }
    Fil_cpy(fil->string + s1_start + s2_len, fil->string + s1_start + s1_len);
    Fil_cpy(fil->string + s1_start, s2);
    fil->string[new_len] = 0;
    fil->len = new_len;
    return FIL_NOT_IMPLEMENTED;
}

int Fil_replacea(Fil *fil, const char *s1, const char *s2)
{
    if (!fil || !s1 || !s2) return FIL_ERR_PARAM;
    const char *found;
    do { 
        found = Fil_searchf(fil, s1);
        if (!found) return FIL_ERR_SEQNOTFOUND;

        unsigned long s1_len = Fil_len(s1);
        unsigned long s1_start = (unsigned long)(found - fil->string);
        unsigned long s2_len = Fil_len(s2);
        unsigned long new_len = (fil->len - s1_len) + s2_len;

        if (new_len + 1 > fil->capacity)
        {
            if (Fil_resize(fil, FIL_MAX(new_len + 1, fil->capacity * FIL_RESIZE_FACTOR)))
            {
                return FIL_ERR_MEMORY;
            }
        }
        Fil_cpy(fil->string + s1_start + s2_len, fil->string + s1_start + s1_len);
        Fil_cpy(fil->string + s1_start, s2);
        fil->string[new_len] = 0;
        fil->len = new_len;
    } while (found);
    return FIL_NOT_IMPLEMENTED;
}

int Fil_replacel(Fil *fil, const char *s1, const char *s2)
{
    if (!fil || !s1 || !s2) return FIL_ERR_PARAM;

    const char *found = Fil_searchl(fil, s1);
    if (!found) return FIL_ERR_SEQNOTFOUND;

    unsigned long s1_len = Fil_len(s1);
    unsigned long s1_start = (unsigned long)(found - fil->string);
    unsigned long s2_len = Fil_len(s2);
    unsigned long new_len = (fil->len - s1_len) + s2_len;

    if (new_len + 1 > fil->capacity)
    {
        if (Fil_resize(fil, FIL_MAX(new_len + 1, fil->capacity * FIL_RESIZE_FACTOR)))
        {
            return FIL_ERR_MEMORY;
        }
    }
    Fil_cpy(fil->string + s1_start + s2_len, fil->string + s1_start + s1_len);
    Fil_cpy(fil->string + s1_start, s2);
    fil->string[new_len] = 0;
    fil->len = new_len;
    return FIL_NOT_IMPLEMENTED;
}

int Fil_replacei(Fil *fil, const char *s1, unsigned int index, const char *s2)
{
    if (!fil || !s1 || index == 0 || !s2) return FIL_ERR_PARAM;

    const char *found = Fil_searchi(fil, s1, index);
    if (!found) return FIL_ERR_SEQNOTFOUND;

    unsigned long s1_len = Fil_len(s1);
    unsigned long s1_start = (unsigned long)(found - fil->string);
    unsigned long s2_len = Fil_len(s2);
    unsigned long new_len = (fil->len - s1_len) + s2_len;

    if (new_len + 1 > fil->capacity)
    {
        if (Fil_resize(fil, FIL_MAX(new_len + 1, fil->capacity * FIL_RESIZE_FACTOR)))
        {
            return FIL_ERR_MEMORY;
        }
    }
    Fil_cpy(fil->string + s1_start + s2_len, fil->string + s1_start + s1_len);
    Fil_cpy(fil->string + s1_start, s2);
    fil->string[new_len] = 0;
    fil->len = new_len;
    return FIL_NOT_IMPLEMENTED;
}

const char* Fil_searchf(Fil *fil, const char *seq)
{
    if (!fil || !seq) return ((void*)0);

    const char *tmp = seq;
    unsigned long seq_len = Fil_len(seq);
    unsigned long down_counter = seq_len;
    char *current = fil->string;

    while (*current)
    {
        if (*current == *tmp)
        {
            char *ptr = current;
            while(*current == *tmp && down_counter)
            {
                current++;
                tmp++;
                down_counter--;
            }
            if (!down_counter)
            {
                return ptr;
            }
            else
            {
                tmp = seq;
                down_counter = seq_len;
            }
        }
        else
        {
            current++;
        }
    }
    return ((void*)0);
}

const char* Fil_searchl(Fil *fil, const char *seq)
{
    if (!fil || !seq) return ((void*)0);

    const char *tmp = seq;
    unsigned long seq_len = Fil_len(seq);
    unsigned long down_counter = seq_len;
    char *current = fil->string;
    char *found_ptr = ((void*)0);

    while (*current)
    {
        if (*current == *tmp)
        {
            char *ptr = current;
            while(*current == *tmp && down_counter)
            {
                current++;
                tmp++;
                down_counter--;
            }
            if (!down_counter)
            {
                found_ptr = ptr;
            }
            tmp = seq;
            down_counter = seq_len;
        }
        else
        {
            current++;
        }
    }
    return found_ptr;
}

const char* Fil_searchi(Fil *fil, const char *seq, unsigned int index)
{
    if (!fil || !seq || index == 0) return ((void*)0);

    const char *tmp = seq;
    unsigned long seq_len = Fil_len(seq);
    unsigned long down_counter = seq_len;
    char *current = fil->string;
    unsigned long found = 0;

    while (*current)
    {
        if (*current == *tmp)
        {
            char *ptr = current;
            while(*current == *tmp && down_counter)
            {
                current++;
                tmp++;
                down_counter--;
            }
            if (!down_counter)
            {
                found++;
                if (found == index)
                {
                    return ptr;
                }
            }
            tmp = seq;
            down_counter = seq_len;
        }
        else
        {
            current++;
        }
    }
    return ((void*)0);
}
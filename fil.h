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

#ifndef FIL_H
#define FIL_H

// Error masks
#define FIL_ERR_NONE            0x0
#define FIL_NOT_IMPLEMENTED     0x1
#define FIL_ERR_PARAM           0x2
#define FIL_ERR_MEMORY          0x3
#define FIL_ERR_NOSPC           0x4
#define FIL_ERR_SEQNOTFOUND     0x4

/**
 * Define FIL_RESIZE_FACTOR before including to use your own resize factor.
 * Must be a positive integer > 0
 * Used when resizing the capacity of a string in a Fil struct.
 */
#ifndef FIL_RESIZE_FACTOR
#define FIL_RESIZE_FACTOR 2
#endif // FIL_RESIZE_FACTOR

#ifndef FIL_DEFAULT_CAPACITY
#define FIL_DEFAULT_CAPACITY 20
#endif // FIL_DEFAULT_CAPACITY

typedef struct {
    char *string;
    unsigned long len;     
    unsigned long capacity;     
} Fil;

#define FIL_MIN(m, n) ((m) < (n) ? (m) : (n))
#define FIL_MAX(m, n) ((m) > (n) ? (m) : (n))

/**
 * Free allocated memory.
 */
void Fil_free(Fil *fil);

/**
 * Internal function used to resize the capacity of a Fil struct string.
 * Returns 0 on success, positive integer on error.
 */
int Fil_resize(Fil *fil, unsigned long new_cap);

/**
 * Returns the length of the provided null terminated string, 0 if str is NULL;
 * 
 * Undefined behavior if the string is not null terminated.
 */
unsigned long Fil_len(const char *str);

/**
 * Copies src into dest.
 * Returns 0 on success, positive integer on error.
 */
unsigned long Fil_cpy(char *dest, const char *src);

/**
 * Compares s1 to s2.
 * Returns 0 if s1 == s2, positive integer otherwise.
 */
unsigned long Fil_cmp(const char *s1, const char *s2);

/**
 * Append a string to your Fil.
 * Null terminates the Fil string, expect + 1 len.
 * Returns 0 on success, positive integer on error.
 */
int Fil_append(Fil *fil, const char *str);

/**
 * Merge two Fil structs.
 * Returns 0 on success, positive integer on error.
 */
int Fil_merge(Fil *dest, Fil *src);

/**
 * Replace the first occurence of s1 by s2 in the Fil.
 * Returns 0 on success, positive integer on error.
 */
int Fil_rfstr(Fil *fil, const char *s1, const char *s2);

/**
 * Replace all occurences of s1 by s2 in the Fil.
 * Returns 0 on success, positive integer on error.
 */
int Fil_rastr(Fil *fil, const char *s1, const char *s2);

/**
 * Replace the last occurence of s1 by s2 in the Fil.
 * Returns 0 on success, positive integer on error.
 */
int Fil_rlstr(Fil *fil, const char *s1, const char *s2);

/**
 * Replace the index-th occurence of s1 by s2 in the Fil.
 * Returns 0 on success, positive integer on error.
 */
int Fil_ristr(Fil *fil, const char *s1, unsigned long index, const char *s2);

/**
 * Look for the first occurence of seq in the Fil.
 * Returns a void* pointer to the found occurence, NULL if not found. 
 */
char* Fil_sfstr(Fil *fil, const char *seq);

/**
 * Look for the last occurence of seq in the Fil.
 * Returns a void* pointer to the found occurence, NULL if not found. 
 */
char* Fil_slstr(Fil *fil, const char *seq);

/**
 * Look for the index-th occurence of seq in the Fil, starting at 1.
 * Fil_searchi(&fil, "example", 1) does the same as Fil_searchf(&fil, "example").
 * Returns a void* pointer to the found occurence, NULL if not found. 
 */
char* Fil_sistr(Fil *fil, const char *seq, unsigned long index);


/**
 * Work in progress:
 * - Search and replace functions with chars on fil.string.
 * - Search and replace utility functions, on char*, might be used with fil.string ?
 * - Implement tests
 */
char *Fil_sfchr(Fil *fil, const char c);
char *Fil_slchr(Fil *fil, const char c);
char *Fil_sichr(Fil *fil, const char c, unsigned long index);

int Fil_rfchr(Fil *fil, const char c);
int Fil_rlchr(Fil *fil, const char c);
int Fil_richr(Fil *fil, const char c, unsigned long index);
int Fil_rachr(Fil *fil, const char c);
// const char *Fil_strsf(const char *s1, const char *s2);
// const char *Fil_strsf(const char *s1, const char *s2);

#endif // FIL_H
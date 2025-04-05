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
#define FIL_ERR_NONE        0x0
#define FIL_NOT_IMPLEMENTED 0x1
#define FIL_ERR_PARAM       0x2
#define FIL_ERR_MEMORY      0x3

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

/**
 * Use fil.len wtf.
 */
// unsigned long Fil_len(Fil *fil);

/**
 * Internal function used to resize the capacity of a Fil struct string.
 * Returns 0 on success, positive integer on error.
 */
int Fil_resize(Fil *fil, int resize_factor);

// Work in progress :
/**
 * Append a string to your Fil.
 * Returns 0 on success, positive integer on error.
 */
int Fil_append(Fil *fil, char *str);

/**
 * Merge two Fil structs.
 * Returns 0 on success, positive integer on error.
 */
int Fil_merge(Fil *dest, Fil *src);

/**
 * Replace the first occurence of seq in the Fil.
 * Returns 0 on success, positive integer on error.
 */
int Fil_replacef(Fil *fil, const char *seq);

/**
 * Replace all occurences of seq in the Fil.
 * Returns 0 on success, positive integer on error.
 */
int Fil_replacea(Fil *fil, const char *seq);

/**
 * Replace the index-th occurence of seq in the Fil.
 * Returns 0 on success, positive integer on error.
 */
int Fil_replacei(Fil *fil, const char *seq, unsigned int index);

/**
 * Look for the first occurence of seq in the Fil.
 * Returns a void* pointer to the found occurence, NULL if not found. 
 */
void* Fil_searchf(Fil *fil, const char *seq);

/**
 * Look for the last occurence of seq in the Fil.
 * Returns a void* pointer to the found occurence, NULL if not found. 
 */
void* Fil_searchl(Fil *fil, const char *seq);

/**
 * Look for the index-th occurence of seq in the Fil.
 * Returns a void* pointer to the found occurence, NULL if not found. 
 */
void* Fil_searchi(Fil *fil, const char *seq, unsigned int index);

#endif // FIL_H
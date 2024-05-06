#ifndef SLICE_H
#define SLICE_H

/*
 *
 
Slices is a dynamic array
-------------------------

Usage:

typedef SLICE(int) int_slice;

int_slice s = {0};
slice_append(&s, 50);
slice_append(&s, 20);
slice_append(&s, 5);
for (int i=0; i<slice_len(&s); i++) {
    printf("%d ", slice_at(&s, i));
}

*
*/

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SLICE(T) struct { T *array; size_t len; size_t cap; }
#define slice_at(s, index) ((s)->array[(index)])
#define slice_len(s) ((s)->len)
#define slice_cap(s) ((s)->cap)
#define slice_grow(s, addlen) do {                                             \
        if ((s)->len+(addlen) > (s)->cap) {                                    \
            (s)->cap = (s)->cap == 0 ? 8 :                                     \
             ((s)->len+(addlen) < (s)->cap*2? (s)->cap*2 : (s)->len+(addlen)); \
            (s)->array = reallocf((s)->array, (s)->cap*sizeof(*(s)->array));   \
            assert((s)->array != NULL && "Out of memory");                     \
        }                                                                      \
    } while (0)
#define slice_append(s, item) do {                                             \
        slice_grow(s, 1);                                                    \
        (s)->array[(s)->len++] = item;                                         \
    } while (0)
#define slice_append_array(s, arr, arrlen) do {                                \
        slice_grow(s, arrlen);                                                 \
        memcpy((s)->array + (s)->len, (arr), (arrlen)*sizeof(*(s)->array));    \
        (s)->len += (arrlen);                                                  \
    } while (0)
#define slice_append_slice(s, sl) slice_append_array(s, (sl)->array, (sl)->len)
#define slice_free(s) free((s)->array)

#endif


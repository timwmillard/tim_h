#include <stdio.h>
#include <assert.h>

#include "slice.h"

typedef SLICE(int) slice_int;

void print_slice(slice_int *iarr){
    printf("(len=%ld, cap=%ld) ", iarr->len, iarr->cap);
    printf("[");
    for (int i=0; i<iarr->len; i++) {
        /* printf("%d=%d, ", i, iarr->array[i]); */
        printf("%d=%d, ", i, slice_at(iarr, i));
    }
    printf("]\n");
}

int main()
{
    slice_int iarr = {0};
    print_slice(&iarr);

    for (int i=1; i<13; i++) {
        slice_append(&iarr, i);
        print_slice(&iarr);
    }

    slice_int yarr = {0};
    for (int i=10; i<40; i+=10) {
        slice_append(&yarr, i);
    }

    slice_append_slice(&iarr, &yarr);
    print_slice(&iarr);

    int arr[] = {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};
    slice_append_array(&iarr, arr, sizeof(arr)/sizeof(int));
    print_slice(&iarr);

    slice_free(&iarr);

    return 0;
}

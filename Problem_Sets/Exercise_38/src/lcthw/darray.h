#ifndef _DArray_h
#define _DArray_h

#include <stdlib.h>
#include <assert.h>
#include <lcthw/dbg.h>

#define DArray_last(A)      ((A)->contents[(A)->end])
#define DArray_first(A)     ((A)->contents[0])
#define DArray_end(A)       ((A)->end)
#define DArray_count(A)     DArray_end(A)
#define DArray_max(A)       ((A)->max)
#define DArray_free(E)      free((E))
#define DEFAULT_EXPAND_RATE 300

// In 'DArray', the 0th element of 'contents' is set to NULL and not used to hold actual data.
// 'end' includes the 0th element. Thus, if 'end' is 300, there will only be 299 elements in
// 'contents' that are used to hold actual data.
typedef struct DArray
{
    int end;
    int max;
    size_t element_size;
    size_t expand_rate;
    void **contents;
} DArray;

// This function creates a 'DArray' pointer.
DArray * DArray_create(size_t element_size,size_t initial_max);

// This function expands the array by using 'DArray_resize' and sets the new memory to 0 using 'memset'.
int DArray_expand(DArray *array);

// This function contracts the array by using 'DArray_resize'.
// The array will only contract to a minimal of 'array->expand_rate' even if there are less elements in 'array->contents'.
int DArray_contract(DArray *array);

// This function adds an element to the end of the array and expands the array if necessary.
int DArray_push(DArray *array,void *el);

// This functions removes an element from the end of the array and contracts the array if necessary.
void * DArray_pop(DArray *array);

// This function clears the contents of a 'DArray'.
void DArray_clear(DArray *array);

// This function destroys a 'DArray' pointer.
void DArray_destroy(DArray *array);

// This function creates memory to hold a single element of type 'void *' and size 'array->element_size'.
static inline void * DArray_new(DArray *array)
{
    check(array->element_size > 0,"Can't use 'DArray_new' on 0 size DArrays");

    return calloc(1,array->element_size);

error:
    return NULL;
}

// This function sets the elements in 'array->contents' and updates the end index of 'array'.
static inline void DArray_set(DArray *array,int i,void *el)
{
    check(i < array->max,"DArray attempt to set past max");

    if (i > array->end)
        array->end = i;

    array->contents[i] = el;

error:
    return;
}

// This function retrieves the ith element in 'array->contents'.
static inline void * DArray_get(DArray *array,int i)
{
    check(i < array->max,"DArray attempt to get past max");

    return array->contents[i];

error:
    return NULL;
}

// This function sets the ith element in 'array' to NULL and returns the removed element.
static inline void * DArray_remove(DArray *array,int i)
{
    check(i < array->max,"DArray attempt to remove past max");

    void *el = array->contents[i];
    array->contents[i] = NULL;

    return el;

error:
    return NULL;
}

#endif

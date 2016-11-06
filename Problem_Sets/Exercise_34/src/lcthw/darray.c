#include <lcthw/darray.h>
#include <assert.h>

DArray * DArray_create(size_t element_size,size_t initial_max)
{ 
    DArray *array = malloc(sizeof(DArray));
    check_mem(array);
    
    array->max = initial_max;
    check(array->max > 0,"Initial max must be > 0.");
    
    array->contents = calloc(initial_max,sizeof(void *));
    check_mem(array->contents);
    
    array->element_size = element_size;
    check(array->element_size > 0,"Element size must be > 0.");

    array->end = 0;
    array->expand_rate = DEFAULT_EXPAND_RATE;

    return array;

error:
    DArray_destroy(array);

    return NULL;
}

static inline int DArray_resize(DArray *array,size_t newsize)
{
    check(newsize > 0,"New size must be > 0.");
    
    array->max = newsize;

    void *contents = realloc(array->contents,array->max*sizeof(void *)); 
    check_mem(contents);

    array->contents = contents;

    return 0;

error:
    return -1;
}

int DArray_expand(DArray *array)
{
    check(array != NULL,"DArray to expand is NULL.");
    check(array->max > 0,"DArray max is less than 0.");
    check(array->expand_rate > 0,"DArray expand rate is less than 0.");

    size_t old_max = array->max;
    check(DArray_resize(array,array->max + array->expand_rate) == 0,"Failed to expand array to new size: %d.",array->max + (int)array->expand_rate);

    // A 'memset' is necessary since any memory past the memory that was present in the original 'array->contents' is left uninitialized after a call to 'realloc'.
    // Note: 'array->expand_rate + 1' because the 0th element of 'array->contents' is permanently set to NULL and is not used to hold actual data. Thus, the first useful element is the 1st element of 'array->contents'.
    memset(array->contents + old_max,0,array->expand_rate + 1);

    return 0;

error:
    return -1;
}

int DArray_contract(DArray *array)
{
    int new_size = array->end < (int)array->expand_rate ? (int)array->expand_rate : array->end;

    return DArray_resize(array,new_size);
}

int DArray_push(DArray *array,void *el)
{
    array->contents[array->end] = el;
    array->end++;

    if (DArray_end(array) >= DArray_max(array))
        return DArray_expand(array);
    else
        return 0;
}

void * DArray_pop(DArray *array)
{
    check(array->end - 1 >= 0,"Attempt to pop from empty array.");

    void *el = DArray_remove(array,array->end - 1);
    array->end--;

    // Contract the size of the array is a multiple of 'array->expand_rate' is reached.
    if (DArray_end(array) > (int)array->expand_rate && DArray_end(array)%array->expand_rate)
        DArray_contract(array);

    return el;

error:
    return NULL;
}

void DArray_clear(DArray *array)
{
    check(array != NULL,"DArray to clear is already NULL.");
    check(array->element_size > 0,"DArray element size is less than 0.");

    for (int i = 0;i < array->max;i++)
    {
        if (array->contents[i] != NULL)
            free(array->contents[i]);
    }

error:
    return;
}

void DArray_destroy(DArray *array)
{
    if (array)
    {
        if (array->contents)
            free(array->contents);

        free(array);
    }
}

#include "minunit.h"
#include <lcthw/darray_algos.h>

// Note: The arguments to 'testcmp' have to be 'char **a' instead of 'char *a' in this case since what is
// being passed to 'testcmp' are already pointers to 'void *' and 'qsort' and friends require pointers to
// the pointers in 'array->contents'.
int testcmp(char **a,char **b)
{
    return strcmp(*a,*b);
}

DArray * create_words()
{
    DArray *result = DArray_create(sizeof(char *),5);
    char *words[] = {"asdfasfd","werwar","13234","asdfasfd","oioj"};
    
    for (int i = 0;i < 5;i++)
        DArray_push(result,words[i]);

    return result;
}

int is_sorted(DArray *array)
{
    for (int i = 0;i < DArray_count(array) - 1;i++)
    {
        if (strcmp(DArray_get(array,i),DArray_get(array,i + 1)) > 0)
            return 0;
    }

    return 1;
}

char * run_sort_test(int (*func)(DArray *,DArray_compare),const char *name)
{
    DArray *words = create_words();
    mu_assert(!is_sorted(words),"Words should start not sorted.");

    debug("---- Testing %s sorting algorithm",name);

    int rc = func(words,(DArray_compare) testcmp);
    mu_assert(rc == 0,"Sort failed");
    mu_assert(is_sorted(words),"Didn't sort it");

    DArray_destroy(words);

    return NULL;
}

char * test_qsort()
{
    return run_sort_test(DArray_qsort,"qsort");
}

char * test_heapsort()
{
    return run_sort_test(DArray_heapsort,"heapsort");
}

char * test_mergesort()
{
    return run_sort_test(DArray_mergesort,"mergesort");
}

char * all_tests()
{
    mu_suite_start();
    
    mu_run_test(test_qsort);
    mu_run_test(test_heapsort);
    mu_run_test(test_mergesort);

    return NULL;
}

RUN_TESTS(all_tests);

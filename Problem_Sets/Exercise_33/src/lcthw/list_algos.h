#ifndef lcthw_List_Algos_h
#define lcthw_List_Algos_h

#include <stdlib.h>
#include <lcthw/list.h>

typedef int (*List_compare)(const void *a,const void *b);

// This function tests the Bubble Sort alogrithm.
int List_bubble_sort(List *words,List_compare cmp);

// This function tests the Merge Sort algorithm.
List * List_merge_sort(List *words,List_compare cmp);

#endif

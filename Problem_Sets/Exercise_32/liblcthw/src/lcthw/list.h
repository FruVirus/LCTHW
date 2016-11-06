#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

#define List_count(A)           ((A)->count)                                            // Returns the number of elements in the list, which is maintained as elements are added and removed
#define List_first(A)           ((A)->first != NULL ? (A)->first->value : NULL)         // Returns the first element of the list, but doesn't remove it
#define List_last(A)            ((A)->last != NULL? (A)->last->value : NULL)            // Returns the last element of the list, but doesn't remove it
#define LIST_FOREACH(L,S,M,V)   ListNode *V = NULL; for (V = L->S;V != NULL;V = V->M)   // Iterates over the elements in the list

// 'ListNode' is a structure for the contents, with elements that links between different nodes.
typedef struct ListNode
{
    struct ListNode *next;
    struct ListNode *prev;
    void *value; // 'value' is a pointer to any type since it's 'void *'
} ListNode;

// 'List' is the main outer structure.
typedef struct List
{
    int count;
    ListNode *first;
    ListNode *last;
} List;

// Create the main 'List' struct.
List * List_create();

// Destroy a 'List' and any elements it might have.
void List_destroy(List *list);

// A convenient function for freeing the values in each node, not the node itself.
void List_clear(List *list);

// Clear and destroy a list. It's not very efficient since it loops through them twice.
void List_clear_destroy(List *list);

// THe first operation that demonstrates the advantage of a linked list. It adds a new element to the *end* of the list, and because that's just a couple of pointer assignments, it does it very fast.
void List_push(List *list,void *value);

// The inverse of 'List_push', this takes the last element off and returns it.
void * List_pop(List *list);

// The other thing you can easily do to a linked list is add elements to the *front* of the list very quickly.
void List_unshift(List *list,void *value);

// Just like 'List_pop', this removes the first element and returns it.
void * List_shift(List *list);

// This is actually doing all of the removal when you do 'List_pop' or 'List_shift'. Something that seems to always be difficult in data structures is removing things, and this function is no different.
// It has to handle quite a few conditions depending on if the element being removed is at the front, the end, both the front and the end, or the middle.
void * List_remove(List *list,ListNode *node);

// Copy an entire list.
List * List_copy(const List *copy_from);

// Join two lists.
void List_join(List *join_to,List *join_from);

// Split two lists.
void List_split(List *a,List *b);

#endif

#include <lcthw/list.h>
#include <lcthw/dbg.h>

List * List_create()
{
    // The calloc will set everything to 0, or equivalently, to NULL. 
    return calloc(1,sizeof(List));
}

void List_destroy(List *list)
{
    // The very first 'node' in the 'list' will not (should not) have a 'list->first->prev'.
    LIST_FOREACH(list,first,next,cur)
    {
        if (cur->prev)
        {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}

void List_clear(List *list)
{
    LIST_FOREACH(list,first,next,cur)
    {
        free(cur->value);
    }
}

void List_clear_destroy(List *list)
{
    List_clear(list);
    List_destroy(list);
}

// This function will create a new 'ListNode' and add it to the end of the 'List'.
void List_push(List *list,void *value)
{
    check(list != NULL && list->count >= 0,"Invalid list.");

    if (list->count > 0)
        check(list->first != NULL,"Invalid list.");

    // The calloc will set everything to 0, or equivalently, to NULL.
    ListNode *node = calloc(1,sizeof(ListNode));
    check_mem(node);
    
    // Assign a pointer to the value.
    node->value = value;

    // If 'list->last' is NULL, this means that there are currently no nodes in 'list'. Thus, the first and last 'ListNode' pointers in 'List' will both point to 'node' initially.
    if (list->last == NULL)
    {
        list->first = node;
        list->last = node;
    }
    // If 'list->last' is not NULL, this means that there is at least one node in 'list'. In this case, the 'next' value of 'list->last' will now point to the newly created 'ListNode', 'node'.
    // Then 'node->prev' will point to 'list->last'. Finally, 'list->last' will point to 'node'. These steps are essentially equivalent to swapping and updating variables.
    else
    {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

error:
    return;
}

void * List_pop(List *list)
{
    check(list != NULL && list->count >= 0,"Invalid list.");

    if (list->count > 0)
        check(list->first != NULL,"Invalid list.");

    ListNode *node = list->last;

    return node != NULL ? List_remove(list,node) : NULL;

error:
    return NULL;
}

// This function adds a 'node' to the front of the 'list'.
void List_unshift(List *list,void *value)
{
    check(list != NULL && list->count >= 0,"Invalid list.");

    if (list->count > 0)
        check(list->first != NULL,"Invalid list.");

    ListNode *node = calloc(1,sizeof(ListNode));
    check_mem(node);

    node->value = value;

    // When creating the very first 'node', this 'node' will always be assigned to 'list->last' as new 'nodes' are added by this function.
    if (list->first == NULL)
    {
        list->first = node;
        list->last = node;
    }
    else
    {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void * List_shift(List *list)
{
    check(list != NULL && list->count >= 0,"Invalid list.");

    if (list->count > 0)
        check(list->first != NULL,"Invalid list.");
    
    ListNode *node = list->first;
    
    return node != NULL ? List_remove(list,node) : NULL;

error:
    return NULL;
}

void * List_remove(List *list,ListNode *node)
{
    void *result = NULL;
    check(list != NULL && list->count >= 0,"Invalid list.");
    check(list->first && list->last,"List is empty.");
    check(node,"node can't be NULL");

    if (list->count > 0)
        check(list->first != NULL,"Invalid list.");

    // Only one 'node' in the 'list'.
    if (node == list->first && node == list->last)
    {
        list->first = NULL;
        list->last = NULL;
    }
    // The 'node' is the first one in the 'list'.
    else if (node == list->first)
    {
        // First, change 'list->first' so that it points to the next 'node'.
        list->first = node->next;
        check(list->first != NULL,"Invalid list, somehow got a first that is NULL.");

        // Then, change the 'node' to NULL.
        list->first->prev = NULL;
    }
    // The 'node' is the last one in the 'list'.
    else if (node == list->last)
    {
        // First, change 'list->last' so that it points to the previous 'node'.
        list->last = node->prev;
        check(list->last != NULL,"Invalid list, somehow got a next that is NULL.");

        // Then, change the 'node' to NULL.
        list->last->next = NULL;
    }
    // The 'node' is somewhere between the first and last nodes in the 'list'.
    else
    {
        // As an example, consider a list of nodes [a,b,c] with 'b' being the 'node' to remove.
        // Before removing the node, we have to ensure that the relevant pointers still make 
        // sense.
        node->next->prev = node->prev;
        node->prev->next = node->next;
        //ListNode *after = node->next;   // after = c
        //ListNode *before = node->prev;  // before = a
        //after->prev = before;           // after->prev = a
        //before->next = after;           // before->next = c
    }

    list->count--;
    result = node->value;
    free(node);

error:
    return result;
}

List * List_copy(const List *copy_from)
{
    check(copy_from != NULL && copy_from->count >= 0,"Invalid list.");
    check(copy_from->first && copy_from->last,"List to copy from is empty.");

    if (copy_from->count > 0)
        check(copy_from->first != NULL,"Invalid list.");

    // Create a new list.
    List *copy_to = List_create();
    
    // Copy all the nodes in the 'copy_from' list to the 'copy_to' list.
    // Note: We have to use 'List_push' since this function will add the nodes in the exact same
    // order as the original list. 'List_unshift' will add the nodes in the opposite order.
    LIST_FOREACH(copy_from,first,next,cur)
        List_push(copy_to,cur->value);

    check(copy_to->count == copy_from->count,"Failed to copy the same number of nodes.");

    return copy_to;
error:
    return NULL;
}

void List_join(List *join_to,List *join_from)
{
    check(join_to != NULL && join_to->count >= 0,"Invalid list.");
    check(join_from != NULL && join_from->count >= 0,"Invalid list.");
    check(join_to->first && join_to->last && join_from->first && join_from->last,"Invalid list.");
    check(join_to->count > 0 && join_from->count > 0,"Invalid list.");

    // Join the two lists.
    join_to->last->next = join_from->first;
    join_from->first->prev = join_to->last;

error:
    return;
}

void List_split(List *a,List *b)
{
    check(a != NULL && a->count >= 0,"Invalid list.");
    check(b != NULL && b->count >= 0,"Invalid list.");
    check(a->first && a->last && b->first && b->last,"Invalid list."); 
    check(a->count > 0 && b->count > 0,"Invalid list.");

    // Split the lists.
    a->last->next = NULL;
    b->first->prev = NULL;

error:
    return;
}

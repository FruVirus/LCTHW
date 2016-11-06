#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

// 'words' is a pointer to a 'List' type.
// 'words->count = 4' will change the value of 'words->count' since this is equivalent to '(*words).count = 4'.
// That is, the syntax 'words->count' accesses the value of 'words->count'. This is how the function 'List_bubble_sort'
// is able to change the values inside 'words' without having to pass a double pointer.
int List_bubble_sort(List *words,List_compare cmp)
{
    int sorted = 0;

    while (!sorted)
    {
        sorted = 1;

        LIST_FOREACH(words,first,next,cur)
        {
            if (cur->next && cmp(cur->value,cur->next->value) > 0)
            {
                void *temp = cur->value;
                cur->value = cur->next->value;
                cur->next->value = temp;
                sorted = 0;
            }
        }
    }

    return 0;
}

List *List_merge(List *left,List *right,List_compare cmp)
{
    List *result = List_create();
    void *val = NULL;

    while (List_count(left) > 0 || List_count(right) > 0)
    {
        if (List_count(left) > 0 && List_count(right) > 0)
        {
            if (cmp(List_first(left),List_first(right)) <= 0)
            {
                val = List_shift(left);
            }
            else
            {
                val = List_shift(right);
            }

            List_push(result,val);
        }
        else if (List_count(left) > 0)
        {
            val = List_shift(left);
            List_push(result,val);
        }
        else if (List_count(right) > 0)
        {
            val = List_shift(right);
            List_push(result,val);
        }
    }

    return result;
}

List * List_merge_sort(List *words,List_compare cmp)
{
    if (List_count(words) <= 1)
        return words;

    List *left = List_create();
    List *right = List_create();
    int middle = List_count(words)/2;

    LIST_FOREACH(words,first,next,cur)
    {
        if (middle > 0)
        {
            List_push(left,cur->value);
        }
        else
        {
            List_push(right,cur->value);
        }

        middle--;
    }

    List *sort_left = List_merge_sort(left,cmp);
    List *sort_right = List_merge_sort(right,cmp);
    
    if (sort_left != left)
        List_destroy(left);

    if (sort_right != right)
        List_destroy(right);
    
    List *result = NULL;
    result = List_merge(sort_left,sort_right,cmp);

    List_destroy(sort_left);
    List_destroy(sort_right);

    return result;
}

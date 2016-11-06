#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

static List *list = NULL;

char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";
char *test4 = "test4 data";
char *test5 = "test5 data";
char *test6 = "test6 data";

char * test_create()
{
    list = List_create();
    mu_assert(list != NULL,"Failed to create list.");

    return NULL;
}

char * test_destroy()
{
    List_clear_destroy(list);

    return NULL;
}

char * test_push_pop()
{
    List_push(list,test1);
    mu_assert(List_last(list) == test1,"Wrong last value.");

    List_push(list,test2);
    mu_assert(List_last(list) == test2,"Wrong last value.");

    List_push(list,test3);
    mu_assert(List_last(list) == test3,"Wrong last value.");
    mu_assert(List_count(list) == 3,"Wrong count on push.");

    char *val = List_pop(list);
    mu_assert(val == test3,"Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test2,"Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test1,"Wrong value on pop.");
    mu_assert(List_count(list) == 0,"Wrong count after pop.");

    return NULL;
}

char * test_unshift()
{
    List_unshift(list,test1);
    mu_assert(List_first(list) == test1,"Wrong first value.");
    
    List_unshift(list,test2);
    mu_assert(List_first(list) == test2,"Wrong first value.");
    
    List_unshift(list,test3);
    mu_assert(List_first(list) == test3,"Wrong first value.");
    mu_assert(List_count(list) == 3,"Wrong count on unshift.");

    return NULL;
}

char * test_remove()
{
    // We only need to test the middle remove case since push/unshift
    // already tests the other cases.
    char *val = List_remove(list,list->first->next);
    mu_assert(val == test2,"Wrong removed element.");
    mu_assert(List_count(list) == 2,"Wrong count after remove.");
    mu_assert(List_first(list) == test3,"Wrong first after remove.");
    mu_assert(List_last(list) == test1,"Wrong last after remove.");

    return NULL;
}

char * test_shift()
{
    mu_assert(List_count(list) != 0,"Wrong count before shift.");

    char *val = List_shift(list);
    mu_assert(val == test3,"Wrong value on shift.");

    val = List_shift(list);
    mu_assert(val == test1,"Wrong value on shift.");
    mu_assert(List_count(list) == 0,"Wrong count after shift.");

    return NULL;
}

char * test_copy()
{
    List *list = List_create();
    List_unshift(list,test1);
    List_unshift(list,test2);
    List_unshift(list,test3);
    List *new_list = List_copy(list);

    /*printf("In 'list': \n");

    LIST_FOREACH(list,first,next,cur)
    {
        printf("%s\n",cur->value);
    }
    
    printf("In 'new_list': \n");

    LIST_FOREACH(new_list,first,next,new_cur)
    {
        printf("%s\n",new_cur->value);
    }*/

    mu_assert(new_list->first->value == test3,"Copy failed.");

    return NULL;
}

char * test_join_split()
{
    List *join_to = List_create();
    List_unshift(join_to,test1);
    List_unshift(join_to,test2);
    List_unshift(join_to,test3);
    
    List *join_from = List_create();
    List_unshift(join_from,test4);
    List_unshift(join_from,test5);
    List_unshift(join_from,test6);

    // 'join_to' and 'join_from' are POINTERS to 'List' types.
    // Passing these variables in this manner essentially passes
    // their address and allows their contents to be changed.
    List_join(join_to,join_from);
    
    LIST_FOREACH(join_to,first,next,cur)
    {
        printf("%s\n",cur->value);
    }

    mu_assert(join_to->last->next != NULL,"Join failed.");
    mu_assert(join_from->first->prev != NULL,"Join failed.");
    mu_assert(join_to->last->next->value == test6,"Join failed.");
    mu_assert(join_from->first->prev->value == test1,"Join failed.");

    List_split(join_to,join_from);
    
    mu_assert(join_to->last->next == NULL,"Split failed.");
    mu_assert(join_from->first->prev == NULL,"Split failed.");

    return NULL;
}

char * all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_destroy);
    mu_run_test(test_copy);
    mu_run_test(test_join_split);

    return NULL;
}

RUN_TESTS(all_tests);

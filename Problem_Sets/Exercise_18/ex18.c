#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

/* Our old friend die from ex17 */
void die(const char *message)
{
    if(errno)
    {
        perror(message);
    }
    else
    {
        printf("ERROR: %s\n",message);
    }

    exit(1);
}

// A typedef creates a fake type, in this case for a function pointer
typedef int (*compare_cb)(int a,int b);

/*
   A classic bubble sort function that uses the compare_cb to do the sorting
*/

int *bubble_sort(int *numbers,int count,compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count*sizeof(int));

    if(!target)
        die("Memory error.");

    memcpy(target,numbers,count*sizeof(int));

    for(;i < count;i++)
    {
        for(j = 0;j < count - 1;j++)
        {
            if(cmp(target[j],target[j + 1]) > 0)
            {
                temp = target[j+1];
                target[j + 1] = target[j];
                target[j] = temp;
            }
        }
    }

    return target;
}

int sorted_order(int a,int b)
{
    return (a > b) - (a < b);
}

int reverse_order(int a,int b)
{
    return (a < b) - (a > b);
}

int strange_order(int a,int b)
{
    if(a == 0 || b == 0)
    {
        return 0;
    }
    else
    {
        return a%b;
    }
}

/* 
   Used to test that we are sorting things correctly
   by doing the sort and printing it out
 */
void test_sorting(int *numbers,int count,compare_cb cmp)
{
    int i = 0;
    int *sorted = bubble_sort(numbers,count,cmp);

    if(!sorted)
        die("Failed to sort as requested.");

    for(;i < count;i++)
    {
        printf("%d ",sorted[i]);
    }

    printf("\n");

    free(sorted);

    /*unsigned char *data = (unsigned char *)cmp;

    for(i = 0;i < 25;i++)
    {
        printf("%02x:",data[i]);
    }

    printf("\n");
    */
}

int main(int argc,char *argv[])
{
    if(argc < 2)
        die("USAGE: ex18 4 3 1 5 6");

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;
    printf("The address of 'argv + 1' is: %p\n",(argv + 1));
    printf("The address of 'argv + 2' is: %p\n",argv + 2);
    
    // Note: inputs is a pointer to an array of character pointers. Thus, 
    // the value of '*inputs' is the pointer to the array of character
    // pointers at 'argv + 1' and '&*inputs' is the address of this
    // pointer.
    printf("'&*inputs' is also the address of 'argv + 1': %p\n",&*inputs);
    printf("'&*(inputs + 1)' is also the address of 'argv + 2': %p\n",&*(inputs + 1));
    printf("'*inputs' points to  the value of 'argv + 1': %s\n",*inputs);
    printf("'*(inputs + 1)' points to the value of 'argv + 2': %s\n",*(inputs + 1));

    int *numbers = malloc(count*sizeof(int));

    if(!numbers)
        die("Memory error.");

    for(;i < count;i++)
    {
        numbers[i] = atoi(inputs[i]);
    }
    
    test_sorting(numbers,count,sorted_order);
    test_sorting(numbers,count,reverse_order);
    test_sorting(numbers,count,strange_order);
    //test_sorting(numbers,count,NULL);

    free(numbers);

    return 0;
}
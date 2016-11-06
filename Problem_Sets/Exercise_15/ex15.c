#include <stdio.h>

int main(int argc,char *argv[])
{
    // Create two arrays we care about.
    int ages[] = {23,43,12,89,2};
    char *names[] = {"Alan","Frank","Mary","John","Lisa"};
    printf("%ld, %ld, %ld\n",sizeof(names),sizeof(names[0]),sizeof(names)/sizeof(names[0])); // 40, 8, 5
    printf("%ld, %ld, %ld\n",sizeof(ages),sizeof(ages[0]),sizeof(ages)/sizeof(ages[0])); // 20, 4, 5
    
    int *new_ages = 

    // Safely get the size of ages.
    int count = sizeof(ages)/sizeof(ages[0]);
    int i = 0;

    // First way using indexing.
    for(;i < count;i++)
    {
        printf("%s has %d years alive.\n",names[i],ages[i]);
    }

    printf("---\n");

    // Setup the pointers to the start of the arrays.
    int *cur_age = ages;
    char **cur_name = names;
    printf("%s, %c\n",*(cur_name + 2),*(cur_name + 2)[0]);

    // Second way using pointers.
    for(i = 0;i < count;i++)
    {
        printf("%s is %d years old.\n",*(cur_name + i),*(cur_age + i));
    }

    printf("---\n");

    // Third way, pointers are just arrays.
    for(i = 0;i < count;i++)
    {
        printf("%s is %d years old again.\n",cur_name[i],cur_age[i]);
    }

    printf("---\n");

    // Fourth way with pointers in a stupid complex way.
    cur_name = names;
    cur_age = ages;
    printf("%p, ",cur_name);
    printf("%p, \n",++cur_name);
    
    for(cur_name = names,cur_age = ages;(cur_age - ages) < count;cur_name += 1,cur_age++)
    {
        printf("%p, %p, %ld\n",cur_name,names,cur_name - names);
        printf("%p, %p, %ld\n",cur_age,ages,cur_age - ages);
        printf("%s lived %d years so far.\n",*cur_name,*cur_age);
    }

    char asdf[] = {'T','o','n','y','\0'};
    char *p_asdf = asdf;
    for(i = 0;i < count;i++)
    {
        printf("%c, ",p_asdf[i]);
    }

    printf("\n");

    return 0;
}

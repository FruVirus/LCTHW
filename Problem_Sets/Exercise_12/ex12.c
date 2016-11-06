#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[])
{
    int areas[] = {10,12,13,14,20};
    char name[] = "Zed";
    areas[0] = name[1];
    name[0] = 'T';
    char full_name[] = {'Z','e','d',' ','A','.',' ','S','h','a','w','\0'};
    full_name[0] = 'T';    
    char *new_name;
    int *new_areas;
    float *new_float;
    double *new_double;
    long double *new_long_double;
    printf("The size of new_name: %lu\n",sizeof(new_name));
    printf("The size of new_areas: %lu\n",sizeof(new_areas));
    printf("The size of new_float: %lu\n",sizeof(new_float));
    printf("The size of new_double: %lu\n",sizeof(new_double));
    printf("The size of new_long_double: %lu\n",sizeof(new_long_double));

    // WARNING: On some systems you may have to change %ld in this code to a %u since it will use unsigned ints.
    printf("%p,%p\n",&areas[0],&areas[1]);
    printf("The size of an int: %lu\n",sizeof(int));
    printf("The size of areas (int[]): %lu\n",sizeof(areas));
    printf("The number of ints in areas: %lu\n",sizeof(areas)/sizeof(int));
    printf("The first area is %d, the 2nd %d.\n",areas[0],areas[1]);
    printf("The size of a char: %lu\n",sizeof(char));
    printf("The size of name (char[]): %lu\n",sizeof(name));
    printf("The number of chars in name: %lu\n",sizeof(name)/sizeof(char));
    printf("The size of full_name (char[]): %lu\n",sizeof(full_name));
    printf("The number of chars in full_name: %lu\n",sizeof(full_name)/sizeof(char));
    printf("name = \"%s\" and full_name = \"%s\"\n",name,full_name);

    return 0;
}

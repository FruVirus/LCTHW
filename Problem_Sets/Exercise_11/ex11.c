#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc,char *argv[])
{
    //printf("%lu\n",sizeof(int)); = 4
    //printf("%lu\n",sizeof(char)); = 1
    //printf("%lu\n",sizeof(char*)); = 8
    
    char name[4] = {'a','b','c','d'};
    int numbers = (name[0]) + (name[1] << 8) + (name[2] << 16) + (name[3] << 24);
    //int numbers = name[0] + name[1] + name[2] + name[3];
    printf("number: %d\n",numbers);
    
    /*
    // First, print then out raw.
    for(int i = 0;i < 4;i++)
    {
        printf("%d ",numbers[i]);
    }
    
    printf("\n");

    for(int i = 0;i < 4;i++)
    {
        printf("%c ",name[i]);
    }

    printf("\n");
    printf("name: %s\n",name);

    // Setup the numbers.
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;

    // Setup the name.
    name[0] = 'Z';
    name[1] = 'e';
    name[2] = 'd';
    name[3] = '\0';

    // Then print them out initialized.
    for(int i = 0;i < 4;i++)
    {
        printf("%d ",numbers[i]);
    }
                 
    printf("\n");
              
    for(int i = 0;i < 4;i++)
    {
        printf("%c ",name[i]);
    }

    printf("\n");
    
    // Print the name like a string.                   
    printf("name: %s\n",name);

    // Another way to use name.
    char *another = "Zed";

    printf("another: %s\n",another);
    printf("another each: %c %c %c %c \n",another[0],another[1],another[2],another[3]);
    */
    return 0;
}

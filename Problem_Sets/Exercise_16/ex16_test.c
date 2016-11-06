#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct Person
{
    char *name;
    int age;
    int height;
    int weight;
};

void Person_print(struct Person *who)
{
    printf("Name: %s\n",who->name);
    printf("\tAge: %d\n",who->age);
    printf("\tHeight: %d\n",who->height);
    printf("\tWeight: %d\n",who->weight);
}

int main(int argc,char *argv[])
{
    // Make two people structures.
    struct Person joe,frank;
    //struct Person frank;
   
    joe.name = "Joe Alex";
    joe.age = 32;
    joe.height = 64;
    joe.weight = 140;

    frank.name = "Frank Blank";
    frank.age = 20;
    frank.height = 72;
    frank.weight = 180;

    // Print them out and where they are in memory.
    printf("Joe is at memory location %p:\n",&joe);
    Person_print(&joe);
    printf("Frank is at memory location %p:\n",&frank);
    Person_print(&frank);
    printf("The difference in their address is: %ld.\n",(&joe - &frank)*sizeof(struct Person));
    
    // Note: Structs are packaged into byte sizes that are multiples of 8.
    // Thus, the overall size of a struct is rounded up to the next multiple of 8.
    printf("The size of the Person struct is: %lu.\n",sizeof(struct Person));
    printf("The size of char *name is: %lu.\nThe size of int is: %lu\n",sizeof(char *),sizeof(int));
    
    return 0;
}

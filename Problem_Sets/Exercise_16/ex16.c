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

struct Person* Person_create(char *name,int age,int height,int weight)
{
    struct Person *who = malloc(sizeof(struct Person));
    assert(who != NULL);

    who->name = strdup(name);
    assert(who->name != NULL);
    who->age = age;
    who->height = height;
    who->weight = weight;
    printf("who (%s) is at memory location %p:\n",who->name,&who);

    return who;
}

void Person_destroy(struct Person *who)
{
    assert(who != NULL);
    free(who->name);
    free(who);
}

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
    struct Person *joe = Person_create("Joe Alex",32,64,140);
    struct Person *frank = Person_create("Frank Blank",20,72,180);

    // Print them out and where they are in memory.
    printf("Joe is at memory location %p:\n",joe);
    Person_print(joe);
    printf("Frank is at memory location %p:\n",frank);
    Person_print(frank);
    
    // Note: The difference in the addresses here will not be 24, which is the size of struct Person.
    // This is because Person_create allocates memory for struct Person *who and strdup allocates 
    // memory as well. This means that two struct Person's are made in Person_create and two are 
    // made in main. Thus, the address difference between joe and frank in main would be twice the
    // size of struct Person.
    printf("The difference in their address is: %ld.\n",(frank - joe)*sizeof(struct Person));
    
    // Note: Structs are packaged into byte sizes that are multiples of 8.
    // Thus, the overall size of a struct is rounded up to the next multiple of 8.
    printf("The size of the Person struct is: %lu.\n",sizeof(struct Person));
    printf("The size of char *name is: %lu.\nThe size of int is: %lu\n",sizeof(char *),sizeof(int));

    // Make everyone age 20 years and print them again.
    joe->age += 20;
    joe->height -= 2;
    joe->weight += 40;
    Person_print(joe);

    frank->age += 20;
    frank->weight += 20;
    Person_print(frank);
    
    // Destroy them both so we clean up.
    Person_destroy(joe);
    Person_destroy(frank);
    //Person_destroy(NULL);

    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

/* This is a comment. */

void change_character(char **b)
{
    **b = 'T';
}

void change_int(int *d)
{
    *d = -1;
}

int main(int argc,char *argv[])
{
    int distance = 100;

    // This is also a comment.
    printf("You are %d miles away.\n",distance);
    
    /*char a = 'X';
    char *b = &a;
    int c = 5;
    int *d = &c;
    char *e[] = {"adsfdsaf","1234"};

    //change_character(b);
    change_character(&b);
    change_int(d);
    
    printf("%c\n",a);
    printf("%d\n",*d);
    printf("%lu\n",sizeof(e[0]));
    printf("%lu\n",sizeof(e[1]));

    srand(time(NULL));
    uint32_t key = (uint32_t)(rand() | (rand() << 16));
    printf("%" PRIu32 "\n",key);

    uint64_t raw = 666;
    uint64_t *sp = &raw;
    short offset = 0;
    printf("%d\n",((uint8_t *)sp)[offset]);

    uint32_t max_32 = 4294967295;
    uint16_t max_16 = 4294967295;
    printf("%" PRIu32 "\n",max_32);
    printf("%" PRIu16 "\n",max_16);

    printf("%d\n",RAND_MAX);

    printf("%d\n",154 << 24);*/

    char *key = "Tony Zhao";
    size_t len = strlen(key);
    uint32_t hash = 0;

    for (uint32_t i = 0;i < len;i++)
    {
        hash += key[i];
        printf("Key[%d]: %c == %" PRIu32 ", Hash: %" PRIu32 "\n",i,key[i],(uint32_t)key[i],hash);
        printf("Hash << 10: %" PRIu32 "\n",hash << 10);
        hash += (hash << 10);
    }

    return 0;
}

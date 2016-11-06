#include "dbg.h"

void funci(int *a)
{
    *a = 666;
}

void funcc(char *b)
{
    *b = 'z';
}

void funcs(char **c)
{
    *c = "Zhao";
}

void funcss(char ***e)
{
    printf("e: %p\n",e);
    printf("*e (same as e in main), %p\n",*e);
    printf("**e, %s\n",**e);
    printf("***e, %c\n",***e);
    printf("size of e: %lu\n",sizeof(e));
    printf("size of *e: %lu\n",sizeof(*e));
    printf("size of **e: %lu\n",sizeof(**e));
    printf("size of ***e: %lu\n",sizeof(***e));

    printf("address of e: %p\n",e);
    printf("address of *e: %p\n",*e);
    printf("address of (*e)++: %p\n",(*e)++);
    **e = "Jiang";
}

int main(int argc,char *argv[])
{
    int a = 0;
    char b = 'b';
    char *c = "Tony";
    char *d = "Minyang";
    char **e = &d;
    printf("e in main: %p\n",e);
    printf("*e in main: %s\n",*e);
    printf("**e in main: %c\n",**e);
    printf("size of e in main: %lu\n",sizeof(e));
    printf("size of *e in main: %lu\n",sizeof(*e));
    printf("size of **e in main: %lu\n",sizeof(**e));
    printf("address of e in main: %p\n",e);
    printf("address of *e in main: %p\n",*e);
    printf("address of (*e)++ in main: %p\n",(*e)++);
    funci(&a);
    funcc(&b);
    funcs(&c);
    funcss(&e);

    printf("%d\n",a);
    printf("%c\n",b);    
    printf("%s\n",c);
    printf("%s\n",*e);

    return 0;
}

#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Forward declarations.
void print_letters(int str_len,char *arg)
{
    int i = 0;

    for(;i < str_len;i++)
    {
        char ch = arg[i];

        //if(can_print_it(ch))
        if(isalpha((int) ch) || isblank((int) ch))
        {
            printf("%c' == %d ",ch,ch);
        }
    }

    printf("\n");
}

void print_arguments(int argc,char *argv[])
{
    int i = 1;

    for(;i < argc;i++)
    {
        int str_len = strlen(argv[i]);
        print_letters(str_len,argv[i]);
    }
}

int main(int argc,char *argv[])
{
    print_arguments(argc,argv);

    return 0;
}

#include "dbg.h"

#define MAX_DATA 100

int read_string(char **out_string,int max_buffer)
{
    // Allocate memory for '*out_string'. '*out_string' is a pointer to char (i.e., a string). 'out_string' is a pointer to a pointer to char (i.e., an address in memory). '**out_string' is a char.
    // The value of 'out_string', denoted by '*out_string', is a char * (i.e., a string). We can allocate memory for this.
    *out_string = calloc(1,max_buffer + 1);
    check_mem(*out_string);

    char *result = fgets(*out_string,max_buffer,stdin);
    check(result != NULL,"Input error.");

    return 0;

error:
    if(*out_string)
        free(*out_string);

    *out_string = NULL;
    
    return -1;
}

int read_int(long *out_int)
{
    char *input = NULL;
    char *end = NULL;
    int rc = read_string(&input,MAX_DATA);
    check(rc == 0,"Failed to read number.");

    // 'strtol' converts the initial part of the string in the first parameter to a long int value according to the given base in the third parameter (2 <= base <= 36, or base = 0).
    // The second parameter is a reference to an object of type char*, whose value is set by 'strtol' to the next character in the first parameter after the numerical value.
    *out_int = strtol(input,&end,10);
    check((*end == '\0' || *end == '\n') && *input != '\0',"Invalid number: %s",input);

    free(input);

    return 0;

error:
    if(input)
        free(input);

    return -1;
}

int read_scan(const char *fmt,...)
{
    int i = 0;
    int rc = 0;
    long *out_int = NULL;
    char *out_char = NULL;
    char **out_string = NULL;
    int max_buffer = 0;

    // Create a 'va_list' variable type.
    va_list argp;

    // 'va_start' initializes a 'va_list'.
    // It is a macro which accepts a 'va_list' and the name of the variable that DIRECTLY precedes the ellipsis.
    va_start(argp,fmt);

    // 'va_arg' takes a 'va_list' and a variable type, and returns the next argument in the list in the form of whatever variable type it is told.
    // It then moves down the list to the next argument.
    
    for(i = 0;fmt[i] != '\0';i++)
    {
        if(fmt[i] == '%')
        {
            i++;

            switch(fmt[i])
            {
                case '\0':
                    sentinel("Invalid format, you ended with %%.");
                    break;

                case 'd':
                    out_int = va_arg(argp,long *);
                    rc = read_int(out_int);
                    check(rc == 0,"Failed to read int.");
                    break;

                case 'c':
                    out_char = va_arg(argp,char *);
                    *out_char = fgetc(stdin);
                    break;

                case 's':
                    // Note: In the case of "%s", the first vararg is 'MAX_DATA', followed by the address of a pointer to char. 
                    max_buffer = va_arg(argp,int);

                    // Note: 'out_string' is of type char ** because it is a pointer that points at a char *. That is, 'first_name' 
                    // in main is defined as a char *, so 'first_name' is a pointer to the first element in a character array
                    // (i.e., a string). We pass the address of 'first_name' to 'read_scan' since we want 'read_scan' to change
                    // the value of 'first_name' back in main. When we pass the address of 'first_name', we essentially pass a
                    // pointer to the pointer of the first element in the character array 'first_name'. Thus, 'out_string' is 
                    // of type char **.
                    out_string = va_arg(argp,char **);
                    rc = read_string(out_string,max_buffer);
                    check(rc == 0,"Failed to read string.");
                    break;

                default:
                    sentinel("Invalid format.");
            }
        }
        else
        {
            // Get the next (unsigned) character from the specified stream and advance the position indicator for the stream.
            // This is used to move past the first parenthesis in 'fmt'.
            fgetc(stdin);
        }
        // 'feof': Tests the end-of-file indicator for the given stream. Returns 0 if EOF.
        // 'ferror': Tests the error indicator for the given stream. Returns 0 if ERROR.
        check(!feof(stdin) && !ferror(stdin),"Input error.");
    }

    va_end(argp);

    return 0;

error:
    va_end(argp);

    return -1;
}

int main(int argc,char *argv[])
{
    char *first_name = NULL;
    char initial = ' ';
    char *last_name = NULL;
    long age = 0;

    printf("What's your first name? ");
    int rc = read_scan("%s",MAX_DATA,&first_name);
    check(rc == 0,"Failed first name.");

    printf("What's your initial? ");
    rc =read_scan("%c\n",&initial);
    check(rc == 0,"Failed initial.");

    printf("What's your last name? ");
    rc = read_scan("%s",MAX_DATA,&last_name);
    check(rc == 0,"Failed last name.");

    printf("How old are you? ");
    rc = read_scan("%d",&age);
    check(rc == 0,"Failed to read age.");

    printf("----- RESULTS -----\n");
    printf("First Name: %s",first_name);
    printf("Initial: '%c'\n",initial);
    printf("Last Name: %s",last_name);
    printf("Age: %ld\n",age);

    free(first_name);
    free(last_name);

    return 0;

error:
    return -1;
}

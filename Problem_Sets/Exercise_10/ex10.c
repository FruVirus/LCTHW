#include <stdio.h>
#include <ctype.h>

int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        printf("ERROR: You need one argument.\n");

        // This is how you abort a program.
        return 1;
    }
   
    int j = 1;
    char letter = argv[j][0];

    for(;j < argc;j++)
    {
        int i = 0;

        for(;letter = toupper(argv[j][i]),letter != '\0';i++)
        {
            switch(letter)
            {
                case 'A':
                    printf("%d: 'A'\n",i);
                    break;

                case 'E':
                    printf("%d: 'E'\n",i);
                    break;

                case 'I':
                    printf("%d: 'I'\n",i);
                    break;

                case 'O':                          
                    printf("%d: 'O'\n",i);
                    break;

                case 'U':
                    printf("%d: 'U'\n",i);
                    break;
        
                case 'Y':
                    // Why i > 2? Is this a bug?
                    if(i > 2)
                    {
                        // It's only sometimes Y.
                        printf("%d: 'Y'\n",i);
                        break;
                    }
                    break;

                default:
                    printf("%d: %c is not a vowel\n",i,letter);
            }                  
        }
    }      
                
    return 0;
}

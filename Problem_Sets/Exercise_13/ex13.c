#include <stdio.h>

int main(int argc,char *argv[])
{
    int i = 1;

    // Go through each string in argv.
    // Skipping argv[0] since this is the name of the file.
    char *states[] = {"California","Orgeon","Washington",NULL};
    //argv[1] = states[1];
    states[1] = "afdasdfads";

    for(;i < argc;i++)
    {
        printf("arg %d: %s\n",i,argv[i]);
    }

    // Let's make our own array of strings.
    //char *states[] = {"California","Orgeon","Washington",NULL};

    int num_states = 4;

    for(i = 0;i < num_states;i++)
    {
        printf("state %d: %s\n",i,states[i]);
    }

    return 0;
}

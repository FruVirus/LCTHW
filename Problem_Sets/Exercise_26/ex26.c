#include "dbg.h"
#include <glob.h>

#define MAX_DATA 1000
#define LOG_FIND ./logfind
#define SEARCH_PATH ~/Documents/C:C++/C/Learn\ C\ the\ Hard\ Way/Problem_Sets/

int parse_arguments(const int argc,const char *argv[],int *or_option,char ***keywords)
{
    int word_index = 0;
    
    if (argc == 1 || (argc == 2 && strcmp(argv[1],"-o") == 0))
    {
        printf("Usage: ex26 [-o] ARG1 ARG2 ...\n");
        
        return 0;
    }

    // Parse the program arguments into keywords and the optional parameter.
    for (int i = 1;i < argc;i++)
    {
        if (strcmp(argv[i],"-o") == 0 && *or_option != 1)
            *or_option = 1;
        else
        {
            (*keywords)[word_index] = calloc(1,sizeof **keywords); // Here, we are allocating memory for pointer to char; thus, we need 1.
            
            if ((*keywords)[word_index] == NULL)
            {
                printf("Allocation failed for 'keywords[%d]'.\n",word_index);
                
                return 0;
            }
            
            memcpy((*keywords)[word_index],argv[i],strnlen(argv[i],MAX_DATA));
            word_index++;
        }
    }
    
    return word_index;
}

void check_if_found(int i,int **index,int *found_count,int word_index)
{
    if (i == 0)
    {
        (*index)[*found_count] = i;
        (*found_count)++;

        return;
    }

    for (int k = 0;k < word_index;k++)
    {
        if ((*index)[k] == i)
            return;
        else if (k == word_index - 1)
        {
            (*index)[*found_count] = i;
            (*found_count)++;
        }
    }
}

void scan_file(const char *filename,char **keywords,int word_index,int or_option)
{
    // Open the file for reading.
    FILE *fp = fopen(filename,"r");

    if (fp == NULL)
    {
        printf("Error opening file: %s\n",filename);
        
        return;
    }

    // Search the file for the keywords.
    char *line = malloc(MAX_DATA*sizeof line);
    int *index = calloc(word_index,sizeof *index);
    int found_count = 0;

    while (fgets(line,MAX_DATA,fp))
    {
        for (int i = 0;i < word_index;i++)
        {
            if (strstr(line,keywords[i]) && or_option)
            {
                printf("File: '%s' contains the keyword: '%s'\n",filename,keywords[i]);
                
                return;
            }
            else if (strstr(line,keywords[i]) && !or_option)
            {
                check_if_found(i,&index,&found_count,word_index);
            }
        }
    }

    if (found_count == word_index)
        printf("File: '%s' contains all the keywords\n",filename);

    free(index);
    free(line);
    fclose(fp);
}

int main(const int argc,const char *argv[])
{
    // Test for invalid program calls and parse program arguments.
    // Note: When allocating memory for pointers or pointers to pointers, etc., 
    // we can generally use sizeof *p for all cases since the size of a pointer 
    // is the same regardless of how many levels of indirection is involved. 
    // That is, the size of a pointer and the size of a pointer to pointer, etc. 
    // is the same.
    int or_option = 0;
    char **keywords = calloc(argc - 1,sizeof keywords); // Here, we are allocating memory for pointers to pointers to char; thus, we need argc - 1.
   
    if (keywords == NULL)
    {
        printf("Allocation failed for 'keywords' in main.\n");
        free(keywords);
        return 1;
    }

    int word_index = parse_arguments(argc,argv,&or_option,&keywords); // Here, we pass the addresses of 'or_option' and 'keywords' since we want to change their values inside the function 'parse_arguments'.
    
    // Search the allowed log files in the search path for the keywords.
    if (word_index)
    {
        const char *filename = "Makefile";
        scan_file(filename,keywords,word_index,or_option);
    }

    // Free memory.
    for (int i = 0;i < word_index;i++)
        free(keywords[i]);

    free(keywords);

    return 0;
}

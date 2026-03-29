#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequence.h"
#include "shell_array.h"
#include "shell_list.h"

int main(int argc, char **argv)
{
    if(argc != 4)
    {
        return EXIT_FAILURE;
    }

    if(!strcmp(argv[1], "-a"))
    {
        //printf("this is an array\n");
        int pSize;
        long comparisons;

        long *sort = Array_Load_From_File(argv[2], &pSize);
        if(sort == NULL){return(EXIT_FAILURE);}
        
        Array_Shellsort(sort, pSize, &comparisons);
        printf("%ld\n", comparisons);
        if(!Array_Save_To_File(argv[3], sort, pSize))
        {
            free(sort);
            return(EXIT_FAILURE);
        }
        free(sort);
    }
    else if(!strcmp(argv[1], "-1"))
    {
        int status;
        long comparisons;
        //printf("this is a list\n");
        Node *sort = List_Load_From_File(argv[2], &status);
        if(!sort){
            return(EXIT_FAILURE);
        }
        
        sort = List_Shellsort(sort, &comparisons);
        printf("%ld\n", comparisons);
        if(!List_Save_To_File(argv[3], sort))
        {
            return(EXIT_FAILURE);
        }
    }
    else
    {
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}
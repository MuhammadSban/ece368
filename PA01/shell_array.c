#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"
#include "shell_array.h"

long *Array_Load_From_File(char *filename, int *size)
{
    FILE *topen = fopen(filename, "rb"); //open file
    long *fileArray = NULL;
    *size = 0;
    if(topen == NULL) {return fileArray;}

    fseek(topen, 0, SEEK_END);
    *size = ftell(topen) / sizeof(long);
    fseek(topen, 0, SEEK_SET);
    
    if(*size == 0){return NULL;}
    
    fileArray = malloc(*size * sizeof(long)); //find length of file
    if(fileArray == NULL) 
    {fclose(topen);
        return NULL;
    }
    
    if(!fread(fileArray, sizeof(long), *size, topen))
    {
        free(fileArray);
        fclose(topen);
        return NULL;
    }
     //read number of elements to array
    fclose(topen);
    return(fileArray);
}

int Array_Save_To_File(char *filename, long *array, int size)
{
    FILE *topen = fopen(filename, "wb"); //open file to write to
    if((topen == NULL) || (array == NULL)){return -1;} //fail case
    int num = fwrite(array, sizeof(long), size, topen); // write elements to file, count how many are successful
    fclose(topen);
    return(num);
}

void Array_Shellsort(long *array, int size, long *n_comp)
{
    int sorts; //length of 2p3q sequence for k-sorting
    int i; //generic counter
    int j; //generic counter
    int k; //generic counter
    long temp; //temporary value to hold value for swapping
    long *sequence = Generate_2p3q_Seq(size, &sorts); //k-sorting sequence
    if(n_comp != NULL) { *n_comp = 0; }
    for(k = sorts - 1; k >= 0; k--) //For every element of 2p3q, largest to smallest
    {
        for(j = sequence[k]; j < size; j++) 
        {
            temp = array[j];
            i = j;
            while((i >= sequence[k]) && (array[i - sequence[k]] > temp))
            {
                (*n_comp)++;
                array[i] = array[i - sequence[k]];
                i = i - sequence[k]; //advance down in Kth subarray
            }
            array[i] = temp;
        }
    }
    free(sequence);
}

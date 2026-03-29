#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"

long *Generate_2p3q_Seq(int n, int *seq_size)
{
    if(n <= 1) //No need for sorting, 2p3q unnecessary
    {
        return NULL;
    }
    *seq_size = 0; //Set sequence length to 0 to count later
    long *finalseq = NULL; //Initialize final array
    int first = 1; //first value of array
    int save; //generic storing variable
    int twop = 0; //index of 2 multiplier variable
    int pottwo; // potential multiplied by two value
    int threeq = 0; // index of 3 multiplier variable
    int potthree; //potential multiplied by three value
    int i; //generic counter

    while(first < n) //count number of values in pyramid
    {
        (*seq_size)++;
        save = first;
        while(first < n)
        {
            first *= 3;
            (*seq_size)++;
        }
        first = save;
        first *= 2;
    }

    if(*seq_size == 0)
    {
        return NULL;
    }
    
    finalseq = malloc(*seq_size * sizeof(long));
    finalseq[0] = 1;

    //Progress through all potential values of 2^p, 3^q, compare potential values so array is in ascending orderZ
    for(i = 1; i < *seq_size; i++) 
    {
        pottwo = finalseq[twop] * 2;
        potthree = finalseq[threeq] * 3;
        if(pottwo <= potthree)
        {
            finalseq[i] = pottwo;
            twop++;
        }
        if(pottwo >= potthree)
        {
            finalseq[i] = potthree;
            threeq++;
        }
    }

    return finalseq;
}
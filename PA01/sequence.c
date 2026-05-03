#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"

long *Generate_2p3q_Seq(int n, int *seq_size)
{
    if(n <= 1) //No need for sorting, 2p3q unnecessary
    {
        long *seq = malloc(sizeof(long));
        *seq = 1;
        return seq;
    }
    *seq_size = 0; //Set sequence length to 0 to count later
    long *finalseq = NULL; //Initialize final array
    long *seqtest = malloc(sizeof(long) * n);
    int twop = 0; //index of 2 multiplier variable
    long pottwo; // potential multiplied by two value
    int threeq = 0; // index of 3 multiplier variable
    long potthree; //potential multiplied by three value
    int i; //generic counter

    seqtest[0] = 1;
    for(i = 1; i < n; i++) 
    {
        pottwo = seqtest[twop] * 2;
        potthree = seqtest[threeq] * 3;
        if(pottwo <= potthree && pottwo < n)
        {
            seqtest[i] = pottwo;
            (*seq_size)++;
            twop++;
        }
        if(pottwo >= potthree && potthree < n)
        {
            seqtest[i] = potthree;
            (*seq_size)++;
            threeq++;
        }
        if(pottwo == potthree){(*seq_size)--;}
        if(pottwo >= n && potthree >= n){break;}
    }

    if(*seq_size == 0)
    {
        return NULL;
    }
    
    finalseq = malloc((*seq_size + 1) * sizeof(long));
    finalseq[0] = 1;
    //printf("%ld\n", finalseq[0]);
    //Progress through all potential values of 2^p, 3^q, compare potential values so array is in ascending orderZ
    twop = 0;
    threeq = 0;
    
    for(i = 1; i <= *seq_size; i++) 
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
        //printf("%ld\n", finalseq[i]);
    }
    free(seqtest);
    return finalseq;
}
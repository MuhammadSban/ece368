#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hbt.h"
#include "evaluate.h"
#include "input.h"
#include "wrout.h"

int main(int argc, char **argv)
{
    if(argc != 4)
    {
        return EXIT_FAILURE;
    }
    if(!(strcmp(argv[1], "-b")))
    {  
        //printf("%s\n%s\n%s\n%s\n", argv[0], argv[1], argv[2], argv[3]);
        Tnode *bftree = buildTree(argv[2]);
        FILE *fptr = fopen(argv[3], "wb");
        finOut(fptr, bftree);
        fclose(fptr);
        freeTree(bftree);
    }
    else if(!(strcmp(argv[1], "-e")))
    {
        //evaluation
        FILE *fptr = fopen(argv[2], "rb");
        if(fptr == NULL)
        {
            fprintf(stdout, "-1");
            return EXIT_FAILURE;
        }
        int status = 1;
        Tnode *evTree = buildTreeOut(fptr, &status);
        if(status == 0)
        {
            fprintf(stdout, "0");
            freeTree(evTree);
            fclose(fptr);
            return EXIT_FAILURE;
        }
        updateBalance(&evTree);
        int isBST = 1;
        int isBalanced = 1;
        evaluateTree(evTree, &isBST, &isBalanced);
        fprintf(stdout, "%d,%d,%d\n", status, isBST, isBalanced);
        freeTree(evTree);
        fclose(fptr);
    }
    else
    {
        fprintf(stdout, "-1\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
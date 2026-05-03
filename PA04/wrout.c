#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"
#include "wrout.h"

void finOut(FILE *output, Tnode *tree)
{
    if(tree == NULL){return;}
    int tprint = tree->key;
    int bal = 0;
    fwrite(&tprint, sizeof(int), 1, output);
    if(tree->right == NULL)
    {
        bal = 0;
    }
    else
    {
        bal = 1;
    }
    
    if(tree->left == NULL)
    {
        bal += 0;
    }
    else
    {
        bal += 2;
    }
    fwrite(&bal, sizeof(char), 1, output);
    //printf("out: %d %d\n", tree->key, bal);
    finOut(output, tree->left);
    finOut(output, tree->right);
}

void freeTree(Tnode *tree)
{
    if(tree == NULL){return;}
    freeTree(tree->left);
    freeTree(tree->right);
    free(tree);
}
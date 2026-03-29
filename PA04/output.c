#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"

void fOut(FILE *output, Tnode *tree)
{
    int tprint = tree->key;
    int bal = 0;
    fwrite(&tprint, 29, 1, output);
    fwrite(&bal, 1, 1, output);
    if(tree->left == NULL)
    {
        
    }

    fOut(output, tree->left);
    fOut(output, tree->right);
}
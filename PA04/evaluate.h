#ifndef __EVALUATE_H__
#define __EVALUATE_H__

#include "hbt.h"
#include "input.h"

Tnode *buildTreeOut(FILE *fptr, int *status);

void evaluateTree(Tnode *tree, int *isBST, int *isBalanced);

#endif
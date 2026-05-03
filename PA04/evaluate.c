#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"
#include "input.h"
#include "evaluate.h"

Tnode *buildTreeOut(FILE *fptr, int *status)
{
    int key;
    char oper;
    Tnode *focal;

    if(!fread(&(key), sizeof(int), 1, fptr))
    {
        *status = 0;
        return NULL;
    }
    if(!fread(&oper, sizeof(char), 1, fptr))
    {
        *status = 0;
        return NULL;
    }

    focal = malloc(sizeof(Tnode));
    focal->key = key;

    if(oper == 0)
    {
        focal->balance = 0;
        focal->left = NULL;
        focal->right = NULL;
    }
    else if(oper == 1)
    {
        focal->balance = 0;
        focal->left = NULL;
        focal->right = buildTreeOut(fptr, status);
    }
    else if(oper == 2)
    {
        focal->balance = 0;
        focal->left = buildTreeOut(fptr, status);
        focal->right = NULL;
    }
    else
    {
        focal->balance = 0;
        focal->left = buildTreeOut(fptr, status);
        focal->right = buildTreeOut(fptr, status);
    }
    return(focal);
}

void evaluateTree(Tnode *tree, int *isBST, int *isBalanced)
{
    if(tree == NULL)
    {
        return;
    }

    if(tree->balance < -1 || tree->balance > 1)
    {
        *isBalanced = 0;
    }
    if(tree->left != NULL && tree->left->key > tree->key)
    {
        *isBST = 0;
    }
    if(tree->right != NULL && tree->right->key < tree->key)
    {
        *isBST = 0;
    }

    evaluateTree(tree->left, isBST, isBalanced);
    evaluateTree(tree->right, isBST, isBalanced);
}
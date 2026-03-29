#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"

Tnode *buildTree(char *filename)
{
    FILE *fptr = fopen(filename, "rb");
    if(fptr == NULL){return NULL;}
    Tnode *binaryTree = NULL;
    Tnode *focal = malloc(sizeof(Tnode));
    char oper;
    int key;
    while(fread(&(key), sizeof(int), 1, fptr) && fread(&oper, sizeof(char), 1, fptr))
    {
        if(oper == 'i')
        {
            focal->key = key;
            focal->balance = 0;
            focal->left, focal->right == NULL;
            insertNode(&binaryTree, focal);
        }
        else if(oper == 'd')
        {
            focal->key = key;
            deleteNode(&binaryTree, focal);
        }
        focal = malloc(sizeof(Tnode));
    }
    free(focal);
    return(binaryTree);

}

int insertNode(Tnode **root, Tnode *new)
{
    Tnode *rt = *root;
    if(rt == NULL)
    {
        *root = new;
    }

    Tnode *last;
    last = rt;

    Tnode *ya;
    Tnode *pya;
    while(rt != NULL)
    {
        if(rt->key <= new->key)
        {
            last =rt;
            rt = rt->left;
        }
        else
        {
            last = rt;
            rt = rt->right;
        }
        if(rt != NULL && rt->balance != 0)
        {
            pya = last;
            ya = rt;
        }
    }
    if(rt->key <= new->key)
    {
        last->left = new;
    }
    else
    {
        last->right = new;
    }
} //adjustbalances

Tnode *deleteNode(Tnode **root, Tnode *new)
{
    Tnode *rt = *root;
    if(rt->key == new->key)
    {
        if(rt->right == NULL && rt->left == NULL)
        {
            return NULL;
        }
        else if(rt->left == NULL && rt->right != NULL)
        {
            return(rt->right);
        }
        else if(rt->right == NULL && rt->left != NULL)
        {

        }
        //find in-order successor
        free(root);
        return NULL; //return in-order successor
    }
    if(rt->key < new->key)
    {
        rt->left = deleteNode(root->left, new);
    }
    else
    {
        rt->right = deleteNode(root->right, new);
    }

    return root;
}
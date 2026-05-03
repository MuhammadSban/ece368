#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"
#include "input.h"

Tnode *buildTree(char *filename)
{
    FILE *fptr = fopen(filename, "rb");
    if(fptr == NULL){return NULL;}
    Tnode *binaryTree = NULL;
    Tnode *focal;
    char oper;
    int key;
    char hc;
    //printf("file: %s\n", filename);
    while((fread(&(key), sizeof(int), 1, fptr) && fread(&oper, sizeof(char), 1, fptr)))
    {
        focal = malloc(sizeof(Tnode));
        //printf("node: %d, oper: %c\n", key, oper);
        if(oper == 'i')
        {
            focal->key = key;
            focal->balance = 0;
            focal->left = NULL;
            focal->right = NULL;
            binaryTree = insertNode(binaryTree, focal, &hc);
        }
        else if(oper == 'd')
        {
            focal->key = key;
            binaryTree = deleteNode(binaryTree, focal, &hc);
            free(focal);
        }
    }
    fclose(fptr);
    return(binaryTree);

}

Tnode *insertNode(Tnode *root, Tnode *newN, char *hChange)
{
    if(root == NULL)
    {
        *hChange = 'A';
        return newN;
    }

    char ch;
    if(newN->key <= root->key)
    {
        root->left = insertNode(root->left, newN, &ch);
        if(ch == 'A')
        {
            if(root->balance == -1)
            {
                root->balance = 0;
                *hChange = 'N';
                return root;
            }
            else if(root->balance == 0)
            {
                root->balance = 1;
                *hChange = 'A';
                return root;
            }
            else //balance is now 2, youngest ancestor, must rotate
            {
                //Case A -- unbalanced in the same direction
                if(root->left->balance == 1)
                {
                    root = cwrot(root);
                    root->balance = 0;
                    root->right->balance = 0;
                }
                //Case B -- unbalanced in opposite directions
                else
                {
                    root->left = ccwrot(root->left);
                    root = cwrot(root);
                    if(root->balance == 1)
                    {
                        root->balance = 0;
                        root->right->balance = -1;
                        root->left->balance = 0;
                    }
                    else if(root->balance == -1)
                    {
                        root->balance = 0;
                        root->right->balance = 0;
                        root->left->balance = 1;
                    }
                    else
                    {
                        root->balance = 0;
                        root->right->balance = 0;
                        root->left->balance = 0;
                    }
                }
                *hChange = 'N';
                return root;
            }
        }
    }
    else
    {
        root->right = insertNode(root->right, newN, &ch);
        if(ch == 'A')
        {
            if(root->balance == 1)
            {
                root->balance = 0;
                *hChange = 'N';
                return root;
            }
            else if(root->balance == 0)
            {
                root->balance = -1;
                *hChange = 'A';
                return root;
            }
            else //balance is now -2, youngest ancestor, must rotate
            {
                //Case A -- unbalanced in the same direction
                if(root->right->balance == -1)
                {
                    root = ccwrot(root);
                    root->balance = 0;
                    root->left->balance = 0;
                }
                //Case B -- unbalanced in opposite directions
                else
                {
                    root->right = cwrot(root->right);
                    root = ccwrot(root);
                    if(root->balance == -1)
                    {
                        root->balance = 0;
                        root->left->balance = 1;
                        root->right->balance = 0;
                    }
                    else if(root->balance == 1)
                    {
                        root->balance = 0;
                        root->left->balance = 0;
                        root->right->balance = -1;
                    }
                    else
                    {
                        root->balance = 0;
                        root->right->balance = 0;
                        root->left->balance = 0;
                    }
                }
                *hChange = 'N';
                return root;
            }
        }
    }
    *hChange = 'N';
    return root;
}

Tnode *deleteNode(Tnode *root, Tnode *newN, char *hChange)
{
    if(root == NULL)
    {
        *hChange = 'N'; 
        return NULL;
    }
    Tnode *rt = root;
    if(rt->key == newN->key)
    {
        *hChange = 'A'; // height decreases
        if(rt->right == NULL && rt->left == NULL)
        {
            free(rt);
            return NULL;
        }
        else if(rt->left == NULL && rt->right != NULL)
        {
            Tnode *temp = rt->right;
            free(rt);
            return(temp);
        }
        else if(rt->right == NULL && rt->left != NULL)
        {
            Tnode *temp = rt->left;
            free(rt);
            return(temp);
        }
        root->left = findPred(root->left, (root), hChange); //return in-order predecessor
        if(*hChange == 'A')
        {
            root = rebalanceLeft(root, hChange);
        }
        return root;
    }
    if(newN->key < root->key)
    {
        root->left = deleteNode(root->left, newN, hChange);
        if(*hChange == 'A')
        {
            root = rebalanceLeft(root, hChange);
        }
    }
    else
    {
        root->right = deleteNode(root->right, newN, hChange);
        if(*hChange == 'A')
        {
            root = rebalanceRight(root, hChange);
        }
    }
    return root;
}

Tnode *findPred(Tnode *root, Tnode *orig, char *hChange)
{
    if(root->right == NULL)
    {
        Tnode *temp = root;
        orig->key = root->key;
        root = root->left;
        free(temp);
        *hChange = 'A';
        return root;
    }
    root->right = findPred(root->right, orig, hChange);
    if(*hChange == 'A') 
    {
        root = rebalanceRight(root, hChange);
    }
    else
    {
        *hChange = 'N';
    }
    return root;
}

Tnode *rebalanceRight(Tnode *root, char *hChange)
{
    if(root == NULL){return root;}
    root->balance++;
    if(root->balance == 0)
    {
        *hChange = 'A';
        return root;
    }
    if(root->balance == 1)
    {
        *hChange = 'N';
        return root;
    }

    //balance is now 2, youngest ancestor, must rotate
    //Case A -- unbalanced in the same direction
    if(root->left->balance == 1)
    {
        root = cwrot(root);
        root->balance = 0;
        root->right->balance = 0;
        *hChange = 'A';
    }
    else if(root->left->balance == 0)
    {
        root = cwrot(root);
        root->balance = -1;
        root->right->balance = 1;
        *hChange = 'N';
    }
    else
    {
        //Case B -- unbalanced in opposite directions
        root->left = ccwrot(root->left);
        root = cwrot(root);
        if(root->balance == 1)
        {
            root->balance = 0;
            root->right->balance = -1;
            root->left->balance = 0;
        }
        else if(root->balance == -1)
        {
            root->balance = 0;
            root->right->balance = 0;
            root->left->balance = 1;
        }
        else
        {
            root->balance = 0;
            root->right->balance = 0;
            root->left->balance = 0;
        }
        *hChange = 'A';
    }
    return root;
}

Tnode *rebalanceLeft(Tnode *root, char *hChange)
{
    if(root == NULL){return root;}
    root->balance--;
    if(root->balance == 0)
    {
        *hChange = 'A';
        return root;
    }
    if(root->balance == -1)
    {
        *hChange = 'N';
        return root;
    }

    //balance is now 2, youngest ancestor, must rotate
    //Case A -- unbalanced in the same direction
    if(root->right->balance == -1)
    {
        root = ccwrot(root);
        root->balance = 0;
        root->left->balance = 0;
        *hChange = 'A';
    }
    else if(root->right->balance == 0)
    {
        root = ccwrot(root);
        root->balance = 1;
        root->left->balance = -1;
        *hChange = 'N';
    }
    else
    {
        //Case B -- unbalanced in opposite directions
        root->right = cwrot(root->right);
        root = ccwrot(root);
        if(root->balance == -1)
        {
            root->balance = 0;
            root->right->balance = 0;
            root->left->balance = 1;
        }
        else if(root->balance == 1)
        {
            root->balance = 0;
            root->right->balance = -1;
            root->left->balance = 0;
        }
        else
        {
            root->balance = 0;
            root->right->balance = 0;
            root->left->balance = 0;
        }
        *hChange = 'A';
    }
    return root;
}

Tnode *ccwrot(Tnode *oldroot)
{
    Tnode *newroot = oldroot->right; //define new root as the right subtree
    oldroot->right = newroot->left; // replace new root with the left subtree of new root
    newroot->left = oldroot; // override newroots left subtree with the original root to complete rotation

    return newroot;
}

Tnode *cwrot(Tnode *oldroot)
{
    Tnode *newroot = oldroot->left; //define new root as the left subtree
    oldroot->left = newroot->right; // replace new root with the right subtree of new root
    newroot->right = oldroot; // override newroots right subtree with the original root to complete rotation

    return newroot;
}

int updateBalance(Tnode **subtree)
{
    if(subtree == NULL || *subtree == NULL){return 0;}
    int hL = updateBalance(&(*subtree)->left); //explore left subtree
    int hR = updateBalance(&(*subtree)->right);
    (*subtree)->balance = hL - hR;
    if(hL > hR)
    {
        (*subtree)->balance = hL - hR;
        if((*subtree)->balance > 1)
        {
            if((*subtree)->left->balance == 1)
            {
                *subtree = cwrot(*subtree);
                (*subtree)->balance = 0;
                (*subtree)->right->balance = 0;
            }
            else
            {
                (*subtree)->left = ccwrot((*subtree)->left);
                *subtree = cwrot(*subtree);
                if((*subtree)->balance == 1)
                {
                    (*subtree)->balance = 0;
                    (*subtree)->right->balance = -1;
                    (*subtree)->left->balance = 0;
                }
                else if((*subtree)->balance == -1)
                {
                    (*subtree)->balance = 0;
                    (*subtree)->right->balance = 0;
                    (*subtree)->left->balance = 1;
                }
                else
                {
                    (*subtree)->balance = 0;
                    (*subtree)->right->balance = 0;
                    (*subtree)->left->balance = 0;
                }
            }
        }
        return hL + 1;
    }
    else
    {
        (*subtree)->balance = hR - hL;
        if((*subtree)->balance < -1)
        {
            if((*subtree)->right->balance == -1)
            {
                *subtree = ccwrot(*subtree);
                (*subtree)  ->balance = 0;
                (*subtree)->left->balance = 0;
            }
            else
            {
                (*subtree)->right = cwrot((*subtree)->right);
                *subtree = ccwrot(*subtree);
                if((*subtree)->balance == -1)
                {
                    (*subtree)->balance = 0;
                    (*subtree)->left->balance = 1;
                    (*subtree)->right->balance = 0;
                }
                else if((*subtree)->balance == 1)
                {
                    (*subtree)->balance = 0;
                    (*subtree)->left->balance = 0;
                    (*subtree)->right->balance = -1;
                }
                else
                {
                    (*subtree)->balance = 0;
                    (*subtree)->right->balance = 0;
                    (*subtree)->left->balance = 0;
                }
            }
        }
        return hR + 1;
    }
}   
#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"
#include "readin.h"
#include "writeout.h"

void findCoords(TreeNode *bTree)
{
    //Post order queueing structure, once it reaches leaf nodes, it queues all the way until it reaches
    //the lowest subtree, either on right or left
    //Dequeues nodes 
    //if cuts are vertical, they should share a y coordinate, left subtree is on the left
    //If cuts are horizontal, they should share an x coordinate for the two rooms, right subtree is on the right
    Stack *preorder = NULL;
    bTree->x = 0;
    bTree->y = 0;
    preorder = push(preorder, bTree);
    TreeNode *temp;
    while(preorder != NULL)
    {
        temp = pop(&preorder);
        if(temp->label == 'V' && temp->leaf == 0) //Check if cut is vertical, set coordinates accordingly
        {
            temp->left->x = temp->x; 
            temp->left->y = temp->y; //Shared y coordinate
            temp->right->x = temp->x + temp->left->width; //right will be to the right of left, by size of left
            temp->right->y = temp->y;
            preorder = push(preorder, temp->right);
            preorder = push(preorder, temp->left);

        }
        else if(temp->label == 'H' && temp->leaf == 0) //Check if horizontal
        {
            temp->left->x = temp->x; //Shared x coordinate
            temp->left->y = temp->y + temp->right->height; //Left tree will be ABOVE right, by size of right
            temp->right->x = temp->x;
            temp->right->y = temp->y;
            preorder = push(preorder, temp->right);
            preorder = push(preorder, temp->left);
        }
    }
}

TreeNode *postorderOut(char *postOrder, char *blockOut, char *detOut, TreeNode *printTree)
{
    //File management
    FILE *trvsl = fopen(postOrder, "w");
    if(trvsl == NULL)
    {
        return NULL;
    }
    FILE *dim = fopen(blockOut, "w");
    if(dim == NULL)
    {
        fclose(trvsl);
        return NULL;
    }
    FILE *det = fopen(detOut, "w");
    if(det == NULL)
    {
        fclose(trvsl);
        fclose(dim);
        return NULL;
    }


    //Pointers and setup
    Stack *postorder = NULL;
    TreeNode *temp = printTree;
    postorder = push(postorder, printTree);
    //Postorder traversal
    while(postorder != NULL)
    {
        temp = pop(&postorder);
        if(temp->visited == 1 || temp->left == NULL)
        {
            postPrint(trvsl, temp); //post order printing
            dimOut(dim, temp); //Dimensions of every box
            detailedOut(det, temp); //Dimensions and coordinates of all leaf nodes
            temp->visited = 0;
        }
        else
        {
            temp->visited = 1; //mark temporarily as visited
            postorder = push(postorder, temp); //since post-order, self will be last
            postorder = push(postorder, temp->right); //Right right before
            postorder = push(postorder, temp->left); //And left tree we descend immediately
        }
    }
    fclose(trvsl); //close files
    fclose(dim);
    fclose(det);
    return(printTree);
}

void postPrint(FILE *stream, TreeNode *focal)
{
    if(focal->leaf == 0 && (focal->label == 'H' || focal->label == 'V'))
    {
        fprintf(stream, "%c\n", focal->label);
    }
    else
    {
        fprintf(stream, "%d(%d,%d)\n", focal->label, focal->width, focal->height);
    }    
}

void dimOut(FILE *stream, TreeNode *focal)
{
    if(focal->leaf == 0 && (focal->label == 'V' || focal->label == 'H'))
    {
        fprintf(stream, "%c(%d,%d)\n", focal->label, focal->width, focal->height);
    }
    else{
        fprintf(stream, "%d(%d,%d)\n", focal->label, focal->width, focal->height);
    }
}

void detailedOut(FILE *stream, TreeNode *focal)
{
    if(focal->leaf == 0 && (focal->label == 'V' || focal->label == 'H')) {return;} //Skips non-leaf nodes
    fprintf(stream, "%d((%d,%d)(%d,%d))\n", focal->label, focal->width, focal->height, focal->x, focal->y);
}

void freeTreeIt(TreeNode *bTree)
{
    Stack *freeing = NULL; //Iterative function to free tree
    TreeNode *node;
    freeing = push(freeing, bTree);
    while(freeing != NULL)
    {
        node = pop(&freeing);
        if(node->left != NULL) {
            freeing = push(freeing, node->left);
            freeing = push(freeing, node->right);
        }
        free(node);
    }
}
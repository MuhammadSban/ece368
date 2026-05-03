#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"
#include "readin.h"
#include "writeout.h"

TreeNode *treeRead(char *filename)
{
    //Main tree, temporary variable for new node, focus node to determine relationship between
    TreeNode *temp;
    TreeNode *left;
    TreeNode *right;

    Stack *reads = NULL;
    int hold = 0;
    FILE *fptr = fopen(filename, "r");
    if(fptr == NULL)
    {
        return NULL;
    }

    //read first, create node and push
    temp = createNode(NULL, NULL, 1, 0, 0);
    if(temp == NULL) {return NULL;}
    fscanf(fptr, "%d(%d,%d)\n", &(temp->label), &(temp->width), &(temp->height));
    temp->leaf = 1;
    reads = push(reads, temp);

    //Exception handling
    if(reads == NULL)
    {
        freeTreeIt(temp);
        freeStack(&reads);
        return NULL;
    }
    while(fscanf(fptr, " %lc", &hold) == 1)
    {
        temp = createNode(NULL, NULL, hold, 0, 0);
        if(temp == NULL)
        {
            freeTreeIt(temp);
            freeStack(&reads);
            return NULL;
        }
        if(hold == 'V' || hold == 'H')
        {
            right = pop(&reads);
            left = pop(&reads);
            temp->left = left;
            temp->right = right;
            temp->leaf = 0;
            reads = push(reads, temp);
            
        }
        else
        {
            fseek(fptr, -1, SEEK_CUR);
            fscanf(fptr, "%d(%d,%d)\n", &(temp->label), &(temp->width), &(temp->height));
            temp->leaf = 1;
            reads = push(reads, temp);
        }
    }
    fclose(fptr);
    temp = pop(&reads);
    freeStack(&reads);
    return temp;
}


TreeNode *createNode(TreeNode *left, TreeNode *right, int label, int width, int height)
{
    TreeNode *newNode = malloc(sizeof(*newNode));
    if(newNode == NULL){return NULL;}
    newNode->left = left;
    newNode->right = right;
    newNode->label = label;
    newNode->width = width;
    newNode->height = height;
    newNode->x = 0;
    newNode->y = 0;
    newNode->visited = 0;
    return(newNode);
}

void NodeAdds(TreeNode *Root, TreeNode *Second)
{
    if(Root->label == 'V')
    {
        Root->width += Second->width;
        if(Second->height > Root->height)
        {
            Root->height = Second->height;
        }
    }
    else if(Root->label == 'H')
    {
        Root->height += Second->height;
        if(Second->width > Root->width)
        {
            Root->width = Second->width;
        }
    }
}


void assignWidths(TreeNode *Root)
{
    if(Root == NULL) return;
    if(Root->leaf == 1) return;
    
    assignWidths(Root->left);
    assignWidths(Root->right);
    
    if(Root->left != NULL)  NodeAdds(Root, Root->left);
    if(Root->right != NULL) NodeAdds(Root, Root->right);
}
#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"
#include "readin.h"
#include "writeout.h"

TreeNode *treeRead(char *filename)
{
    //Main tree, temporary variable for new node, focus node to determine relationship between
    TreeNode *binaryTree;
    TreeNode *temp;
    TreeNode *focus;

    Stack *reads = NULL;
    int hold = 0;
    FILE *fptr = fopen(filename, "r");
    if(fptr == NULL)
    {
        return NULL;
    }

    //read first, create node and push
    fscanf(fptr, " %lc", &hold);
    binaryTree = createNode(NULL, NULL, hold, 0, 0);
    if(binaryTree == NULL) {return NULL;}
    reads = push(reads, binaryTree);
    binaryTree->leaf = 0;
    if(reads == NULL)
    {
        freeTreeIt(binaryTree);
        freeStack(&reads);
        return NULL;
    }

    while(fscanf(fptr, " %lc", &hold) == 1)
    {
        temp = createNode(NULL, NULL, hold, 0, 0);
        if(temp == NULL)
        {
            freeTreeIt(binaryTree);
            freeStack(&reads);
            return NULL;
        }
        if(hold == 'V' || hold == 'H')
        {
            temp->leaf = 0;
            fscanf(fptr, "\n");
            focus = pop(&reads);
            if(focus->visited)
            {
                focus->right = temp;
                focus->visited = 0;
            }
            else
            {
                focus->left = temp;
                focus->visited = 1;
                reads = push(reads, focus);
                if(reads == NULL)
                {
                    freeTreeIt(binaryTree);
                    freeStack(&reads);
                    return NULL;
                }
            }
            reads = push(reads, temp);
            if(reads == NULL)
            {
                freeTreeIt(binaryTree);
                freeStack(&reads);
                return NULL;
            }
        }
        else
        {
            temp->leaf = 1;
            fseek(fptr, -1, SEEK_CUR);
            fscanf(fptr, "%d(%d,%d)\n", &(temp->label), &(temp->width), &(temp->height));
            focus = pop(&reads);
            if(focus->visited)
            {
                focus->right = temp;
                focus->visited = 0;
            }
            else{
                focus->left = temp;
                focus->visited = 1;
                reads = push(reads, focus);
                if(reads == NULL)
                {
                    freeTreeIt(binaryTree);
                    freeStack(&reads);
                    return NULL;
                }
            }
        }
            //Build left subtrees until leafs, then try right. Once right is done, go back to last right, repeat until you
            //get back to root, then do entire right subtree, repeating the process. Requires a top down construction of the tree
            //push all non-leaf nodes, pop every time you encounter a leaf node, and use a status marker to tell
            //whether we need to add to the left or right subtree
            //If add to right subtree, don't requeuu
            //continue
    }
    fclose(fptr);
    freeStack(&reads);
    return binaryTree;
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
    //Pointers and setup
    Stack *postorder = NULL;
    TreeNode *temp = Root;
    TreeNode *last;
    TreeNode *nextlast;
    postorder = push(postorder, Root);
    while(postorder != NULL)
    {
        temp = pop(&postorder);
        if(temp == NULL){break;}
        if(temp->visited == 1 || temp->left == NULL)
        {
            last = pop(&postorder);
            nextlast = pop(&postorder);
            if((last != NULL) && (last->left == temp || last->right == temp))
            {
                NodeAdds(last, temp);
            }
            if((nextlast != NULL) && (nextlast->left == temp || nextlast->right == temp))
            {
                NodeAdds(nextlast, temp);
            }
            postorder = push(postorder, nextlast);
            postorder = push(postorder, last);
            //printf("temp lab %c\n", temp->label);
            temp->visited = 0;
        }
        else
        {
            temp->visited = 1;
            postorder = push(postorder, temp);
            postorder = push(postorder, temp->right);
            postorder = push(postorder, temp->left);
        }
    }
    freeStack(&postorder);
}
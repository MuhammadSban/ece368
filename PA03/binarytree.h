#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct _TreeNode {
    int label;
    int width;
    int height;
    char leaf;
    int x;
    int y;
    char visited;
    struct _TreeNode *left;
    struct _TreeNode *right;
} TreeNode;

typedef struct _Stack {
    TreeNode *curr;
    struct _Stack *next;
} Stack;

#endif

Stack *push(Stack *current, TreeNode *newnode);

TreeNode *pop(Stack **current);

void freeStack(Stack **current);


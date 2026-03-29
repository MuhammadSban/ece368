#ifndef __READIN_H__
#define __READIN_H__
#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"
#include "readin.h"

TreeNode *treeRead(char *filename);

TreeNode *createNode(TreeNode *left, TreeNode *right, int label, int width, int height);

void NodeAdds(TreeNode *Root, TreeNode *Second);

void assignWidths(TreeNode *Root);

#endif
#include "binarytree.h"

void findCoords(TreeNode *bTree);

TreeNode *postorderOut(char *postOrder, char *blockOut, char *detailedOut, TreeNode *printTree);

void prePrint(FILE *stream, TreeNode *focal);

void dimOut(FILE *stream, TreeNode *focal);

void detailedOut(FILE *stream, TreeNode *focal);

void freeTreeIt(TreeNode *bTree);

void newPrint(TreeNode *curr, FILE* fptr);
#include "hbt.h"

Tnode *buildTree(char *filename);

Tnode *insertNode(Tnode *root, Tnode *newN, char *hChange);

Tnode *deleteNode(Tnode *root, Tnode *newN, char *hChange);

Tnode *ccwrot(Tnode *oldroot);

Tnode *cwrot(Tnode *oldroot);

int updateBalance(Tnode **subtree);

Tnode *rebalanceLeft(Tnode *root, char *hChange);
Tnode *rebalanceRight(Tnode *root, char *hChange);
Tnode *findPred(Tnode *root, Tnode *orig, char *hChange);

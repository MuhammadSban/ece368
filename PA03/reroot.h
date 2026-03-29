void rerootAB(TreeNode **root, TreeNode **focal, int dirtrav, char *writeFile);

void preOrderOut(TreeNode *root, FILE *stream);

void resetCoords(TreeNode *root);

void findOptimalSubtree(TreeNode **root, TreeNode **focal, long *minSize, char *writeFile);

//void coordAdds(TreeNode *Root, TreeNode *Second);

//void coordSubtract(TreeNode *Root, TreeNode *other, TreeNode *Second);
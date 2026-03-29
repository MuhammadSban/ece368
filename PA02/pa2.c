#include "readin.h"
#include "writeout.h"
#include "binarytree.h"

#include <stdio.h>s
#include <stdlib.h>

//TreeNode *makeTestTree(int length);

int main(int argc, char **argv)
{
    if(argc != 5)
    {
        printf("wrong args\n");
        return EXIT_FAILURE;
    }

    TreeNode *postread = treeRead(argv[1]);
    //TreeNode *preread = makeTestTree(500000);
    if(postread == NULL)
    {
        return EXIT_FAILURE;
    }

    assignWidths(postread);

    findCoords(postread);

    if(postorderOut(argv[2], argv[3], argv[4], postread) == NULL)
    {
        freeTreeIt(postread);
        return EXIT_FAILURE;
    }

    freeTreeIt(postread);

    return EXIT_SUCCESS;
}

/*TreeNode *makeTestTree(int length)
{
    TreeNode *root = createNode(NULL, NULL, 'V', 1, 1);
    TreeNode *slide = root;
    for(int i = 0; i < length; i++)
    {
        if(i == 'H' || i == 'V'){continue;}
        slide->left = createNode(NULL, NULL, i, 1, 1);
        slide->left->visited = 1;
        slide->right = createNode(NULL, NULL, 'H', 0, 0);
        slide = slide->right;
    }
    slide->left = createNode(NULL, NULL, 1, 1, 1);
    slide->right = createNode(NULL, NULL, 2, 1, 1);
    slide->left->visited = 1;
    slide->right->visited = 1;
    return root;
}*/
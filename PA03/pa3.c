#include "readin.h"
#include "writeout.h"
#include "binarytree.h"
#include "reroot.h"

#include <stdio.h>
#include <stdlib.h>

//TreeNode *makeTestTree(int length);

int main(int argc, char **argv)
{
    if(argc != 6)
    {
        printf("wrong args\n\n\n");
        return EXIT_FAILURE;
    }
    TreeNode *preread = treeRead(argv[1]);
    //TreeNode *preread = makeTestTree(500000);
    if(preread == NULL)
    {
        return EXIT_FAILURE;
    }

    rerootAB(&preread, &preread->left, 0, argv[2]);
    //printf("clears first\n");
    rerootAB(&preread, &preread->right, 1, argv[3]);

    //long minSize = (long)(preread->x) * (long)(preread->y);
    long minSize = (long)(preread->x) * (long)(preread->y);

    assignWidths(preread);
    FILE *fptr = fopen(argv[4], "w");
    if(fptr == NULL)
    {
        freeTreeIt(preread);
        return EXIT_FAILURE;
    }
    newPrint(preread, preread, fptr);

    fclose(fptr);
    freeTreeIt(preread);

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
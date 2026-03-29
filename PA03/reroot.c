#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"
#include "readin.h"
#include "writeout.h"
#include "reroot.h"

void rerootAB(TreeNode **root, TreeNode **focal, int dirtrav, char *writeFile)
{
    //printf("reroot recurses\n");
    if(focal == NULL || *focal == NULL || (*focal)->leaf == 1)
    {
        FILE *toWrite = fopen(writeFile, "w");
        assignWidths(*root);
        findCoords(*root);
        preOrderOut(*root, toWrite);

        //Clean up
        resetCoords(*root);
        fclose(toWrite);
        return;
    }

    TreeNode *currSave = *focal;
    if(dirtrav == 0) //just went left, preserve right edge
    {
        TreeNode *oldRoot = *root;
        *root = currSave;
        oldRoot->left = currSave->left;
        (*root)->left = oldRoot;

        rerootAB(root, &(currSave->right), 1, writeFile);

        currSave->left = oldRoot->left;
        oldRoot->left = currSave;
        (*root) = oldRoot;

    }
    else //just went right, preserve left edge
    {
        TreeNode *oldRoot = *root;
        *root = currSave;
        oldRoot->right = currSave->right;
        (*root)->right = oldRoot;

        rerootAB(root, &(currSave->left), 0, writeFile);

        currSave->right = oldRoot->right;
        oldRoot->right = currSave;
        (*root) = oldRoot;

    }

}

void preOrderOut(TreeNode *root, FILE *stream)
{
    //printf("prout recurses\n");
    if(root == NULL){return;}
    if(root->leaf == 1)
    {
        fprintf(stream, "%d(%d,%d)\n", root->label, root->width, root->height);
        return;
    }
    else
    {
        fprintf(stream, "%c\n", root->label);
    }
    preOrderOut(root->left, stream);
    preOrderOut(root->right, stream);
}

void resetCoords(TreeNode *root)
{
    if(root->leaf == 1)
    {
        root->x = 0;
        root->y = 0;
        return;
    }
    root->x = 0;
    root->y = 0;
    root->width = 0;
    root->height = 0;
    resetCoords(root->left);
    resetCoords(root->right);
}

//Add SAFE restoration and tracking for nodes
//Pass left and right separately? Handle the unique cases 

/*
void findOptimalSubtree(TreeNode **root, TreeNode **focal, long *minSize, char *writeFile)
{
    if((*focal)->leaf == 1)
    {
        return;
    }

    TreeNode *currSave = *focal;
    TreeNode *oldRoot = *root;

    TreeNode *oldRootR = (*root)->right;

    *root = currSave;
    oldRoot->left = currSave->left;
    (*root)->left = oldRoot;

    //update vals

    coordSubtract(oldRoot, oldRoot->right, oldRoot->left);
    coordAdds(oldRoot, currSave->left);

    coordSubtract(*root, (*root)->right, oldRoot->left);
    coordAdds(*root, oldRoot);

    long leftArea = (long)(*root)->x * (long)(*root)->y;

    currSave->left = oldRoot->left;
    oldRoot->left = currSave;
    (*root) = oldRoot;

    //restore vals

    coordSubtract(*root, (*root)->right, oldRoot);
    coordAdds(*root, currSave);

    coordSubtract(oldRoot, oldRoot->right, currSave->left);
    coordAdds(oldRoot, currSave);


    *root = currSave;
    oldRoot->right = currSave->right;
    (*root)->right = oldRoot;

    //update vals

    coordSubtract(oldRoot, oldRoot->left, oldRoot->right);
    coordAdds(oldRoot, currSave->right);

    coordSubtract(*root, (*root)->left, oldRoot->right);
    coordAdds(*root, oldRoot);

    long rightArea = (long)(*root)->x * (long)(*root)->y;

    if(rightArea < leftArea && rightArea < *minSize)
    {
        *minSize = rightArea;
        findOptimalSubtree(root, &(currSave->left), minSize, writeFile);
    }
    else if(leftArea < rightArea && leftArea < *minSize)
    {
        *minSize = leftArea;
        currSave->right = oldRoot->right;
        oldRoot->right = oldRootR;
        (*root) = oldRoot;
        //restore vals
        coordSubtract(*root, (*root)->left, oldRoot);
        coordAdds(*root, currSave);

        coordSubtract(oldRoot, oldRoot->left, currSave->right);
        coordAdds(oldRoot, currSave);

            //update vals

        coordSubtract(oldRoot, oldRoot->right, oldRoot->left);
        coordAdds(oldRoot, currSave->left);

        coordSubtract(*root, (*root)->right, oldRoot->left);
        coordAdds(*root, oldRoot);

        currSave->left = oldRoot->left;
        oldRoot->left = currSave;
        (*root) = oldRoot;
        findOptimalSubtree(root, &(currSave->left), minSize, writeFile);
    }
    else
    {
        currSave->right = oldRoot->right;
        oldRoot->right = oldRootR;
        (*root) = oldRoot;
        //restore vals
        coordSubtract(*root, (*root)->left, oldRoot);
        coordAdds(*root, currSave);

        coordSubtract(oldRoot, oldRoot->left, currSave->right);
        coordAdds(oldRoot, currSave);
    }
}

void coordSubtract(TreeNode *Root, TreeNode *other, TreeNode *Second)
{
    if(Root->label == 'V')
    {
        Root->width -= Second->width;
        if(Second->height > other->height)
        {
            Root->height = other->height;
        }
    }
    else if(Root->label == 'H')
    {
        Root->height -= Second->height;
        if(Second->width > other->width)
        {
            Root->width = other->width;
        }
    }
}

void coordAdds(TreeNode *Root, TreeNode *Second)
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
    */
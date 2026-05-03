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

void rdimPacking(TreeNode **root, TreeNode *focal, TreeNode *prev, int dirtrav, FILE *writeFile)
{
    if(focal == NULL){return;}
    if(focal == (*root) || focal == (*root)->right || focal == (*root)->left)
    {
    if(focal->leaf == 0)
    {
        fprintf(writeFile, "%c\n", focal->label, focal->width, focal->height);
    }
    else
    {
        fprintf(writeFile, "%d\n", focal->label, focal->width, focal->height);
    }
        rdimPacking(root, focal->left, focal, 0, writeFile);
        rdimPacking(root, focal->right, focal, 1, writeFile);
    }

    //reroot according to dirtrav

    TreeNode *currSave = prev;
    long larea;
    long rarea;
    if(dirtrav == 1) //just went right, preserve right edge
    {
        TreeNode *oldRoot = *root;
        *root = currSave;
        oldRoot->left = focal->left;
        (*root)->left = oldRoot;

        rdimPacking(root, focal->left, focal, 0, writeFile);
        rdimPacking(root, focal->right, focal, 1, writeFile);

        currSave->left = oldRoot->left;
        oldRoot->left = currSave;
        (*root) = oldRoot;

    }
    else //just went left, preserve left edge
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

    //Solve for smallest room

    //Print smallest room
    if(focal->leaf == 0)
    {
        fprintf(writeFile, "%c(%d,%d)\n", focal->label, focal->width, focal->height);
    }
    else
    {
        fprintf(writeFile, "%d(%d,%d)\n", focal->label, focal->width, focal->height);
    }
    //Restore and continue recursing


    rdimPacking(root, focal->left, focal, 0, writeFile);
    rdimPacking(root, focal->right, focal, 1, writeFile);
}
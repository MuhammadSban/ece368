#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"
#include "shell_list.h"

Node *advancek(Node *nodeptr, int k);

void swapPts(Node **firstprev, Node **secondprev);

void FreeList(Node *list);

void printLL(Node *list);

Node *List_Load_From_File(char *filename, int *status)
{
    FILE *topen = fopen(filename, "rb");
    long recent;
    if(topen == NULL) {
        *status = -1;
        return NULL;
    }

    Node *fileList = malloc(sizeof(Node));
    if(!fread(&(fileList->value), sizeof(long), 1, topen))
    {
        fclose(topen);
        *status = -1;
        free(fileList);
        return(NULL);
    }
    Node *dummy = fileList;

    while(fread(&recent, sizeof(long), 1, topen))
    {
        dummy->next = malloc(sizeof(Node));
        if(dummy->next == NULL) {
            // allocation failed, clean up
            Node *cur = fileList;
            while(cur) 
            { 
                Node *tmp = cur->next; 
                free(cur); 
                cur = tmp; 
            }
            fclose(topen);
            *status = -1;
            return NULL;
        }
        dummy = dummy->next;
        dummy->value = recent;
    }

    dummy->next = NULL;
    fclose(topen);
    *status = 0;
    return(fileList);
}

int List_Save_To_File(char *filename, Node *list)
{
    FILE *topen = fopen(filename, "wb");
    Node *save = list;
    if(topen == NULL) {
        FreeList(list);
        return -1;
    }
    int num = 0;
    while(list != NULL)
    {
        num += fwrite(&list->value, sizeof(long), 1, topen);
        list = list->next;
    }
    fclose(topen);
    FreeList(save);
    return(num);
}

Node *List_Shellsort(Node *list, long *n_comp)
{
    int sorts;
    //int i;
    int k;
    //int last_exchange;
    //int lastel;
    int sorted;
    //int nle;
    *n_comp = 0;
    Node *first = list;
    Node *second;
    Node *sentinel = malloc(sizeof(Node));
    sentinel->next = list;

    int len = 0;
    while(first != NULL)
    {
        len++;
        first = first->next;
    }
    first = list;
    long *sequence = Generate_2p3q_Seq(len, &sorts);
    //printLL(list);
    for(k = sorts - 1; k >= 0; k--)
    {
        sorted = 0;
        while(!sorted)
        {
            sorted = 1;
            first = sentinel;
            second = advancek(first, sequence[k]);
            while(!(first == NULL || first->next == NULL || second == NULL || second->next == NULL))
            {
                (*n_comp)++;
                if(first->next->value > second->next->value)
                {
                    sorted = 0;
                    swapPts(&first, &second);
                }
                first = first->next;
                second = second->next;
            }
            if(sequence[k] == 1){break;}
        }
    }

    first = sentinel->next;
    free(sequence);
    list = sentinel->next;
    free(sentinel);
    //printLL(list);
    return(list);
}




void swapPts(Node **firstprev, Node **secondprev)
{
    if((*firstprev) == (*secondprev)) {return;}
    Node *first = (*firstprev)->next;
    Node *second = (*secondprev)->next;
    
    // Adjacency special case
    if(first->next == second )
    {
        (*firstprev)->next = second;
        first->next = second->next;
        second->next = first;
        *secondprev = second;
        return;
    }
    
    // Non-adjacent case
    Node *first_next = first->next;
    Node *second_next = second->next;
    
    (*firstprev)->next = second;
    second->next = first_next;
    
    (*secondprev)->next = first;
    first->next = second_next;
}

Node *advancek(Node *nodeptr, int k)
{
    int i;
    for(i = 0; i < k; i++)
    {
        if(nodeptr == NULL){return(NULL);}
        nodeptr = nodeptr->next;
    }
    if(nodeptr == NULL){return(NULL);}
    return nodeptr;
}

void FreeList(Node *list)
{
    Node *temp;
    while(list != NULL)
    {
        temp = list->next;
        free(list);
        list = temp;
    }
}

void printLL(Node *list)
{
    int i = 0;
    while(list != NULL)
    {
        i++;
        printf("%d element: %ld\n", i, list->value);
        list = list->next;
    }
}
#include "decl.h"

//Push new node to stack
Stack *push(Stack *current, graphNode *newnode)
{
    if(newnode == NULL) {return current;}
    Stack *addend = malloc(sizeof(*addend));
    if(addend == NULL) //exception handling
    {
        freeStack(&current);
        return NULL;
    }
    addend->curr = newnode;
    addend->next = current;
    return addend;
}

//Pop node from top of stack
graphNode *pop(Stack **current)
{
    if(*current == NULL) {return NULL;}
    graphNode *node = (*current)->curr;
    Stack *save = *current;
    *current = (*current)->next;
    free(save);
    return node;
}

graphNode *peek(Stack *current)
{
    if(current == NULL || current->curr == NULL) {return NULL;}
    graphNode *node = current->curr;
    return node;
}

//Mostly used for exception-handling /special case where we need to empty stack
void freeStack(Stack **current)
{
    if(current == NULL){return;}
    Stack *save = *current;
    while(*current != NULL)
    {
        *current = (*current)->next;
        free(save);
        save = *current;
    }
}
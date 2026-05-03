#include "decl.h"

void fOut(char *filename, graphNode **list, graphNode *source)
{
    FILE *fptr = fopen(filename, "w");
    if(fptr == NULL){return;}
    Stack *order = NULL;
    graphNode *focal = list[0];
    int destForce = focal->poleY;
    focal->poleX = focal->pred->poleX;
    graphNode *next;

    int xmove;
    int ymove;
    char statsave;


    while(focal != NULL && focal->pred != NULL && focal->curridx != -1)
    {
        order = push(order, focal);
        //printf("Pushed node with poleX: %d, poleY: %d\n", focal->poleX, focal->poleY);
        focal = focal->pred;
        if(focal->poleY == -1)
        {
            focal->poleX = order->curr->poleX;
        }
    }
    order = push(order, source);
    //printf("Pushed node with poleX: %d, poleY: %d\n", focal->poleX, focal->poleY);


    while(order != NULL && destForce != 0)
    {
        focal = pop(&order);
        next = peek(order);
        if(focal == NULL || next == NULL){break;}
        if(focal->curridx == -1 && focal->weights[next->curridx] == 0)
        {
            fprintf(fptr, "(%d,%d)(%d,%d)\n", focal->poleX, focal->poleY, next->poleX, next->poleY);
            continue;
        }
        if(focal->weights[next->curridx] == 0)
        {
            fprintf(fptr, "(%d,%d)(%d,%d)\n", focal->poleX, focal->poleY, focal->poleX + 1, focal->poleY);
            continue;
        }
        statsave = focal->boardState;
        xmove = focal->poleX;
        ymove = focal->poleY;
        while(1)
        {
            if(focal->boardState == 'V')
            {
                fprintf(fptr, "(%d,%d)(%d,%d)\n", xmove, ymove, xmove + 1, ymove);
                //printf("originating at poleX: %d, poleY: %d, currently at poleX: %d, poleY: %d\n", focal->poleX, focal->poleY, xmove, ymove);
                if(ymove == next->poleY && (xmove == next->poleX || xmove + 1 == next->poleX || xmove == next->poleX + 1)){break;}
            }
            else
            {
                fprintf(fptr, "(%d,%d)(%d,%d)\n", xmove, ymove, xmove, ymove + 1);
                //printf("originating at poleX: %d, poleY: %d, currently at poleX: %d, poleY: %d\n", focal->poleX, focal->poleY, xmove, ymove);
                if((xmove == next->poleX || xmove == next->poleX + 1) && (ymove == next->poleY || ymove + 1 == next->poleY)){break;}

            }
            if(focal->boardState == 'V')
            {
                if(next->poleY > ymove) // Going right
                {
                    if(next->poleX >= (xmove + 1)) //down
                    {
                        xmove++;
                    }
                    //do nothing if up
                }
                else //Going left
                {
                    if(next->poleX >= (xmove + 1)) // going down
                    {
                        xmove++;
                        ymove--;
                        if(ymove < 0)
                        {
                            ymove += 1;
                        }
                    }
                    else //going up
                    {
                        ymove--;
                        if(ymove < 0)
                        {
                            ymove = 0;
                        }
                    }
                }
                focal->boardState = 'H';
            }
            else
            {
                if(ymove == destForce || ymove == (destForce - 1))
                {
                    destForce = 0;
                    break;
                }
                if(next->poleX >= (xmove - 1)) //down
                {
                    if(next->poleY > ymove) //right
                    {
                        ymove++;
                    }
                    //if go left, no change
                }
                else //up
                {
                    if(next->poleY > ymove) //right
                    {
                        xmove--;
                        ymove++;
                        if(xmove < 0)
                        {
                            xmove = 0;
                        }
                    }
                    else //left
                    {
                        xmove--;
                        if(xmove < 0)
                        {
                            xmove = 0;
                        }
                    }
                }
                focal->boardState = 'V';
            }
        }
        focal->boardState = statsave;
    }
    freeStack(&order);
    fclose(fptr);
}

void sOut(char *filename, graphNode **list, graphNode *source, int m, int n, int numNodes)
{
    FILE *fptr = fopen(filename, "w");
    int curr;
    graphNode *track;
    for(int i = 0; i < m; i++)
    {
        source->poleX = i;
        source->hops = 0;
        source->weights[0] = 2 * n;
        for(int j = 1; j <= numNodes; j++)
        {
            source->poleX = i;
            //source->poleY = 0;
            trivialTwo(&source, list[j]);  
            list[j]->inPQ = 1;   
            list[j]->pred = source;  
            list[j]->hops = __INT_MAX__ - 10;    
        }
        dijkstra(source->adjNodes, source, numNodes);
        curr = 0;
        track = list[0];
        while(track->pred != NULL)
        {
            curr += track->pred->weights[track->curridx];
            track = track->pred;
        }
        fprintf(fptr, "%d\n", curr);
    }
    fclose(fptr);
}

void cleanUp(graphNode **list, int n)
{
    for(int i = 0; i <= n; i++)
    {
        if(list[i]->weights != NULL)
        {
            free(list[i]->weights);
        }
        free(list[i]);
    }
    free(list);
}
#include "decl.h"

void dijkstra(graphNode **list, graphNode *source, int numNodes)
{
    int i;
    graphNode *u;
    pQueue *PQ = malloc(sizeof(pQueue));
    PQ->weights = malloc(sizeof(int) * (numNodes + 1));

    PQ->heap = malloc(sizeof(graphNode *) * (numNodes + 1));
    memcpy(PQ->heap, source->adjNodes, sizeof(graphNode *) * (numNodes + 1));
    PQ->size = numNodes + 1;
    memcpy(PQ->weights, source->weights, sizeof(int) * (numNodes + 1));

    for(i = ((numNodes + 1) / 2 - 1); i >= 0; i--)
    {
        PQ = downwardsHeapify(PQ, i, numNodes);
    }


    while(PQ->size != 0)
    {
        u = ExtractMin(PQ);

        if(u->weights == NULL || u->curridx == 0){continue;}
        for(i = 0; i <= numNodes; i++)
        {
            if(i == u->curridx)
            {
                continue;
            }
            if(u->adjNodes[i]->inPQ && (source->weights[i] > source->weights[u->curridx] + u->weights[i]))
            {
                //d[v] = d[u] + w<u,v>;
                source->weights[i] = source->weights[u->curridx] + u->weights[i];
                PQ->weights[source->adjNodes[i]->pqind] = source->weights[i];
                u->adjNodes[i]->pred = u;
                u->adjNodes[i]->hops = u->hops + 1;
                PQ = upwardsHeapify(PQ, source->adjNodes[i]->pqind);
            }
            else if(u->adjNodes[i]->inPQ && (source->weights[i] == source->weights[u->curridx] + u->weights[i]) && (u->hops + 1 > u->adjNodes[i]->hops))
            {
                source->weights[i] = source->weights[u->curridx] + u->weights[i];
                PQ->weights[source->adjNodes[i]->pqind] = source->weights[i];
                u->adjNodes[i]->pred = u;
                u->adjNodes[i]->hops = u->hops + 1;
                PQ = upwardsHeapify(PQ, source->adjNodes[i]->pqind);
            }
        }
    }
    free(PQ->weights);
    free(PQ->heap);
    free(PQ);
}


//called after read at the end, initializes all weights to zero or the trivial distance between them
//calculates number of rotations between two nodes, based on their orientations and 
void trivialSolution(graphNode **source, graphNode *destination) 
{
    //find index of new node
    int nodeInd;
    nodeInd = destination->curridx;
    if(nodeInd == (*source)->curridx)
    {
        return;
    }
        
    // end node case
    if(nodeInd == 0)
    {
        (*source)->weights[nodeInd] = (2 * (destination->poleY - (*source)->poleY)) - 1;
        if((*source)->poleY == -1)
        {
            (*source)->weights[nodeInd] --;
        }
        //printf("Distance between source (%d, %d) and destination (%d, %d) is %d\n", (*source)->poleX, (*source)->poleY, destination->poleX, destination->poleY, (*source)->weights[nodeInd]);
        return;
    }

    //detect adjacency logic

    if(determineAdj((*source)->poleX, (*source)->poleY, destination->poleX, destination->poleY))
    {
        //printf("Distance between source (%d, %d) and destination (%d, %d) is 0\n", (*source)->poleX, (*source)->poleY, destination->poleX, destination->poleY);
        (*source)->weights[nodeInd] = 0;
        return;
    }

    //if not adjacent, find the appropriate distance
    (*source)->weights[nodeInd] = detDist(*source, destination);
}

void trivialTwo(graphNode **source, graphNode *destination) 
{
    //find index of new node
    int nodeInd;
    nodeInd = destination->curridx;
    if(nodeInd == (*source)->curridx)
    {
        return;
    }
        
    // end node case
    if(nodeInd == 0)
    {
        (*source)->weights[nodeInd] = (2 * (destination->poleY - (*source)->poleY)) - 1;
        if((*source)->poleY == -1)
        {
            (*source)->weights[nodeInd] --;
        }
        //printf("2Distance between source (%d, %d) and destination (%d, %d) is %d\n", (*source)->poleX, (*source)->poleY, destination->poleX, destination->poleY, (*source)->weights[nodeInd]);
        return;
    }

    //detect adjacency logic

    if(((destination->poleX == (*source)->poleX) || (destination->poleX == (*source)->poleX - 1)) && destination->poleY == 0)
    {
        //printf("2Distance between source (%d, %d) and destination (%d, %d) is 0\n", (*source)->poleX, (*source)->poleY, destination->poleX, destination->poleY);
        (*source)->weights[nodeInd] = 0;
        return;
    }

    //if not adjacent, find the appropriate distance

    int absX;//2n -1
    int absY; //2n
    absX = 2 * (destination->poleX - (*source)->poleX);
    if(absX < 0)
    {
        absX = absX * -1;
    }
    absX--;
    absY = 2 * (destination->poleY);
    (*source)->weights[nodeInd] = absX > absY ? absX : absY;
    //printf("2Distance between source (%d, %d) and destination (%d, %d) is %d\n", (*source)->poleX, (*source)->poleY, destination->poleX, destination->poleY, (*source)->weights[nodeInd]);
}

int determineAdj(int x, int y, int xp, int yp)
{
    if(y != yp) //cannot be adjacent, return
    {
        return 0;
    }
    if((x - xp) == 1 || (x - xp) == -1) //adjacent
    {
        return 1;
    }
    return 0; //non-adjacent in all remaining cases
}

int detDist(graphNode *source, graphNode *destination)
{
    int absX;

    absX = (source->poleX - destination->poleX);

    if(absX < 0)
    {
        absX = absX * -1;
    }
    absX--;
    absX *= 2;


    int absY = 2 * (destination->poleY - source->poleY);

    if(absY < 0)
    {
        absY = absY * -1;
    }
    absY -= 1;

    //printf("absX: %d, absY: %d\n", absX, absY);
    int max = (absX > absY) ? absX : absY;
    if(source->poleY == -1)
    {
        max = 2 * (destination->poleY);
    }

    //printf("Distance between source (%d, %d) and destination (%d, %d) is %d\n", source->poleX, source->poleY, destination->poleX, destination->poleY, max);
    return max;
}
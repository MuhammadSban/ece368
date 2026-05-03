#include "decl.h"

graphNode *trueInitialization(graphNode **list, int numNodes, int M, int N)
{
    int i;
    graphNode *superSource = malloc(sizeof(graphNode));
    graphNode *superDestination = malloc(sizeof(graphNode));

    //source initialized
    superSource->poleX = -1;
    superSource->poleY = -1;
    superSource->hops = 0;
    superSource->adjNodes = list;
    superSource->curridx = -1;
    superSource->weights = malloc(sizeof(int)* (numNodes + 1));
    superSource->boardState = 'H';
    superSource->pred = NULL;

    //destination initialized
    superDestination->poleX = M;
    superDestination->poleY = N;
    superDestination->adjNodes = list;
    superDestination->curridx = 0;
    superDestination->pqind = 0;
    superDestination->inPQ = 1;
    superDestination->weights = NULL;
    list[0] = superDestination;
    superDestination->pred = superSource;
    superDestination->hops = __INT_MAX__;

    for(i = 1; i <= numNodes; i++)
    {
        list[i]->adjNodes = list;
        list[i]->boardState = 'V';
        list[i]->inPQ = 1;
        list[i]->pred = superSource;
        list[i]->weights = malloc(sizeof(int) * (numNodes + 1));
        list[i]->hops = __INT_MAX__;
        for(int j = 0; j <= numNodes; j++)
        {
            if(i == j){continue;}
            trivialSolution(&(list[i]), list[j]);
        }
    }

    for(int j = 0; j <= numNodes; j++)
    {
        trivialSolution(&superSource, list[j]);
    }

    return superSource;
}


graphNode *readIn(char *filename, int *nodes) //type define graph
{
    FILE *read = fopen(filename, "r");
    if(read == NULL){return NULL;}

    int m; //rows
    int n; //columns

    int x = 0; //counter x
    int y = 0; //counter y
    char c; //temp char
    *nodes = 0;
    fscanf(read, "%d %d\n", &m, &n);
    stLL *lofnodes = NULL;


while((c = fgetc(read)) != EOF)    {
    if(c == '\n')
        {
            x++;
            y = 0;
            continue;
        }
    if(c == '1')
        {
            (*nodes)++;
            stLL *temp = lofnodes;
            lofnodes = malloc(sizeof(stLL));
            lofnodes->curr = malloc(sizeof(graphNode));
            lofnodes->curr->poleX = x;
            lofnodes->curr->poleY = y;
            lofnodes->curr->boardState = 'V';
            lofnodes->next = temp;
            //printf("vertical board at poleX: %d, poleY: %d\n", x, y);
        }
    y++;
    }

    graphNode **standardList = linkedListtoArray(lofnodes, *nodes);
    graphNode *source = trueInitialization(standardList, *nodes, m, n);
    fclose(read);
    return source;
}

graphNode **linkedListtoArray(stLL *listofnodes, int n)
{
    graphNode **list = malloc(sizeof(graphNode) * (n + 1));
    stLL *save;
    while(listofnodes != NULL)
    {
        save = listofnodes;
        listofnodes->curr->curridx = n;
        listofnodes->curr->pqind = n;
        list[n--] = listofnodes->curr;
        listofnodes = listofnodes->next;
        free(save);
    }
    return list;
}
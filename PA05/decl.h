#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct graphNode
{
    char boardState; 
    struct graphNode **adjNodes; //List of adjacent nodes
    struct graphNode *pred;
    int curridx; //illegal index, self-referential
    int pqind;
    int inPQ;
    int poleX;
    int poleY;
    int hops;
    int *weights; //number of rotations required for a board to reach the corresponding adj board/node
} typedef graphNode; 

struct stLL
{
    graphNode *curr;
    struct stLL *next;
} typedef stLL;

struct pQueue
{
    graphNode **heap;
    int *weights;
    int size;
    int capacity;
} typedef pQueue;

typedef struct _Stack {
    graphNode *curr;
    struct _Stack *next;
} Stack;

//stack.c

Stack *push(Stack *current, graphNode *newnode);

graphNode *pop(Stack **current);

graphNode *peek(Stack *current);

void freeStack(Stack **current);

//queue.c

pQueue *downwardsHeapify(pQueue *queue, int ind, int n);

pQueue *upwardsHeapify(pQueue *queue, int ind);

graphNode *ExtractMin(pQueue *queue);

//readin.c

graphNode *trueInitialization(graphNode **list, int numNodes, int M, int N);

graphNode *readIn(char *filename, int *nodes);

graphNode **linkedListtoArray(stLL *listofnodes, int n);

//solving.c

void dijkstra(graphNode **list, graphNode *source, int numNodes);

void trivialSolution(graphNode **source, graphNode *destination); 

void trivialTwo(graphNode **source, graphNode *destination);

int detDist(graphNode *source, graphNode *destination);

int determineAdj(int x, int y, int xp, int yp);

//output.c

void cleanUp(graphNode **list, int n);

void fOut(char *filename, graphNode **list, graphNode *source);

void sOut(char *filename, graphNode **list, graphNode *source, int m, int n, int numNodes);
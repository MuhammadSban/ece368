#include "decl.h"



int main(int argc, char **argv)
{
    if(argc != 4)
    {
        return EXIT_FAILURE;
    }
    int gSize;
    graphNode *greatGraph = readIn(argv[1], &gSize); //set everything up
    if(greatGraph == NULL){return EXIT_FAILURE;}

    int n = greatGraph->adjNodes[0]->poleY;
    int m = greatGraph->adjNodes[0]->poleX;
    //for(int i = 0; i <= gSize; i++)
    //{
    //    printf("Node %d: poleX: %d, poleY: %d, weight: %d\n", i, greatGraph->adjNodes[i]->poleX, greatGraph->adjNodes[i]->poleY, greatGraph->weights[i]);
    //}

    dijkstra(greatGraph->adjNodes, greatGraph, gSize); //solve

    //output
    fOut(argv[2], greatGraph->adjNodes, greatGraph);

    sOut(argv[3], greatGraph->adjNodes, greatGraph, m, n, gSize);
    cleanUp(greatGraph->adjNodes, gSize);

    free(greatGraph->weights);
    free(greatGraph);

    return EXIT_SUCCESS;
}
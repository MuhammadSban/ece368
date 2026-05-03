#include "decl.h"

pQueue *upwardsHeapify(pQueue *queue, int ind)
{
    graphNode *temp = queue->heap[ind];
    int new = queue->weights[ind];
    int child = ind;
    int parent = (child-1)/2;
    while(child > 0 && queue->weights[parent] > new)
    {
        queue->weights[child] = queue->weights[parent];
        queue->heap[child] = queue->heap[parent];
        queue->heap[child]->pqind = child;

        child = parent;
        parent = (child-1)/2;
    }
    queue->weights[child] = new;
    queue->heap[child] = temp;
    queue->heap[child]->pqind = child;
    return queue;

}

pQueue *downwardsHeapify(pQueue *queue, int ind, int n)
{
    graphNode *temp = queue->heap[ind];
    int tempweight = queue->weights[ind];
    int j;
    while((j = 2*ind+1) <= n)
    {
        if (j < (n) && queue->weights[j] > queue->weights[j+1])
        {
            j = j + 1;
        }
        if (tempweight <= queue->weights[j])
        {
            break;
        }
        else
        {
            //array[ind] = array[j];
            queue->heap[ind] = queue->heap[j];
            queue->weights[ind] = queue->weights[j];
            queue->heap[ind]->pqind = ind;
            
            ind = j;

            //array[ind] = temp;
            queue->heap[ind] = temp;
            queue->weights[ind] = tempweight;
            queue->heap[ind]->pqind = ind;
        }
    }
    return queue;
}

graphNode *ExtractMin(pQueue *queue)
{
    if(queue->size == 0){return NULL;}

    graphNode *min = queue->heap[0];
    min->inPQ = 0;

    queue->heap[0] = queue->heap[queue->size - 1];
    queue->weights[0] = queue->weights[queue->size - 1];

    queue->heap[0]->pqind = 0;

    queue->size--;

    downwardsHeapify(queue, 0, queue->size - 1);

    return min;
}
#ifndef _QUEUE_H
#define	_QUEUE_H
#include<assert.h>
#include "heap.h"
#include "bilist.h"
struct queue{
    int length;
    int heapSize;
    void *heap;
};


typedef struct queue priorityQueue;
priorityQueue heapAlloc(int size,int n){
    priorityQueue q;
    q.length=n;
    q.heapSize=0;
    q.heap=(void *)malloc(n*size);
    return q;
}

void enQueue(priorityQueue *q,int size,void *e,int(*compare)(void *,void *)){
    if(q->heapSize==q->length)
        return;
    int i=q->heapSize++;
    memcpy(q->heap+i*size,e,size);
    while (i>0&&compare(q->heap+parent(i)*size,q->heap+i*size)<0){
        swap(q->heap+i*size,q->heap+parent(i)*size,size);
        i=parent(i);
    }
}

void * deQueue(priorityQueue *q,int size,int(*compare)(void *,void *)){
    assert(q->heapSize>=1);
    void *top=(void*)malloc(size);
    memcpy(top,q->heap,size);
    memcpy(q->heap,q->heap+(--q->heapSize)*size,size);
    heapify(q->heap,size,0,q->heapSize,compare);
    return top;
}

int empty(priorityQueue q){
    if(q.heapSize<1)
        return 1;
    return 0;
}
void fix(priorityQueue *q,int size,int(*compare)(void *,void *)){
    int i;
    for(i=q->heapSize/2;i>=0;i--)
        heapify(q->heap,size,i,q->heapSize,compare);
}
void pqueueClear(priorityQueue *q){
    free(q->heap);
    q->heap=NULL;
    q->heapSize=q->length=0;
}
struct Queue{
    List *head;
    List *trail;
};
typedef struct Queue Queue;
Queue *createQueue(){
    Queue *q=(Queue*)malloc(sizeof(Queue));
    q->head=q->trail=NULL;
    return q;
}
int Empty(Queue *q){
    return q->head==NULL;
}
void EnQueue(Queue *q, void *e){
    listPushBack(&(q->trail),e);
    if(Empty(q))
        q->head=q->trail;
}
void *DeQueue(Queue *q){
    void *e=listDeleteBeging(&(q->head));
    if(Empty(q))
        q->trail=NULL;
    return e;
}
void queueClear(Queue *q){
    q->trail=NULL;
    if(q->head!=NULL){
        listClear(q->head);
        free(q->head);
        q->head=NULL;
   }
}
#endif

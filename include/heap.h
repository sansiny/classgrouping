#ifndef _HEAP_H
#define	_HEAP_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "swap.h"

//int heap_size;
int left(int i){
    return 2*i+1;
}
int right(int i){
    return 2*i+2;
}
int parent(int i){
    if(i%2)
        return (i-1)/2;
    return (i-2)/2;
}
void heapify(void *a,int size,int i,int heapSize,int(*comp)(void *,void *)){
    int l=left(i),r=right(i),most;
    if(l<heapSize&&comp(a+l*size,a+i*size)>0)
        most=l;
    else
        most=i;
    if(r<heapSize&&comp(a+r*size,a+most*size)>0)
        most=r;
    if(most!=i){
        swap(a+i*size,a+most*size,size);
        heapify(a,size,most,heapSize,comp);
    }
}
void buildHeap(void *a,int size, int length, int(*comp)(void *,void *)){
    int i;
    for(i=length/2;i>=0;i--)
        heapify(a,size,i,length,comp);
}
#ifdef	__cplusplus
}
#endif

#endif


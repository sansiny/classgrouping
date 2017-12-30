#ifndef _SWAP_H
#define	_SWAP_H
void swap(void* x,void* y,int size){
    void* key=(void*)malloc(size);
    memcpy(key,x,size);
    memcpy(x,y,size);
    memcpy(y,key,size);
    free(key);
}
#endif	/* _SWAP_H */


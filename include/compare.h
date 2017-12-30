#ifndef _COMPARE_H
#define	_COMPARE_H
typedef struct HeapNode{
	double ms;
	double verlike;
	int M[24];
}HP;

//che compare funtion,below return largest vale
int likecmp(HP *x,HP *y){
    if((x->verlike-y->verlike)>0.0)
        return 1;
    if((x->verlike-y->verlike)<0.0)
        return -1;
    return 0;
}

#endif


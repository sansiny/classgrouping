/* 
 * File:   main.h
 * Author: sansinyang
 * email:  sansinyang@gmail.com
 * Created on 2018.3.23
 */

#define A0 1 
#define A1 (A[cur-1]+1 )
#define A2 (A[cur-1]+1 )
#define A3 (A[cur-3]+1 )
#define A4 (A[cur-1]+1 )
#define A5 (A[cur-1]+1 )
#define A6 (A[cur-3]+1 )
#define A7 (A[cur-1]+1 )
#define A8 (A[cur-1]+1 )
#define A9 (A[cur-3]+1 )
#define A10 (A[cur-1]+1 )
#define A11 (A[cur-1]+1 )
#define A12 (A[cur-3]+1 )
#define A13 (A[cur-1]+1 )
#define A14 (A[cur-1]+1 )
#define A15 (A[cur-3]+1 )
#define A16 (A[cur-1]+1 )
#define A17 (A[cur-1]+1 )
#define A18 (A[cur-3]+1 )
#define A19 (A[cur-1]+1 )
#define A20 (A[cur-1]+1 )
#define A21 (A[cur-3]+1 )
#define A22 (A[cur-1]+1 )
#define A23 (A[cur-1]+1 )

#include <unistd.h>  
#include <stdio.h>  
#include <sys/types.h>    
#include <dirent.h> 
#include <string.h>
#include <stdlib.h>
#include "include/compare.h"
#include "include/queue.h"

//This is programming ability evaluation score from reading grade.txt
//The grade.txt was averaged by class committee from the scores of the last few programming courses.
double grade[24];

//The below score is preferences score 
//Every student has a willingness to evaluate 24 students(abtaining hiself for convenience)
int score[24][24];

//count the passing result 
long long z=0;

//average grade ,average score,Every group 
double a[8],s[8];

//average grade ,average score,All
double ax,sx;

//calculate the variance of grade
double va=0;

double mva=0;

double max=100.0;

//read from grade.txt to grade[24] by my classmate Luo
void read_grade();

//main functional implementation
//n=24;
//char *A save the current result
//argv[] transport the adjustment parameters
void p(int n, char * A, int cur,char * argv[]);


//compute the value
void cpt(char * A,int cur);


void printA(char *A){
			printf("\t%lf\t",va);
			printf("%d+%d+%d ",A[0],A[1],A[2]);
			printf("%d+%d+%d ",A[3],A[4],A[5]);
			printf("%d+%d+%d ",A[6],A[7],A[8]);
			printf("%d+%d+%d ",A[9],A[10],A[11]);
			printf("%d+%d+%d ",A[12],A[13],A[14]);
			printf("%d+%d+%d ",A[15],A[16],A[17]);
			printf("%d+%d+%d ",A[18],A[19],A[20]);
			printf("%d+%d+%d ",A[21],A[22],A[23]);
			printf("\n");
}
//scan the directory "score" by my classmate Tang and Wang 
void scan_dir(char *dir,int s[24][24]) 
{  
    DIR *dp;   
	char*no,*name,*path;
	FILE*fp;
	int number,i,score;
    struct dirent *entry;
    if((dp = opendir(dir)) == NULL)
    {  
        puts("can't open dir.");  
        return;  
    }  
    chdir(dir);            
    while((entry = readdir(dp)) != NULL)
    {  	
		name=strdup(entry->d_name);
		if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
			fp=fopen(name,"rt");
			if(fp!=NULL){	
				if(strtok(name,"_")){
					no=strdup(strtok(NULL,"_")); 
				}else printf("file name error!\n");
				number=atoi(no);
				for(i=0;i<24;i++)
				{
					if(fscanf(fp,"%d\n",&score)==EOF)
					{
						printf("read %s error\n",entry->d_name);
						exit(1);
					}
					s[number-1][i]=score;
				}
				fclose(fp);
			}else{
				printf("open file error\n");
				exit (1);
			}
		}
		
    }  
    closedir(dp);
	return;
}

//use datastruct---"heap" to save the smallest variance of 10(instance)
//this is maximum heap
priorityQueue q;

int main(int argc, char *argv[]){
	int n=24;
	char A[24];
	int cur=0;
	q=heapAlloc(sizeof(HP),10);
	
	if(argc<8)
	{	
		printf("input<format>:./program argv[1] argv[2] ... argv[7]\n\t\targv[i] is double type for select the best result\n");
		exit(1);
	}
	
	read_grade();

	scan_dir("score/",score);  

	p(n,A,cur,argv);

	printf("this is reslut of heap\n");

	while(!empty(q)){

			HP * dq=(HP *)deQueue(&q,sizeof(HP),likecmp);
			printf("Average score:%lf ",dq->verlike);
			printf("Grage variance:%lf ",dq->ms);
			printf("%d+%d+%d ",dq->M[0],dq->M[1],dq->M[2]);
			printf("%d+%d+%d ",dq->M[3],dq->M[4],dq->M[5]);
			printf("%d+%d+%d ",dq->M[6],dq->M[7],dq->M[8]);
			printf("%d+%d+%d ",dq->M[9],dq->M[10],dq->M[11]);
			printf("%d+%d+%d ",dq->M[12],dq->M[13],dq->M[14]);
			printf("%d+%d+%d ",dq->M[15],dq->M[16],dq->M[17]);
			printf("%d+%d+%d ",dq->M[18],dq->M[19],dq->M[20]);
			printf("%d+%d+%d ",dq->M[21],dq->M[22],dq->M[23]);
			printf("\n");
	}
	pqueueClear(&q);
	return 0;
}

void read_grade(){
	FILE *fp = fopen("grade.txt","r");
	if(fp == NULL)
	{
		printf("Cannot read the file!");
	}
	int i =0;
	while(!feof(fp))
	{
		char num[12];
		fscanf(fp,"%s",num);
		grade[i] = atof(num);
		i++;
	}
	fclose(fp);
}
void cpt(char * A,int cur){
	if(cur==5){
		a[0]=(grade[A[0]-1]+grade[A[1]-1]+grade[A[2]-1])/3;
		a[1]=(grade[A[3]-1]+grade[A[4]-1]+grade[A[5]-1])/3;
		ax=(a[0]+a[1])/2;
		s[0]=(score[A[1]-1][A[0]-1]+score[A[0]-1][A[1]-1]
                +score[A[1]-1][A[2]-1]+score[A[2]-1][A[1]-1]
                +score[A[0]-1][A[2]-1]+score[A[2]-1][A[0]-1])/6;
		s[1]=(score[A[3]-1][A[4]-1]+score[A[4]-1][A[3]-1]
                +score[A[3]-1][A[5]-1]+score[A[5]-1][A[3]-1]
                +score[A[4]-1][A[5]-1]+score[A[5]-1][A[4]-1])/6;
		sx=(s[0]+s[1])/2;
		va=((a[0]-ax)*(a[0]-ax)
			+(a[1]-ax)*(a[1]-ax))/2;
	}
	else if(cur==8){
		a[0]=(grade[A[0]-1]+grade[A[1]-1]+grade[A[2]-1])/3;
		a[1]=(grade[A[3]-1]+grade[A[4]-1]+grade[A[5]-1])/3;
		a[2]=(grade[A[6]-1]+grade[A[7]-1]+grade[A[8]-1])/3;
		ax=(a[0]+a[1]+a[2])/3;
		s[0]=(score[A[1]-1][A[0]-1]+score[A[0]-1][A[1]-1]
                +score[A[1]-1][A[2]-1]+score[A[2]-1][A[1]-1]
                +score[A[0]-1][A[2]-1]+score[A[2]-1][A[0]-1])/6;
		s[1]=(score[A[3]-1][A[4]-1]+score[A[4]-1][A[3]-1]
                +score[A[3]-1][A[5]-1]+score[A[5]-1][A[3]-1]
                +score[A[4]-1][A[5]-1]+score[A[5]-1][A[4]-1])/6;
		s[2]=(score[A[6]-1][A[7]-1]+score[A[7]-1][A[6]-1]
                +score[A[6]-1][A[8]-1]+score[A[8]-1][A[6]-1]
                +score[A[8]-1][A[7]-1]+score[A[7]-1][A[8]-1])/6;
		sx=(s[0]+s[1]+s[2])/3;
		va=((a[0]-ax)*(a[0]-ax)
			+(a[2]-ax)*(a[2]-ax)
			+(a[1]-ax)*(a[1]-ax))/3;
	}
	else if(cur==11){
		a[0]=(grade[A[0]-1]+grade[A[1]-1]+grade[A[2]-1])/3;
		a[1]=(grade[A[3]-1]+grade[A[4]-1]+grade[A[5]-1])/3;
		a[2]=(grade[A[6]-1]+grade[A[7]-1]+grade[A[8]-1])/3;
		a[3]=(grade[A[9]-1]+grade[A[10]-1]+grade[A[11]-1])/3;
		ax=(a[0]+a[1]+a[2]+a[3])/4;
		s[0]=(score[A[1]-1][A[0]-1]+score[A[0]-1][A[1]-1]
                +score[A[1]-1][A[2]-1]+score[A[2]-1][A[1]-1]
                +score[A[0]-1][A[2]-1]+score[A[2]-1][A[0]-1])/6;
		s[1]=(score[A[3]-1][A[4]-1]+score[A[4]-1][A[3]-1]
                +score[A[3]-1][A[5]-1]+score[A[5]-1][A[3]-1]
                +score[A[4]-1][A[5]-1]+score[A[5]-1][A[4]-1])/6;
		s[2]=(score[A[6]-1][A[7]-1]+score[A[7]-1][A[6]-1]
                +score[A[6]-1][A[8]-1]+score[A[8]-1][A[6]-1]
                +score[A[8]-1][A[7]-1]+score[A[7]-1][A[8]-1])/6;
		s[3]=(score[A[9]-1][A[10]-1]+score[A[10]-1][A[9]-1]
                +score[A[9]-1][A[11]-1]+score[A[11]-1][A[9]-1]
                +score[A[11]-1][A[10]-1]+score[A[10]-1][A[11]-1])/6;

		sx=(s[0]+s[1]+s[2]+s[3])/4;
		va=((a[0]-ax)*(a[0]-ax)
			+(a[1]-ax)*(a[1]-ax)
			+(a[3]-ax)*(a[3]-ax)
			+(a[2]-ax)*(a[2]-ax))/4;
	}
	else if(cur==14){
		a[0]=(grade[A[0]-1]+grade[A[1]-1]+grade[A[2]-1])/3;
		a[1]=(grade[A[3]-1]+grade[A[4]-1]+grade[A[5]-1])/3;
		a[2]=(grade[A[6]-1]+grade[A[7]-1]+grade[A[8]-1])/3;
		a[3]=(grade[A[9]-1]+grade[A[10]-1]+grade[A[11]-1])/3;
		a[4]=(grade[A[12]-1]+grade[A[13]-1]+grade[A[14]-1])/3;
		ax=(a[0]+a[1]+a[2]+a[3]+a[4])/5;
		s[0]=(score[A[1]-1][A[0]-1]+score[A[0]-1][A[1]-1]
                +score[A[1]-1][A[2]-1]+score[A[2]-1][A[1]-1]
                +score[A[0]-1][A[2]-1]+score[A[2]-1][A[0]-1])/6;
		s[1]=(score[A[3]-1][A[4]-1]+score[A[4]-1][A[3]-1]
                +score[A[3]-1][A[5]-1]+score[A[5]-1][A[3]-1]
                +score[A[4]-1][A[5]-1]+score[A[5]-1][A[4]-1])/6;
		s[2]=(score[A[6]-1][A[7]-1]+score[A[7]-1][A[6]-1]
                +score[A[6]-1][A[8]-1]+score[A[8]-1][A[6]-1]
                +score[A[8]-1][A[7]-1]+score[A[7]-1][A[8]-1])/6;
		s[3]=(score[A[9]-1][A[10]-1]+score[A[10]-1][A[9]-1]
                +score[A[9]-1][A[11]-1]+score[A[11]-1][A[9]-1]
                +score[A[11]-1][A[10]-1]+score[A[10]-1][A[11]-1])/6;
		s[4]=(score[A[12]-1][A[13]-1]+score[A[13]-1][A[12]-1]
                +score[A[12]-1][A[14]-1]+score[A[14]-1][A[12]-1]
                +score[A[13]-1][A[14]-1]+score[A[14]-1][A[13]-1])/6;

		sx=(s[0]+s[1]+s[2]+s[3]+s[4])/5;
		va=((a[0]-ax)*(a[0]-ax)
			+(a[1]-ax)*(a[1]-ax)
			+(a[3]-ax)*(a[3]-ax)
			+(a[4]-ax)*(a[4]-ax)
			+(a[2]-ax)*(a[2]-ax))/5;
	}
	else if(cur==17){
		a[0]=(grade[A[0]-1]+grade[A[1]-1]+grade[A[2]-1])/3;
		a[1]=(grade[A[3]-1]+grade[A[4]-1]+grade[A[5]-1])/3;
		a[2]=(grade[A[6]-1]+grade[A[7]-1]+grade[A[8]-1])/3;
		a[3]=(grade[A[9]-1]+grade[A[10]-1]+grade[A[11]-1])/3;
		a[4]=(grade[A[12]-1]+grade[A[13]-1]+grade[A[14]-1])/3;
		a[5]=(grade[A[15]-1]+grade[A[16]-1]+grade[A[17]-1])/3;
		ax=(a[0]+a[1]+a[2]+a[3]+a[4]+a[5])/6;
		s[0]=(score[A[1]-1][A[0]-1]+score[A[0]-1][A[1]-1]
                +score[A[1]-1][A[2]-1]+score[A[2]-1][A[1]-1]
                +score[A[0]-1][A[2]-1]+score[A[2]-1][A[0]-1])/6;
		s[1]=(score[A[3]-1][A[4]-1]+score[A[4]-1][A[3]-1]
                +score[A[3]-1][A[5]-1]+score[A[5]-1][A[3]-1]
                +score[A[4]-1][A[5]-1]+score[A[5]-1][A[4]-1])/6;
		s[2]=(score[A[6]-1][A[7]-1]+score[A[7]-1][A[6]-1]
                +score[A[6]-1][A[8]-1]+score[A[8]-1][A[6]-1]
                +score[A[8]-1][A[7]-1]+score[A[7]-1][A[8]-1])/6;
		s[3]=(score[A[9]-1][A[10]-1]+score[A[10]-1][A[9]-1]
                +score[A[9]-1][A[11]-1]+score[A[11]-1][A[9]-1]
                +score[A[11]-1][A[10]-1]+score[A[10]-1][A[11]-1])/6;
		s[4]=(score[A[12]-1][A[13]-1]+score[A[13]-1][A[12]-1]
                +score[A[12]-1][A[14]-1]+score[A[14]-1][A[12]-1]
                +score[A[13]-1][A[14]-1]+score[A[14]-1][A[13]-1])/6;

		s[5]=(score[A[15]-1][A[16]-1]+score[A[16]-1][A[15]-1]
                +score[A[15]-1][A[17]-1]+score[A[17]-1][A[15]-1]
                +score[A[16]-1][A[17]-1]+score[A[17]-1][A[16]-1])/6;
		sx=(s[0]+s[1]+s[2]+s[3]+s[4]+s[5])/6;
		va=((a[0]-ax)*(a[0]-ax)
			+(a[1]-ax)*(a[1]-ax)
			+(a[3]-ax)*(a[3]-ax)
			+(a[4]-ax)*(a[4]-ax)
			+(a[5]-ax)*(a[5]-ax)
			+(a[2]-ax)*(a[2]-ax))/6;
	}else if(cur==20){
		a[0]=(grade[A[0]-1]+grade[A[1]-1]+grade[A[2]-1])/3;
		a[1]=(grade[A[3]-1]+grade[A[4]-1]+grade[A[5]-1])/3;
		a[2]=(grade[A[6]-1]+grade[A[7]-1]+grade[A[8]-1])/3;
		a[3]=(grade[A[9]-1]+grade[A[10]-1]+grade[A[11]-1])/3;
		a[4]=(grade[A[12]-1]+grade[A[13]-1]+grade[A[14]-1])/3;
		a[5]=(grade[A[15]-1]+grade[A[16]-1]+grade[A[17]-1])/3;
		a[6]=(grade[A[18]-1]+grade[A[19]-1]+grade[A[20]-1])/3;
		ax=(a[0]+a[1]+a[2]+a[3]+a[4]+a[5]+a[6])/7;
		s[0]=(score[A[1]-1][A[0]-1]+score[A[0]-1][A[1]-1]
                +score[A[1]-1][A[2]-1]+score[A[2]-1][A[1]-1]
                +score[A[0]-1][A[2]-1]+score[A[2]-1][A[0]-1])/6;
		s[1]=(score[A[3]-1][A[4]-1]+score[A[4]-1][A[3]-1]
                +score[A[3]-1][A[5]-1]+score[A[5]-1][A[3]-1]
                +score[A[4]-1][A[5]-1]+score[A[5]-1][A[4]-1])/6;
		s[2]=(score[A[6]-1][A[7]-1]+score[A[7]-1][A[6]-1]
                +score[A[6]-1][A[8]-1]+score[A[8]-1][A[6]-1]
                +score[A[8]-1][A[7]-1]+score[A[7]-1][A[8]-1])/6;
		s[3]=(score[A[9]-1][A[10]-1]+score[A[10]-1][A[9]-1]
                +score[A[9]-1][A[11]-1]+score[A[11]-1][A[9]-1]
                +score[A[11]-1][A[10]-1]+score[A[10]-1][A[11]-1])/6;
		s[4]=(score[A[12]-1][A[13]-1]+score[A[13]-1][A[12]-1]
                +score[A[12]-1][A[14]-1]+score[A[14]-1][A[12]-1]
                +score[A[13]-1][A[14]-1]+score[A[14]-1][A[13]-1])/6;

		s[5]=(score[A[15]-1][A[16]-1]+score[A[16]-1][A[15]-1]
                +score[A[15]-1][A[17]-1]+score[A[17]-1][A[15]-1]
                +score[A[16]-1][A[17]-1]+score[A[17]-1][A[16]-1])/6;
		s[6]=(score[A[18]-1][A[19]-1]+score[A[19]-1][A[18]-1]
                +score[A[18]-1][A[20]-1]+score[A[20]-1][A[18]-1]
                +score[A[19]-1][A[20]-1]+score[A[20]-1][A[19]-1])/6;
		sx=(s[0]+s[1]+s[2]+s[3]+s[4]+s[5]+s[6])/7;
		va=((a[0]-ax)*(a[0]-ax)
			+(a[1]-ax)*(a[1]-ax)
			+(a[3]-ax)*(a[3]-ax)
			+(a[4]-ax)*(a[4]-ax)
			+(a[5]-ax)*(a[5]-ax)
			+(a[6]-ax)*(a[6]-ax)
			+(a[2]-ax)*(a[2]-ax))/7;
	}else if(cur==23){
		a[0]=(grade[A[0]-1]+grade[A[1]-1]+grade[A[2]-1])/3;
		a[1]=(grade[A[3]-1]+grade[A[4]-1]+grade[A[5]-1])/3;
		a[2]=(grade[A[6]-1]+grade[A[7]-1]+grade[A[8]-1])/3;
		a[3]=(grade[A[9]-1]+grade[A[10]-1]+grade[A[11]-1])/3;
		a[4]=(grade[A[12]-1]+grade[A[13]-1]+grade[A[14]-1])/3;
		a[5]=(grade[A[15]-1]+grade[A[16]-1]+grade[A[17]-1])/3;
		a[6]=(grade[A[18]-1]+grade[A[19]-1]+grade[A[20]-1])/3;
		a[7]=(grade[A[21]-1]+grade[A[22]-1]+grade[A[23]-1])/3;
		ax=(a[0]+a[1]+a[2]+a[3]+a[4]+a[5]+a[6]+a[7])/8;
		s[0]=(score[A[1]-1][A[0]-1]+score[A[0]-1][A[1]-1]
                +score[A[1]-1][A[2]-1]+score[A[2]-1][A[1]-1]
                +score[A[0]-1][A[2]-1]+score[A[2]-1][A[0]-1])/6;
		s[1]=(score[A[3]-1][A[4]-1]+score[A[4]-1][A[3]-1]
                +score[A[3]-1][A[5]-1]+score[A[5]-1][A[3]-1]
                +score[A[4]-1][A[5]-1]+score[A[5]-1][A[4]-1])/6;
		s[2]=(score[A[6]-1][A[7]-1]+score[A[7]-1][A[6]-1]
                +score[A[6]-1][A[8]-1]+score[A[8]-1][A[6]-1]
                +score[A[8]-1][A[7]-1]+score[A[7]-1][A[8]-1])/6;
		s[3]=(score[A[9]-1][A[10]-1]+score[A[10]-1][A[9]-1]
                +score[A[9]-1][A[11]-1]+score[A[11]-1][A[9]-1]
                +score[A[11]-1][A[10]-1]+score[A[10]-1][A[11]-1])/6;
		s[4]=(score[A[12]-1][A[13]-1]+score[A[13]-1][A[12]-1]
                +score[A[12]-1][A[14]-1]+score[A[14]-1][A[12]-1]
                +score[A[13]-1][A[14]-1]+score[A[14]-1][A[13]-1])/6;

		s[5]=(score[A[15]-1][A[16]-1]+score[A[16]-1][A[15]-1]
                +score[A[15]-1][A[17]-1]+score[A[17]-1][A[15]-1]
                +score[A[16]-1][A[17]-1]+score[A[17]-1][A[16]-1])/6;
		s[6]=(score[A[18]-1][A[19]-1]+score[A[19]-1][A[18]-1]
                +score[A[18]-1][A[20]-1]+score[A[20]-1][A[18]-1]
                +score[A[19]-1][A[20]-1]+score[A[20]-1][A[19]-1])/6;
		s[7]=(score[A[21]-1][A[22]-1]+score[A[22]-1][A[21]-1]
                +score[A[21]-1][A[23]-1]+score[A[23]-1][A[21]-1]
                +score[A[22]-1][A[23]-1]+score[A[23]-1][A[22]-1])/6;
		sx=(s[0]+s[1]+s[2]+s[3]+s[4]+s[5]+s[6]+s[7])/8;
		va=((a[0]-ax)*(a[0]-ax)
			+(a[1]-ax)*(a[1]-ax)
			+(a[3]-ax)*(a[3]-ax)
			+(a[4]-ax)*(a[4]-ax)
			+(a[5]-ax)*(a[5]-ax)
			+(a[6]-ax)*(a[6]-ax)
			+(a[7]-ax)*(a[7]-ax)
			+(a[2]-ax)*(a[2]-ax))/8;

		}
	}
void p(int n, char * A, int cur,char *argv[]){
	if(cur==n)
	{
		z++;

		if(va<max){
			max=va;
			mva=va;
			HP HN;
			int i;
			for(i=0;i<24;i++){
				HN.M[i]=A[i];
			}
			HN.ms=va;
			HN.verlike=sx;	

			//entry the current smallest variance of result
			enQueue(&q,sizeof(HP),&HN,likecmp);
			}

			printA(A);
			printf("%ld\n",z);
	}
	else{
		if(cur==0){	
			int q;
		for(q=A0;q<=n-9;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			p(n,A,cur+1,argv);
		}
		}
		}
		else if(cur==1)
		{	
			int q;
		for(q=A1;q<=n;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			//if one input 1 for the preference to other,the result pass
			//you can change it
			if(score[A[cur]-1][A[cur]-2]==1||score[A[cur]-2][A[cur]-1]==1){}
			else{
			p(n,A,cur+1,argv);
			}
		}
		}
		}	
		else if(cur==2)
		{	
			int q;
		for(q=A2;q<=n;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			if(score[A[cur]-1][A[cur]-2]==1||score[A[cur]-2][A[cur]-1]==1||score[A[cur]-1][A[cur]-3]==1||score[A[cur]-3][A[cur]-1]==1){}
			else{
			p(n,A,cur+1,argv);
			}
		}
		}
		}
		else if(cur==3)
		{	
			int q;
		for(q=A3;q<=n-8;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
						p(n,A,cur+1,argv);
			}
		}
		}
		else if(cur==4)
		{	
			int q;
		for(q=A4;q<=n;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
A[cur]=q;
			if(score[A[cur]-1][A[cur]-2]==1||score[A[cur]-2][A[cur]-1]==1){}
			else{
			p(n,A,cur+1,argv);
			}
		}
		}
		}
		else if(cur==5)
		{	
			int q;
		for(q=A5;q<=n;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			if(score[A[cur]-1][A[cur]-2]==1||score[A[cur]-2][A[cur]-1]==1||score[A[cur]-1][A[cur]-3]==1||score[A[cur]-3][A[cur]-1]==1){}
			else{
		
            			cpt(A,cur);
			if(va<atof(argv[1]))
			p(n,A,cur+1,argv);
			}
		}
		}
		}
		else if(cur==6)
		{	
			int q;
		for(q=A6;q<=n-7;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			p(n,A,cur+1,argv);
		}
		}
		}
		else if(cur==7)
		{	
			int q;
		for(q=A7;q<=n;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			if(score[A[cur]-1][A[cur]-2]==1||score[A[cur]-2][A[cur]-1]==1){}
			else{
			p(n,A,cur+1,argv);
			}
		}
		}
		}
		else if(cur==8)
		{	
			int q;
		for(q=A8;q<=n;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			if(score[A[cur]-1][A[cur]-2]==1||score[A[cur]-2][A[cur]-1]==1||score[A[cur]-1][A[cur]-3]==1||score[A[cur]-3][A[cur]-1]==1){}
			else{
        			cpt(A,cur);
			if(va<atof(argv[2]))
			p(n,A,cur+1,argv);
			}
		}
		}
		}
		else if(cur==9)
		{	
			int q;
		for(q=A9;q<=n-6;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			p(n,A,cur+1,argv);
		}
		}
		}	
		else if(cur==10)
		{	
			int q;
		for(q=A10;q<=n;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			if(score[A[cur]-1][A[cur]-2]==1||score[A[cur]-2][A[cur]-1]==1){}
			else{
			p(n,A,cur+1,argv);
			}
		}
		}
		}
		else if(cur==11)
		{	
			int q;
		for(q=A11;q<=n;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			if(score[A[cur]-1][A[cur]-2]==1||score[A[cur]-2][A[cur]-1]==1||score[A[cur]-1][A[cur]-3]==1||score[A[cur]-3][A[cur]-1]==1){}
			else{
			cpt(A,cur);
           	if(va<atof(argv[3]))
			p(n,A,cur+1,argv);
			}
		}
		}
		}
		else if(cur==12)
		{	
			int q;
		for(q=A12;q<=n-5;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			p(n,A,cur+1,argv);
		}
		}
		}
		else if(cur==13)
		{	
			int q;
		for(q=A13;q<=n;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			if(score[A[cur]-1][A[cur]-2]==1||score[A[cur]-2][A[cur]-1]==1){}
			else{
			p(n,A,cur+1,argv);
			}
		}
		}
		}
		else if(cur==14)
		{	
			int q;
		for(q=A14;q<=n;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			if(score[A[cur]-1][A[cur]-2]==1||score[A[cur]-2][A[cur]-1]==1||score[A[cur]-1][A[cur]-3]==1||score[A[cur]-3][A[cur]-1]==1){}
			else{
			cpt(A,cur);
			if(va<atof(argv[4]))
			p(n,A,cur+1,argv);
			}
		}
		}
		}
		else if(cur==15)
		{	
			int q;
		for(q=A15;q<=n-4;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			p(n,A,cur+1,argv);
		}
		}
		}
		else if(cur==16)
		{	
			int q;
		for(q=A16;q<=n;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			if(score[A[cur]-1][A[cur]-2]==1||score[A[cur]-2][A[cur]-1]==1){}
			else{
			p(n,A,cur+1,argv);
			}
		}
		}
		}
		else if(cur==17)
		{	
			int q;
		for(q=A17;q<=n;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			if(score[A[cur]-1][A[cur]-2]==1||score[A[cur]-2][A[cur]-1]==1||score[A[cur]-1][A[cur]-3]==1||score[A[cur]-3][A[cur]-1]==1){}
			else{
			cpt(A,cur);
			if(va<atof(argv[5]))
			p(n,A,cur+1,argv);
			}
		}
		}
		}

		else if(cur==18)
		{	
			int q;
		for(q=A18;q<=n-3;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			p(n,A,cur+1,argv);
		}
		}
		}
		else if(cur==19)
		{	
			int q;
		for(q=A19;q<=n;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			if(score[A[cur]-1][A[cur]-2]==1||score[A[cur]-2][A[cur]-1]==1){}
			else{
			p(n,A,cur+1,argv);
			}
		}
		}
		}

		else if(cur==20)
		{	
			int q;
			for(q=A20;q<=n;q++){
			int j;
			int k=1;
			for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
				}
			}
			if(k){
			A[cur]=q;
			if(score[A[cur]-1][A[cur]-2]==1||score[A[cur]-2][A[cur]-1]==1||score[A[cur]-1][A[cur]-3]==1||score[A[cur]-3][A[cur]-1]==1){}
			else{
			cpt(A,cur);
			if(va<atof(argv[6]))
			p(n,A,cur+1,argv);
			}
		}
		}
		}
		else if(cur==21)
		{	
			int q;
		for(q=A21;q<=n-2;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			p(n,A,cur+1,argv);
		}
		}
		}
		else if(cur==22)
		{	
			int q;
		for(q=A22;q<=n-1;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			if(score[A[cur]-1][A[cur]-2]==1||score[A[cur]-2][A[cur]-1]==1){}
			else{
			p(n,A,cur+1,argv);
			}
		}
		}
		}
		else if(cur==23)
		{	
			int q;
		for(q=A23;q<=n;q++){
		int j;
		int k=1;
		for(j=0;j<cur;j++){
			if(A[j]==q){
				k=0;
			}
		}
		if(k){
			A[cur]=q;
			if(score[A[cur]-1][A[cur]-2]==1||score[A[cur]-2][A[cur]-1]==1||score[A[cur]-1][A[cur]-3]==1||score[A[cur]-3][A[cur]-1]==1){}
			else{
			cpt(A,cur);
		if(va<atof(argv[7]))
			p(n,A,cur+1,argv);
			}
		}
		}
		}
	}
}


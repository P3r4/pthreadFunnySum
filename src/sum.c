#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct{int *numbers; int start; int len;} sum_params;

int sum_part(int a[], int start, int len){
    int i;
    int half = len;
    while(half>4){
        half = half >> 1;    
        for(i = start; i<half; i += 4){
            a[i] += a[i+half];
        }
    }
    return a[start];
}

void sum_elem(int *a, int i, int j){
    a[i] += a[j];
}

void *_sum_part(void *params){
    sum_params *sp = (sum_params *) params;
    int i;
    int half = sp->len;

    while(half>4){
        half = half >> 1;    
        for(i = sp->start; i<half; i += 4){
            sum_elem(sp->numbers, i, i+half);
        }
    }
    pthread_exit(NULL);
}

int getValue(int *a, int i){
    return a[i];
}

void setValue(int *a, int i, int v){
    a[i] = v;
}

void *_sum_part2(void *params){
    sum_params *sp = (sum_params *) params;
    int i;
    int s = sp->len >> 2;
    int end = s * (sp->start+1);
    int total = 0;
    
    for(i = s*sp->start; i < end; total += getValue(sp->numbers, i++));
    
    setValue(sp->numbers,sp->start,total);
    pthread_exit(NULL);
}

sum_params *make_sp(int a[], int l, int s){
    sum_params *sp = malloc(sizeof(sum_params));
    sp->numbers = a;
    sp->start = s;
    sp->len = l;
    return sp;
}

int parallel_sum(int a[], int l){
    sum_params *sp0 = make_sp(a,l,0);
    pthread_t thr0;
    pthread_create(&thr0, NULL,_sum_part,(void*)sp0);

    sum_params *sp1 = make_sp(a,l,1);
    pthread_t thr1;
    pthread_create(&thr1, NULL,_sum_part,(void*)sp1);

    sum_params *sp2 = make_sp(a,l,2);
    pthread_t thr2;
    pthread_create(&thr2, NULL,_sum_part,(void*)sp2);

    sum_params *sp3 = make_sp(a,l,3);
    pthread_t thr3;
    pthread_create(&thr3, NULL,_sum_part,(void*)sp3);

    pthread_join(thr0,NULL);    
	pthread_join(thr1,NULL);
	pthread_join(thr2,NULL);
	pthread_join(thr3,NULL);
	
    return a[0]+a[1]+a[2]+a[3];    
}

int parallel_sum2(int a[], int l){
    sum_params *sp0 = make_sp(a,l,0);
    pthread_t thr0;
    pthread_create(&thr0, NULL,_sum_part2,(void*)sp0);

    sum_params *sp1 = make_sp(a,l,1);
    pthread_t thr1;
    pthread_create(&thr1, NULL,_sum_part2,(void*)sp1);

    sum_params *sp2 = make_sp(a,l,2);
    pthread_t thr2;
    pthread_create(&thr2, NULL,_sum_part2,(void*)sp2);

    sum_params *sp3 = make_sp(a,l,3);
    pthread_t thr3;
    pthread_create(&thr3, NULL,_sum_part2,(void*)sp3);

    pthread_join(thr0,NULL);    
	pthread_join(thr1,NULL);
	pthread_join(thr2,NULL);
	pthread_join(thr3,NULL);
	
    return a[0]+a[1]+a[2]+a[3];    
}

int sum(int a[], int len){
    sum_part(a,0,len);
    sum_part(a,1,len);
    sum_part(a,2,len);
    sum_part(a,3,len);
    return a[0]+a[1]+a[2]+a[3];
}

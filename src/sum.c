/*
    Lucas Perassoli Melquiades ra70896
    Vinicius Martins Cornieri ra58453

    O laço da função _sum_part executa n/4 vezes.
    O custo de memória é o mesmo da execução linear. 
    Entretanto o tempo gasto para executar é 4 vezes menor que uma soma linear.

    O ponteiro "out" acumula os elementos da soma.
    A variável "a" é um vetor de valores.
    hipótese: No inicio de cada iteração *out = somatória(a[start, i - 1]).

    base: i = 0 -> *out = 0

    para i+1:
    *out + a[i] = somatória(a[start, i])
    *out + a[i] = somatória(a[start, i - 1]) + a[i]
    somatória(a[start, i - 1]) + a[i] = somatória(a[start, i - 1]) + a[i]

    para i = end:
    *out = somatória(a[start, end - 1])
    end = ultimo indice + 1
    end - 1 = ultimo indice
    *out = somatória(a[start, ultimo indice])
            
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct{int *numbers; int start; int end;} sum_params;

int getValue(int *a, int i){
    return a[i];
}

sum_params *make_sum_params(int a[], int length, int part){    
    sum_params *sp = malloc(sizeof(sum_params));
    sp->numbers = a;
    int part_len = (length >> 2);
    sp->start = part * part_len;
    sp->end = (part+1) * part_len;
    return sp;
}

void *_sum_part(void *params){
    sum_params *sp = (sum_params *) params;
    int i;
    int *out = malloc(sizeof(int));
    *out = 0;
    for(i = sp->start; i < sp->end; *out += getValue(sp->numbers, i++));
    pthread_exit((void *)out);
}

int parallel_sum(int a[], int l){

    int *out0;
    int *out1;
    int *out2;
    int *out3;

    sum_params *sp0 = make_sum_params(a,l,0);
    pthread_t thr0;
    pthread_create(&thr0, NULL,_sum_part,(void*)sp0);

    sum_params *sp1 = make_sum_params(a,l,1);
    pthread_t thr1;
    pthread_create(&thr1, NULL,_sum_part,(void*)sp1);

    sum_params *sp2 = make_sum_params(a,l,2);
    pthread_t thr2;
    pthread_create(&thr2, NULL,_sum_part,(void*)sp2);

    sum_params *sp3 = make_sum_params(a,l,3);
    pthread_t thr3;
    pthread_create(&thr3, NULL,_sum_part,(void*)sp3);

    pthread_join(thr0,(void **)&out0);
    pthread_join(thr1,(void **)&out1);
    pthread_join(thr2,(void **)&out2);
    pthread_join(thr3,(void **)&out3);

    return *out0+*out1+*out2+*out3;
 
}

void *_sum_part0(void *params){
    int *numbers = (int *) params;
    int i;
    int *out = malloc(sizeof(int));
    *out = 0;
    for(i = 0; i < 67108864; *out += numbers[i++]);
    pthread_exit((void *)out);
}

void *_sum_part1(void *params){
    int *numbers = (int *) params;
    int i;
    int *out = malloc(sizeof(int));
    *out = 0;
    for(i = 67108864; i < 134217728; *out += numbers[i++]);
    pthread_exit((void *)out);
}

void *_sum_part2(void *params){
    int *numbers = (int *) params;
    int i;
    int *out = malloc(sizeof(int));
    *out = 0;
    for(i = 134217728; i < 201326592; *out += numbers[i++]);
    pthread_exit((void *)out);
}

void *_sum_part3(void *params){
    int *numbers = (int *) params;
    int i;
    int *out = malloc(sizeof(int));
    *out = 0;
    for(i = 201326592; i < 268435456; *out += numbers[i++]);
    pthread_exit((void *)out);
}


int parallel_sum2(int a[]){

    int *out0;
    int *out1;
    int *out2;
    int *out3;

    pthread_t thr0;
    pthread_create(&thr0, NULL,_sum_part0,(void*)a);

    pthread_t thr1;
    pthread_create(&thr1, NULL,_sum_part1,(void*)a);

    pthread_t thr2;
    pthread_create(&thr2, NULL,_sum_part2,(void*)a);

    pthread_t thr3;
    pthread_create(&thr3, NULL,_sum_part3,(void*)a);

    pthread_join(thr0,(void **)&out0);
	pthread_join(thr1,(void **)&out1);
	pthread_join(thr2,(void **)&out2);
	pthread_join(thr3,(void **)&out3);

    return *out0+*out1+*out2+*out3;
 
}

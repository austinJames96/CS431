#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int max = 1;
static volatile unsigned int counter = 0;

void *mythread(void *arg){
    char *letter = arg;
    int i;
    printf("%s: begin [address of i: %p]\n", letter, i);

}


int main(int argc, char *argv[]){
    if (argc != 1){
        fprintf(stderr, "usage:main\n");
        exit(1);
    }
    pthread_t p1, p2;
    int rc; 
    int num_threads = 26;
    printf("main: begin\n");

    pthread_t threads[num_threads];
    for(int i = 0; i<num_threads; i++){
        pthread_create(&threads[i], NULL, mythread, "A");
    }


    for (int i = 0; i<num_threads; i++){
        pthread_join(threads[i], NULL);
    }


    printf("main: end\n");
    
    return 0;

}

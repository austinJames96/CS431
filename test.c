#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *mythread(void *arg){
    printf("%s\n", (char *) arg);
    return NULL;
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
/*
    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
*/
    //printf("%d", (char *) "A");
    //char starting = (int *) 65;
    
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

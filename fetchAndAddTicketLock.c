#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <atomic_ops.h>

//compile with -lpthread and -latomic_ops

typedef struct __lock_t{
    AO_t ticket;
    AO_t turn;
} lock_t;

void lock_init(lock_t *lock){
    lock->ticket = 0;
    lock->turn = 0;
}

void lock(lock_t *lock){
    //int myturn = FetchAndAdd(&lock->ticket);
    AO_t myturn = AO_fetch_and_add(&lock->ticket, (AO_t) 1);
    while(lock->turn!=myturn){
        //Spin
    }
}

void unlock(lock_t *lock){
    lock->turn = lock->turn + 1;
}

int max = 1;
static volatile unsigned int = 0;

void *mythread(void *arg){
    char *letter = arg;
    int i;
    printf("%s: begin [addr of i: %p]\n", letter, &i);

    for(i = 0; i<max; i++){
        lock(&counter_lock);
        counter = counter + 1;

        unlock(&counter_lock);
    }
    printf("%s: done\n", letter);
    return NULL;
}

int main(int argc, char *argv[]){
    
    if (argc != 2){
        fprintf(stderr, "usage: %s <loopcount>\n", argv[0]);
        exit(1);
    }
    max = atoi(argv[1]);
    init(&counter_lock);
    return 0;

}

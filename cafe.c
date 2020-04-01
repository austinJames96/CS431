/*

CS431 Concurrency Assignment
Austin Sypolt
Due: 12/16/19

*/

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


sem_t empty;
sem_t full;
sem_t mutex;
// total number of customers
#define NUM_CUSTOMERS 10

// maximum length of the line waiting for service
// when 1 person is being served, and 2 more are 
// waiting, new customers will leave
#define MAX_OCCUPANCY 2

// variable to track the number of customers in line
int waiting = 0;

// you'll also need some semaphores (at least 3)
// declare them globally and then initialize them in main()
// 1. one to safely update the shared variable waiting
// 2. one to signal customers
// 3. one to signal the barista


// simulate time passing
long random();
void random_wait(int time)
{
  int length = random() % time;
  sleep(length);
}


void *barista_thread(void *args)
{
  int served = 0;
  int i = (int *)args;

  // only serve the number of customers that we expect 
  // in this run, then close the cafe
  while(served < NUM_CUSTOMERS) {
    // Wait for a customer to arrive
    // take the customer from the line

    // make a coffee
    sem_wait(&full);
    sem_wait(&mutex);
    
    printf("[Customer %d] present. Barista working on customer's coffee! \n", i);

    sem_post(&mutex);
    sem_post(&empty);

    printf("[Customer %d]'s coffee is complete. Thank you!"\n, i);

    random_wait(7);

    served += 1;
  }


  pthread_exit(0);
}


void *customer_thread(void *arg)
{
  int i = (int *)arg;

  /* wait a random time before going to the cafe */
  random_wait(10);

  // Each customer should try to get one (1) coffee
  if (waiting >= MAX_OCCUPANCY) 
  {
    printf("[Customer %d] **** leaving. ****\n", i);
    pthread_exit(0);
  } else {
      sem_wait(&empty);
      sem_wait(&mutex);
    
      printf("[Customer %d] waiting for coffee.\n", i);

      sem_post(&mutex);
      sem_post(&full);

      printf("[Customer %d] recieved coffee.\n", i);
    // join the line to get a coffee
    // signal the barista in case I'm the only customer here
    // wait for my coffee
  }
  pthread_exit(0);
}


int main()
{
  // seed the random number generator
  srandom(2688);
    sem_init(&empty, 0, MAX_OCCUPANCY);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
  pthread_t barista;
  pthread_create(&barista, NULL, barista_thread, NULL);

  printf("Creating %d customer threads.\n", NUM_CUSTOMERS);
  printf("There are/is %d spot(s) in the line.\n", MAX_OCCUPANCY-1);

  pthread_t customers[NUM_CUSTOMERS];

  for(int i = 0; i < NUM_CUSTOMERS; i++)
  {
    pthread_create(&customers[i], NULL, customer_thread, (void *)i);
  }

  for(int i = 0; i < NUM_CUSTOMERS; i++)
  {
    pthread_join(customers[i], NULL);
  }

  pthread_join(barista, NULL);
  printf("The cafe is now closed!\n");
  
  exit(0);
}
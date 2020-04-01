#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

sem_t empty;
sem_t full;
sem_t mutex;

void enterCar(){
    sem_wait(&full);
    sem_wait(&mutex);

    printf("Car entering parking lot.\n");

    sem_post(&mutex);
    sem_post(&empty);
}

void exitCar(){
    sem_wait(&empty);
    sem_wait(&mutex);
    
    printf("Car leaving parking lot.\n");

    sem_post(&mutex);
    sem_post(&full);
}

int main(){
    int n = //n is the max capacity of the garage
    int duration = //number of cars try to enter/leave garage before closing
    sem_init(&empty, 0, n);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

	for(int i = 0; i < duration; i++){
		if(currentCars < n){
			enterCar();
		}
        else if (currentCars == n){
            wait(); //Wait for availability in the garage
            printf("Potential parker has left.");
        }

        srandom(time(NULL));//Set a changing seed
        if((random()%100)>50){
            exitCar(); //50% chance of a car entering the garage
        }
	}
}
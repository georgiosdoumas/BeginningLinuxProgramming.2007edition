#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
// int sem_init(sem_t* sem, int pshared, unsigned int value);
// int sem_wait(sem_t* sem);
// int sem_post(sem_t* sem);
// int sem_destroy(sem_t * sem);

void* threadProcessingInput(void* arg);  //to process text and count entered chars on a seperate thread
sem_t binarySemaphore;
#define WORK_SIZE 1024
char work_area[WORK_SIZE];

int main()
{
  int result;
  pthread_t semThread;
  void* threadResult;
  result = sem_init(&binarySemaphore, 0, 0); // the last 0 is the value that binarySemaphore gets
  if(result != 0)
  {
    perror("Semaphore initialization failed");
    exit(EXIT_FAILURE);
  }
  result = pthread_create(&semThread, NULL, threadProcessingInput, NULL); // creating a thread for characters counting
  if(result != 0)
  {
    perror("Thread creation failed");
    exit(EXIT_FAILURE);
  }
  printf("Input some text. Enter 'end' (on a line of its own) to finish\n");
  while(strncmp("end", work_area, 3) != 0) // reading happens in main thread, processing happens in created thread
  {
    fgets(work_area, WORK_SIZE, stdin);
    sem_post(&binarySemaphore);           // increments the semaphore
  }
  printf("\nWaiting for counting-thread to finish...\n");
  result = pthread_join(semThread, &threadResult);
  if (result != 0)
  {
    perror("Thread join failed");
    exit(EXIT_FAILURE);
  }
  printf("Thread joined\n");
  sem_destroy(&binarySemaphore);
  exit(EXIT_SUCCESS);
}

void *threadProcessingInput(void *arg)
{
  sem_wait(&binarySemaphore);             //waits for the semaphore to become nonzero and then decreases it
  while(strncmp("end", work_area, 3) != 0)
  {
    printf("  You input %zd characters\n", strlen(work_area) -1);
    sem_wait(&binarySemaphore);
  }
  pthread_exit(NULL);
}

// gcc -Wall -O -o page505thread3semaphore page505thread3semaphore.c -lpthread

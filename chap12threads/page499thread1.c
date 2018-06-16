/* I edited the example of the book in many ways. Instead of having a sleep(3) I decided to ask the user for input
and use that imput to change the message, instead of using a predifined string. Also I tried to declare the message
as a local variable in main, instead of global variable, and it works. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define MSG_SIZE 25
// int pthread_create(pthread_t *thread, pthread_attr_t *attr, void*(*start_routine)(void *), void *arg);
void* threadWork(void* input);

int main(void)
{
  char message[MSG_SIZE] = "Thread will change me!";
  int result; // for storing return values of functions
  pthread_t simpleThread;
  void* threadResult;
  result = pthread_create(&simpleThread, NULL, threadWork, (void*)message);
  if(result != 0)
  {
    perror("Thread creation failed");
    exit(EXIT_FAILURE);
  }
  printf("Thread was created,witing for it to finish...\n");
  result = pthread_join(simpleThread, &threadResult);
  if(result != 0)
  {
    perror("Thread join failed");
    exit(EXIT_FAILURE);
  }
  printf("Thread joined, it returned :%s \n", (char*)threadResult);
  printf("Message is now: %s\n", message);
  exit(EXIT_SUCCESS);
}

void* threadWork(void* input)
{
  printf("  Thread function is running. Argument passed was: %s \n", (char*)input);
  printf("  Enter the new message to edit the original message to:");
  fgets(input, MSG_SIZE, stdin);
  pthread_exit("  Thank you for the CPU time");
}

// gcc -Wall -O -D_REENTRANT -o page499thread1 page499thread1.c -lpthread
// or even without the -D_REENTRANT

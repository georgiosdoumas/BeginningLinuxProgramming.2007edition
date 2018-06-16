/* A bad example for observing simultaneous execution of a main proc and its thread 
As sown in the output, we are missing some steps */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define MSG_SIZE 25
// int pthread_create(pthread_t *thread, pthread_attr_t *attr, void*(*start_routine)(void *), void *arg);
// int pthread_join(pthread_t th, void **thread_return);
// void pthread_exit(void *retval);

int run_now = 1; //Set run_now to 1 when the main function is executing and to 2 when your new thread is executing.
void* threadWork(void* input);

int main(void)
{
  int result; // for storing return values of functions
  pthread_t simpleThread;
  void* threadReturn;
  result = pthread_create(&simpleThread, NULL, threadWork, NULL);
  if(result != 0)
  {
    perror("Thread creation failed");
    exit(EXIT_FAILURE);
  }
  int print_count1 = 0;
  while(print_count1++ < 20)
  {
    if (run_now == 1)
    {
      printf("1-%d ", print_count1); // the book does not print the print_count1 number, but I want to see all steps
      run_now = 2;
    }
    else   sleep(2);
  }
  printf("Thread was created,waiting for it to finish...\n");
  result = pthread_join(simpleThread, &threadReturn);
  if(result != 0)
  {
    perror("Thread join failed");
    exit(EXIT_FAILURE);
  }
  printf("Thread joined, it returned :%s \n", (char*)threadReturn);
  exit(EXIT_SUCCESS);
}

void* threadWork(void* input)
{
  int print_count2 = 0;
  while(print_count2++ < 20)
  {
    if (run_now == 2)
    {
      printf("2-%d ",print_count2); // the book does not print the print_count2 number, but I want to see all steps
      run_now = 1;
    }
    else   sleep(1);
  }
  pthread_exit("  Thank you for the CPU time"); // this string now becomes the threadReturn value
}

// gcc -Wall -O -o page502thread2 page502thread2.c -lpthread
/* ./page502thread2 
1-1 2-2 1-3 2-4 1-5 2-7 1-7 2-10 1-9 2-13 1-11 2-16 1-13 2-19 1-15 Thread was created,waiting for it to finish...
Thread joined, it returned :  Thank you for the CPU time 
*/
// As seen from the above output, some steps are not outputed. 

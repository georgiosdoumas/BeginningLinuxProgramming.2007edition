#include <signal.h>  // for function: void (*signal(int sig, void (*func)(int)))(int);
#include <stdio.h>
#include <unistd.h>  // for sleep(n)

void ouch(int sig)
{
  printf("   OUCH! - I got signal %d , and this was my reaction.\n", sig);
  printf("   Give me another Ctrl+c to deal with it traditionally\n");
  (void) signal(SIGINT, SIG_DFL);
}

int main()
{
  (void) signal(SIGINT, ouch);
  while(1)
  {
    printf("Interrupt me with Ctrl+c! \n");
    sleep(1);
  }
  printf("You will not see this line!\n");
}

// gcc -Wall -o page483ctrlc1 page483ctrlc1.c

#include <signal.h>  // for function: void (*signal(int sig, void (*func)(int)))(int);
#include <stdio.h>
#include <unistd.h>  // for sleep(n)

void ouchbehavior(int sig)
{
  printf("   OUCH! - I got signal %d , and this was my reaction.\n", sig);
  printf("   Give me a Ctrl+ \\ to really stop me! \n");
}

int main()
{
  printf("  Using the sigaction struct, to monitor the SIGINT signal.\n");
  struct sigaction brave_act;
  brave_act.sa_handler = ouchbehavior; //when we catch the signal, we do as function ouchbehavior instructs
  sigemptyset(&brave_act.sa_mask);
  brave_act.sa_flags = 0;
  sigaction(SIGINT, &brave_act, 0);
  while(1)
  {
    printf("Interrupt me with Ctrl+c! \n");
    sleep(1);
  }
  printf("You will not see this line!\n");
}

// gcc -Wall -o page488ctrlc_sigaction page488ctrlc_sigaction.c

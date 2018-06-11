/* Not recommended to use the signal interface for catching signals. We include it here because
you will find it in many older programs. A more cleanly defined and reliable interface  is sigaction , 
and it better be used in all new programs. */
#include <signal.h>  // for function: void (*signal(int sig, void (*func)(int)))(int);
#include <stdio.h>
#include <unistd.h>  // for sleep(n)

void ouchbehavior(int sig)
{
  printf("   OUCH! - I got signal %d , and this was my reaction.\n", sig);
  printf("   Give me another Ctrl+c to deal with it using default behavior\n");
  (void) signal(SIGINT, SIG_DFL);
}

int main()
{
  printf("  Initiating the signal function, to monitor the SIGINT signal.\n");
  (void) signal(SIGINT, ouchbehavior);
  while(1)
  {
    printf("Interrupt me with Ctrl+c! \n");
    sleep(1);
  }
  printf("You will not see this line!\n");
}

// gcc -Wall -o page483ctrlc1 page483ctrlc1.c


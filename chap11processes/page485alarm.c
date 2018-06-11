
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0;

void ding(int sig)
{
  alarm_fired = 1;
  printf("\t Just changed value of static global variable. Alarm is fired from function ding()\n");
}

int main()
{
  pid_t pid;
  printf("alarm application starting\n");
  pid = fork();
  switch(pid)
  {
    case -1:    /* Failure */
      perror("fork failed");
      exit(1);
    case 0:     /* child */
      printf("\t Inside the child process, the alarm will fire in 5 secs!\n");
      sleep(5);
      kill(getppid(), SIGALRM);
      exit(0);
  }
  /* if we get here we are the parent process  */ //all that follows could go in a default: block inside switch
  printf("..waiting for alarm to go off\n");
  (void) signal(SIGALRM, ding);
  pause();
  if (alarm_fired)
    printf("\tDing!\n");
  printf("done\n");
  exit(0);
}
// gcc -Wall -o page485alarm page485alarm.c

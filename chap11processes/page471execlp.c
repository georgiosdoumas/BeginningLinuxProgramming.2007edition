/* using execvp or execlp to run bash shell commands */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define STRSIZE 50

int main()
{
  char * command1_argv[STRSIZE] = { "ps", "elf"};
  char * command2_argv[STRSIZE] = { "ps", "u"};
  printf("Running ps with execvp\n");
  execvp("ps", command1_argv); // uncomment this line , to see the execlp) used
  // execvp("ps", command2_argv);  // also correct
  printf("Done with execvp. Running ps with execlp\n"); // does not get executed because execl has replaced running program!
  execlp("ps", "ps", "xu", 0);   // does not execute
  printf("Done.\n");          // does not execute
  exit(0);
}

// gcc -Wall -o page471execlp page471execlp.c

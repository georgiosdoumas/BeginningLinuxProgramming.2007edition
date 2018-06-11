// no need to include <sys/types.h>  on my Scientific linux 7 distro 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
  pid_t pid;
  char *message;
  int n;
  printf(" fork program starting\n");
  pid = fork();
  switch(pid)
  {
    case -1:
      perror("fork failed");
      exit(1);
    case 0:
      message = "\tThis is the child";
      n = 5;  // default number of repetitions for the child
      break;
    default:
      message = "This is the parent";
      //n = 3;  // for this default value, parent would finish before child. Alternatively, ask user:
      printf("Enter number of repetitions for the message display:");
      scanf("%d", &n);
      break;
  }
  for(; n > 0; n--) {
    puts(message);
    sleep(1);
  }
  exit(0);
}

// gcc -Wall -o page474fork1 page474fork1.c

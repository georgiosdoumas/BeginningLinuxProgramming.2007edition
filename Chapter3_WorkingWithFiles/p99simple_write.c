/* Beginning Linux Programming 4th ed , page 99 ,variation of example , p99simple_write.c */
#include <unistd.h>
#include <string.h>
/* Syntax reminder : size_t write(int fildes, const void *buf, size_t nbytes); */
/* file descriptor values (fildes): 0 for std input, 1 for std output , 2 for std error */
#include <stdlib.h>
int main()
{
	char * phrase = "Some more data\n";
	char * error_text = "A write error occurred on file descriptor 1\n";
	if ((write(1, "Here is \n some data\n", 20)) != 20)  /*writes to std output*/
	  write(2, "A write error has occurred on file descriptor 1\n",46);
	/* The above lines are from the book. And I am generalize them in the next lines */
	if( (write(1,phrase,strlen(phrase))) != strlen(phrase) )
	  write(2, error_text,strlen(error_text) );
	exit(0);
}
/* gcc -Wall -o p99simple_write p99simple_write.c */
/*
to see an error message substitute 
if( (write(1,phrase,strlen(phrase))) != strlen(phrase) )
with , for example :
if( (write(1,phrase,strlen(phrase))) != strlen(phrase)+1 )
so that the if statement will not be true
*/

/* Beginning Linux Programming 4th ed , page 99-100 ,variation of example , p100simple_read.c */
/* Syntax reminder : size_t read(int fildes, void *buf, size_t nbytes); */
/* file descriptor (fildes) values: 0 for std input, 1 for std output , 2 for std error */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	char buffer[128];  /* a small buffer */
	int nread;
	char * read_err_msg = "A read error has occurred\n";
	char * write_err_msg = "A write error has occurred\n"; 
	nread = read(0, buffer, 128);  /* reading from standard input */
	if (nread == -1)
	  write( 2 , read_err_msg , strlen(read_err_msg));
	if ((write(1,buffer,nread)) != nread)
	  write( 2 , write_err_msg , strlen(write_err_msg) );
    exit(0);
}
/* gcc -Wall -o p100simple_read p100simple_read.c */
/*Run it like this: 
 * ./p100simple_read < sometextfile 
 * or
 * cat sometextfile | ./p100simple_read  
 * or 
 * echo "some phrase here" | ./p100simple_read   */

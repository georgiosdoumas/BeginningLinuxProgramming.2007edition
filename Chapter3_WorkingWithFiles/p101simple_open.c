#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
/* Syntax reminder : int open(const char *path, int oflags); */
int main(void)
{
	char buffer[128];
	int fdopen1, fdopen2, bytes_read;
	char * read_err_msg = "A read error has occurred\n";
	char * write_err_msg = "A write error has occurred\n";
	char * some_line = "Some line with no new line character" ;
	char* inputfile="input_file";
	
	fdopen1 = open(inputfile,O_RDONLY);  /* creating  fdopen1 for reading only.If input file does not exist,the next lines take care */
	bytes_read = read(fdopen1, buffer, 128); /* read from input_file ,and put the contents to buffer array (does not finish with /0 ,so not a proper string) */
	if (bytes_read == -1)  
	    write(2, read_err_msg , strlen(read_err_msg) );
	else buffer[bytes_read]='\0' ; 
	if ( (write(1,buffer, bytes_read)) != bytes_read )  /* writes to stdout , so it sends a message to terminal */
	    write( 2, write_err_msg , strlen(write_err_msg) );
	fdopen2 = open("readwritefile.txt",O_RDWR|O_APPEND); /* creating file descriptor fdopen2 for reading and writing on an existing file */
	if ( (write(fdopen2, buffer, strlen(buffer)) ) != strlen(buffer) )  /* writes to readwritefile.txt */
	    write(2, "A write error has occurred on file descriptor fdopen2\n",46);
	if ( (write(fdopen2, some_line, strlen(some_line)) ) != strlen(some_line) )  /* appends to readwritefile.txt */
	    write(2, "A write error has occurred on file descriptor fdopen2\n",46);
	close(fdopen1);
	close(fdopen2);
	exit(0);
}
/* echo "Line from input file " > input_file */
/* gcc -Wall -o p101simple_open p101simple_open.c */
/* after running it, check contents of readwritefile.txt */

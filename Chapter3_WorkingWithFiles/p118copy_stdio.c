/* Beginning Linux Programming 4th ed , page 118 , A Third File Copy Program
   My version with line-by-line as an exercise suggested by the book */ 
#include <stdio.h>
#include <stdlib.h>
/* Syntax reminder : 
char *fgets(char *s, int size, FILE *stream);
fgets() reads in at most size-1 characters from stream and stores them into the buffer pointed to by s.  
Reading stops after  an  EOF  or  a newline.  If a newline is read, it is stored into the buffer. 
A terminating null byte ('\0') is stored after the last character in the buffer.
fgets() return s on success, and NULL on error or when end of file occurs while no characters have been read.
*/
int main()
{
    char line[120]; // chose a size enough to accomodate a line of text! The terminating \0 will be placed by fgets
    // char  *line;
    FILE *instream, *outstream;
    instream = fopen("file.in","r");
    outstream = fopen("p118file.out","w");
    while ( fgets(line, 121, instream) )  
    // while ( (line = fgets(line, 121, instream)) != NULL ) : produces a compiler error about pointer types
        fprintf(outstream, "%s", line);
    exit(0);
}
/* gcc -Wall -o p118copy_stdio p118copy_stdio.c */

/* A variation of programm connect2.c , of pages 341-342 */
#include <stdlib.h>
#include <stdio.h>
#include "mysql.h"   
int main(int argc, char *argv[]) 
{
    MYSQL myconnection;
    mysql_init(&myconnection);
    /* My user is rick,the database he will connect to,on localhost,is practicedb ,we give wrong values to see erors */
    //if(mysql_real_connect(&myconnection, "localhst","rick","secret","practicedb", 0, NULL, 0) )
    //if(mysql_real_connect(&myconnection, "localhost","rock","secret","practicedb", 0, NULL, 0) ) 
    //if(mysql_real_connect(&myconnection, "localhost","rick","wrongpass","practicedb", 0, NULL, 0) ) 
    //if(mysql_real_connect(&myconnection, "localhost","rick","secret","nonexistingdb", 0, NULL, 0) )
    if(mysql_real_connect(&myconnection, "localhost","rick","secret","practicedb", 0, NULL, 0) )  /* all is correct here */
        { printf("Connection success\n"); mysql_close(&myconnection);} 
      else 
        { 
            fprintf(stderr,"Connection failed\n");
            if (mysql_errno(&myconnection) )
             {fprintf(stderr,"Connection error %d: %s\n",mysql_errno(&myconnection), mysql_error(&myconnection));}
        }
    return EXIT_SUCCESS;
}
/* 
I was able to compile it with the exact line that is given in the book on page 340 
gcc -I/usr/include/mysql page341connect2.c -L/usr/lib/mysql -lmysqlclient -o connect2 
I did it on a linux-Mint system
*/
/* Errors output that I get [ according to the if() line that I have uncommented, I get different execution error ]
Connection error 2005: Unknown MySQL server host 'localhst' (0)
Connection error 1045: Access denied for user 'rock'@'localhost' (using password: YES)
Connection error 1045: Access denied for user 'rick'@'localhost' (using password: YES)
Connection error 1049: Unknown database 'nonexistingdb'
*/

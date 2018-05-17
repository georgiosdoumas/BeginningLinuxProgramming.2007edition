// select2.c is not fully presented in the book , so I write it here with some modifications ,
// like to avoide the global declaration of MYSQL , MYSQL_RES , MYSQL_ROW , and to add 
// the mysql_errno(&my_connection) in the outputs 
// I also used a match criteria of name-text , not of age , to be sure that it works well
// page 351
#include <stdlib.h>
#include <stdio.h>
#include "mysql.h"
int main(int argc, char *argv[]) 
{
    MYSQL my_connection;  //The book had these 3 declared before main(), at global scope, which I find unneccesssary 
    MYSQL_RES *res_ptr;
    MYSQL_ROW sqlrow;
    int res;
    mysql_init(&my_connection);
    if (mysql_real_connect(&my_connection,"localhost","rick","secret","practicedb", 0, NULL, 0)) 
    {
        printf("Connection success\n");
        res = mysql_query(&my_connection,"SELECT childno, fname, age FROM children WHERE fname = 'Ann' ");
        /* by typing mistakenly something from the above line , eg childrenn , we can get various SELECT errors: */
        if (res) { printf("SELECT error %d: %s\n",mysql_errno(&my_connection), mysql_error(&my_connection)); }
        else
         { 
            res_ptr = mysql_use_result(&my_connection);
            if (res_ptr) 
             {
                while ((sqlrow = mysql_fetch_row(res_ptr))) 
                  { printf("Fetched data , one row at a time ...\n"); }
                if (mysql_errno(&my_connection)) 
                  { fprintf(stderr, "Retrive error %d: %s\n",mysql_errno(&my_connection), mysql_error(&my_connection)); }
                mysql_free_result(res_ptr);
             }
         }
        mysql_close(&my_connection);
     } 
    else 
     {
        fprintf(stderr, "Connection failed\n");
        if (mysql_errno(&my_connection)) 
         { fprintf(stderr,"Connection error %d: %s\n",mysql_errno(&my_connection), mysql_error(&my_connection)); }
     }
    return EXIT_SUCCESS;
}
// gcc -I/usr/include/mysql page351select2.c -L/usr/lib/mysql -lmysqlclient -o select2 
// For the practicedb of page 344-345 , I get 4 rows returned , which is correct

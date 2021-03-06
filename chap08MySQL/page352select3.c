//select3.c is a variation of the book program on pages 352-353 , where I follow the 
//avoidance of usage of global [outside main] variables. So I need to do some modifications
//on the declaration and definition and usage of function display_row() 
#include <stdlib.h>
#include <stdio.h>
#include "mysql.h"
//void display_row(MYSQL * some_connection_ptr , MYSQL_ROW dbrow);  //alternate declaration
void display_row(MYSQL  some_connection , MYSQL_ROW dbrow);   // but this aslo works
int main(void) 
{
    MYSQL my_connection;
    MYSQL_RES *res_ptr;
    MYSQL_ROW sqlrow;
    int res;
    mysql_init(&my_connection);
    if (mysql_real_connect(&my_connection,"localhost","rick","secret","practicedb", 0, NULL, 0)) 
    {
        printf("Connection success\n");
        res = mysql_query(&my_connection,"SELECT childno, fname, age FROM children WHERE fname = 'Ann' ");
        /* by typing mistakenly something from the above line , eg childrenn , we can get various SELECT error: */
        if (res) { printf("SELECT error %d: %s\n",mysql_errno(&my_connection), mysql_error(&my_connection)); }
        else
         { 
            res_ptr = mysql_use_result(&my_connection);
            if (res_ptr) 
             {
                while ((sqlrow = mysql_fetch_row(res_ptr))) 
                  { 
                    printf("Fetched data , one row at a time ...\n"); 
                    //display_row(&my_connection , sqlrow ); //use this line for the alternate definition case
                    display_row(my_connection , sqlrow );
                  }
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
// The definition could go to a seperate file, but to keep things simple, we have it in this file:
//void display_row(MYSQL * some_connection_ptr , MYSQL_ROW dbrow)  //alternate definition
void display_row(MYSQL some_connection , MYSQL_ROW dbrow)
{
    unsigned int field_count;  /* number of columns */
    field_count = 0;
    //while ( field_count < mysql_field_count(some_connection_ptr) )  //use this line for the alternate definition case
    while ( field_count < mysql_field_count(&some_connection) ) 
     {
        printf("%s ", dbrow[field_count]);
        field_count++;
     }
    printf("\n");
}
// gcc -I/usr/include/mysql page352select3.c -L/usr/lib/mysql -lmysqlclient -o select3 

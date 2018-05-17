// select4.c , again different from what the book has on pages 355-356
// page 355-356 
#include <stdlib.h>
#include <stdio.h>
#include "mysql.h"
void display_header(MYSQL_RES * some_res_ptr);
//void display_row(MYSQL * some_connection_ptr , MYSQL_ROW dbrow);
void display_row(MYSQL  some_connection , MYSQL_ROW dbrow);
int main(void) 
{
    MYSQL my_connection;
    MYSQL_RES *res_ptr;
    MYSQL_ROW sqlrow;
    int res;
    int first_row = 1; /* Used to ensure we display the row header exactly once when data is successfully retrieved */
    mysql_init(&my_connection);
    if (mysql_real_connect(&my_connection,"localhost","rick","secret","practicedb", 0, NULL, 0)) 
    {
        printf("Connection success\n");
        res = mysql_query(&my_connection,"SELECT childno, fname, age FROM children WHERE fname = 'Ann' ");
        if (res) { fprintf(stderr,"SELECT error %d: %s\n",mysql_errno(&my_connection), mysql_error(&my_connection)); }
        else
         { 
            res_ptr = mysql_use_result(&my_connection);
            if (res_ptr) 
             {
                while ((sqlrow = mysql_fetch_row(res_ptr))) 
                   { 
                    if (first_row) 
                     {
                        display_header(res_ptr);
                        first_row = 0;
                     }
                    //display_row(&my_connection , sqlrow ); 
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
void display_header(MYSQL_RES * some_res_ptr)
{
    MYSQL_FIELD * field_ptr;
    printf("Column details : \n");
    while ( (field_ptr = mysql_fetch_field(some_res_ptr)) != NULL )
     {
        printf("\t Name: %s\n", field_ptr->name);
        printf("\t Type: ");
        if (IS_NUM(field_ptr->type)) 
         { printf("Numeric field\n"); }
        else 
         {
            switch(field_ptr->type)
             {
                case FIELD_TYPE_VAR_STRING: printf("VARCHAR\n"); break;
                case FIELD_TYPE_LONG:       printf("LONG\n");    break;
                default : printf("Type is %d, check in mysql_com.h\n", field_ptr->type);
             }
         }
        printf("\t Max width %ld\n", field_ptr->length);
        if (field_ptr->flags & AUTO_INCREMENT_FLAG)  printf("\t Auto increments\n");
        printf("\n");
     }
}
//void display_row(MYSQL * some_connection_ptr , MYSQL_ROW dbrow)
void display_row(MYSQL some_connection , MYSQL_ROW dbrow)
{
    unsigned int field_count;  /* number of columns */
    field_count = 0;
    //while ( field_count < mysql_field_count(some_connection_ptr) )
    while ( field_count < mysql_field_count(&some_connection) ) 
     {
        if (dbrow[field_count]) printf("%s ", dbrow[field_count]);
        else printf("NULL");
        field_count++;
     }
    printf("\n");
}
// gcc -I/usr/include/mysql select4.c -L/usr/lib/mysql -lmysqlclient -o select4 
// For the practicedb of page 344-345 , I get 4 rows returned , which is correct

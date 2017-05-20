/* Beginning Linux Programming 4th ed , page 102 , there is no example in the book, so I tried something on my own  */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/* Syntax reminder : int open(const char *path, int oflags, mode_t mode); */
int main(void)
{
    open ("myfile_with_permissions1", O_CREAT, S_IRUSR|S_IXOTH);
    open ("myfile_with_permissions2", O_CREAT, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP);
    /* for my ubuntu system, with umask 022, the S_IWGRP will not manage to give w permission to grp. See pages 101-102, paragraph umask */
    exit(0);
}
/* gcc -Wall -o p102create_file_with_permissions p102create_file_with_permissions.c */
/* and then run the program and check the created files : 
./p102create_file_with_permissions
umask
ls -l myfile_with_permissions* 
-r-------x 1 george george 0 May 20 23:28 myfile_with_permissions1
-rwxr----- 1 george george 0 May 20 23:28 myfile_with_permissions2
*/

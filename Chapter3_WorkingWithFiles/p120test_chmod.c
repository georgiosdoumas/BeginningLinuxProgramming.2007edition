/* Beginning Linux Programming 4th ed , page 120 , trying to make a small program to use function chmod() */
#include <sys/stat.h>
/* Syntax reminder : int chmod(const char *path, mode_t mode); */
int main(int argc ,char * argv[] ) 
{
    chmod(argv[1], S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IROTH  ) ; /* rwxrw-r-- */
    return 0;
}
/* gcc -Wall -o p120test_chmod p120test_chmod.c 
./p120test_chmod existing_file_to_make_rwxrw-r
ls -l existing_file_to_make_rwxrw-r
*/

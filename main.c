// 2. Să se scrie un program care primește ca și argument în linie de comandă calea către o intrare de pe disc.
// Programul va afișa pentru intrarea respectivă următoarele informații:
// Tipul intrării: director / fișier obișnuit / legătură simbolică
// Permisiunile pentru owner/user, sub forma: rwx, - dacă vreuna lipsește
// Dimensiunea în octeți 

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <stdint.h>

int main(int argc,char** argv){

    if(argc != 2){
        printf("INVALID ARGUMENTS");
        exit(EXIT_FAILURE);
    }

    struct stat sb;

    if(lstat(argv[1], &sb) < 0){
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    printf("File type:                ");

    switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("symlink\n");                 break;
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFSOCK: printf("socket\n");                  break;
    default:       printf("unknown?\n");                break;
    }

    printf("Size allocated:         %jd\n",(intmax_t)sb.st_size);
    // printf("Ownership:                UID=%ju\n",(uintmax_t) sb.st_uid);
    printf("%s", (sb.st_mode & S_IRUSR) ? "r" : "-");
    printf("%s", (sb.st_mode & S_IWUSR) ? "w" : "-");
    printf("%s\n", (sb.st_mode & S_IXUSR) ? "x" : "-");

    return 0;
}
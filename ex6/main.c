#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/sysmacros.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

// void readDir(char* path){

//     struct dirent* dr;
//     struct stat sb;
//     char newPath[1000];

//     DIR * dirStream = NULL;
//     if((dirStream = opendir(path)) == NULL){
//         printf("ERROR OPEN DIR\n");
//         exit(EXIT_FAILURE);
//     }

//     while((dr = readdir(dirStream)) != NULL){

//         if(strcmp(dr->d_name,".") == 0 || strcmp(dr->d_name,"..") == 0){
//             continue;
//         }
//         sprintf(newPath,"%s/%s",path,dr->d_name);
//         // printf("%s\n",newPath);

//         if (lstat(newPath, &sb) == -1) {
//             perror("lstat");
//             exit(EXIT_FAILURE);
//         }

//         switch (sb.st_mode & S_IFMT) {
//             case S_IFBLK:  printf("block device\n");            break;
//             case S_IFCHR:  printf("character device\n");        break;
//             case S_IFDIR:  
//                 printf("directory\n");               
//                 readDir(newPath);
//                 break;
//             case S_IFIFO:  printf("FIFO/pipe\n");               break;
//             case S_IFLNK:  printf("symlink\n");                 break;
//             case S_IFREG:  
//                 printf("regular file\n");          
//                 if( ( pid=fork() ) < 0)
//                 {
//                     perror("Eroare");
//                     exit(1);
//                 }
//                 if(pid==0)
//                 {
//                     /* codul fiului - doar codul fiului poate ajunge aici (doar in fiu fork() returneaza 0)*/
//                     exit(0); // apel necesar pentru a se opri codul fiului astfel incat acesta sa nu execute si codul parintelui
//                 }
//                 break;
//             case S_IFSOCK: printf("socket\n");                  break;
//                 default:       printf("unknown?\n");                break;
//         }
//     }

//     if(closedir(dirStream) == -1){
//         perror("error closing dir");
//         exit(EXIT_FAILURE);
//     }
// }

int main(int argc,char** argv){
    if(argc != 2 ){
        printf("WRONG ARGS");
        exit(EXIT_FAILURE);
    }

    int pfd[2];
    int pid;
    //0 for read 1 for write
    if(pipe(pfd) < 0){
        perror("ERROR CREATING PIPE\n");
        exit(EXIT_FAILURE);
    }

    if( ( pid=fork() ) < 0)
    {
        perror("Eroare");
        exit(1);
    }
    if(pid==0)
    {
        /* codul fiului - doar codul fiului poate ajunge aici (doar in fiu fork() returneaza 0)*/
        close(pfd[0]);

        int fdIn = -1;
        if((fdIn = open(argv[1],O_RDONLY)) < 0){
            perror("FAIL OPENING FILE\n");
            close(pfd[1]);
            exit(EXIT_FAILURE);
        }

        char temp;

        while((read(fdIn,&temp,1)) > 0){
            if(temp == 'a' || temp == 'e' || temp == 'i' || temp == 'o' || temp == 'u'){
                write(pfd[1],&temp,sizeof(char));
                // printf("LETTER:%c\n",temp);
            }
        }

        close(pfd[1]);
        exit(0); // apel necesar pentru a se opri codul fiului astfel incat acesta sa nu execute si codul parintelui
    }
    /* codul parintelui */
    close(pfd[1]);

    char temp1 = -1;
    
    while(read(pfd[0],&temp1,sizeof(char)) > 0){
        printf("LETTER:%c\n",temp1);
    }

    close(pfd[0]);

    int wstatus;

    waitpid(pid,&wstatus,0);

    if (WIFEXITED(wstatus)) {
        printf("Procesul părinte: Procesul copil s-a terminat cu codul de ieșire %d.\n", WEXITSTATUS(wstatus));
    } else {
        printf("Procesul părinte: Procesul copil nu s-a terminat corect.\n");
    }

    return 0;
    // readDir(argv[1]);
}

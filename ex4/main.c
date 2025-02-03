// Să se scrie un program C care primește ca și argumente în linie de comandă o cale relativă sau absolută de director și o cale către un fișier.
// Programul va avea următoarele funcționalități:
// va parcurge recursiv directorul dat ca și parametru
// pentru fiecare fișier întâlnit, programul va număra câte litere mici conține acesta
// va scrie rezultatul într-un fișier text dat ca și argument în linie de comandă, sub forma:
// <cale-director> <dimensiune> <nr-litere-mici> <tip-fișier>
// unde tip-fișier poate fi: REG, LNK , DIR sau PIPE
// dacă primul argument nu este director, programul va afișa un mesaj de eroare
// dacă al doilea argument reprezintă un fișier deja existent pe disc, acesta va fi suprascris
// Programul se va testa folosind un director ce conține directoare, fișiere obișnuite, legături simbolice și named pipes.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int wc(char* path){
    int fd = -1;
    int counter = 0;

    if((fd = open(path,O_RDONLY)) < 0){
        perror("ERROR OPENING FILE FOR COUNTING");
        exit(EXIT_FAILURE);
    }

    char buff;
    int aux = 0;

    while((aux = read(fd,&buff,1)) > 0){
        // printf("%s",buff);
        counter += aux;
    }
    // char buff[1000];
    // int aux = 0;

    // while((aux = read(fd,&buff,1000)) > 0){
    //     // printf("%s",buff);
    //     counter += aux;
    // }

    if(aux < 0){
        perror("error reading file");
        exit(EXIT_FAILURE);
    }

    close(fd);
    return counter;
}

void iterateDir(char* path){

    struct dirent * dr;
    DIR* dirStream = NULL;
    char newPath[1000];
    struct stat sb;

    
    if((dirStream = opendir(path)) == NULL){
        perror("ERROR OPENING DIR");
        exit(EXIT_FAILURE);
    }

    while((dr = readdir(dirStream)) != NULL){
        // switch (dr->d_type) {
        //     case DT_DIR:  
        //         printf("DIRECTOR: %s\n",dr->d_name);
        //         break;
        //     default:       
        //         printf("argv[1] is not a dir \n");  
        //         exit(EXIT_FAILURE); 
        //         break;
        // }

        if(strcmp(dr->d_name,".") == 0 || strcmp(dr->d_name,"..") == 0)
            continue;
        sprintf(newPath,"%s/%s",path,dr->d_name);
        // printf("%s\n",newPath);


        if(lstat(newPath,&sb) < 0){
            perror("error stat function");
            exit(EXIT_FAILURE);
        }

        switch (sb.st_mode & __S_IFMT) {
            case __S_IFDIR:  
                // printf("dir\n");
                printf("DIRECTOR: %s\n",newPath);
                iterateDir(newPath);
                break;
            case __S_IFIFO:  
                // printf("dir\n");
                printf("NAMED PIPE: %s\n",newPath);
                break;
            case __S_IFLNK:  
                // printf("dir\n");
                printf("SYMBO-LINK: %s\n",newPath);        
                break;
            case __S_IFREG:  
                printf("WC:%d\n",wc(newPath));       
                printf("REGULAR FILE: %s\n",newPath);
                break;
            default:       printf(" unknown?\n");                break;
        }
    }

    if(closedir(dirStream) == -1){
        perror("error closing dir");
        exit(EXIT_FAILURE);
    }
}

int main(int argc,char** argv){

    if(argc != 3){
        printf("INVALID ARGUMENTS\n");
        exit(EXIT_FAILURE);
    }

    int fdIn = -1;

    struct stat sb;

    if (lstat(argv[1], &sb) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    switch (sb.st_mode & S_IFMT) {
        case S_IFDIR:  
            iterateDir(argv[1]);
            break;
        default:       printf("argv[1] is not a dir \n");  exit(EXIT_FAILURE); break;
    }

    return 0;
}

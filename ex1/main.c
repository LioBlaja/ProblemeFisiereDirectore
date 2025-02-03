// 1. Să se scrie un program care primește ca și argumente în linie de comandă calea către 2 fișiere:
//           <program> <fișier-intrare> <fișier-ieșire>
// Programul va citi în întregime <fișier-intrare>, și va afișa la ieșirea standard octeții transformați după regula următoare:
// dacă octetul are valoarea între 97 și 122, va fi afișat folosind printf, ca și literă mică
// altfel se va afișa în hexadecimal
// La final, programul va scrie în <fișier-ieșire> o linie de forma:
// ''Numărul total de litere mici afișate este ...''

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc,char** argv){

    if(argc != 3){
        printf("INVALID ARGUMENTS\n");
        exit(EXIT_FAILURE);
    }

    int counter = 0;

    int inputFile = -1;

    if((inputFile = open(argv[1], O_RDONLY))< 0){
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    char readChar;
    while(read(inputFile, &readChar, sizeof(char)) == 1){
        if(readChar > 97 && readChar < 122){
            counter++;
            printf("%c",readChar);
        }else{
            printf("Ox%x",readChar);
        }
    }
    
    int outFile = -1;

    if((outFile = open(argv[2], O_WRONLY | O_CREAT  | O_TRUNC , S_IRWXU))< 0){
        perror(NULL);
        close(inputFile);
        exit(EXIT_FAILURE);
    }

    char buffer[50];
    sprintf(buffer, "Numărul total de litere mici afișate este %d", counter);

    if(write(outFile,buffer,strlen(buffer)) < 0){
        close(inputFile);
        close(outFile);
        perror(NULL);
        exit(EXIT_FAILURE);
    } 

    close(inputFile);
    close(outFile);

    return 0;
}

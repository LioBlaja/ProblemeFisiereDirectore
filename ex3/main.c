#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

// 3. Să se scrie un program care primește ca și argumente în linie de comandă calea către 2 fișiere:
//           <program> <fișier-intrare> <fișier-ieșire>
// Fișierul de intrare va conține un număr necunoscut de numere întregi pe 4 octeți.
// Programul va citi fișierul de intrare în întregime și va scrie în fișierul de ieșire, în format text, numărul minim, numărul maxim și media numerelor citite din fișierul de intrare binar.

int cmpFunction(const void *a, const void *b) {
    // Cast the void pointers to integers
    int int_a = *(int*)a;
    int int_b = *(int*)b;

    // Compare the integers and return the result
    if (int_a < int_b) return -1;  // a is less than b
    if (int_a > int_b) return 1;   // a is greater than b
    return 0;                       // a is equal to b
}

int main(int argc,char** argv){

    if(argc != 3){
        printf("INVALID ARGUMENTS");
        exit(EXIT_FAILURE);
    }

    int fdIn = -1;

    if((fdIn = open(argv[1],  O_RDONLY)) < 0){
        perror("INPUT FILE OPEN\n");
        exit(EXIT_FAILURE);
    }

    int number = -1;
    ssize_t bytes_read;

    // printf("%ld",sizeof(number));
    int values[10];
    int counter = 0;

    while ((bytes_read = read(fdIn, &number, sizeof(number))) > 0) {
        if (bytes_read == sizeof(number)) {
            // printf("Read number: %d\n", number);
            values[counter] = number;
            counter++;
        } else {
            fprintf(stderr, "Error reading number\n");
            close(fdIn);
            return 1;
        }
    }

    for (int i = 0; i < counter; i++)
    {
        printf("%d\n",values[i]);
    }
    
    qsort(values, counter, sizeof(int), cmpFunction);
    printf("Min:%d",values[0]);
    printf("Max:%d",values[counter]);

    close(fdIn);
    return 0;
}

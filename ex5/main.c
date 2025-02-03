// 5. Să se scrie un program C care constă în 2 procese înrudite:
// procesul copil: își va seta un comportament nou la recepția semnalului SIGUSR1: va afișa un mesaj și își va termina execuția.
// procesul părinte: va trimite semnalul SIGUSR1 procesului copil și după va prelua starea acestuia.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler(int signum)
{
    printf ("am primit semnal de SIGUSR1\n");
    exit(100);
}

int main(void){

    int sigaction(int signum, const struct sigaction *act,
                     struct sigaction *oldact);

    int pid = -1;

    pid_t cpid, w;
    int wstatus;

    if( ( pid=fork() ) < 0)
    {
        perror("Eroare");
        exit(1);
    }

    if(pid==0)
    {
        struct sigaction sig;
        memset(&sig, 0, sizeof(struct sigaction));
        sig.sa_handler = handler;
        sig.sa_flags = SA_RESTART; // sa rezume apelurile sistem dupa intrerupere, kind of checkpoint de unde continua executia
        printf("PID:%d\n",getpid());
        if (sigaction(SIGUSR1, &sig, NULL) < 0)
        {
            perror(NULL);
            exit(EXIT_FAILURE);
        }
        // while(1){
            printf("running\n");
            pause();
        // }
        /* codul fiului - doar codul fiului poate ajunge aici (doar in fiu fork() returneaza 0)*/
        exit(0); // apel necesar pentru a se opri codul fiului astfel incat acesta sa nu execute si codul parintelui
    }
    /* codul parintelui */
    sleep(5);
    printf("Procesul părinte: Trimit semnalul SIGUSR1 către procesul copil.\n");
    kill(pid, SIGUSR1);  // Trimite semnalul SIGUSR1 către procesul copil

    w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
    if (w == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    if (WIFEXITED(wstatus)) {
        printf("Procesul părinte: Procesul copil s-a terminat cu codul de ieșire %d.\n", WEXITSTATUS(wstatus));
    } else {
        printf("Procesul părinte: Procesul copil nu s-a terminat corect.\n");
    }

    return 0;
}

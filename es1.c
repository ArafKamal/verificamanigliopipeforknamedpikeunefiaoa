#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <errno.h>

int main(void){
    int n;
    
    printf("Scrivi il numero di processi (1-10)\n");
    scanf("%d", &n);
    
    if (n > 10 || n< 1){
        printf("Errore, numero non valido\n");
        exit(-1);
    }
    
    int pid_padre = getpid();

    printf("[Padre - Livello 0] PID %d\n", pid_padre);    
    
    int somma = 0;
    
    for (int i = 0; i < n; i++){
        
        pid_t pid = fork();
        
        if(pid < 0){
            printf("Errore fork");
            exit(1);
        } else if (pid == 0){
            // FIGLIO
            
            printf("[Figlio - Livello %d] PID %d, padre %d\n", i + 1, getpid(), pid_padre);
            fflush(stdout);
            exit(i + 1);
            
            
        } else {
            // PADRE
            
            int status;
                wait(&status);
                
                if (WIFEXITED(status) == -1){
                    printf("Errore");
                    exit(1);
                }
            
            int num = WEXITSTATUS(status);
            somma += num;
                
            printf("[Padre] Figlio terminato con codice %d\n", num);
            fflush(stdout);
        }
        printf("\n");
        
        printf("[Padre] Somma dei codici di uscita: %d\n", somma);
        fflush(stdout);
    }
    
    
    
    
    
    
    return 0;
}

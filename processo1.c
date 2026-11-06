#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO1 "fifo_p1_to_p2"
#define FIFO2 "fifo_p_to_p2"

int main(void){
    int array[5];
    
    printf("Inerisci 5 numeri:\n");
    
    for(int i = 0; i < 5; i++){
        printf("Numero %d:\n", i+1);
        
        int num;
        scanf("%d", &num);
        array[i] = num;
    }
    
    if (mkfifo(FIFO1, 0666) == -1){
        if (errno == EEXIST){
            printf("La pipe esiste\n");
        } else {
            perror("Errore pipe\n");
            exit(1);
        }
    }

    if (mkfifo(FIFO2, 0666) == -1){
        if (errno == EEXIST){
            printf("La pipe esiste\n");
        } else {
            perror("Errore pipe\n");
            exit(1);
        }
    }
    
    int fd1 = open(FIFO1, O_WRONLY);
    int fd2 = open(FIFO2, O_RDONLY);
    
    write(fd1, array, sizeof(array));
    
    int pari;
    read(fd2, &pari, sizeof(pari));
    
    int dispari;
    read(fd2, &dispari, sizeof(dispari));
    
    printf("Numeri pari trovati: %d\n", pari);
    printf("Numeri dispari trovati: %d\n", dispari);
    
    close (fd1);
    close (fd2);
    
    unlink(FIFO1);
    unlink(FIFO2);
    
    return 0;    
}

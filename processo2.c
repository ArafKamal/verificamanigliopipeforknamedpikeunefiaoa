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
    
    if (mkfifo(FIFO1, 0666) == -1){
        if (errno == EEXIST){
            printf("La pipe esiste\n");
        } else {
            perror("Errore pipe\n");
            exit(1);
        }
    }
    
    int fd1 = open(FIFO1, O_RDONLY);
    int fd2 = open(FIFO2, O_WRONLY);
    
    int array[5];
    
    read(fd1, array, sizeof(array));
    
    int n1 = 0;
    int n2 = 0;
    
    for(int i = 0; i < 5; i++){
        if (array[i] % 2 == 0){
            n1++;
        } else {
            n2++;
        }
    }
    
    write(fd2, &n1, sizeof(n1));
    write(fd2, &n2, sizeof(n2));
    
    close (fd1);
    close (fd2);
    
    return 0;
}

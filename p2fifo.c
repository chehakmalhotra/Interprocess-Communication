#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#define FIFO_NAME1 "goodfifo"
#define FIFO_NAME2 "badfifo"



int main() {

    struct timespec start, stop1, stop2, stop3;
    double accum;
    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
        perror( "clock gettime" );
        return EXIT_FAILURE;
        //return NULL;
    }

    mkfifo(FIFO_NAME1, 0666);
    mkfifo(FIFO_NAME2, 0666);
    char buffer[7];
    int count;
    //char array[5];
    printf("waiting for writer\n");
    int fp = open(FIFO_NAME1, O_RDONLY);
    printf("writer gotten\n");
    int fd = open(FIFO_NAME2, O_WRONLY);
    while(1) {



        for (int i = 0; i < 5; i++) {
            read(fp, buffer, 7);

            printf("received: %s\n", buffer);
        }
       /* id[0] = buffer[0];
        id[1] = buffer[1];*/



        /*int maxindex=0;
        for(int i = 0; i < 5; i++) {
            if(buff[i]>array[maxindex]) {
                maxindex=i;
            }
        }*/



        write(fd, buffer, 7);
        count++;
        if(count==10) {
            break;
        }


    }


    close(fp);
    close(fd);
    accum = ( stop1.tv_sec - start.tv_sec )
            + (double)( stop1.tv_nsec - start.tv_nsec )
              /(double) 1000000000L;
    printf("%ld\n",stop1.tv_nsec - start.tv_nsec);








}

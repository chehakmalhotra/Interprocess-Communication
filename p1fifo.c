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

    char stringArray[50][6];
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 5; j++) {
            stringArray[i][j] = rand() % 26 + 65;
        }
        stringArray[i][5] = '\0';


    }
    for (int i = 0; i < 50; i++)
        printf("%s\n", stringArray[i]);

    mkfifo(FIFO_NAME1, 0666);
    mkfifo(FIFO_NAME2, 0666);

    printf("waiting for reader\n");
    int fp = open(FIFO_NAME1, O_WRONLY);
    printf("reader gotten\n");
     int count=0;
    int fd = open(FIFO_NAME2, O_RDONLY);
    int index = 0;
    while(1) {
        char *id;
        id = (char *) malloc(7 * sizeof(char));
        for (int i = 0; i < 5; i++) {
            if (index < 10) {
                sprintf(id, "0%d", index);
            } else {
                sprintf(id, "%d", index);
            }

            strcat(id, stringArray[index]);

            write(fp, id, 7);
            index++;
        }

        char buf[7];
        read(fd, buf, 7);
        printf("received: %s\n", buf);
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













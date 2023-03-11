#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/un.h>
#include <pcap/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
#include <sys/mman.h>
#include <fcntl.h>

int main() {
    char stringArray[50][8];
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 5; j++) {
            stringArray[i][j] = rand() % 26 + 65;
        }
        stringArray[i][5] = '\0';


    }
    for (int i = 0; i < 50; i++)
        printf("%s\n", stringArray[i]);



    //int key_t = ftok("file", 65);
    int fd= shm_open("server", O_RDONLY | O_CREAT | O_EXCL, 0666);
    //int fd = shm_open("server", O_RDONLY | O_CREAT | O_EXCL, 0666);
    if (fd == -1) {
        if (errno == EEXIST) {
            // Shared memory object already exists, just open it for reading
            fd = shm_open("server", O_RDONLY, 0666);
            if (fd == -1) {
                fprintf(stderr, "Error: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
        else {
            // Some other error occurred
            fprintf(stderr, "Error: %s\n", strerror(errno));
            //printf("Error");
            exit(EXIT_FAILURE);
        }

    }


    ftruncate(fd, 50*7 );
    char* data = (char*) mmap(0, 50 * 7, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        //printf("error");
        exit(EXIT_FAILURE);
    }
    int count=0;
    int index = 0;
    char *id;
    int count1=0;
    while(count1<10) {
        id = (char *) malloc(8 * sizeof(char));
        for (int i = 0; i < 5; i++) {
            if (index < 10) {
                sprintf(id, "0%d", index);
            } else {
                sprintf(id, "%d", index);
            }
            stringArray[index][5] = id[0];
            stringArray[index][6] = id[1];
            stringArray[index][7] = '\0';

            index++;
        }
        count1++;
    }

    while(count < 10) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 7; j++) {
                data[i * 7 + j] = stringArray[i][j];
                printf("%c", data[i * 7 + j]);

            }

        }
        count++;
    }





    /*shm_open(key_t, IPC_CREAT | 0666);
    //int shm_open = shmget(key_t, 1024, 0666 | IPC_CREAT);
    char *str = (char *) shmat(shmid, (void *) 0, 0);

    int count = 0;
    int index = 0;
    while (1) {
        char *id;
        id = (char *) malloc(7 * sizeof(char));
        for (int i = 0; i < 5; i++) {
            if (index < 10) {
                sprintf(id, "0%d", index);
            } else {
                sprintf(id, "%d", index);
            }

            strcat(id, stringArray[index]);

            printf("sending: %s\n", id);
            strncpy(str, id, 7);
            index++;
        }


    }*/
    munmap(data,50*7);
    close(fd);

}

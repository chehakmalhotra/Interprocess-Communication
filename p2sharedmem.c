#include <stdio.h>
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
    int fd = shm_open("server", O_RDONLY, 0666);
    if (fd == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    char *data = (char *) mmap(0, 50 * 7, PROT_READ, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    int count = 0;
    while (count < 10) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 7; j++) {
                printf("%c", data[i * 7 + j]);
            }
            printf("\n");
        }
        count++;
    }


    munmap(data, 50 * 7);
    close(fd);
    shm_unlink("server");



}

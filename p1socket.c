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

int main() {
    char stringArray[50][6];
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 5; j++) {
            stringArray[i][j] = rand() % 26 + 65;
        }
        stringArray[i][5] = '\0';


    }
    for (int i = 0; i < 50; i++)
        printf("%s\n", stringArray[i]);

    struct sockaddr_un soky;
    unsigned int fp;
    fp = socket(AF_UNIX, SOCK_STREAM, 0);
    soky.sun_family = AF_UNIX;
    strcpy(soky.sun_path, "server");
    unlink(soky.sun_path);
    bind(fp, (struct sockaddr *) &soky, sizeof(struct sockaddr_un));
    listen(fp, 1);
    unsigned int fd = accept(fp, NULL, NULL);
    printf("Connected.\n");
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

            send(fd, id, 7, 0);
            index++;
        }

        char buf[7];
        recv(fd, buf, 7, 0);
        printf("received: %s\n", buf);
        count++;
        if (count == 10) {
            break;
        }

    }


    close(fd);
}











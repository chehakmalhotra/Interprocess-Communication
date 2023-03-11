#include <stdio.h>
#include <pcap/socket.h>
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


int main() {
    struct sockaddr_un soky;
    unsigned int fp;
    fp = socket(AF_UNIX, SOCK_STREAM, 0);
    soky.sun_family = AF_UNIX;
    strcpy(soky.sun_path, "server");
    connect(fp, (struct sockaddr *) &soky, sizeof(struct sockaddr_un));
    printf("Connected.\n");
    char buf[7];
    int count = 0;
    while (1) {

        for (int i = 0; i < 5; i++) {
            recv(fp, buf, 7, 0);

            printf("received: %s\n", buf);
        }
        send(fp, buf, 7, 0);
        count++;
        if (count == 10) {
            break;
        }
    }


}

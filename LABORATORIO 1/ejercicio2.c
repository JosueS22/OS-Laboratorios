#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#define MODE 0666
#define BUF_SIZE 8192

int main(int argc, char* argv[]) {
    int source, destination, init, output;
    char buf[BUF_SIZE];
    if (argc != 3) exit(1);
    source = open(argv[1], O_RDONLY);
    if (source < 0) exit(2);
    destination = creat(argv[2], MODE); if (destination < 0) exit(3);

    while(1) {
        init = read(source, buf, BUF_SIZE);
        if (init <= 0) break;
        output = write(destination, buf, init);
        if (output <= 0) break;
    }
    close(source);
    close(destination);
    exit(0);
}
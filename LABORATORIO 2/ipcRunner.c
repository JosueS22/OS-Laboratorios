#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (){
    pid_t a = fork();

    if ( a == 0) {
        execl("ipc", "ipc", "10", "a", (char*)NULL);
    }
    else {
        usleep(1000);
        execl("ipc", "ipc", "10", "b", (char*)NULL);

    }
}
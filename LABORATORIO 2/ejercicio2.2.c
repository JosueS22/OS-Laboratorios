#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    clock_t a, b, c;
    pid_t x, y, t;
    int i;
    x = clock();
    a = fork();

    // Si es el proceso hijo
    if (a == 0){
        b = fork();

        // Si es el proceso nieto
        if (b == 0) {
            c = fork();

            // Si es el proceso bisnieto
            if (c == 0) {
                for (i=0;i<1000000;i++){}
            } else {
                for (i=0;i<1000000;i++){}
                wait(NULL);
            }
        } else {
            for (i=0;i<1000000;i++){}
            wait(NULL);
        }
    } else {
        wait(NULL);
        y = clock();
    }

    t = (double)x-y;
    printf("Delta = %f", t);
    return 0;
}
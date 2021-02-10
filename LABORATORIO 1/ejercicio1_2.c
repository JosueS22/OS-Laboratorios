#include <stdio.h>
#include <unistd.h>

int main(){
    int f = fork();
    printf("Hello World \n");
    printf("%d\n", (int)getpaid());
    if (f==0) {
        printf("Hello from child\n");
        execl("ejercicio1.c",(char*)NULL);
    } else {
        printf("Hello from parent\n");
        execl("ejercicio1.c",(char*)NULL);
    }
    return 0;
}
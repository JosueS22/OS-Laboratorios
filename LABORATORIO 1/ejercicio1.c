#include <stdio.h>
#include <unistd.h>

int main(){
    printf("Hello World \n");
    printf("%d\n", (int)getpaid());
    execl("ejercicio1.c",(char*)NULL);
    return 0;
}
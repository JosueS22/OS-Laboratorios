#include <stdio.h>
#include <unistd.h>

int main(){
    fork();
    fork();
    fork();
    fork();
    printf("fork \n");
    return 0;
}
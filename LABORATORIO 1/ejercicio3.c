#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    int x = syscall(345,5);
    printf("%d\n", x);
    return 0;
}
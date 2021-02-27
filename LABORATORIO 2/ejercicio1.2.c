#include <stdio.h>
#include <unistd.h>

int main(){
    int i = 1;
    for(i = 0; i <= 4; i++){
        fork();
        printf("fork \n");
    }
    return 0;
}
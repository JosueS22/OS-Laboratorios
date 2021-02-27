#include <stdio.h>
#include <time.h>

int main(){
    clock_t a, b, t;
    int i,j,k;
    a = clock();
    for(i = 0; i < 1000000; i++){}
    for(j = 0; j < 1000000; j++){}
    for(k = 0; k < 1000000; k++){}
    b = clock();
    t = (double)(a - b);
    printf("Delta: %f \n", t);
    return 0;
}
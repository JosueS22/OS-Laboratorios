#include <stdio.h>
#include <time.h>

int main(){
    clock_t a, b, t;
    int i,j,k;
    a = clock();

    for (i=0;i<1000000;i++){
        printf("%d", i);
    }
    for (j=0;j<1000000;j++){
        printf("%d", j);
    }
    for (k=0;k<1000000;k++){
        printf("%d", k);
    }

    b = clock();
    t = (double)a-b;
    printf("Delta = %f", t);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int *test(){
    int *teste = (int *)malloc(sizeof(int));
    return teste;
}

int main(){
    //free();
    int *d = test();
    return 0;
}
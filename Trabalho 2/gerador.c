#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void imprime_rajadas(char *rajada, int numCartas){
    for (int i = 0;i < 2*numCartas; i++){
        printf("%s %d\n", rajada, 1+(rand()%numCartas));
    }
}

int main(){
    char rajada[9];
    int numCartas;

    srand(time(NULL));

    if (scanf("%s %d", rajada, &numCartas) == 2){
        printf("BARALHO %d\n", numCartas);

        if (strcmp(rajada,"SOBE") == 0){
            imprime_rajadas(rajada,numCartas);
        }
        else if (strcmp(rajada,"CARTA") == 0){
            imprime_rajadas(rajada,numCartas);
        }
        else if (strcmp(rajada,"POSICAO") == 0){
            imprime_rajadas(rajada,numCartas);
        }
        else if (strcmp(rajada,"CORTA") == 0){
            for (int i = 0;i < 2*numCartas; i++){
                int coin = rand()%2;
                if (coin == 0){
                    printf("%s %d\n", rajada, 1+(rand()%numCartas));
                }
                else{
                    printf("VIRA\n");
                }
            }
        }
        else if (strcmp(rajada,"DESFAZ") == 0){
            for (int i = 0; i < numCartas; i++){
                int dice = rand()%3;
                if (dice == 0){
                    //CORTA x
                    printf("%s %d\n", "CORTA", 1+(rand()%numCartas));
                }
                else if (dice == 1){
                    //VIRA
                    printf("%s\n", "VIRA");
                }
                else{
                    //SOBE x
                    printf("%s %d\n", "SOBE", 1+(rand()%numCartas));
                }
                printf("DESFAZ\n");
            }
            /*
            pro jogo :3
            for (int i = 0; i < numCartas; i++){
                printf("DESFAZ\n");
            }*/
        }
        //printf("MOSTRA\n");
        printf("FIM\n");
    }
    else{
        fprintf(stderr,"ERRO AO LER RAJADA\n");
    }

    return 0;
}
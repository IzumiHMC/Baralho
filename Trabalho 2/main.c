#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "deck.h"
#include "historico.h"

int main(){

    char comando[30];
    scanf("%s", comando);

    Baralho *baralho = NULL;
    //Se eu digito FIM
    while(strcmp(comando, "FIM" ) != 0){
        if(strcmp(comando, "BARALHO" ) == 0){
            int numero_cartas;
            scanf("%d", &numero_cartas);
            baralho_apagar(baralho);
            baralho = criar_baralho(numero_cartas);
        }  
        else if(strcmp(comando, "CORTA") == 0){
            int x;
            scanf("%d", &x);
            CORTA(baralho, x, TRUE);
        }
        else if(strcmp(comando, "SOBE") == 0){
            int x;
            scanf("%d", &x);
            SOBE(baralho, x, TRUE);
        }
        else if(strcmp(comando, "VIRA") == 0){
            VIRA(baralho, TRUE);
        }
        else if(strcmp(comando, "VIRATOPO") == 0){
            int k;
            scanf("%d", &k);
            VIRATOPO(baralho, k, TRUE);
        }
        else if(strcmp(comando, "DESFAZ") == 0){
            DESFAZ(baralho);
        }
        else if(strcmp(comando, "CARTA") == 0){
            int p;
            scanf("%d", &p);
            int carta;
            carta = CARTA(baralho, p);
            printf("%d\n", carta);
        }
        else if(strcmp(comando, "POSICAO") == 0){
            int x;
            scanf("%d", &x);
            int posicao;
            posicao = POSICAO(baralho, x);
            printf("%d\n", posicao);
        }
        else if(strcmp(comando, "MOSTRA") == 0){
            MOSTRA(baralho);
        }
        scanf("%s", comando);
    }
    baralho_apagar(baralho);
}
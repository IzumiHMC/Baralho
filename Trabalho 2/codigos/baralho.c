#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baralho.h"
#include "relatorio.h"


struct baralho{
    CARTA *inicio;
    int tam;
};

struct carta{
    CARTA *proximo;
    int num;
};

//eh so uma struct q guarda os ponteiros do baralho e relatorio
//ela tbm existe em main.c
struct instance{
    BARALHO *baralho;
    RELATORIO *relatorio;
};

INSTANCE criar_baralho(BARALHO *baralho, RELATORIO *relatorio, int n){
    apagar_baralho(baralho);
    apagar_relatorio(relatorio);

    INSTANCE instance = {NULL, NULL};
    
    BARALHO *prox_baralho = (BARALHO *)malloc(sizeof(BARALHO));
    prox_baralho->inicio = NULL;
    prox_baralho->tam = 0;
    
    for (int i = n; i >= 1; i--){
        BarPUSH(prox_baralho,i);
    }
    
    instance.baralho = prox_baralho;
    instance.relatorio = criar_relatorio();

    return instance;
}

boolean BarPUSH(BARALHO *baralho, int x){
    if (baralho != NULL){
        CARTA *carta = (CARTA *)malloc(sizeof(CARTA));
        carta->num = x;
        if (baralho->inicio == NULL){
            baralho->inicio = carta;
            carta->proximo = NULL;
        }
        else{
            carta->proximo = baralho->inicio;
            baralho->inicio = carta;
        }
        baralho->tam++;
        return TRUE;
    }
    return FALSE;
}

int BarPOP(BARALHO *baralho){
    if (baralho != NULL && baralho->inicio != NULL){
        int x;
        x = baralho->inicio->num;
        if (baralho->inicio->proximo == NULL){
            free(baralho->inicio);
            baralho->inicio = NULL;
        }
        else{
            CARTA *aux = baralho->inicio->proximo;
            baralho->inicio->proximo = NULL;
            free(baralho->inicio);
            baralho->inicio = aux;
        }

        baralho->tam--;
        return x;
    }
    return FALSE;
}

//adiciona ao relatorio
boolean CORTA(BARALHO *baralho, RELATORIO *relatorio, int x){
    if (baralho != NULL && relatorio != NULL){

        //code

        PUSH(relatorio,criar_operacao("CORTA",x));
        return TRUE;
    }
    return FALSE;
}

//adiciona ao relatorio
boolean SOBE(BARALHO *baralho, RELATORIO *relatorio, int x){
    if (baralho != NULL && relatorio != NULL){

        //code

        PUSH(relatorio,criar_operacao("SOBE",x));
        return TRUE;
    }
    return FALSE;
}

//adiciona ao relatorio
boolean VIRA(BARALHO *baralho, RELATORIO *relatorio){
    if (baralho != NULL && relatorio != NULL){

        //code

        PUSH(relatorio,criar_operacao("VIRA",-727));
        return TRUE;
    }
    return FALSE;
}

//adiciona ao relatorio
boolean VIRATOPO(BARALHO *baralho, RELATORIO *relatorio, int k){
    if (baralho != NULL && relatorio != NULL){

        //code

        PUSH(relatorio,criar_operacao("VIRATOPO",k));
        return TRUE;
    }
    return FALSE;
}

boolean DESFAZ(BARALHO *baralho, RELATORIO *relatorio){
    if (baralho != NULL && relatorio != NULL){
        if (strcmp(comando_operacao(relatorio),"CORTA") == 0){
            int x = k_operacao(relatorio);

            //code

        }
        else if (strcmp(comando_operacao(relatorio),"SOBE") == 0){
            int x = k_operacao(relatorio);

            //code

        }
        else if (strcmp(comando_operacao(relatorio),"VIRA") == 0){

            //code

        }
        else if (strcmp(comando_operacao(relatorio),"VIRATOPO") == 0){
            int k = k_operacao(relatorio);

            //code

        }

        return TRUE;
    }
    return FALSE;
}

int pegar_carta(BARALHO *baralho, int p){
    if (baralho != NULL){

        //code

    }
    return FALSE;

}

int POSICAO(BARALHO *baralho, int x){
    if (baralho != NULL){

        //code

    }
    return FALSE;
}

boolean MOSTRA(BARALHO *baralho){
    if (baralho != NULL){
        CARTA *aux = baralho->inicio;
        while (aux != NULL){
            printf("%d ",aux->num);
            aux = aux->proximo;
        }
        printf("\n");

        return TRUE;
    }
    return FALSE;
}

boolean apagar_baralho(BARALHO *baralho){
    if (baralho != NULL){
        while (baralho->inicio != NULL){
            BarPOP(baralho);
        }
        free(baralho);

        return TRUE;
    }
    return FALSE;
}

boolean FIM(BARALHO *baralho, RELATORIO *relatorio){
    if (baralho != NULL && relatorio != NULL){
        apagar_baralho(baralho);
        apagar_relatorio(relatorio);

        return TRUE;
    }
    return FALSE;
}

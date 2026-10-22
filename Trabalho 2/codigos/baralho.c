#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baralho.h"
#include "relatorio.h"


struct baralho{

};

struct carta{

};

//eh so uma struct q guarda os ponteiros do baralho e relatorio
//ela tbm existe em main.c
struct instance{
    BARALHO *baralho;
    RELATORIO *relatorio;
};

INSTANCE *criar_baralho(BARALHO *baralho, RELATORIO *relatorio){
    apagar_baralho(baralho);
    apagar_relatorio(relatorio);

    INSTANCE *instance;

    //alocar dinamicamente o baralho
    
    instance->relatorio = criar_relatorio();

    return instance;
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

        PUSH(relatorio,criar_operacao("VIRA",NULL));
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

        //code

    }
    return FALSE;
}

boolean apagar_baralho(BARALHO *baralho){
    if (baralho != NULL){

        //??

        return TRUE;
    }
    return FALSE;
}

boolean FIM(BARALHO *baralho, RELATORIO *relatorio){
    if (baralho != NULL && relatorio != NULL){

        //code


        return TRUE;
    }
    return FALSE;
}

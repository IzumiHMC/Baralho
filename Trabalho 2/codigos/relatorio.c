#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relatorio.h"


//implementacao de pilha sequencial estatica

RELATORIO *criar_relatorio(){
    RELATORIO *relatorio = (RELATORIO *)malloc(sizeof(RELATORIO));

    relatorio->inicio = 0;

    return relatorio;
}

//relatorio->inicio corresponde ao index depois do index da ultima operacao
//o "else" no fim eh a operacao normal de push.
//O "if == 100" vai usar uma pilha auxiliar pra tirar o primeiro elemento.
//Quando vc coloca todos os elementos de uma pilha em outra, o ultimo elemento
//se torna o primeiro e vice-versa
boolean PUSH(RELATORIO *relatorio, OPERACAO operacao){
    if (relatorio != NULL){
        if (relatorio->inicio == 100){
            RELATORIO *aux = (RELATORIO *)malloc(sizeof(RELATORIO));
            for (int i = 0; i < relatorio->inicio; i++){
                PUSH(aux,POP(relatorio));
            }
            POP(aux);
            for (int i = 0; i < relatorio->inicio; i++){
                PUSH(relatorio,POP(aux));
            }
            relatorio->comandos[relatorio->inicio-1].comando = operacao.comando;
            relatorio->comandos[relatorio->inicio-1].k = operacao.k;
            free(aux);
        }
        else{
            relatorio->comandos[relatorio->inicio].comando = operacao.comando;
            relatorio->comandos[relatorio->inicio].k = operacao.k;
            relatorio->inicio++;
        }
        
        return TRUE;
    }

    return FALSE;
}

OPERACAO POP(RELATORIO *relatorio){
    if (relatorio != NULL && relatorio->inicio != 0){
        relatorio->inicio--;
        return relatorio->comandos[relatorio->inicio+1];
    }
    return criar_operacao(NULL, FALSE);
}

//acho q depois vou apagar essa funcao, eh so pra debug
boolean mostrar_relatorio(RELATORIO *relatorio){
    if (relatorio != NULL && relatorio->inicio != 0){
        for (int i = 0; i < relatorio->inicio; i++){
            printf("%s %d | ", relatorio->comandos[i].comando, relatorio->comandos[i].k);
        }
        return TRUE;
    }
    return FALSE;
}

boolean apagar_relatorio(RELATORIO *relatorio){
    if (relatorio != NULL){
        free(relatorio);
        return TRUE;
    }
    return FALSE;
}

OPERACAO criar_operacao(char *comando, int k){
    OPERACAO operacao;
    operacao.comando = comando;
    operacao.k = k;

    return operacao;
}

char *comando_operacao(RELATORIO *relatorio){
    if (relatorio != NULL && relatorio->inicio != 0){
        return relatorio->comandos[relatorio->inicio-1].comando;
    }
    return NULL;
}

int k_operacao(RELATORIO *relatorio){
    if (relatorio != NULL && relatorio->inicio != 0){
        return relatorio->comandos[relatorio->inicio-1].k;
    }
    return FALSE;
}

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
//tempo  -  O(2*100) ou O(1)
boolean PUSH(RELATORIO *relatorio, OPERACAO operacao){
    if (relatorio != NULL){
        if (relatorio->inicio == FIMRELATORIO){
            RELATORIO aux = {0};
            for (int i = 0; i < FIMRELATORIO; i++){
                PUSH(&aux,POP(relatorio));
            }
            POP(&aux);
            for (int i = 0; i < FIMRELATORIO; i++){
                PUSH(relatorio,POP(&aux));
            }
            relatorio->comandos[relatorio->inicio-1].comando = operacao.comando;
            relatorio->comandos[relatorio->inicio-1].k = operacao.k;
            relatorio->comandos[relatorio->inicio-1].pos = operacao.pos;
        }
        else{
            relatorio->comandos[relatorio->inicio].comando = operacao.comando;
            relatorio->comandos[relatorio->inicio].k = operacao.k;
            relatorio->comandos[relatorio->inicio].pos = operacao.pos;
            relatorio->inicio++;
        }
        
        return TRUE;
    }
    fprintf(
        stderr,
        "ERRO AO DAR PUSH: relatorio null\n"
    );
    return FALSE;
}

//tempo  -  O(1)
OPERACAO POP(RELATORIO *relatorio){
    if (relatorio != NULL && relatorio->inicio != 0){
        relatorio->inicio--;
        return relatorio->comandos[relatorio->inicio+1];
    }
    return criar_operacao(NULL, -727, -727);
}

//acho q depois vou apagar essa funcao, eh so pra debug
boolean mostrar_relatorio(RELATORIO *relatorio){
    if (relatorio != NULL && relatorio->inicio != 0){
        for (int i = 0; i < relatorio->inicio; i++){
            if (strcmp(relatorio->comandos[i].comando,"VIRA") == 0){
                printf("%s | ",relatorio->comandos[i].comando);
            }
            else{
                printf("%s %d | ", relatorio->comandos[i].comando, relatorio->comandos[i].k);
            }
        }
        printf("\n");
        printf("inicio: %d\n", relatorio->inicio);
        return TRUE;
    }
    printf("NENHUMA OPERACAO NO RELATORIO\n");
    return FALSE;
}

boolean apagar_relatorio(RELATORIO *relatorio){
    if (relatorio != NULL){
        free(relatorio);
        return TRUE;
    }
    fprintf(
        stderr,
        "ERRO AO APAGAR RELATORIO: relatorio null\n"
    );
    return FALSE;
}

OPERACAO criar_operacao(char *comando, int k, int pos){
    OPERACAO operacao;
    operacao.comando = comando;
    operacao.k = k;
    operacao.pos = pos;

    return operacao;
}

char *comando_operacao(RELATORIO *relatorio){
    if (relatorio != NULL && relatorio->inicio != 0){
        return relatorio->comandos[relatorio->inicio-1].comando;
    }
    fprintf(
        stderr,
        "ERRO AO RETORNAR comando\nPonteiro relatorio: %p\nrelatorio->inicio == 0?\n",
        relatorio
    );
    return NULL;
}

int k_operacao(RELATORIO *relatorio){
    if (relatorio != NULL && relatorio->inicio != 0){
        return relatorio->comandos[relatorio->inicio-1].k;
    }
    fprintf(
        stderr,
        "ERRO AO RETORNAR k\nPonteiro relatorio: %p\nrelatorio->inicio == 0?\n",
        relatorio
    );
    return FALSE;
}

int pos_operacao(RELATORIO *relatorio){
    if (relatorio != NULL && relatorio->inicio != 0){
        return relatorio->comandos[relatorio->inicio-1].pos;
    }
    fprintf(
        stderr,
        "ERRO AO RETORNAR pos\nPonteiro relatorio: %p\nrelatorio->inicio == 0?\n",
        relatorio
    );
    return FALSE;
}

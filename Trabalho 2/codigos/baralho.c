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
    prox_baralho->tam = n;
    
    for (int i = n; i >= 1; i--){
        BarPUSH(prox_baralho,i);
    }
    
    instance.baralho = prox_baralho;
    instance.relatorio = criar_relatorio();

    return instance;
}

//tempo  -  O(1)
//memoria  -  ?
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
        return TRUE;
    }
    return FALSE;
}

//tempo  -  O(1)
//memoria  -  ?
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
        return x;
    }
    return FALSE;
}

//adiciona ao relatorio

//mal feito?
boolean CORTA(BARALHO *baralho, RELATORIO *relatorio, int x, boolean desfaz){
    if (baralho != NULL && relatorio != NULL){
        CARTA *aux = baralho->inicio;
        BARALHO baralhoBaixo = {NULL, 0};
        BARALHO baralhoCima = {NULL, 0};

        int pos = POSICAO(baralho,x,TRUE);

        while (aux->num != x){
            BarPUSH(&baralhoBaixo,BarPOP(baralho));
            aux = baralho->inicio;
            if (aux == NULL){
                return FALSE;
            }
        }

        aux = baralho->inicio;

        while (aux != NULL){
            BarPUSH(&baralhoCima,BarPOP(baralho));
            aux = baralho->inicio;
        }

        aux = baralhoBaixo.inicio;

        while (aux != NULL){
            BarPUSH(baralho,BarPOP(&baralhoBaixo));
            aux = baralhoBaixo.inicio;
        }

        aux = baralhoCima.inicio;

        while (aux != NULL){
            BarPUSH(baralho,BarPOP(&baralhoCima));
            aux = baralhoCima.inicio;
        }

        if (desfaz == FALSE){
            PUSH(relatorio,criar_operacao("CORTA",x, pos));
        }
        else if (desfaz == TRUE){
            POP(relatorio);
        }
        return TRUE;
    }
    return FALSE;
}

//adiciona ao relatorio
boolean SOBE(BARALHO *baralho, RELATORIO *relatorio, int x, boolean desfaz){
    if (baralho != NULL && relatorio != NULL){
        CARTA *aux = baralho->inicio;
        BARALHO baralhoAteX = {NULL, 0};

        int pos = POSICAO(baralho,x,TRUE);

        while (aux->num != x){
            BarPUSH(&baralhoAteX,BarPOP(baralho));
            aux = baralho->inicio;
            if (aux == NULL){
                return FALSE;
            }
        }

        BarPOP(baralho);
        aux = baralhoAteX.inicio;

        while (aux != NULL){
            BarPUSH(baralho,BarPOP(&baralhoAteX));
            aux = baralhoAteX.inicio;
        }
        BarPUSH(baralho,x);

        if (desfaz == FALSE){
            PUSH(relatorio,criar_operacao("SOBE",x,pos));
        }
        return TRUE;
    }
    return FALSE;
}

//adiciona ao relatorio
boolean VIRA(BARALHO *baralho, RELATORIO *relatorio, boolean desfaz){
    if (baralho != NULL && relatorio != NULL){
        BARALHO baralhoVirado = {NULL, 0};

        while (baralho->inicio != NULL){
            BarPUSH(&baralhoVirado,BarPOP(baralho));
        }
        baralho->inicio = baralhoVirado.inicio;
        baralhoVirado.inicio = NULL;

        if (desfaz == FALSE){
            PUSH(relatorio,criar_operacao("VIRA",-727,-727));
        }
        else if (desfaz == TRUE){
            POP(relatorio);
        }
        return TRUE;
    }
    return FALSE;
}

//adiciona ao relatorio
boolean VIRATOPO(BARALHO *baralho, RELATORIO *relatorio, int k, boolean desfaz){
    if (baralho != NULL && relatorio != NULL && baralho->tam >= k){
        BARALHO aux = {NULL, 0};
        BARALHO aux2 = {NULL, 0};

        for (int j = 1; j <= k; j++){
            BarPUSH(&aux,BarPOP(baralho));
        }

        for (int j = 1; j <= k; j++){
            BarPUSH(&aux2,BarPOP(&aux));
        }

        for (int j = 1; j <= k; j++){
            BarPUSH(baralho,BarPOP(&aux2));
        }

        if (desfaz == FALSE){
            PUSH(relatorio,criar_operacao("VIRATOPO",k,-727));
        }
        else if (desfaz == TRUE){
            POP(relatorio);
        }
        return TRUE;
    }
    return FALSE;
}

boolean DESFAZ(BARALHO *baralho, RELATORIO *relatorio){
    if (baralho != NULL && relatorio != NULL && relatorio->inicio != 0){
        if (strcmp(comando_operacao(relatorio),"CORTA") == 0){
            int pos = pos_operacao(relatorio);
            CORTA(baralho,relatorio,pegar_carta(baralho,baralho->tam-pos+2,TRUE),TRUE);
        }
        else if (strcmp(comando_operacao(relatorio),"SOBE") == 0){
            int pos = pos_operacao(relatorio);
            for (int i = 1; i < pos; i++){
                SOBE(baralho,relatorio,pegar_carta(baralho,pos,TRUE),TRUE);
            }
            POP(relatorio);
        }
        else if (strcmp(comando_operacao(relatorio),"VIRA") == 0){
            VIRA(baralho,relatorio,TRUE);
        }
        else if (strcmp(comando_operacao(relatorio),"VIRATOPO") == 0){
            int k = k_operacao(relatorio);
            VIRATOPO(baralho,relatorio,k,TRUE);
        }

        return TRUE;
    }
    return FALSE;
}

//operacao "CARTA p"
int pegar_carta(BARALHO *baralho, int p,boolean desfaz){
    if (baralho != NULL && p > 0 && baralho->tam >= p){
        CARTA *aux = baralho->inicio;
        for (int i = 1; i < p; i++){
            aux = aux->proximo;
        }

        if (desfaz == FALSE){
            printf("%d\n", aux->num);
        }

        return aux->num;
    }
    printf("errooo\n");
    printf("%d\n", baralho->tam);
    return FALSE;

}

int POSICAO(BARALHO *baralho, int x, boolean desfaz){
    if (baralho != NULL && x > 0 && baralho->tam >= x){
        int pos = 1;
        CARTA *aux = baralho->inicio;

        while (aux->num != x){
            aux = aux->proximo;
            pos++;
        }

        if (desfaz == FALSE){
            printf("%d\n", pos);
        }
        
        return pos;
    }
    printf("errooo\n");
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

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
    fprintf(
        stderr,
        "ERRO AO FAZER BarPUSH: baralho null\n"
    );
    return FALSE;
}

//tempo  -  O(1)
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
    fprintf(
        stderr,
        "ERRO AO FAZER BarPOP\nPonteiro baralho: %p\nbaralho->inicio == NULL?\n",
        baralho
    );
    return FALSE;
}

//adiciona ao relatorio
//tempo  -  O(2n)
boolean CORTA(BARALHO *baralho, RELATORIO *relatorio, int x, boolean desfaz){
    if (baralho != NULL && relatorio != NULL && x > 0 && baralho->tam >= x){
        CARTA *aux = baralho->inicio;
        BARALHO baralhoBaixo = {NULL, 0};
        BARALHO baralhoCima = {NULL, 0};

        int pos = POSICAO(baralho,x, TRUE);

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
        return TRUE;
    }
    fprintf(
        stderr,
        "ERRO AO FAZER OPERACAO CORTA\nPonteiro baralho: %p\nPonteiro relatorio: %p\nx: %d\nbaralho->tam >= x?\n",
        baralho, relatorio, x
    );
    return FALSE;
}

//adiciona ao relatorio
//tempo  -  O(2pos(x)) -> O(2n)
boolean SOBE(BARALHO *baralho, RELATORIO *relatorio, int x, boolean desfaz){
    if (baralho != NULL && relatorio != NULL && x > 0 && baralho->tam >= x){
        CARTA *aux = baralho->inicio;
        BARALHO baralhoAteX = {NULL, 0};

        int pos = POSICAO(baralho,x, TRUE);

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
    fprintf(
        stderr,
        "ERRO AO FAZER OPERACAO SOBE\nPonteiro baralho: %p\nPonteiro relatorio: %p\nx: %d\nbaralho->tam >= x?\n",
        baralho, relatorio, x
    );
    return FALSE;
}

//adiciona ao relatorio
//tempo  -  O(n)
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
        return TRUE;
    }
    fprintf(
        stderr,
        "ERRO AO FAZER OPERACAO VIRA\nPonteiro baralho: %p\nPonteiro relatorio: %p\n",
        baralho, relatorio
    );
    return FALSE;
}

//adiciona ao relatorio
//tempo  -  O(3k) -> O(3n) -> O(n)
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
        return TRUE;
    }
    fprintf(
        stderr,
        "ERRO AO FAZER OPERACAO VIRATOPO\nPonteiro baralho: %p\nPonteiro relatorio: %p\nbaralho->tam >= k?\n",
        baralho, relatorio
    );
    return FALSE;
}

boolean DESFAZ(BARALHO *baralho, RELATORIO *relatorio){
    if (baralho != NULL && relatorio != NULL && relatorio->inicio != 0){
        if (strcmp(comando_operacao(relatorio),"CORTA") == 0){
            int pos = pos_operacao(relatorio);
            //tempo  -  O(2n + (n-pos+2)%n) -> O(n)
            CORTA(baralho,relatorio,pegar_carta(baralho,1+(baralho->tam-pos+1)%baralho->tam, TRUE),TRUE);
            POP(relatorio);
        }
        else if (strcmp(comando_operacao(relatorio),"SOBE") == 0){
            //tempo  -  O(n)
            int pos = pos_operacao(relatorio);
            if (pos != 1){
                //tempo  -  O(2n + pos+1 + 3(n-1) + n) -> O(n)
                CORTA(baralho,relatorio,pegar_carta(baralho,1+(pos)%baralho->tam, TRUE),TRUE);
                VIRATOPO(baralho,relatorio,baralho->tam-pos,TRUE);
                VIRA(baralho,relatorio,TRUE);
                VIRATOPO(baralho,relatorio,pos-1,TRUE);
            }
            POP(relatorio);
        }
        else if (strcmp(comando_operacao(relatorio),"VIRA") == 0){
            //tempo  -  O(n) 
            VIRA(baralho,relatorio,TRUE);
            POP(relatorio);
        }
        else if (strcmp(comando_operacao(relatorio),"VIRATOPO") == 0){
            //tempo  -  O(3k) -> se k for n: O(3n)  -> O(n)
            int k = k_operacao(relatorio);
            VIRATOPO(baralho,relatorio,k,TRUE);
            POP(relatorio);
        }

        return TRUE;
    }
    fprintf(
        stderr,
        "ERRO AO FAZER OPERACAO DESFAZ\nPonteiro baralho: %p\nPonteiro relatorio: %p\nrelatorio->inicio == 0?\n",
        baralho, relatorio
    );
    return FALSE;
}

//operacao "CARTA p"
//tempo  -  O(p) -> O(n)
int pegar_carta(BARALHO *baralho, int p, boolean desfaz){
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
    fprintf(
        stderr,
        "ERRO AO PEGAR A CARTA NA POSICAO p\nPonteiro baralho: %p\np: %d\nbaralho->tam >= p?\n",
        baralho, p
    );
    return FALSE;
}

//tempo  -  O(pos(x)) -> O(n)
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
    fprintf(
        stderr,
        "ERRO AO PEGAR A POSICAO DA CARTA x\nPonteiro baralho: %p\nx: %d\nbaralho->tam >= x?\n",
        baralho, x
    );
    return FALSE;
}

//tempo  -  O(n)
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
    fprintf(
        stderr,
        "ERRO AO FAZER OPERACAO MOSTRA: baralho null\n"
    );  
    return FALSE;
}

//tempo  -  O(n)
boolean apagar_baralho(BARALHO *baralho){
    if (baralho != NULL){
        while (baralho->inicio != NULL){
            BarPOP(baralho);
        }
        free(baralho);

        return TRUE;
    }
    /*
    fprintf(
        stderr,
        "ERRO AO APAGAR BARALHO: baralho null\n"
    );  
    */
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

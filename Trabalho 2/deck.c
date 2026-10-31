#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deck.h"
#include "historico.h"

struct baralho{
    Carta *topo;
    Carta *fundo;
    int tamanho_baralho;
    Historico *historico;
};

struct carta{
    int carta;
    Carta *anterior;
    Carta *proximo;
};

Baralho *criar_baralho(int numero_cartas){
    if(numero_cartas > TAM_MAX || numero_cartas <= 0){
        return NULL;
    }
    
    Baralho *baralho = malloc(sizeof(Baralho));
    if(baralho == NULL){
        return NULL;
    }
    else if(baralho != NULL){
        baralho->topo = NULL;
        baralho->fundo = NULL;
        baralho->tamanho_baralho = 0;
        baralho->historico = criar_historico();
        if(baralho->historico == NULL){
            free(baralho); //Posso dar free pq não tem nenhuma carta
            return NULL;
        }   
    }
    for(int i = 1; i <= numero_cartas; i++){
    //Alocando carta por carta (no)
      Carta *carta = malloc(sizeof(Carta));
        if(carta != NULL){
            //verifico se o baralho->topo != NULL, se for, eu insiro 
            //no baralho->topo->proximo
            //Aqui o baralho tem uma carta só
            carta->proximo = NULL;
            carta->anterior = NULL;
            carta->carta = i;
            if(baralho->fundo == NULL){
                baralho->fundo = carta;
                baralho->topo = baralho->fundo;
            }
            else{
                carta->anterior = baralho->fundo;
                baralho->fundo->proximo = carta;
                baralho->fundo = carta;
            }
        }
        else{
            baralho_apagar(baralho);
            return NULL;
        }
        baralho->tamanho_baralho++;
    }
    return baralho;
 
}
 
boolean CORTA(Baralho *baralho, int numero_carta, boolean registrar){
    
    if(baralho == NULL || baralho->tamanho_baralho == 0){
        return FALSE;
    }
    else{
        int topo = baralho->topo->carta;         

        // acha o nó de x
        Carta *no_numero_carta = baralho->topo;
        while (no_numero_carta != NULL && no_numero_carta->carta != numero_carta) {
            no_numero_carta = no_numero_carta->proximo;
        }
        if (no_numero_carta == NULL) {
            return FALSE;  
        }
          
        // se x já está no topo 
        if (no_numero_carta != baralho->topo) {
            Carta *anterior = no_numero_carta->anterior;       

            // fundo antigo -> topo antigo
            baralho->fundo->proximo = baralho->topo;
            baralho->topo->anterior = baralho->fundo;

            
            anterior->proximo = NULL;
            no_numero_carta->anterior = NULL;

            baralho->topo = no_numero_carta;
            baralho->fundo = anterior;
    }
        if (registrar) {
            return INSERIR_no_HISTORICO(baralho->historico, CORTA_comando, topo, 0);
        }
        return TRUE;
    }
}

boolean VIRA(Baralho *baralho, boolean registrar){
    if(baralho == NULL){
        return FALSE;
    }
    else{
        //O próximo vira o anterior e o anterior vira o próximo
        Carta *carta_atual = baralho->topo;
        for(int i = 0; i < baralho->tamanho_baralho; i++){
            Carta *carta_proxima = carta_atual->proximo;
            //Inverte o carta_proximo pelo anterior de atual
            carta_atual->proximo = carta_atual->anterior;
            carta_atual->anterior = carta_proxima;
            carta_atual = carta_proxima;

        }
        
        //topo vira fundo e fundo vira topo
        Carta *topo = baralho->topo;
        baralho->topo = baralho->fundo;
        baralho->fundo = topo;
        if (registrar){
            INSERIR_no_HISTORICO(baralho->historico, VIRA_comando,0, 0);
        }
        return TRUE;

       
    }
} 

boolean VIRATOPO(Baralho *baralho, int k, boolean registrar){
   if(baralho == NULL || k < 1 || k > baralho->tamanho_baralho){
    return FALSE;
   }
   else{
        if (k > 1) {
            Carta *primeiro = baralho->topo;    
            Carta *ultimo = primeiro;             
            for (int i = 1; i < k; i++) {
                ultimo = ultimo->proximo;
            }
            
            Carta *depois = ultimo->proximo;      

            Carta *atual = primeiro;
            for (int i = 0; i < k; i++) {
                Carta *prox = atual->proximo;
                atual->proximo = atual->anterior;
                atual->anterior = prox;
                atual = prox;
            }

            ultimo->anterior = NULL;
            baralho->topo = ultimo;

            primeiro->proximo = depois;
            if (depois != NULL){
                depois->anterior = primeiro;
            } 
            else {
                baralho->fundo = primeiro;
            }          
        }
        if (registrar){
            INSERIR_no_HISTORICO(baralho->historico, VIRATOPO_comando,0, k);
        }
        return TRUE;
   }
}

boolean SOBE(Baralho *baralho, int numero_carta, boolean registrar) {

    if (baralho == NULL || baralho->tamanho_baralho == 0) {
        return FALSE;
    }

    Carta *atual = baralho->topo;
    int posicao = 1;

    while (atual != NULL && atual->carta != numero_carta) {
        atual = atual->proximo;
        posicao++;
    }

    if (atual == NULL) {
        return FALSE;
    }

    if (registrar) {
        if (!INSERIR_no_HISTORICO(baralho->historico,SOBE_comando,numero_carta,posicao)) {
            return FALSE;
        }
    }

    if (atual == baralho->topo) {
        return TRUE;
    }

    atual->anterior->proximo = atual->proximo;

    if (atual->proximo != NULL) {
        atual->proximo->anterior = atual->anterior;
    }
    else {
        // A carta removida era o fundo.
        baralho->fundo = atual->anterior;
    }

    // Inserir a carta no topo.

    atual->anterior = NULL;
    atual->proximo = baralho->topo;

    baralho->topo->anterior = atual;
    baralho->topo = atual;

    return TRUE;
}

int CARTA(Baralho *baralho, int posicao){
    //A Carta que está na posicao p não pode ser maior que o baralho
    if(baralho == NULL || posicao < 1 || posicao > baralho -> tamanho_baralho){
        return -1;
    }

    else{
        //começo no topo e percorro até a posicao
        Carta *carta_posicao = baralho -> topo;
        for(int i = 0; i < posicao - 1; i++){
            carta_posicao = carta_posicao->proximo;
        }
        return carta_posicao->carta;

    }
}

boolean reposicionar(Baralho *baralho, int numero_carta, int posicao) {

    if (baralho == NULL || posicao < 1 ||
        posicao > baralho->tamanho_baralho) {
        return FALSE;
    }

    // Encontrar a carta
    Carta *atual = baralho->topo;

    while (atual != NULL && atual->carta != numero_carta) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        return FALSE;
    }

    // retirar a carta da posição atual
    if (atual->anterior != NULL) {
        atual->anterior->proximo = atual->proximo;
    }
    else {
        baralho->topo = atual->proximo;
    }

    if (atual->proximo != NULL) {
        atual->proximo->anterior = atual->anterior;
    }
    else {
        baralho->fundo = atual->anterior;
    }

    // Inserir no topo, se a posição for 1
    if (posicao == 1) {

        atual->anterior = NULL;
        atual->proximo = baralho->topo;

        if (baralho->topo != NULL) {
            baralho->topo->anterior = atual;
        }
        else {
            baralho->fundo = atual;
        }

        baralho->topo = atual;
    }

    // Inserir em qualquer outra posição
    else {

        Carta *anterior = baralho->topo;

        for (int i = 1; i < posicao - 1; i++) {
            anterior = anterior->proximo;
        }

        atual->proximo = anterior->proximo;
        atual->anterior = anterior;

        if (anterior->proximo != NULL) {
            anterior->proximo->anterior = atual;
        }
        else {
            baralho->fundo = atual;
        }

        anterior->proximo = atual;
    }

    return TRUE;
}

boolean DESFAZ(Baralho *baralho){
    if(baralho == NULL){
        return FALSE;
    }

    else{
        int tipo;
        int rotulo;
        int numero_operacao;

        // Retirar a operação mais recente do histórico
        if (!REMOVER_ULTIMO( baralho->historico, &tipo, &rotulo, &numero_operacao)) {
            return FALSE;
        }

        // AQui eu executo a função inversa a função chamada lá no main
        switch (tipo) {

            case CORTA_comando:
                return CORTA(baralho, rotulo, FALSE);
            //Para o SOBE, precisamos uma função auxiliar
            case SOBE_comando:
                return reposicionar(baralho, rotulo, numero_operacao);

            case VIRA_comando:
                return VIRA(baralho, FALSE);

            case VIRATOPO_comando:
                return VIRATOPO(baralho, numero_operacao, FALSE);

            default:
                return FALSE;
        }
    }

}

void MOSTRA(Baralho *baralho){
    if(baralho == NULL){
        return;
    }
    else{
        //COmeço no topo e vou até o tamanho do baralho
        Carta *carta = baralho -> topo;
        for(int i = 0; i <baralho->tamanho_baralho; i++){
            printf("%d ", carta->carta);
            carta = carta->proximo;
        }
        //Esse espaço aqui é para formatar igual tava no pdf
        printf("\n");

    }
}

int POSICAO(Baralho *baralho, int numero_carta) {
    if (baralho == NULL) {
        return 0;
    }

    //minha posição inicial é o 1 pq é o topo
    int pos = 1;
    //E minha carta inicial é o topo
    Carta *no = baralho->topo;

    while (no != NULL && no->carta != numero_carta) {
        no = no->proximo;
        pos++;
    }

    if (no == NULL) {
        return 0;   
    }

    return pos;
}


boolean baralho_apagar(Baralho *baralho){
    
    if(baralho == NULL){
        return FALSE;
    }


    else{
    //Variável auxiliar para percorrer a o baralho
    Carta *carta_atual = baralho -> topo;

    while(carta_atual != NULL){
        Carta *proxima_carta = carta_atual -> proximo;
        free(carta_atual);
        carta_atual = proxima_carta;

    }

    //Como o historico é alocado desaloca-lo e apagar o que tem dentro dele
    destruir_historico(&baralho->historico);
    free(baralho);
    return TRUE;
 }

}
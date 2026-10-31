#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historico.h"


//Implementaçao de deque duplamente encadeado

struct Registro{
    Registro *anterior;
    Registro *proximo;
    int numero_operacao; //p no sobe e o k no viratopo
    int rotulo; // rotulo se refere a carta
    int tipo; //aqui é o tipo da operação
};

struct Historico{
    Registro *inicio;
    Registro *fim;
    int tamanho_historico;
};

Historico *criar_historico(){
    Historico *historico = malloc(sizeof(Historico));
    if(historico != NULL){
        historico->inicio = NULL;
        historico -> fim = NULL;
        historico -> tamanho_historico = 0;
        return historico;
    }

    else{
        return NULL;
    }
}

boolean INSERIR_no_HISTORICO(Historico *historico, int tipo, int rotulo, int numero_operacao ){
    if(historico == NULL){
        return FALSE;
    }

    Registro *novo_registro = malloc(sizeof(Registro));
    if(novo_registro == NULL){
        return FALSE;
    }

    novo_registro -> tipo = tipo;
    novo_registro -> rotulo = rotulo;
    novo_registro ->numero_operacao = numero_operacao;
    novo_registro -> proximo = NULL;
    novo_registro -> anterior = historico -> fim;

    if(historico -> fim == NULL){
        historico -> inicio = novo_registro;
    }

    else{
        historico -> fim -> proximo = novo_registro;
    }

    historico -> fim = novo_registro;
    historico -> tamanho_historico++;
    //Aqui é a verificação de tamanho máximo, caso ultrapasse 100
    if(historico -> tamanho_historico > HISTORICO_TAM_MAX){
        Registro *registro_velho = historico->inicio;
        historico -> inicio = registro_velho ->proximo;
        historico -> inicio -> anterior = NULL;
        free(registro_velho);
        historico -> tamanho_historico --;
    }

    return TRUE;
}
//Essa função é um caso especial, aqui usamos ponteiros dentro de campos que 
//fora daqui não são ponteiros, isso acontece pq estamos tentandi modificar variáveis que
// foram declaradas fora da função e para acessar o conteúdo delas na heap usamos ponteiros

boolean REMOVER_ULTIMO(Historico *historico, int *tipo, int *rotulo, int *numero_operacao){
    
    //Se historico -> fim for NULL é pq a lista está vazia e não há nada a remover
    if (historico == NULL || historico->fim == NULL) {
        return FALSE;                       
    }


    Registro *ultimo = historico->fim;
    *tipo = ultimo->tipo;
    *rotulo = ultimo->rotulo;
    *numero_operacao = ultimo->numero_operacao;

    historico->fim = ultimo->anterior;
    if (historico->fim == NULL) {
        historico->inicio = NULL;           
    } 
    

    else {
        historico->fim->proximo = NULL;
    }

    free(ultimo);
    historico->tamanho_historico--;
    return TRUE;
}

void ESVAZIAR_HISTORICO(Historico *historico){
    if(historico == NULL){
        return;
    }

    else{
        //Começo no ínicio do deque e avanço até que meu atual seja NUll
        //Enquanto isso acontece eu dou um free no atual e avanço
        Registro *atual = historico->inicio;
        while (atual != NULL) {
            Registro *prox = atual->proximo;
            free(atual);
            atual = prox;
    }
    //Se o fim e o ínicio forem NULL é pq o histprico está vazio
    historico->inicio = NULL;
    historico->fim = NULL;
    historico->tamanho_historico = 0;
   }
}

void destruir_historico(Historico **historico){
    if(historico == NULL){
        return;
    }

    else{

    ESVAZIAR_HISTORICO(*historico); 
    //Dps de esvaziar o conteúdo, podemos dar um free nele
    //como historico é um ponteiro duplo precisamos do "*" aqui
    free(*historico); 
    //Isso aqui é se tem ponteiro pendurado                
    *historico = NULL;                
    }

}

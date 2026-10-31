//Ao criar um deque, é necessário inicializa-lo em NULL
//LEMBRE-SE QUE UM PARÂMETRO **head REQUER O ENDEREÇO (&) DE UM PONTEIRO *head

//Neste deque o "front" é o FINAL da lista e o "back" é o INÍCIO dela

#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

//Inserir no final
void push_front (int valor, node **head) {
    node *novo = malloc(sizeof(node));
    if (novo == NULL) {
        return;
    }

    novo->valor = valor;
    novo->prox = NULL;
    novo->ant = NULL;

    //Com esse if, tratamos o caso onde a lista está vazia
    if (*head == NULL) {
        *head = novo;
        return;
    }

    node *atual = *head;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    atual->prox = novo;
    novo->ant = atual;
}

//Inserir no início (REQUER PONTEIRO DUPLO)
void push_back (int valor, node **head) {
    node *novo = malloc(sizeof(node));
    if (novo == NULL) {
        return;
    }

    novo->valor = valor;
    novo->ant = NULL;
    novo->prox = *head;

    if (*head != NULL) {
        (*head)->ant = novo;
    }

    *head = novo;
}

//Remove um elemento do final do deque
void pop_front (node **head) {
    if (*head == NULL) {
        printf("Nao ha nada a ser removido!");
        return;
    }

    node *ultimo = *head;
    while (ultimo->prox != NULL) {
        ultimo = ultimo->prox;
    }

    //Se o último node não tem anterior, ele é o único e a lista fica vazia
    if (ultimo->ant == NULL) {
        *head = NULL;
    } else {
        ultimo->ant->prox = NULL;
    }

    free(ultimo);
}

//Remove um elemento do início do deque (REQUER PONTEIRO DUPLO)
void pop_back (node **head) {
    if (*head == NULL) {
        printf("Nao ha nada a ser removido!");
        return;
    }

    node *segundo = (*head)->prox;
    free(*head);
    *head = segundo;

    //Se havia só um node, agora a lista está vazia e não há ant para ajustar
    if (*head != NULL) {
        (*head)->ant = NULL;
    }
}

//Imprime todos os elementos do deque
void imprimeDeque (node *head) {
    if (head == NULL) {
        printf("Vazio.");
        return;
    }

    node *atual = head;

    while (atual != NULL) {
        printf("%d\n", atual->valor);
        atual = atual->prox;
    }
}

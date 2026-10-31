#ifndef DEQUE_H
#define DEQUE_H

typedef struct node {
    int valor;
    struct node *prox;
    struct node *ant;
} node;

typedef node *deque;

void push_front (int valor, node **head);
void push_back (int valor, node **head);
void pop_front (node **head);
void pop_back (node **head);
void imprimeDeque (node *head);

#endif

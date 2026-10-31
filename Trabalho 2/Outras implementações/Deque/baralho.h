#ifndef BARALHO_H
#define BARALHO_H

#include <stdbool.h>
#include "deque.h"

typedef deque baralho;

//Cada item do histórico guarda uma cópia inteira do baralho
typedef struct snapshot {
    baralho cartas;
    struct snapshot *prox;
} snapshot;

typedef snapshot *historico;

void novoBaralho (baralho *b, int qtde);
void liberaBaralho (baralho *b);
bool existeCarta (baralho b, int x);
void corta (baralho *b, int x);
void sobe (baralho *b, int x);
void vira (baralho *b);
void viraTopo (baralho b, int x);
void mostra (baralho b);
void carta (baralho b, int p);
void posicao (baralho b, int x);
void salva (historico *h, baralho b);
void desfaz (historico *h, baralho *b);
void liberaHistorico (historico *h);

#endif

/*
-----------------------------------------------------------------------------
DEQUES & DECKS: PROJETO DE BARALHO INTERATIVO FEITO COM ESTRUTURAS DE DADOS
-----------------------------------------------------------------------------
O projeto foi feito utilizando como principal estrutura de dados a lista dupla (Double ended queue)

Cada carta consiste de um tipo struct definido como "node"

O baralho é feito utilizando uma estrutura de deque, feito por sua vez por uma sequência de nodes
duplamente encadeados entre si

O programa só lê comandos e executa ações. Entradas inválidas são ignoradas.
Comandos: BARALHO n, CORTA x, SOBE x, VIRA, VIRATOPO x, MOSTRA, CARTA p, POSICAO x, DESFAZ, FIM
(x é o número escrito na carta e p é a posição contada a partir do topo)
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "baralho.h"

int main () {
    int qtde_cartas, valor;
    bool rodando = true;
    char entrada[20];

    baralho b = NULL;
    historico hist = NULL;

    while (rodando == true) {
        //Se a entrada acabar, o programa encerra
        if (scanf("%19s", entrada) != 1) {
            rodando = false;
            continue;
        }

        //Antes de cada comando que muda o baralho, o estado atual é salvo no histórico
        if (strcmp(entrada, "BARALHO") == 0) {
            if (scanf("%d", &qtde_cartas) == 1 && qtde_cartas > 0) {
                salva(&hist, b);
                novoBaralho(&b, qtde_cartas);
            }
        } else if (strcmp(entrada, "CORTA") == 0) {
            if (scanf("%d", &valor) == 1 && existeCarta(b, valor)) {
                salva(&hist, b);
                corta(&b, valor);
            }
        } else if (strcmp(entrada, "FIM") == 0) {
            rodando = false;
        } else if (strcmp(entrada, "MOSTRA") == 0) {
            mostra(b);
        } else if (strcmp(entrada, "VIRA") == 0) {
            if (b != NULL) {
                salva(&hist, b);
                vira(&b);
            }
        } else if (strcmp(entrada, "SOBE") == 0) {
            if (scanf("%d", &valor) == 1 && existeCarta(b, valor)) {
                salva(&hist, b);
                sobe(&b, valor);
            }
        } else if (strcmp(entrada, "CARTA") == 0) {
            if (scanf("%d", &valor) == 1) {
                carta(b, valor);
            }
        } else if (strcmp(entrada, "POSICAO") == 0) {
            if (scanf("%d", &valor) == 1) {
                posicao(b, valor);
            }
        } else if (strcmp(entrada, "VIRATOPO") == 0) {
            if (scanf("%d", &valor) == 1 && existeCarta(b, valor)) {
                salva(&hist, b);
                viraTopo(b, valor);
            }
        } else if (strcmp(entrada, "DESFAZ") == 0) {
            desfaz(&hist, &b);
        }
    }

    //Liberando toda a memória antes de encerrar
    liberaBaralho(&b);
    liberaHistorico(&hist);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "deque.h"
#include "baralho.h"

//COMO O BARALHO É GUARDADO:
//O primeiro node da lista é o FUNDO e o último node é o TOPO
//Por isso push_front (insere no final) coloca uma carta no topo
//e push_back (insere no início) coloca uma carta no fundo
//As posições são contadas a partir do topo (posição 1 = primeira carta do MOSTRA)
//Só recebem o ponteiro duplo (&) as funções que podem mudar o início da lista

//Devolve o node que guarda a carta x (NULL se ela não existir)
static node *buscaCarta (baralho b, int x) {
    node *atual = b;

    while (atual != NULL && atual->valor != x) {
        atual = atual->prox;
    }

    return atual;
}

//Devolve o último node da lista, ou seja, o topo do baralho (NULL se estiver vazio)
static node *topo (baralho b) {
    if (b == NULL) {
        return NULL;
    }

    node *atual = b;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    return atual;
}

//Cria uma cópia independente do baralho
static baralho copia (baralho b) {
    baralho nova = NULL;
    node *atual = b;

    while (atual != NULL) {
        push_front(atual->valor, &nova);
        atual = atual->prox;
    }

    return nova;
}

//Libera a memória de todos os nodes do baralho
void liberaBaralho (baralho *b) {
    node *atual = *b, *aux;

    while (atual != NULL) {
        aux = atual->prox;
        free(atual);
        atual = aux;
    }

    *b = NULL;
}

//Cria um novo baralho com uma dada quantidade de cartas
void novoBaralho (baralho *b, int qtde) {
    //Liberando a memória de todos os nodes caso já exista um baralho criado
    liberaBaralho(b);

    int i;
    for (i = 1; i <= qtde; i++) {
        push_front(i, b);
    }
}

//Diz se a carta x existe no baralho
bool existeCarta (baralho b, int x) {
    return buscaCarta(b, x) != NULL;
}

//Faz todas as cartas acima de x irem para o fundo do baralho (mantendo a ordem entre elas)
void corta (baralho *b, int x) {
    node *alvo = buscaCarta(*b, x);

    //Se x não existe ou já está no topo, não tem nada acima dele
    if (alvo == NULL || alvo->prox == NULL) {
        return;
    }

    node *primeiroAcima = alvo->prox;
    node *ultimo = topo(*b);

    //Separa a lista em duas partes: de baixo (até x) e de cima (acima de x)
    alvo->prox = NULL;
    primeiroAcima->ant = NULL;

    //A parte de cima passa a ficar antes da parte de baixo
    ultimo->prox = *b;
    (*b)->ant = ultimo;

    *b = primeiroAcima;
}

//Coloca a carta selecionada no topo do baralho
void sobe (baralho *b, int x) {
    node *alvo = buscaCarta(*b, x);

    //Se x não existe ou já está no topo, não precisa fazer nada
    if (alvo == NULL || alvo->prox == NULL) {
        return;
    }

    //Tira o alvo do meio da lista (se ele era o início, o início da lista muda)
    if (alvo->ant == NULL) {
        *b = alvo->prox;
    } else {
        alvo->ant->prox = alvo->prox;
    }
    alvo->prox->ant = alvo->ant;

    //Coloca o alvo no final da lista
    node *ultimo = topo(*b);
    ultimo->prox = alvo;
    alvo->ant = ultimo;
    alvo->prox = NULL;
}

//Inverte a ordem de todas as cartas
void vira (baralho *b) {
    node *atual = *b, *aux;

    //Em cada node, troca o prox com o ant
    while (atual != NULL) {
        aux = atual->prox;
        atual->prox = atual->ant;
        atual->ant = aux;

        //O último node visitado (o antigo topo) vira o novo início
        *b = atual;
        atual = aux;
    }
}

//Mostra todas as cartas do baralho. Do topo ao fundo
void mostra (baralho b) {
    node *atual = topo(b);

    while (atual != NULL) {
        printf("%d\n", atual->valor);
        atual = atual->ant;
    }
}

//Inverte a ordem de todas as cartas acima de uma tal carta
void viraTopo (baralho b, int x) {
    node *alvo = buscaCarta(b, x);
    if (alvo == NULL) {
        return;
    }

    node *inicio = alvo->prox;
    node *fim = topo(b);

    //Conta quantas cartas tem acima de x
    int acima = 0;
    node *atual = inicio;
    while (atual != NULL) {
        acima++;
        atual = atual->prox;
    }

    //Troca as pontas e vai andando em direção ao meio
    int i, aux;
    for (i = 0; i < acima / 2; i++) {
        aux = fim->valor;
        fim->valor = inicio->valor;
        inicio->valor = aux;

        inicio = inicio->prox;
        fim = fim->ant;
    }
}

//Imprime a carta que está na posição p (contando a partir do topo)
void carta (baralho b, int p) {
    if (p < 1) {
        return;
    }

    node *atual = topo(b);

    int i;
    for (i = 1; i < p && atual != NULL; i++) {
        atual = atual->ant;
    }

    if (atual != NULL) {
        printf("%d\n", atual->valor);
    }
}

//Imprime a posição da carta x (contando a partir do topo)
void posicao (baralho b, int x) {
    int pos = 1;
    node *atual = topo(b);

    while (atual != NULL && atual->valor != x) {
        atual = atual->ant;
        pos++;
    }

    if (atual != NULL) {
        printf("%d\n", pos);
    }
}

//Guarda uma cópia do baralho atual no histórico
void salva (historico *h, baralho b) {
    snapshot *novo = malloc(sizeof(snapshot));
    if (novo == NULL) {
        return;
    }

    novo->cartas = copia(b);
    novo->prox = *h;
    *h = novo;
}

//Volta o baralho para a última cópia guardada no histórico
void desfaz (historico *h, baralho *b) {
    if (*h == NULL) {
        return;
    }

    snapshot *ultimo = *h;

    liberaBaralho(b);
    *b = ultimo->cartas;

    *h = ultimo->prox;
    free(ultimo);
}

//Libera toda a memória do histórico
void liberaHistorico (historico *h) {
    snapshot *proximo;

    while (*h != NULL) {
        proximo = (*h)->prox;
        liberaBaralho(&(*h)->cartas);
        free(*h);
        *h = proximo;
    }
}

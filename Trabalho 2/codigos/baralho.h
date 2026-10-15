#ifndef BARALHO_H
#define BARALHO_H

#define boolean int
#define TRUE 1
#define FALSE 0

typedef struct baralho BARALHO;
typedef struct carta CARTA;

typedef struct relatorio RELATORIO;

BARALHO *criar_baralho(BARALHO *baralho, RELATORIO *relatorio);

boolean CORTA(BARALHO *baralho, int x);

boolean SOBE(BARALHO *baralho, int x);

boolean VIRA(BARALHO *baralho);

boolean VIRATOPO(BARALHO *baralho, int k);

boolean DESFAZ(BARALHO *baralho, RELATORIO *relatorio);

int pegar_carta(BARALHO *baralho, int p);

int POSICAO(BARALHO *baralho, int x);

boolean MOSTRA(BARALHO *baralho);

boolean FIM(BARALHO *baralho, RELATORIO *relatorio);


#endif


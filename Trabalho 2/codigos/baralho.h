#ifndef BARALHO_H
#define BARALHO_H

#define boolean int
#define TRUE 1
#define FALSE 0

typedef struct baralho BARALHO;
typedef struct carta CARTA;
typedef struct instance INSTANCE;

INSTANCE *criar_baralho(BARALHO *baralho, RELATORIO *relatorio);

boolean CORTA(BARALHO *baralho, RELATORIO *relatorio, int x);

boolean SOBE(BARALHO *baralho, RELATORIO *relatorio, int x);

boolean VIRA(BARALHO *baralho, RELATORIO *relatorio);

boolean VIRATOPO(BARALHO *baralho, RELATORIO *relatorio, int k);

boolean DESFAZ(BARALHO *baralho, RELATORIO *relatorio);

int pegar_carta(BARALHO *baralho, int p);

int POSICAO(BARALHO *baralho, int x);

boolean MOSTRA(BARALHO *baralho);

boolean apagar_baralho(BARALHO *baralho);

boolean FIM(BARALHO *baralho, RELATORIO *relatorio);


#endif


#ifndef BARALHO_H
#define BARALHO_H

#define boolean int
#define TRUE 1
#define FALSE 0

typedef struct baralho BARALHO;
typedef struct carta CARTA;
typedef struct instance INSTANCE;

typedef struct relatorio RELATORIO;

INSTANCE criar_baralho(BARALHO *baralho, RELATORIO *relatorio,int n);

boolean BarPUSH(BARALHO *baralho, int x);

int BarPOP(BARALHO *baralho);

boolean CORTA(BARALHO *baralho, RELATORIO *relatorio, int x, boolean desfaz);

boolean SOBE(BARALHO *baralho, RELATORIO *relatorio, int x, boolean desfaz);

boolean VIRA(BARALHO *baralho, RELATORIO *relatorio, boolean desfaz);

boolean VIRATOPO(BARALHO *baralho, RELATORIO *relatorio, int k, boolean desfaz);

boolean DESFAZ(BARALHO *baralho, RELATORIO *relatorio);

int pegar_carta(BARALHO *baralho, int p, boolean desfaz);

int POSICAO(BARALHO *baralho, int x, boolean desfaz);

boolean MOSTRA(BARALHO *baralho);

boolean apagar_baralho(BARALHO *baralho);

boolean FIM(BARALHO *baralho, RELATORIO *relatorio);


#endif


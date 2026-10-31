#ifndef DECK_H
#define DECK_H

#define boolean int
#define TRUE 1
#define FALSE 0
#define TAM_MAX 100000

typedef struct carta Carta;
typedef struct baralho Baralho;

/*  BARALHO n -> Cria um baralho novo, com as cartas 1, 2, ....n
    do topo para o fundo (pilha); o baralho anterior e o historico 
    sao descartados

    CORTA - Corta o baralho acima da carta x; as cartas que esta
    vam acima de x vao para o fundo, na mesma ordem, e x fica no topo

    SOBE x   - Tira a carta x de onde ela esta e a poe no topo; as outras mantem a ordem entre si
    VIRA     - Inverte o baralho inteiro: a carta do fundo passa ao topo
    VIRATOPO - Inverte so as k cartas de cima
    DESFAZ   - Desfaz a operaçao mais recente do historico, descrito abaixo
    CARTA    - A carta que esta na posicao p
    POSICAO  - A posicao que esta a carta x
    MOSTRA   - O baralho, do topo ao fundo
    FIM      - Encerra
*/

Baralho *criar_baralho(int numero_cartas); 
boolean baralho_inserir(Baralho *baralho, Carta carta); 
boolean CORTA(Baralho *baralho, int numero_carta, boolean registrar);
int CARTA(Baralho *baralho, int posicao);
boolean VIRA(Baralho *baralho, boolean registrar); 
boolean VIRATOPO(Baralho *baralho, int k, boolean registrar);
boolean SOBE(Baralho *baralho, int numero_carta, boolean registrar);
boolean DESFAZ(Baralho *baralho);
void MOSTRA(Baralho *baralho);
int POSICAO(Baralho *baralho, int numero_carta); 
boolean baralho_apagar(Baralho *baralho);




#endif
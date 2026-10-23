#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baralho.h"
#include "relatorio.h"

typedef struct instance INSTANCE;
struct instance{
    BARALHO *baralho;
    RELATORIO *relatorio;
};

int main(){
    char inputUsuario[9];
    int fimLoop = 0;

    INSTANCE instance = criar_baralho(NULL,NULL, -1);

    while (fimLoop == 0){
        scanf("%s", inputUsuario);
        if (strcmp(inputUsuario, "BARALHO") == 0){
            int n = 0;
            scanf("%d", &n);
            instance = criar_baralho(instance.baralho,instance.relatorio,n);
        }
        else if (strcmp(inputUsuario, "CORTA") == 0){
            int x;
            scanf("%d", &x);
            printf("%d", x);
            CORTA(instance.baralho,instance.relatorio,x);
        }
        else if (strcmp(inputUsuario, "SOBE") == 0){
            int x;
            scanf("%d", &x);
            SOBE(instance.baralho,instance.relatorio,x);
        }
        else if (strcmp(inputUsuario, "VIRA") == 0){
            VIRA(instance.baralho,instance.relatorio);
        }
        else if (strcmp(inputUsuario, "VIRATOPO") == 0){
            int k;
            scanf("%d", &k);
            CORTA(instance.baralho,instance.relatorio,k);
        }
        else if (strcmp(inputUsuario, "DESFAZ") == 0){
            DESFAZ(instance.baralho,instance.relatorio);
        }
        else if (strcmp(inputUsuario, "CARTA") == 0){
            int p;
            scanf("%d", &p);
            pegar_carta(instance.baralho,p);
        }
        else if (strcmp(inputUsuario, "POSICAO") == 0){
            int x;
            scanf("%d", &x);
            POSICAO(instance.baralho,x);
        }
        else if (strcmp(inputUsuario, "MOSTRA") == 0){
            MOSTRA(instance.baralho);
        }
        else if (strcmp(inputUsuario, "FIM") == 0){
            FIM(instance.baralho,instance.relatorio);
            fimLoop = 1;   
        }
    }

    return 0;
}
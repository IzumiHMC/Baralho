#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baralho.h"
#include "relatorio.h"

int main(){
    char inputUsuario[9];
    int fimLoop = 0;

    BARALHO *baralho = criar_baralho(NULL,NULL);

    while (fimLoop == 0){
        scanf("%s", &inputUsuario);
        if (strcmp(inputUsuario, "BARALHO") == 0){
            
        }
        else if (strcmp(inputUsuario, "CORTA") == 0){
            
        }
        else if (strcmp(inputUsuario, "SOBE") == 0){
            
        }
        else if (strcmp(inputUsuario, "VIRA") == 0){
            
        }
        else if (strcmp(inputUsuario, "VIRATOPO") == 0){
            
        }
        else if (strcmp(inputUsuario, "DESFAZ") == 0){
            
        }
        else if (strcmp(inputUsuario, "CARTA") == 0){
            
        }
        else if (strcmp(inputUsuario, "POSICAO") == 0){
            
        }
        else if (strcmp(inputUsuario, "MOSTRA") == 0){
            
        }
        else if (strcmp(inputUsuario, "FIM") == 0){
            
        }
    }

    return 0;
}
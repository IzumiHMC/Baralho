#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baralho.h"
#include "relatorio.h"

//So um aviso: ha uma infeliz denominacao nesse trabalho, chamar o historico de "relatorio"
//eh possivel ver infos do relatorio, quando o programa estiver rodando, digitando "relatorio"

typedef struct instance INSTANCE;
struct instance{
    BARALHO *baralho;
    RELATORIO *relatorio;
};

int main(){
    char inputUsuario[15];
    int fimLoop = 0;

    INSTANCE instance = criar_baralho(NULL,NULL, -1);

    while (fimLoop == 0){
        int returnScanf = scanf("%s", inputUsuario);
        if (returnScanf == 1){
            if (strcmp(inputUsuario, "BARALHO") == 0){
                int n = 0;
                if (scanf("%d", &n) == 1){
                    instance = criar_baralho(instance.baralho,instance.relatorio,n);
                }
                else{
                    printf("ERRO AO LER TAMANHO DO BARALHO\n");
                }
            }
            else if (strcmp(inputUsuario, "CORTA") == 0){
                int x;
                if(scanf("%d", &x) == 1){
                    CORTA(instance.baralho,instance.relatorio,x, FALSE);
                }
                else{
                    printf("ERRO AO LER ROTULO DA CARTA\n");
                }
            }
            else if (strcmp(inputUsuario, "SOBE") == 0){
                int x;
                if(scanf("%d", &x) == 1){
                    SOBE(instance.baralho,instance.relatorio,x, FALSE);
                }
                else{
                    printf("ERRO AO LER O ROTULO DA CARTA\n");
                }
            }
            else if (strcmp(inputUsuario, "VIRA") == 0){
                VIRA(instance.baralho,instance.relatorio, FALSE);
            }
            else if (strcmp(inputUsuario, "VIRATOPO") == 0){
                int k;
                if(scanf("%d", &k) == 1){
                   VIRATOPO(instance.baralho,instance.relatorio,k, FALSE);
                }
                else{
                    printf("ERRO AO LER k\n");
                }
            }
            else if (strcmp(inputUsuario, "DESFAZ") == 0){
                DESFAZ(instance.baralho,instance.relatorio);
            }
            else if (strcmp(inputUsuario, "CARTA") == 0){
                int p;
                if(scanf("%d", &p) == 1){
                   pegar_carta(instance.baralho,p, FALSE);
                }
                else{
                    printf("ERRO AO LER A POSICAO DA CARTA\n");
                }
            }
            else if (strcmp(inputUsuario, "POSICAO") == 0){
                int x;
                if(scanf("%d", &x) == 1){
                    POSICAO(instance.baralho,x, FALSE);
                }
                else{
                    printf("ERRO AO LER O ROTULO DA CARTA\n");
                }
            }
            else if (strcmp(inputUsuario, "MOSTRA") == 0){
                MOSTRA(instance.baralho);
            }
            else if (strcmp(inputUsuario, "FIM") == 0){
                FIM(instance.baralho,instance.relatorio);
                fimLoop = 1;   
            }
            else if (strcmp(inputUsuario, "relatorio") == 0){
                mostrar_relatorio(instance.relatorio);
            }
        }
        else{
            fprintf(
                stderr,
                "=======\nERRO AO LER INPUT DE OPERACAO\nreturn scanf: %d\ninputUsuario: %s\n",
                returnScanf, inputUsuario
            );
        }

    }

    return 0;
}
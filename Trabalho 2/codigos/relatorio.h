#ifndef RELATORIO_H
#define RELATORIO_H

#define boolean int
#define TRUE 1
#define FALSE 0

typedef struct relatorio RELATORIO;

RELATORIO *criar_relatorio();

boolean PUSH(RELATORIO *relatorio, char *operacao, int k);

boolean POP(RELATORIO *relatorio);

boolean apagar_relatorio(RELATORIO *relatorio);


#endif
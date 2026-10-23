#ifndef RELATORIO_H
#define RELATORIO_H

#define boolean int
#define TRUE 1
#define FALSE 0

typedef struct relatorio RELATORIO;
typedef struct operacao OPERACAO;

struct operacao{
    char *comando;
    int k;
};

struct relatorio{
    OPERACAO comandos[100];
    int inicio;
};

RELATORIO *criar_relatorio();

boolean PUSH(RELATORIO *relatorio, OPERACAO operacao);

OPERACAO POP(RELATORIO *relatorio);

boolean mostrar_relatorio(RELATORIO *relatorio);

boolean apagar_relatorio(RELATORIO *relatorio);

OPERACAO criar_operacao(char *comando, int k);

char *comando_operacao(RELATORIO *relatorio);

int k_operacao(RELATORIO *relatorio);

#endif
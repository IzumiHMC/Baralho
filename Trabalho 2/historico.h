#ifndef HISTORICO_H
#define HISTORICO_H

#define boolean int
#define TRUE 1
#define FALSE 0
#define HISTORICO_TAM_MAX 100



#define CORTA_comando    0
#define SOBE_comando     1
#define VIRA_comando     2
#define VIRATOPO_comando 3

typedef struct Historico Historico;
typedef struct Registro Registro;


Historico *criar_historico();
boolean INSERIR_no_HISTORICO(Historico *historico, int tipo, int rotulo, int numero_operacao );
void ESVAZIAR_HISTORICO(Historico *historico);
void destruir_historico(Historico **historico);

//Aqui eu uso ponteiros por conta do return
boolean REMOVER_ULTIMO(Historico *historico, int *tipo, int *rotulo, int *numero_operacao);


#endif
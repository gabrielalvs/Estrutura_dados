#ifndef JOGO_H
#define JOGO_H

#define TRUE 1
#define FALSE 0
#define boolean char
#define ERRO -32000

typedef struct jogo_st JOGO;

JOGO *jogo_new(const char *nome_jogo, const char *nome_empresa, int ano);
boolean jogo_delete(JOGO **jogo);
void jogo_print(const JOGO *jogo);

#endif //JOGO_H

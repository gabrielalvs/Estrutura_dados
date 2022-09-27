#ifndef ATTACK_H
#define ATTACK_H

#define TRUE 1
#define FALSE 0
#define boolean char
#define ERRO -32000

typedef struct attack_st ATTACK;

ATTACK *new_attack (const char *nome, const int powerBase, const float accuracy, const char classe);

boolean attack_apagar(ATTACK **attack);

void attack_imprimir(const ATTACK *attack);

#endif //ATTACK_H

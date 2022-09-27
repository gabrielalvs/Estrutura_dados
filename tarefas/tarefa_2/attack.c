#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "attack.h"

struct attack_st
{
    char nome[20];
    int powerBase;
    float accuracy;
    // 's' para especial, 'p' para físico
    char classe;
};

ATTACK *new_attack (const char *nome, const int powerBase, const float accuracy, const char classe)
{
    ATTACK *attack;

    attack = (ATTACK *) malloc(sizeof(ATTACK));

    if (attack != NULL)
    {
        strcpy(attack->nome, nome);
        attack->powerBase = powerBase;
        attack->accuracy = accuracy;
        attack->classe = classe;
        return attack;
    }
    return NULL;
}

boolean attack_apagar(ATTACK **attack)
{
    if (*attack != NULL)
    {
        free (*attack);
        *attack = NULL;
        return TRUE;
    }
    return FALSE;
}

void attack_imprimir(const ATTACK *attack)
{
    if (attack != NULL)
    {
        printf("Nome do Ataque: %s\n", attack->nome);
        printf("Poder base: %d\n", attack->powerBase);
        printf("Acuracia: %f\n", attack->accuracy);
        printf("Classe: %c\n", attack->classe);
    }
}
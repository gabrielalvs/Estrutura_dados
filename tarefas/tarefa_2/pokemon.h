#ifndef POKEMON_H
#define POKEMON_H

#define TRUE 1
#define FALSE 0
#define boolean char
#define ERRO -32000
#include "attack.h"

typedef struct pokemon_st POKEMON;
typedef struct status_st STATUS;


POKEMON *new_pokemon(const char *nome, const char *tipo_primario, const char *tipo_secundario, const int hp,
                    const int attack, const int deffense, const int specialAttack,
                    const int specialDeffense, const int speed);

                    STATUS *new_status(const int hp, const int attack, const int deffense, const int specialAttack, const int specialDeffense, const int speed);

boolean pokemon_apagar(POKEMON **pokemon);

void pokemon_imprimir(const POKEMON *pokemon);

void pokemon_imprimir_status(const STATUS *status);

void addAttack(POKEMON *pokemon, ATTACK *attack, int index);

void pokemon_imprimir_attacks(const POKEMON *pokemon, int index);

ATTACK *getAttack(const POKEMON *pokemon, int index);

STATUS *getStatus(const POKEMON *pokemon);

#endif //POKEMON_H

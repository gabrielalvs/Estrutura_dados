#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pokemon.h"
#include "attack.h"

struct pokemon_st
{
    char nome[50];
    char tipo_primario[20];
    char tipo_secundario[20];
    STATUS *status;
    ATTACK *attacks[4];
};

struct status_st {
    int hp;
    int attack;
    int deffense;
    int specialAttack;
    int specialDeffense;
    int speed;
};

POKEMON *new_pokemon (const char *nome, const char *tipo_primario, const char *tipo_secundario, const int hp,
                    const int attack, const int deffense, const int specialAttack,
                    const int specialDeffense, const int speed ){
    POKEMON *pokemon;

    pokemon = (POKEMON *) malloc(sizeof(POKEMON));

    if (pokemon != NULL)
    {
        strcpy(pokemon->nome, nome);
        strcpy(pokemon->tipo_primario, tipo_primario);
        strcpy(pokemon->tipo_secundario, tipo_secundario);
        pokemon->status = new_status(hp, attack, deffense, specialAttack, specialDeffense, speed);
        return pokemon;
    }
    return NULL;
}

STATUS *new_status(const int hp, const int attack, const int deffense, const int specialAttack, const int specialDeffense, const int speed){
    STATUS *status = (STATUS *) malloc(sizeof(STATUS));
    status->hp = hp;
    status->attack = attack;
    status->deffense = deffense;
    status->specialAttack = specialAttack;
    status->specialDeffense = specialDeffense;
    status->speed = speed;
    return status;
}

boolean pokemon_apagar(POKEMON **pokemon)
{
    if (*pokemon != NULL){
        free(getStatus(*pokemon));
            for(int i = 0; i < 4; i++){
                if(getAttack(*pokemon, i) != NULL){
                    free(getAttack(*pokemon, i));
                }
            }
        free(*pokemon);
        *pokemon = NULL;
        return TRUE;
    }   
    return FALSE;
}

void pokemon_imprimir(const POKEMON *pokemon)
{
    if (pokemon != NULL)
    {
        printf("Nome do Pokemon: %s\n", pokemon->nome);
        printf("Tipo primario: %s\n", pokemon->tipo_primario);
        printf("Tipo secundario: %s\n", pokemon->tipo_secundario);
        pokemon_imprimir_status(pokemon->status);
    }
}

void pokemon_imprimir_status(const STATUS *status)
{
    if (status != NULL)
    {
        printf("Status:\n");
        printf("\tHP: %d\n", status->hp);
        printf("\tAtaque: %d\n", status->attack);
        printf("\tDefesa: %d\n", status->deffense);
        printf("\tAtaque Especial: %d\n", status->specialAttack);
        printf("\tDefesa Especial: %d\n", status->specialDeffense);
        printf("\tVelocidade: %d\n", status->speed);
    }
}

void pokemon_imprimir_attacks(const POKEMON *pokemon, int index)
{
    if (pokemon != NULL)
    {
        attack_imprimir(pokemon->attacks[index]); 
    }
}


void addAttack(POKEMON *pokemon, ATTACK *attack, int index)
{
    if (pokemon != NULL)
    {
        pokemon->attacks[index] = attack;
    }
}

ATTACK *getAttack(const POKEMON *pokemon, int index){
    return pokemon->attacks[index];
}

STATUS *getStatus(const POKEMON *pokemon){
    return pokemon->status;
}

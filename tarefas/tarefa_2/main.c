#include <stdio.h>
#include <stdlib.h>
#include "pokemon.h"
#include "attack.h"

int main (void){

    // Pokemon
    char nome[50];
    char tipo_primario[20];
    char tipo_secundario[20];
    int hp;
    int deffense;
    int attack;
    int specialAttack;
    int specialDeffense; 
    int speed;

    // Ataque
    char nomeAttack[20];
    int powerBase;
    float accuracy;
    char classe;

    int n_elements = 10;
    int n_pokemons = 0;
    POKEMON **pokedex = (POKEMON **) malloc(n_elements * sizeof(POKEMON*));

    int pos_pokemon = 0;
    int pos_attack = 0;

    int option = -1;
    while(option != 0){
         scanf("%d", &option);
         switch (option)
        {
        case 1:
            if(n_pokemons==n_elements){
                n_elements *= 2;
                pokedex = (POKEMON **) realloc(pokedex, sizeof(POKEMON*) * n_elements);
            }

            scanf("%s\n", nome);
            scanf("%s\n", tipo_primario);
            scanf("%s\n", tipo_secundario);
            scanf("%d\n", &hp);
            scanf("%d\n", &attack);
            scanf("%d\n", &deffense);
            scanf("%d\n", &specialAttack);
            scanf("%d\n", &specialDeffense);
            scanf("%d\n", &speed);

            pokedex[n_pokemons] = new_pokemon(nome, tipo_primario, tipo_secundario, hp,attack,deffense,specialAttack,specialDeffense,speed);
            n_pokemons++;
        break;

        case 2:
            scanf("%d\n", &pos_pokemon);
            scanf("%d\n", &pos_attack);

            scanf("%s\n", nomeAttack);
            scanf("%d\n", &powerBase);
            scanf("%f\n", &accuracy);
            scanf("%c\n", &classe);

            addAttack(pokedex[pos_pokemon], new_attack(nomeAttack,powerBase,accuracy,classe ), pos_attack);

        break;

        case 3:
            scanf("%d",&pos_pokemon);
            pokemon_imprimir(pokedex[pos_pokemon]);

            printf("\n");
        break;

        case 4:
            scanf("%d",&pos_pokemon);
            scanf("%d",&pos_attack);
            pokemon_imprimir_attacks(pokedex[pos_pokemon],pos_attack);

            printf("\n");
        break;

        }
        
    }

    return 0;


}
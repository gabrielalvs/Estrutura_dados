#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Jogo.h"
#include "Avl.h"

int main (void){

    AVL *arvore_binaria = avl_criar();

    set_jogos_file(arvore_binaria, "CSV-TodosJogos.csv");

    char aux_control[ 100 ];
    int t_impress = 0;

    scanf("%i",&t_impress);

    while (TRUE)
    {   
        scanf("%s",aux_control);
        if (strcmp(aux_control,"F")==0) break;

        avl_remover(arvore_binaria, atoi(aux_control));
    }

     switch (t_impress)
        {
            case 1:
                arvore_binaria_pre_ordem(arvore_binaria);
            break;

            case 2:
                arvore_binaria_em_ordem(arvore_binaria);;
            break;

            case 3:
                arvore_binaria_pos_ordem(arvore_binaria);
            break;
        }

        avl_apagar(&arvore_binaria);
}

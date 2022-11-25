#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Big_int.h"

int main(){

    int q_oper;
    char num1[30],num2[30],ope[10];

    BIG_INT *big_int_1;
    BIG_INT *big_int_2;
    BIG_INT *big_int_3;

    scanf("%d\n",&q_oper);

    for (int i = 0; i < q_oper; i++)
    {
    
        scanf("%s %s %s",ope,num1,num2);

        big_int_1 = big_int_criar(num1);
        big_int_2 = big_int_criar(num2);

        printf("Resultado :: ");
        
        if(strcmp(ope,"soma") == 0){
          big_int_3 = big_int_somar(big_int_1,big_int_2);
          big_int_imprimir(big_int_3);
          printf("\n");
          big_int_apagar(&big_int_3);
        }

        if(strcmp(ope,"maior") == 0){
            if(big_int_maior(big_int_1,big_int_2)){
                printf("True\n");
            }else{
                printf("False\n");
            }
        }
        if(strcmp(ope,"menor") == 0){
            if(big_int_maior(big_int_2,big_int_1)){
                printf("True\n");
            }else{
                printf("False\n");
            }
        }

        if(strcmp(ope,"igual") == 0){
            if(big_int_igual(big_int_1,big_int_2)==1){
                printf("True\n");
            }else{
                printf("False\n");
            }
        }

        big_int_apagar(&big_int_1);
        big_int_apagar(&big_int_2);
    }
}

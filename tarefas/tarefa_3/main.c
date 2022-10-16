#include <stdio.h>
#include "Jogo.h"
#include "Catologo.h"

int main (void){
    CATALOGO *catologo;
    catologo = catologo_new();
    catologo_add(catologo, jogo_new("teste", "teste", 2001));
    catologo_print(catologo);
    catologo_delete(&catologo);
    return 0;
}
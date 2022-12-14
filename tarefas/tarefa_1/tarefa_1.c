#include <stdio.h>

void gerar_troco(int total, int* mod){
    const int valores[6] = {100,50,25,10,5,1};
    for(int i = 0; i<6; i++) {
        if (total >= valores[i]) {
            mod[i] = total / valores[i];
            total = total - mod[i] * valores[i];
        }
    }
}

int main(){
	int valor = 0;
    int moedas[6] = {0,0,0,0,0,0};
	scanf("%d", &valor);

    gerar_troco(valor,moedas);
    
    printf("O valor consiste em %d moedas de 1 real \n"
           "O valor consiste em %d moedas de 50 centavos \n"
           "O valor consiste em %d moedas de 25 centavos \n"
           "O valor consiste em %d moedas de 10 centavos \n"
           "O valor consiste em %d moedas de 5 centavos \n"
           "O valor consiste em %d moedas de 1 centavo",
           moedas[0],moedas[1],moedas[2],moedas[3],moedas[4],moedas[5]);

	return 0;	
}

#include <stdio.h>

int fneuronio (int *, int *, int , int, int *);

int main(){
    int i, n,limiarT,retorno;
    printf("Digite a quantidade de entradas: ");
    scanf("%d", &n);
    int entradas[n], pesos[n];
    printf("Digite o valor do limiarT: ");
    scanf("%d", &limiarT);
    for (i=0 ; i < n ; i++){
        printf("Digite a entrada %d : ", i);
        scanf("%d", &entradas[i]);
        printf("Digite o peso %d : ", i);
        scanf("%d", &pesos[i]);
    }
    fneuronio(entradas, pesos, limiarT, n, &retorno);
    if (retorno == 0)
    printf("Neurono inibido!");
    else
    printf("Neuronio ativado!");
return 0;
}

int fneuronio (int *xi, int *wi, int limiarT, int n, int *retorno){
int i, somap=0;
for (i=0; i<n ; i++)
    somap += *(xi + i)* *(wi + i);
if (somap > limiarT)
    *retorno = 1;
else
    *retorno = 0;
}

#include <stdio.h>

int hanoi(int n, char origem, char destino, char aux, int contador);

int main()
{
  int n, contador = 0, resultado;

  printf("Digite o numero de discos: ");
  scanf("%d", &n);
  resultado = hanoi(n, 'A', 'C', 'B', contador);

  printf("\n=========\n%d\n==========\n", resultado);
  return 0;
}

int hanoi(int n, char origem, char destino, char aux, int contador)
{
  if (n == 1)
  {
    return ++contador;
    // printf("Mover 1 de %c para %c\n", origem, destino);
  }
  else
  {
    contador = hanoi(n - 1, origem, aux, destino, contador);
    // printf("Mover %d de %c para %c\n", n, origem, destino);
    contador = hanoi(n - 1, aux, destino, origem, contador);
    contador++;
  }
  return contador;
}

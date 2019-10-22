#include <stdio.h>

void recebe_notas (float *notas, int *apr, int n);
void conta_notas (int *apr, int n, int *n_apr, int *n_rep);
int percent_aprov (int n, int n_apr, int n_rep, float *perc_apr, float *perc_rep);

int main(){
  int n, n_apr = 0, n_rep = 0;
  float perc_apr, perc_rep;
  printf("Digite o número de notas: ");
  scanf("%d", &n);
  float notas[n];
  int apr[n];

  for(int i = 0; i < n; i++) {
    printf("Digite a nota da posição %d: ", i);
    scanf("%f", &notas[i]);
  }

  recebe_notas(notas, apr, n);
  conta_notas(apr, n, &n_apr, &n_rep);
  int x = percent_aprov(n, n_apr, n_rep, &perc_apr, &perc_rep);

  printf("Quantidade de aprovados: %d\n", n_apr);
  printf("Quantidade de reprovados: %d\n", n_rep);
  printf("Percentual de aprovados: %.1f%%\n", perc_apr*100);
  printf("Percentual de reprovados: %.1f%%\n", perc_rep*100);

  if(x == 1)
    printf("Mais da metade da turma foi APROVADA\n");
  else
    printf("Mais da metade da turma foi REPROVADA\n");

  return 0;
}

void recebe_notas (float *notas, int *apr, int n) {
  for(int i = 0; i < n; i++) {
    if (*(notas + i) >= 6.0)
      *(apr + i) = 1;
    else
      *(apr + i) = 0;
  }
}

void conta_notas (int *apr, int n, int *n_apr, int *n_rep) {
  for(int i = 0; i < n; i++){
    if(*(apr + i) == 1)
      *n_apr += 1;
    else
      *n_rep += 1;
  }
}

int percent_aprov (int n, int n_apr, int n_rep, float *perc_apr, float *perc_rep) {
  *perc_apr = (float)n_apr/n;
  *perc_rep = (float)n_rep/n;

  if (n_apr > n/2)
    return 1;
  else
    return 0;
}

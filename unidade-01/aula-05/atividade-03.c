/*
ATIVIDADE 03:
Uma loja quer saber a nota média do
atendimento dos clientes.
Enunciado:
Um sistema deve ler a nota de atendimento (de 0 a
10) de 10 clientes e calcular a média geral. Se a
média for menor que 7, deve exibir uma
mensagem de alerta.
*/

#include <stdio.h>

int main() {
  int somaNotas = 0;
  float media = 0;
  float qtdClientes = 10.0;

  for (int i = 0; i < qtdClientes; i++) {
    int nota;
    printf("Digite a nota do cliente %d: ", i + 1);
    scanf("%d", &nota);
    somaNotas += nota;
  }

  media = somaNotas / qtdClientes;

  if ( media < 7)
  {
    printf("Alerta media foi menor que 7!\n");
  }

  printf("Media: %.2f", media);

  return 0;
}
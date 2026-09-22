/*
ATIVIDADE 04:
Um aplicativo quer acompanhar a meta diária
de passos de um usuário. Faça um programa que
leia a quantidade de passos dados por um usuário
a cada hora. O programa deve parar quando o
total atingir ou ultrapassar 10.000 passos e então
informar quantas horas foram necessárias.
*/

#include <stdio.h>

int main() {
  int metaPassos = 10000;
  int passosTotal = 0;
  int qtdHoras = 0;

  do {
    int qtdPassosPorHora = 0;
    printf("Registre a quantidade de passos\n");
    scanf("%d", &qtdPassosPorHora);

    if (qtdPassosPorHora >= 0) {
      passosTotal += qtdPassosPorHora;
      qtdHoras += 1;
    } else {
      printf("Valor invalido!\n");
    }

  } while (passosTotal < metaPassos);

  printf("Voce precisou de %d horas para atingir a meta diaria de 10.000 passos. e executou %d passos.", qtdHoras, passosTotal);

  return 0;
}
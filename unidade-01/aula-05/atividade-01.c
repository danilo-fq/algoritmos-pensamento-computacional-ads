/*
ATIVIDADE 01:
Um condomínio quer monitorar o consumo de
água de cada morador. 

Escreva um programa que leia o consumo mensal de água (em m³) de 5 moradores. 
  - Para cada morador, informe se o
  consumo está dentro da média (até 20 m³) ou
  acima. 
Ao final, mostre o consumo médio geral.
*/

#include <stdio.h>

int main() {
  int qtdMoradores = 5;
  float consumoTotal = 0;

  for (int index = 0; index < qtdMoradores; index++) {
    float consumoMensal = 0;
    printf("Digite o consumo mensal de agua do morador %d: ", index + 1);
    scanf("%f", &consumoMensal);

    consumoTotal += consumoMensal;

        if (consumoMensal <= 20)
    {
      printf("O Consumo esta dentro da media!\n");
    }
    else
    {
      printf("O consumo esta acima da media\n");
    }
  }

  printf("O consumo medio total foi de: %.2f m3", consumoTotal / qtdMoradores);
}
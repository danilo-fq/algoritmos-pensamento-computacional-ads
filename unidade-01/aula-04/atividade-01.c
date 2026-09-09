/*
ATIVIDADE 01:
Leia três valores inteiros representando os lados de um triângulo. O programa deve:

- Verificar se os valores podem formar um triângulo;

- Classificar o triângulo como:
  - Equilátero;
  - Isósceles;
  - Escaleno;

- Determinar se o triângulo é:
  - Acutângulo;
  - Retângulo;
  - Obtusângulo;

- Informar quando os valores não formarem um triângulo.

Restrição: não utilizar funções prontas para classificação.
*/

#include <stdio.h>

int main () {
  int ladoA, ladoB, ladoC;

  printf("Digite os 3 lados de um triangulo:\n");
  
  printf("Primeiro lado: ");
  scanf("%d", &ladoA);
  printf("Segundo lado: ");
  scanf("%d", &ladoB);
  printf("Terceiro lado: ");
  scanf("%d", &ladoC);

  if (
    (ladoA + ladoB) > ladoC && 
    (ladoA + ladoC) > ladoB && 
    (ladoB + ladoC) > ladoA && 
    ladoA > 0 && 
    ladoB > 0 && 
    ladoC > 0
  ) {
    if ( ladoA == ladoB && ladoA == ladoC) {
      printf("Triangulo Equilatero e ");
    } else if (ladoA != ladoB && ladoA != ladoC) {
      printf("Triangulo Escaleno e ");
    } else {
      printf("Triangulo Isosceles e ");
    }

    if(ladoA >= ladoB && ladoA >= ladoC) {
      if (ladoA * ladoA == ladoB * ladoB + ladoC * ladoC) {
        printf("Retangulo\n");
      } else if (ladoA * ladoA > ladoB * ladoB + ladoC * ladoC) {
        printf("Obtusangulo\n");
      } else {
        printf("Acutangulo\n");
      }
    } else if (ladoB >= ladoA && ladoB >= ladoC) {
      if (ladoB * ladoB == ladoA * ladoA + ladoC * ladoC) {
        printf("Retangulo\n");
      }
      else if (ladoB * ladoB > ladoA * ladoA + ladoC * ladoC) {
        printf("Obtusangulo\n");
      }
      else {
        printf("Acutangulo\n");
      }
    } else {
      if (ladoC * ladoC == ladoA * ladoA + ladoB * ladoB) {
        printf("Retangulo\n");
      }
      else if (ladoC * ladoC > ladoA * ladoA + ladoB * ladoB) {
        printf("Obtusangulo\n");
      }
      else {
        printf("Acutangulo\n");
      }
    }

  } else {
    printf("\nValores nao formam um triangulo\n");
  }

  return 0;
}
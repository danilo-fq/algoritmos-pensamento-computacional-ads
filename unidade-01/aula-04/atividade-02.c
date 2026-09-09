/*
ATIVIDADE 2
Um caixa possui notas de:
- R$ 200, R$ 100, R$ 50, R$ 20, R$ 10 e R$ 5
usuário informa o valor do saque.

- O programa deve verificar:
  - Se o valor é válido;
  - Se é possível realizar o saque;
  - Quais notas devem ser entregues;
  - A quantidade de cada nota;
  - A quantidade total de cédulas.

- Porém, existe uma regra adicional:
  - O caixa deve preservar pelo menos uma nota de
cada denominação disponível.
  - O programa deve decidir se consegue realizar o
saque sem violar essa regra.
*/

#include <stdio.h>

int main() {
  int estoque200 = 3, estoque100 = 3, estoque50 = 3, estoque20 = 3, estoque10 = 3, estoque5 = 3;
  int notasRetidadas200 = 0, notasRetidadas100 = 0, notasRetidadas50 = 0, notasRetidadas20 = 0, notasRetidadas10 = 0, notasRetidadas5 = 0;
  int valorSaque;
  int valorRestante;
  #define CEDULA_200 200
  #define CEDULA_100 100
  #define CEDULA_50 50
  #define CEDULA_20 20
  #define CEDULA_10 10
  #define CEDULA_5 5

  // printf("Quantidade de notas de R$ 200: ");
  // scanf("%d", &estoque200);
  // printf("Quantidade de notas de R$ 100: ");
  // scanf("%d", &estoque100);
  // printf("Quantidade de notas de R$ 50: ");
  // scanf("%d", &estoque50);
  // printf("Quantidade de notas de R$ 20: ");
  // scanf("%d", &estoque20);
  // printf("Quantidade de notas de R$ 10: ");
  // scanf("%d", &estoque10);
  // printf("Quantidade de notas de R$ 5: ");
  // scanf("%d", &estoque5);

  printf("Digite o valor de saque: ");
  scanf("%d", &valorSaque);

  if (valorSaque % 5 != 0 || valorSaque <= 0) {
    printf("Valor invalido!\n");
    return 0;
  }

  valorRestante = valorSaque;

  if (estoque200 > 1) {
    notasRetidadas200 = valorRestante / CEDULA_200;

    if (notasRetidadas200 > estoque200 - 1) {
      notasRetidadas200 = estoque200 - 1;
    }

    valorRestante -= notasRetidadas200 * CEDULA_200;
  }

  if (estoque100 > 1) {
    notasRetidadas100 = valorRestante / CEDULA_100;

    if (notasRetidadas100 > estoque100 - 1) {
      notasRetidadas100 = estoque100 - 1;
    }

    valorRestante -= notasRetidadas100 * CEDULA_100;
  }

  if (estoque50 > 1) {
    notasRetidadas50 = valorRestante / CEDULA_50;

    if (notasRetidadas50 > estoque50 - 1) {
      notasRetidadas50 = estoque50 - 1;
    }

    valorRestante -= notasRetidadas50 * CEDULA_50;
  }

  if (estoque20 > 1) {
    notasRetidadas20 = valorRestante / CEDULA_20;

    if (notasRetidadas20 > estoque20 - 1) {
      notasRetidadas20 = estoque20 - 1;
    }

    valorRestante -= notasRetidadas20 * CEDULA_20;
  }

  if (estoque10 > 1) {
    notasRetidadas10 = valorRestante / CEDULA_10;

    if (notasRetidadas10 > estoque10 - 1) {
      notasRetidadas10 = estoque10 - 1;
    }

    valorRestante -= notasRetidadas10 * CEDULA_10;
  }

  if (estoque5 > 1) {
    notasRetidadas5 = valorRestante / CEDULA_5;

    if (notasRetidadas5 > estoque5 - 1) {
      notasRetidadas5 = estoque5 - 1;
    }

    valorRestante -= notasRetidadas5 * CEDULA_5;
  }

  if (valorRestante != 0) {
    printf("Estoque insuficiente!\n");
    printf("Nao foi possivel sacar o valor de R$%d.\n", valorSaque);
    return 0;
  }

  printf("Saque Realizado:\n");

  if (notasRetidadas200 > 0) {
    printf("R$ 200 -> %d cedulas.\n", notasRetidadas200);
  }
  if (notasRetidadas100 > 0) {
    printf("R$ 100 -> %d cedulas.\n", notasRetidadas100);
  }
  if (notasRetidadas50 > 0) {
    printf("R$ 50 -> %d cedulas.\n", notasRetidadas50);
  }
  if (notasRetidadas20 > 0) {
    printf("R$ 20 -> %d cedulas.\n", notasRetidadas20);
  }
  if (notasRetidadas10 > 0) {
    printf("R$ 10 -> %d cedulas.\n", notasRetidadas10);
  }
  if (notasRetidadas5 > 0) {
    printf("R$ 5 -> %d cedulas.\n", notasRetidadas5);
  }
  printf(
    "Quantidade total de cedulas: %d\n", 
    notasRetidadas200 + 
    notasRetidadas100 + 
    notasRetidadas50 + 
    notasRetidadas20 + 
    notasRetidadas10 + 
    notasRetidadas5
  );
  printf(
    "Valor sacado: R$ %d\n", 
    notasRetidadas200 * CEDULA_200 + 
    notasRetidadas100 * CEDULA_100 + 
    notasRetidadas50 * CEDULA_50 + 
    notasRetidadas20 * CEDULA_20 + 
    notasRetidadas10 * CEDULA_10 + 
    notasRetidadas5 * CEDULA_5
  );
  return 0;
}
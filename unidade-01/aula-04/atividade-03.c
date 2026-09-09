/*
ATIVIDADE 3
Leia três números inteiros A, B e C.
- Sem ordenar os valores e sem utilizar funções auxiliares, o programa deve informar:
  - Maior valor;
  - Menor valor;
  - Valor intermediário;
  - Se existem valores repetidos;
  - Se os três valores são iguais;
  - Se estão em ordem crescente;
  - Se estão em ordem decrescente.
- Restrição: resolver utilizando apenas comparações
condicionais.
*/

#include <stdio.h>

int main() {
  int numA, numB, numC;

  printf("Digite o primeiro numero: ");
  scanf("%d", &numA);
  printf("Digite o segundo numero: ");
  scanf("%d", &numB);
  printf("Digite o terceiro numero: ");
  scanf("%d", &numC);

  int maiorNumero;
  int menorNumero;
  int numeroIntermediario;

  if (numA >= numB && numA >= numC) {
    maiorNumero = numA;

    if (numB <= numC) {
      menorNumero = numB;
      numeroIntermediario = numC;
    } else {
      menorNumero = numC;
      numeroIntermediario = numB;
    }
  } else if (numB >= numA && numB >= numC) {
    maiorNumero = numB;
    if (numA <= numC) {
      menorNumero = numA;
      numeroIntermediario = numC;
    } else {
      menorNumero = numC;
      numeroIntermediario = numA;
    }
  } else {
    maiorNumero = numC;
    if (numA <= numB) {
      menorNumero = numA;
      numeroIntermediario = numB;
    } else {
      menorNumero = numB;
      numeroIntermediario = numA;
    }
  }

  printf("\nMaior numero: %d\n", maiorNumero);
  printf("Numero intermediario: %d\n", numeroIntermediario);
  printf("Menor numero: %d\n", menorNumero);

  if (numA == numB || numA == numC || numB == numC) {
    printf("\nExistem valores repetidos!\n");
  } else {
    printf("\nSem numeros repetidos!\n");
  }
  
  if (numA == numB && numB == numC) {
    printf("Os tres numeros sao iguais!\n");
  }

  if (numA > numB && numB > numC) {
    printf("Ordem Decrescente;\n");
  }

  if (numA < numB && numB < numC) {
    printf("Ordem Crescente;\n");
  }

  return 0;
}
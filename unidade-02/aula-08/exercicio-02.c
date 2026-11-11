/*
EXERCICIO 2
Desenvolva um algoritmo em linguagem C que leia 10 valores inteiros e identifique quais são positivos e pares e quais são
negativos e ímpares. Os valores que atenderem a cada uma dessas condições deverão ser armazenados em vetores distintos.
Ao final, o programa deverá apresentar os dois conjuntos de valores, organizados em ordem crescente.
*/

#include <stdio.h>
#include <stdlib.h>

#define QTD_VALORES 10

int ehPar(int numero);

void ordenarCrescente(int *ptr, int tamanhoPtr);

int main()
{
  int valores[QTD_VALORES] = {2, -3, 4, -5, 12, -7, 8, -9, 20, -15};
  int qtdPosPar = 0;
  int qtdNegImpar = 0;
  int indiceAtualPositivosPares = 0;
  int indiceAtualNegativosImpares = 0;
  int *vetPositivosPares;
  int *vetNegativosImpares;

  for (int i = 0; i < QTD_VALORES; i++)
  {
    // printf("Digite o valor %d: ", i + 1);
    // scanf("%d", &valores[i]);
    if (valores[i] > 0 && ehPar(valores[i]))
    {
      qtdPosPar++;
    }
    if (valores[i] < 0 && !ehPar(valores[i]))
    {
      qtdNegImpar++;
    }
  }

  vetPositivosPares = (int *)malloc(sizeof(int) * qtdPosPar);
  if(vetPositivosPares == NULL)
  {
    printf("Erro na alocacao!\n");
    return 1;
  }
  vetNegativosImpares = (int *)malloc(sizeof(int) * qtdNegImpar);
  if (vetNegativosImpares == NULL)
  {
    printf("Erro na alocacao!\n");
    return 1;
  }

  for (int i = 0; i < QTD_VALORES; i++)
  {
    if (valores[i] > 0 && ehPar(valores[i]))
    {
      vetPositivosPares[indiceAtualPositivosPares] = valores[i];
      indiceAtualPositivosPares++;
    }
    if (valores[i] < 0 && !ehPar(valores[i]))
    {
      vetNegativosImpares[indiceAtualNegativosImpares] = valores[i];
      indiceAtualNegativosImpares++;
    }
  }

  ordenarCrescente(vetPositivosPares, qtdPosPar);
  ordenarCrescente(vetNegativosImpares, qtdNegImpar);

  printf("\n===IMPRIMINDO O VETOR DE POSITIVOS PARES===\n");
  for (int i = 0; i < qtdPosPar; i++)
  {
    printf("%d\n", vetPositivosPares[i]);
  }

  printf("\n===IMPRIMINDO O VETOR DE NEGATIVOS IMPARES===\n");
  for (int i = 0; i < qtdNegImpar; i++)
  {
    printf("%d\n", vetNegativosImpares[i]);
  }
  free(vetPositivosPares);
  free(vetNegativosImpares);
}

int ehPar(int numero)
{
  return numero % 2 == 0;
}

void ordenarCrescente(int *ptr, int tamanhoPtr)
{
  for (int i = 0; i < tamanhoPtr - 1; i++)
  {
    int encontrou = 0;
    for (int j = 0; j < tamanhoPtr - 1 - i; j++)
    {

      if (ptr[j] > ptr[j + 1])
      {
        int aux = ptr[j];
        ptr[j] = ptr[j + 1];
        ptr[j + 1] = aux;
        encontrou = 1;
      }
    }
    if (!encontrou)
    {
      break;
    }
  }
}

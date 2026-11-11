/*
EXERCICIO 3
Desenvolva um algoritmo em linguagem C que leia 15 números inteiros e armazene-os em um vetor.
  a) Em seguida, o programa deverá identificar quais números aparecem mais de uma vez e contar a quantidade de
ocorrências de cada um.
  b) Para os números que forem primos e apresentarem quantidade ímpar de ocorrências, o programa deverá calcular a
soma de todas as ocorrências daquele número e solicitar ao usuário o cadastro de nomes de animais
correspondentes a essa soma.
  c) Já para os números que apresentarem quantidade par de ocorrências, o programa deverá utilizar a posição que
ocupam no vetor para estabelecer uma correspondência com os nomes dos animais previamente cadastrados pelo
usuário.
  d) Ao final, o programa deverá apresentar os nomes dos animais correspondentes às regras identificadas durante o
processamento.
    d.1) Exemplo de saída:
    Tabela de números e classificações:
    +--------+------------+------------------+
    | Número | Ocorrências| Classificação    |
    +--------+------------+------------------+
    |   3    |     3      | Primo - Ímpar    |
    |   4    |     2      | Par              |
    |   5    |     2      | Primo - Par      |
    |   7    |     3      | Primo - Ímpar    |
    |   8    |     2      | Par              |
    |   6    |     1      | Não repetido     |
    |   9    |     1      | Não repetido     |
    |   2    |     1      | Não repetido     |
    +--------+------------+------------------+

    Animais cadastrados:

    1. Cachorro
    2. Gato
    3. Cavalo
    4. Coelho
    5. Leão
    6. Tigre

    SAÍDA:

    1. Leão.
    2. Não existe correspondência.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int numero;
  int quantidade;
} ContagemNumero;

int ehPrimo(int numero);
int ehPar(int numero);
int calculaQtdAnimais(ContagemNumero *ptr, int tamanhoVetor);

int main()
{
  #define QTD_NUMEROS 15
  int numerosEscolhidos[QTD_NUMEROS];
  int qtdNumerosUnicos = 0;
  ContagemNumero *ptrNumerosUnicos;
  int indiceNumeroUnicoAtual = 0;

  for(int i = 0; i < QTD_NUMEROS; i++)
  {
    printf("Escolha o numero de ordem %d: ", i + 1);
    scanf("%d", &numerosEscolhidos[i]);
  }

  for(int i = 0; i < QTD_NUMEROS; i++)
  {
    int encontrouNumero = 0;
    for(int j = 0; j < i; j++)
    {
      if(numerosEscolhidos[i] == numerosEscolhidos[j])
      {
        encontrouNumero = 1;
        break;
      }
    }
    if(!encontrouNumero)
    {
      qtdNumerosUnicos++;
    }
  }

  if(qtdNumerosUnicos > 0)
  {
    ptrNumerosUnicos = malloc(sizeof(ContagemNumero) * qtdNumerosUnicos);
    if (ptrNumerosUnicos == NULL)
    {
      printf("Erro na alocacao!\n");
      free(ptrNumerosUnicos);
      return 1;
    }
  }

  for(int i = 0; i < QTD_NUMEROS; i++)
  {
    int encontrouNumero = 0;
    for(int j = 0; j < indiceNumeroUnicoAtual; j++)
    {
      if(ptrNumerosUnicos[j].numero == numerosEscolhidos[i])
      {
        encontrouNumero = 1;
        ptrNumerosUnicos[j].quantidade++;
        break;
      }
    }
    if(!encontrouNumero)
    {
      ptrNumerosUnicos[indiceNumeroUnicoAtual].numero = numerosEscolhidos[i];
      ptrNumerosUnicos[indiceNumeroUnicoAtual].quantidade = 1;
      indiceNumeroUnicoAtual++;
    }
  }
}

int ehPrimo(int numero)
{
  if (numero <= 1)
  {
    return 0;
  }

  for(int i = 2; i < numero; i++)
  {
    if (numero % i == 0)
    {
      return 0;
    }
  }

  return 1;
}

int ehPar(int numero)
{
  return numero % 2 == 0;
}

int calculaQtdAnimais(ContagemNumero *ptr, int tamanhoPtr)
{
  int quantidade = 0;
  for(int i = 0; i < tamanhoPtr; i++)
  {
    if(ehPrimo(ptr[i].numero) && !ehPar(ptr[i].quantidade))
    {
      quantidade += ptr[i].quantidade * ptr[i].numero;
    }
  }
  return quantidade;
}
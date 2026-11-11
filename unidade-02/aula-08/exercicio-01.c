/*
EXERCÍCIO 01
Uma equipe está organizando um sorteio beneficente e precisa analisar os números registrados durante o planejamento da
compra dos produtos. Para isso, desenvolva um algoritmo em linguagem C que leia 12 números inteiros e armazene-os em
um vetor. Em seguida, o programa deverá:
  a) Contar quantas vezes cada número aparece no vetor.
  b) Os números cuja quantidade de ocorrências for ímpar representarão as quantidades de produtos que deverão ser
  comprados para o sorteio beneficente.
  c) Os números cuja quantidade de ocorrências for par deverão ser armazenados em um segundo vetor, que deverá ser
  organizado em ordem decrescente.
  d) Para cada número cuja quantidade de ocorrências for ímpar, o programa deverá solicitar o cadastro dos produtos
  que serão comprados, informando o nome e o preço unitário de cada produto
  e) Após o cadastro, os produtos deverão ser apresentados em ordem alfabética pelo nome. Ao final, o programa
  deverá apresentar:
    e.1) Os 12 números informados pelo usuário.
    e.2) Cada número distinto e a quantidade de vezes que aparece no vetor.
    e.3) Os produtos cadastrados para compra, com seus respectivos nomes e preços, organizados em ordem
    alfabética.
    e.4) Os números cuja quantidade de ocorrências seja par, armazenados em um segundo vetor e apresentados em
    ordem decrescente.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int numero;
  int quantidade;
} ContagemNumero;

typedef struct {
  char nome[20];
  float preco;
} Produto;

int ehPar(int numero);
int calcularQtdProdutos(ContagemNumero *ptr, int tamanhoPtr);
int calcularQtdNumerosOcorrenciaPar(ContagemNumero *ptr, int tamanhoPtr);
void ordenaOrdemDecrescente(int *ptr, int tamanhoPtr);
void ordenacaoNomeProdutosOrdemAlfabetica(Produto produtos[], int tamanhoVetor);



int main()
{
  #define QTD_NUMEROS 12
  int numerosEscolhidos[QTD_NUMEROS];
  ContagemNumero *ptrNumerosUnicos;
  int qtdNumerosUnicos = 0;
  int indiceNumerosUnicosAtual = 0;
  int qtdProdutos = 0;
  Produto *ptrListaProdutos;
  int qtdNumerosOcorrenciaPar = 0;
  int indiceNumerosOcorrenciaParAtual = 0;
  int *ptrNumerosOcorrenciaPar;

  printf("===INICIANDO PROGRAMA===\n");

  for (int i = 0; i < QTD_NUMEROS; i++) {
    printf("Escolha o numero de ordem %d: ", i+1);
    scanf("%d", &numerosEscolhidos[i]);
  }

  for(int i = 0; i < QTD_NUMEROS; i++) 
  {
    int encontrouNumero = 0;
    for(int j = 0; j < i; j++) 
    {
      if (numerosEscolhidos[i] == numerosEscolhidos[j])
      {
        encontrouNumero = 1;
        break;
      }
    }
    if (!encontrouNumero)
    {
      qtdNumerosUnicos++;
    }
  }

  ptrNumerosUnicos = ( ContagemNumero * ) malloc( sizeof(ContagemNumero) * qtdNumerosUnicos);

  if (ptrNumerosUnicos == NULL)
  {
    printf("Erro: nao foi possivel alocar memoria.\n");
    return 1;
  }

  for(int i = 0; i < QTD_NUMEROS; i++) 
  {
    int encontrouNumero = 0;
    for (int j = 0; j < indiceNumerosUnicosAtual; j++)
    {
      if (ptrNumerosUnicos[j].numero == numerosEscolhidos[i])
      {
        encontrouNumero = 1;
        ptrNumerosUnicos[j].quantidade++;
        break;
      }
    }
    if(!encontrouNumero) 
    {
      ptrNumerosUnicos[indiceNumerosUnicosAtual].numero = numerosEscolhidos[i];
      ptrNumerosUnicos[indiceNumerosUnicosAtual].quantidade = 1;
      indiceNumerosUnicosAtual++;
    }
  }

  qtdProdutos = calcularQtdProdutos(ptrNumerosUnicos, qtdNumerosUnicos);
  ptrListaProdutos = malloc(sizeof(Produto) * qtdProdutos);

  if (ptrListaProdutos == NULL)
  {
    printf("Erro: nao foi possivel alocar memoria.\n");
    return 1;
  }

  qtdNumerosOcorrenciaPar = calcularQtdNumerosOcorrenciaPar(ptrNumerosUnicos, qtdNumerosUnicos);
  ptrNumerosOcorrenciaPar = malloc(sizeof(int) * qtdNumerosOcorrenciaPar);

  if (ptrNumerosOcorrenciaPar == NULL)
  {
    printf("Erro: nao foi possivel alocar memoria.\n");
    return 1;
  }

  for (int i = 0; i < qtdNumerosUnicos; i++)
  {
    if(ehPar(ptrNumerosUnicos[i].quantidade))
    {
      ptrNumerosOcorrenciaPar[indiceNumerosOcorrenciaParAtual] = ptrNumerosUnicos[i].numero;
      indiceNumerosOcorrenciaParAtual++;
    }
  }

  ordenaOrdemDecrescente(ptrNumerosOcorrenciaPar, qtdNumerosOcorrenciaPar);


  for (int i = 0; i < qtdProdutos; i++)
  {
    printf("\nDigite o nome do Produto %d: ", i + 1);
    scanf("%s", ptrListaProdutos[i].nome);
    printf("\nDigite o preco do Produto %s: ", ptrListaProdutos[i].nome);
    scanf("%f", &ptrListaProdutos[i].preco);
  }

  ordenacaoNomeProdutosOrdemAlfabetica(ptrListaProdutos, qtdProdutos);


  printf("\n===SAIDA DOS VALORES===\n");
  for(int i = 0; i < QTD_NUMEROS; i++)
  {
    printf("Valor %d: %d\n", i + 1, numerosEscolhidos[i]);
  }

  printf("\n===SAIDA DOS VALORES UNICOS E SUAS QUANTIDADES===\n");
  for (int i = 0; i < qtdNumerosUnicos; i++)
  {
    printf("Numero = %d, quantidade = %d\n", ptrNumerosUnicos[i].numero, ptrNumerosUnicos[i].quantidade);
  }

  printf("\n===LISTA DE PRODUTOS E SEUS PRECOS===\n");
  for (int i = 0; i < qtdProdutos; i++)
  {
    printf("Produto = %s, preco = R$ %.2f\n", ptrListaProdutos[i].nome, ptrListaProdutos[i].preco);
  }

  printf("\n===LISTA DOS NUMEROS DE OCORRENCIA PAR EM ORDEM DECRESCENTE===\n");
  for (int i = 0; i < qtdNumerosOcorrenciaPar; i++)
  {
    printf("Numero = %d\n", ptrNumerosOcorrenciaPar[i]);
  }

  free(ptrListaProdutos);
  free(ptrNumerosOcorrenciaPar);
  free(ptrNumerosUnicos);
}

int ehPar(int numero)
{
  return numero % 2 == 0;
}

int calcularQtdProdutos(ContagemNumero *ptr, int tamanhoPtr)
{
  int quantidade = 0;
  for(int i = 0; i < tamanhoPtr; i++) 
  {
    if (!ehPar(ptr[i].quantidade)) 
    {
      quantidade += ptr[i].numero;
    }
  }
  return quantidade;
}

int calcularQtdNumerosOcorrenciaPar(ContagemNumero *ptr, int tamanhoPtr)
{
  int quantidade = 0;
  for(int i = 0; i < tamanhoPtr; i++) 
  {
    if (ehPar(ptr[i].quantidade)) 
    {
      quantidade += 1;
    }
  }
  return quantidade;
}

void ordenaOrdemDecrescente(int *ptr, int tamanhoPtr)
{
  for (int i = 0; i < tamanhoPtr - 1; i++)
  {
    int trocou = 0;
    for (int j = 0; j < tamanhoPtr - 1 - i; j++) {
      if(ptr[j] < ptr[j + 1])
      {
        int aux = ptr[j];
        ptr[j] = ptr[j + 1];
        ptr[j + 1] = aux;
        trocou = 1;
      }
    }

    if(!trocou) {
      break;
    }
  }
}

char transformaParaMinusculo(char caractere)
{
  if( caractere >= 'A' && caractere <= 'Z') {
    return caractere + 32;
  }
  return caractere;
}

void ordenacaoNomeProdutosOrdemAlfabetica(Produto produtos[], int tamanhoVetor)
{
  for(int i = 0; i < tamanhoVetor - 1; i++)
  {
    for(int j = 0; j < tamanhoVetor - 1 - i; j++)
    {
      int indiceCaractere = 0;
      while (
        produtos[j].nome[indiceCaractere] != '\0' &&
        transformaParaMinusculo(produtos[j].nome[indiceCaractere]) == transformaParaMinusculo(produtos[j+1].nome[indiceCaractere])
      )
      {
        indiceCaractere++;
      }

      if(
        transformaParaMinusculo(produtos[j].nome[indiceCaractere]) > 
        transformaParaMinusculo(produtos[j + 1].nome[indiceCaractere])
      )
      {
        Produto aux = produtos[j];
        produtos[j] = produtos[j + 1];
        produtos[j + 1] = aux;
      }
    }
  }
}
/*
Uma equipe está organizando um sorteio beneficente e precisa analisar os números registrados durante o planejamento da compra dos produtos. Para isso, desenvolva um algoritmo em linguagem C que leia 12 números inteiros e armazene-os em um vetor.

Em seguida, o programa deverá contar quantas vezes cada número aparece no vetor. Os números cuja quantidade de ocorrências for ímpar representarão as quantidades de produtos que deverão ser comprados para o sorteio beneficente. Já os números cuja quantidade de ocorrências for par deverão ser armazenados em um segundo vetor, que deverá ser organizado em ordem decrescente.

Para cada número cuja quantidade de ocorrências for ímpar, o programa deverá solicitar o cadastro dos produtos que serão comprados, informando o nome e o preço unitário de cada produto. Após o cadastro, os produtos deverão ser apresentados em ordem alfabética pelo nome.

Ao final, o programa deverá apresentar:

Os 12 números informados pelo usuário.
Cada número distinto e a quantidade de vezes que aparece no vetor.
Os produtos cadastrados para compra, com seus respectivos nomes e preços, organizados em ordem alfabética.
Os números cuja quantidade de ocorrências seja par, armazenados em um segundo vetor e apresentados em ordem decrescente.
Orientações de implementação
Utilize vetores para armazenar os números e os dados dos produtos.
Utilize funções para organizar as diferentes operações do programa.
Utilize estruturas de repetição para percorrer os vetores e realizar os cadastros.
Utilize estruturas condicionais para identificar as quantidades de ocorrências pares e ímpares.
Implemente algoritmos de ordenação para organizar os produtos alfabeticamente e os números em ordem decrescente.
Não utilize ponteiros explicitamente nem alocação dinâmica de memória.
Importante: cada número distinto cuja quantidade de ocorrências seja ímpar deverá ser considerado uma quantidade de produtos a comprar. O programa deverá cadastrar exatamente essa quantidade de produtos para cada número identificado, solicitando o nome e o preço unitário de cada produto.
*/

#include <stdio.h>

#define QTD_CARACTERES 20
#define QTD_NUMEROS 12

typedef struct {
  int numero;
  int quantidade;
} ContadorNumero;

typedef struct {
  char nome[QTD_CARACTERES];
  float precoUnitario;
} Produto;

int ehPar(int numero);
int obterQuantidadesDeProdutosParaCompra(ContadorNumero numerosUnicos[], int tamanhoVetor);
void ordenacaoBubbleDecrescente(int vetor[], int tamanhoVetor);
void ordenacaoNomeProdutosOrdemAlfabetica(Produto vetor[], int tamanhoVetor);

int main() {
  int numeros[QTD_NUMEROS]; // = {2, 7, 8, 5, 3, 2, 3, 2, 8, 7, 5, 5} <==> {2: 3, 7: 2, 8: 2, 5: 3, 3: 2}
  ContadorNumero qtdNumeros[QTD_NUMEROS];
  int numerosOcorrenciaPar[QTD_NUMEROS];
  int numerosUnicosRegistrados = 0;
  int qtdProdutos = 0;
  Produto produtos[QTD_NUMEROS]; /*= {
    {"Arroz", 25.90},
    {"Feijao", 8.50},
    {"Macarrao", 5.99},
    {"Acucar", 4.75},
    {"Cafe", 16.90},
    {"Leite", 5.49},
    {"Biscoito", 3.25}
  }; */
  int qtdNumerosOcorrenciaPar = 0;

  printf("===Comecando o programa===\n");

  for(int i = 0; i < QTD_NUMEROS; i++) {
    printf("Digite o numero: ");
    scanf("%d", &numeros[i]);
  }

  for(int i = 0; i < QTD_NUMEROS; i++) {
    int numeroEncontrado = 0;

    for(int j = 0; j < numerosUnicosRegistrados; j++) {
      if(qtdNumeros[j].numero == numeros[i]) {
        qtdNumeros[j].quantidade += 1;
        numeroEncontrado = 1;
      }
    }

    if(numeroEncontrado == 0) {
      qtdNumeros[numerosUnicosRegistrados].numero = numeros[i];
      qtdNumeros[numerosUnicosRegistrados].quantidade = 1;
      numerosUnicosRegistrados += 1;
    }
  }

  qtdProdutos = obterQuantidadesDeProdutosParaCompra(qtdNumeros, numerosUnicosRegistrados);

  for(int i = 0; i < qtdProdutos; i++) {
    printf("Digite o produto %d: ", i+1);
    scanf(" %s", produtos[i].nome);
    printf("Digite o valor unitario do produto %s em R$: ", produtos[i].nome);
    scanf("%f", &produtos[i].precoUnitario);
  }

  ordenacaoNomeProdutosOrdemAlfabetica(produtos, qtdProdutos);

  printf("===Imprimindo produtos em Ordem Alfabetica===\n");

  for(int i = 0; i < qtdProdutos; i++) {
    printf("Produto %s custa R$%.2f\n", produtos[i].nome, produtos[i].precoUnitario);
  }

  for (int i = 0; i < numerosUnicosRegistrados; i++) {
    if(!ehPar(qtdNumeros[i].quantidade)) {
      numerosOcorrenciaPar[qtdNumerosOcorrenciaPar] = qtdNumeros[i].numero;
      qtdNumerosOcorrenciaPar += 1;
    }
  }

  ordenacaoBubbleDecrescente(numerosOcorrenciaPar, qtdNumerosOcorrenciaPar);

  printf("===Imprimindo numeros de ocorrencia par em ordem decrescente===\n");
  for(int i = 0; i < qtdNumerosOcorrenciaPar; i++) {
    printf("Numero: %d\n", numerosOcorrenciaPar[i]);
  }

}

int ehPar(int numero) {
  return numero % 2 == 0;
}

int obterQuantidadesDeProdutosParaCompra(ContadorNumero numerosUnicos[], int tamanhoVetor) {
  int quantidadeProdutos = 0;
  for(int i = 0; i < tamanhoVetor; i++) {
    if(!ehPar(numerosUnicos[i].quantidade)) {
      quantidadeProdutos += numerosUnicos[i].numero;
    } 
  }
  return quantidadeProdutos;
}

void ordenacaoBubbleDecrescente(int vetor[], int tamanhoVetor) {
  for(int i = 0; i < tamanhoVetor - 1; i++) {
    int fezTroca = 0;
    for(int j = 0; j < tamanhoVetor - 1 - i; j++) {
      if(vetor[j] < vetor[j+1]) {
        int aux = vetor[j];
        vetor[j] = vetor[j+1];
        vetor[j+1] = aux;
        fezTroca = 1;
      }
    }
    if(!fezTroca) {
      break;
    }
  }
}

char paraMinusculo(char caractere) {
  if (caractere >= 'A' && caractere <= 'Z') {
    return caractere + 32;
  }
  return caractere;
}

void ordenacaoNomeProdutosOrdemAlfabetica(Produto produtos[], int tamanhoVetor) {
  for(int i = 0; i < tamanhoVetor - 1; i++) {
    for (int j = 0; j < tamanhoVetor - 1 - i; j++) {
      int indiceCaractere = 0;

      while(
        produtos[j].nome[indiceCaractere] != '\0' && 
        paraMinusculo(produtos[j].nome[indiceCaractere]) == paraMinusculo(produtos[j + 1].nome[indiceCaractere])
      ) {
        indiceCaractere++;
      }
      if (paraMinusculo(produtos[j].nome[indiceCaractere]) > paraMinusculo(produtos[j + 1].nome[indiceCaractere])) {
        Produto aux = produtos[j];
        produtos[j] = produtos[j + 1];
        produtos[j + 1] = aux;
      }
    }
  }
}
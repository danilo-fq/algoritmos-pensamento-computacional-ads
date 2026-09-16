/*
ATIVIDADE 04:
Faça um programa que apresente o seguinte menu:

===== MENU =====
1 - Verificar número par ou ímpar
2 - Verificar se é positivo ou negativo
3 - Calcular o quadrado do número
4 - Sair

- O usuário deverá escolher uma opção e, quando
necessário, informar um número. Utilize switch para
controlar o menu.
- O programa deve tratar também opções inválidas.
- Restrições: na opção 1, além de informar se o
número é par ou ímpar, informe também se ele é
positivo, negativo ou zero.
*/

#include <stdio.h>

void verificaParOuImpar(int numero);
void verificaSinal(int numero);
void calcularQuadrado(int numero);
int escolherNumero();

int main() {
  int opcao;

  printf("===== MENU =====\n");
  printf("1 - Verificar numero par ou impar\n");
  printf("2 - Verificar se e positivo ou negativo\n");
  printf("3 - Calcular o quadrado do numero\n");
  printf("4 - Sair\n");

  printf("Digite sua opcao: ");
  scanf("%d", &opcao);
  int numero;

  switch (opcao) 
  {
    case 1:
      numero = escolherNumero();
      verificaParOuImpar(numero);
      break;
    case 2:
      numero = escolherNumero();
      verificaSinal(numero);
      break;
    case 3:
      numero = escolherNumero();
      calcularQuadrado(numero);
      break; 
    case 4:
      printf("Saindo...\n");
      break;
    default:
      printf("Opcao Invalida!\n");
  }

  return 0;
}

void verificaParOuImpar(int numero) {
  if (numero % 2 == 0) 
  {
    printf("O numero %d e PAR!\n", numero);

    verificaSinal(numero);
  } 
  else 
  {
    printf("O numero %d e IMPAR!\n", numero);

    verificaSinal(numero);
  }
}

void verificaSinal(int numero)
{
  if (numero > 0 )
  {
    printf("O numero %d e POSITIVO!\n", numero);
  }
  else if (numero < 0)
  {
    printf("O numero %d e NEGATIVO!\n", numero);
  }
  else 
  {
    printf("O numero escolhido e Zero!\n", numero);
  }
}

void calcularQuadrado(int numero)
{
  printf("O quadrado do numero %d e: %d\n", numero, numero * numero);
}

int escolherNumero() 
{
  int numeroEscolhido;
  printf("Digite um numero: ");
  scanf("%d", &numeroEscolhido);

  return numeroEscolhido;
}
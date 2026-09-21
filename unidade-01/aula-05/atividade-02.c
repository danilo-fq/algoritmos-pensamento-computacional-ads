/*
ATIVIDADE 02:
Um jovem quer juntar dinheiro e acompanhar o
saldo do seu cofrinho. Faça um programa que
simule um cofrinho digital. 
O usuário pode adicionar moedas de R$0,50, R$1,00 ou R$2,00
quantas vezes quiser. 
Quando decidir parar, o programa deve mostrar o total acumulado
*/

#include <stdio.h>

int main() {
  int querParar = 0;
  float totalAcumulado = 0;

  do {
    int opcao = 0;
    printf("===== MENU =====\n");
    printf("1 - Adicionar dinheiro\n");
    printf("2 - Sair\n\n");

    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
      float deposito;
      printf("Valores validos: R$0,50, R$1,00, R$2,00\n");
      printf("Digite o valor depositado: ");
      scanf("%f", &deposito);

      if (deposito == 0.5 || deposito == 1 || deposito == 2) {
        totalAcumulado += deposito;
        printf("Valor depositado de: R$%.2f\n", deposito);
      } else {
        printf("Valor invalido!\n");
      }
    } else if (opcao == 2) {
      printf("Saindo...\n");
      querParar = 1;
    } else {
      printf("Valor invalido!\n");
      printf("===============\n");
    }
  }
  while (querParar == 0);

  if (totalAcumulado == 0) {
    printf("Sem valores acumulados.\n");
  } else {
    printf("Valor acumulado: R$%.2f\n", totalAcumulado);
  }


  return 0;
}
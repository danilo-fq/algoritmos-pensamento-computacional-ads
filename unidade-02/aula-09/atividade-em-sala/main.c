#include <stdio.h>
#include <stdlib.h>
#include "meuBanco.h"
int main()
{
  Cliente *listaClientes;
  int qtdClientes = 0;
  Cliente *listaClientesAptosEmprestimo;
  int qtdClientesAptosEmprestimo = 0;
  Cliente *listaClientesSaldoNegativo;
  int qtdClientesNegativos = 0;
  char opcao = 's';

  printf("\n===ABRINDO APLICATIVO===\n");

  do 
  {
    printf("Escolha uma opcao:\n");
    printf("a - Abrir Banco\n");
    printf("c - consultar historico\n");
    printf("s - sair\n");
    switch (opcao)
    {
    case 'a':
      printf("Abrindo banco...");
      break;
    case 'c':
      if(qtdClientes > 0)
      {
        printf("===Emitindo Relatorio===\n");
      }
      else
      {
        printf("Banco nao foi aberto\n");
      }
      break;
    default:
      printf("Opcao invalida!\n");
      break;
    }
  } while (opcao != 's');
}
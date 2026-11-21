#include <stdio.h>
#include <stdlib.h>
#include "meuBanco.h"

Cliente clientesTeste[] =
  {
    {"Ana Souza",
      1001,
      0,
      2,
      {
        {CONTA_CORRENTE, 500.00f},
        {CONTA_POUPANCA, 1000.00f}
      },
      {
        {'D', 200.00f},
        {'S', 50.00f},
        {'D', 300.00f},
        {'\0', 0.0f},
        {'\0', 0.0f}
      }
    },

    {
      "Bruno Lima",
      1002,
      0,
      1,
      {{CONTA_CORRENTE, -200.00f}},
      {
        {'D', 500.00f},
        {'S', 700.00f},
        {'D', 100.00f},
        {'S', 50.00f},
        {'D', 80.00f}
      }
    },

    {
      "Carla Mendes",
      1003,
      0,
      1,
      {{CONTA_SALARIO, 1000.00f}},
      {
        {'D', 1000.00f},
        {'S', 200.00f},
        {'D', 300.00f},
        {'S', 100.00f},
        {'D', 50.00f}
      }
    }
  };

int qtdClientesTeste =
    sizeof(clientesTeste) / sizeof(clientesTeste[0]);

int main()
{
  Cliente *listaClientes = NULL;
  Cliente *listaClientesAptosEmprestimo = NULL;
  Cliente *listaClientesSaldoNegativo = NULL;
  Cliente *listaClientesContaSalarioFaixaSaldo = NULL;
  int qtdClientes = 0;
  int qtdClientesAptosEmprestimo = 0;
  int qtdClientesNegativos = 0;
  int qtdClientesContaSalarioFaixaSaldo = 0;
  char opcao = 's';

  qtdClientes = qtdClientesTeste;
  listaClientes = malloc(sizeof(Cliente) * qtdClientes);

  if (listaClientes == NULL)
  {
    printf("Erro ao alocar memoria para os clientes de teste\n");
    return 1;
  }

  for (int i = 0; i < qtdClientes; i++)
  {
    listaClientes[i] = clientesTeste[i];
  }

  printf("\n===ABRINDO APLICATIVO===\n");

  do 
  {
    // if (qtdClientes > 0)
    // {
    //   for(int i = 0; i < qtdClientes; i++)
    //   {
    //     printf("\n===LISTA DE CLIENTES===\n");
    //     printf("CLIENTE %d: \n", i + 1);
    //     printf("Nome: %s \n", listaClientes[i].nome);
    //     printf("Numero Conta: %d \n", listaClientes[i].numeroConta);
    //     for (int j = 0; j < listaClientes[i].qtdContas; j++)
    //     {
    //       printf("Tipo da conta: %s\n", nomeTipoConta(listaClientes[i].contas[j].tipo));
    //     }
    //     printf("Fez Emprestimo: %s\n", nomeFezEmprestimo(listaClientes[i].fezEmprestimo));
    //   }
    // }
    printf("a - Abrir Banco\n");
    printf("c - Emitir Relatorio\n");
    printf("s - Sair\n");
    printf("\nEscolha uma opcao: ");
    scanf(" %c", &opcao);
    switch (opcao)
    {
    case 'a':
      printf("\nAbrindo banco...\n");
      abrirBanco(&listaClientes, &qtdClientes);
      break;
    case 'c':
      int fezAtualizacao = atualizarRelatorios(
        listaClientes,
        qtdClientes,
        &listaClientesAptosEmprestimo,
        &qtdClientesAptosEmprestimo,
        &listaClientesSaldoNegativo,
        &qtdClientesNegativos,
        &listaClientesContaSalarioFaixaSaldo,
        &qtdClientesContaSalarioFaixaSaldo
      );

      if(fezAtualizacao)
      {
        float saldoBanco = calcularSaldoBanco(listaClientes, qtdClientes);
        emitirRelatorio(
          qtdClientes,
          listaClientesAptosEmprestimo,
          qtdClientesAptosEmprestimo,
          listaClientesSaldoNegativo,
          qtdClientesNegativos,
          listaClientesContaSalarioFaixaSaldo,
          qtdClientesContaSalarioFaixaSaldo,
          saldoBanco
        );
      }
      else
      {
        printf("\n[ERRO]: Nao ha clientes cadastrados!\n");
        printf("Voltando para o menu inicial...\n");
      }
      break;
    case 's':
      printf("Fechando o banco\n");
      break;
    default:
      printf("Opcao invalida!\n");
      break;
    }
  } while (opcao != 's');
  free(listaClientesAptosEmprestimo);
  free(listaClientesSaldoNegativo);
  free(listaClientesContaSalarioFaixaSaldo);
  free(listaClientes);

  return 0;
}
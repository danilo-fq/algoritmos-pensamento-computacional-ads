/*Funções*/
#include "meuBanco.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void abrirBanco(Cliente **listaClientes, int *qtdClientes)
{
  char opcaoBanco = 's';
  do
  {
    printf("\nc - Cadastrar Cliente\n");
    printf("s - Voltar para menu principal\n");
    printf("Digite a opcao desejada: ");
    scanf(" %c", &opcaoBanco);
    switch (opcaoBanco)
    {
    case 'c':
    {
      int qtdNovosClientes = -1;
      int verificacaoInput = -1;
      while (qtdNovosClientes <= 0 || verificacaoInput == 0)
      {
        printf("Digite a quantidade de clientes que deseja cadastrar: ");
        verificacaoInput = scanf("%d", &qtdNovosClientes);
        if (qtdNovosClientes <= 0 || verificacaoInput == 0)
        {
          printf("\n[ERRO]: Entrada invalido, digite um numero inteiro maior do que zero!\n");
        }
      }
      int qtdAnterior = *qtdClientes;
      int qtdTotalClientes = qtdAnterior + qtdNovosClientes;

      if (qtdAnterior == 0)
      {
        Cliente *temp = (Cliente *)malloc(sizeof(Cliente) * qtdTotalClientes);

        if (temp == NULL)
        {
          printf("Erro ao alocar memoria na lista de clientes\n");
          break;
        }
        *listaClientes = temp;
      }
      else
      {
        Cliente *temp = (Cliente *)realloc(*listaClientes, sizeof(Cliente) * qtdTotalClientes);
        if (temp == NULL)
        {
          printf("Erro ao alocar memoria na lista de clientes\n");
          break;
        }

        *listaClientes = temp;
      }

      *qtdClientes = qtdTotalClientes;
      cadastrarCliente(*listaClientes, qtdClientes, qtdAnterior);
      break;
    }
    case 's':
      printf("\nVoltando ao menu principal...\n");
      break;
    default:
      printf("\nOpcao invalida!\n");
      break;
    };
  } while (opcaoBanco != 's');
}

void emitirRelatorio(
    int qtdClientes,
    Cliente *listaClientesAptosEmprestimo,
    int qtdClientesAptosEmprestimo,
    Cliente *listaClientesSaldoNegativo,
    int qtdClientesNegativos,
    Cliente *listaClientesContaSalarioFaixaSaldo,
    int qtdClientesContaSalarioFaixaSaldo,
    float saldoBanco)
{
  printf("\n== Saldo Total do banco ==\n");
  printf("%d | R$ %.2f\n", qtdClientes, saldoBanco);

  printf("\n== Clientes Aptos a Empréstimos ==\n");

  for (int i = 0; i < qtdClientesAptosEmprestimo; i++)
  {
    printf(
        "%s|%d-0%d|R$ %.2f\n",
        listaClientesAptosEmprestimo[i].nome,
        listaClientesAptosEmprestimo[i].numeroConta,
        CONTA_POUPANCA,
        calcularLimiteEmprestimo(listaClientesAptosEmprestimo[i]));
  }

  printf("\n== Clientes com Saldo Negativo na Conta Corrente ==\n");
  for (int i = 0; i < qtdClientesNegativos; i++)
  {
    printf(
      "%s|%d-0%d|R$ %.2f\n",
      listaClientesSaldoNegativo[i].nome,
      listaClientesSaldoNegativo[i].numeroConta,
      CONTA_CORRENTE,
      buscaSaldoClientePorTipo(listaClientesSaldoNegativo[i], CONTA_CORRENTE)
    );
  }

  printf("== Clientes Aptos a Compra de Títulos ==\n");

  for (int i = 0; i < qtdClientesContaSalarioFaixaSaldo; i++)
  {
    printf(
        "%s|%d-0%d|R$ %.2f\n",
        listaClientesContaSalarioFaixaSaldo[i].nome,
        listaClientesContaSalarioFaixaSaldo[i].numeroConta,
        CONTA_SALARIO,
        buscaSaldoClientePorTipo(listaClientesContaSalarioFaixaSaldo[i], CONTA_SALARIO));
  }

  printf("== Clientes Contemplado no Sorteio ==\n");
}

int validarTipoConta(TipoConta tipo)
{
  return (
      tipo == CONTA_CORRENTE ||
      tipo == CONTA_POUPANCA ||
      tipo == CONTA_SALARIO);
}

int validarTiposConta(Cliente cliente)
{
  if (cliente.qtdContas <= 0 || cliente.qtdContas > 2)
  {
    printf("\n [ERRO]: Numero de contas invalido. Numero de contas permitidos: 1 ou 2 contas!\n");
    return 0;
  }

  if (
      cliente.qtdContas == 2 &&
      (!validarTipoConta(cliente.contas[0].tipo) ||
      !validarTipoConta(cliente.contas[1].tipo)))
  {
    printf("\n [ERRO]: Uma ou duas opcoes de conta esta(ao) invalido(s)!\n");
    return 0;
  }

  if (cliente.qtdContas == 2 && (cliente.contas[0].tipo == cliente.contas[1].tipo))
  {
    printf("\n [ERRO]: As Contas nao podem ser do mesmo tipo!\n");
    return 0;
  }

  if (cliente.qtdContas == 2 && (cliente.contas[0].tipo != cliente.contas[1].tipo))
  {
    if (
        (cliente.contas[0].tipo == CONTA_CORRENTE && cliente.contas[1].tipo == CONTA_SALARIO) ||
        (cliente.contas[0].tipo == CONTA_SALARIO && cliente.contas[1].tipo == CONTA_CORRENTE))
    {
      printf("\n [ERRO]: Nao eh possivel criar conta corrente e conta salario juntas!\n");
      return 0;
    }
    else
    {
      return 1;
    }
  }

  if (
      !validarTipoConta(cliente.contas[0].tipo))
  {
    printf("\n [ERRO]: Tipo de conta desconhecido, utilize uma das opcoes validas! \n");
    return 0;
  }

  return 1;
}

void cadastrarCliente(Cliente *listaClientes, int *qtdClientes, int indiceAtual)
{
  for (int i = indiceAtual; i < (*qtdClientes); i++)
  {
    Cliente novoCliente = {0};
    int numeroConta = 1000 + i;
    printf("Criando cliente %d:\n", i + 1);
    printf("Nome: ");
    limparBuffer();
    fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin);
    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0';

    printf("Numero da Conta do cliente: %d", numeroConta);
    novoCliente.numeroConta = numeroConta;
    novoCliente.qtdContas = 1;

    int tipoDeConta1 = 0;
    do
    {
      printf("===SELECIONANDO TIPOS DE CONTA===\n");
      printf("1 - CONTA CORRENTE\n");
      printf("2 - CONTA SALARIO\n");
      printf("Selecione o tipo da conta: ");
      scanf("%d", &tipoDeConta1);

      novoCliente.contas[0].tipo = tipoDeConta1;
      novoCliente.contas[0].saldo = 0;
    } while (tipoDeConta1 < 1 || tipoDeConta1 > 2);
      
    int desejaContaPoupanca = 0;

    printf("\nDeseja criar uma CONTA POUPANCA?\n");
    printf("1 - SIM\n");
    printf("2 - NAO\n");
    printf("Opcao: ");
    scanf("%d", &desejaContaPoupanca);

    if (desejaContaPoupanca == 1)
    {
      novoCliente.qtdContas = 2;
      novoCliente.contas[1].tipo = CONTA_POUPANCA;
      novoCliente.contas[1].saldo = 0;
    }
    while (!validarTiposConta(novoCliente));
    
    novoCliente.fezEmprestimo = 0;
    listaClientes[i] = novoCliente;
    printf("Cliente Cadastrado com sucesso!\n");
  }
}


float calcularSaldoBanco(Cliente *listaClientes, int qtdClientes)
{
  float total = 0;
  for (int i = 0; i < qtdClientes; i++)
  {
    for (int j = 0; j < listaClientes[i].qtdContas; j++)
    {
      total += listaClientes[i].contas[j].saldo;
    }
  }
  return total;
}

float buscaSaldoClientePorTipo(Cliente cliente, TipoConta tipo)
{
  float total = 0;
  for (int i = 0; i < cliente.qtdContas; i++)
  {
    if (cliente.contas[i].tipo == tipo)
    {
      total += cliente.contas[i].saldo;
    }
  }
  return total;
}

int podeFazerEmprestimo(Cliente cliente)
{
  if (cliente.fezEmprestimo == 1)
  {
    return 0;
  }

  if (
      cliente.qtdContas == 2)
  {
    if (
        (cliente.contas[0].tipo == CONTA_CORRENTE && cliente.contas[1].tipo == CONTA_POUPANCA) ||
        (cliente.contas[0].tipo == CONTA_POUPANCA && cliente.contas[1].tipo == CONTA_CORRENTE))
    {
      if (
          (cliente.contas[0].tipo == CONTA_POUPANCA && cliente.contas[0].saldo > 0) ||
          (cliente.contas[1].tipo == CONTA_POUPANCA && cliente.contas[1].saldo > 0))
      {
        return 1;
      }
      return 0;
    }
    return 0;
  }
  return 0;
}

float calcularLimiteEmprestimo(Cliente cliente)
{
  if (podeFazerEmprestimo(cliente))
  {
    return 0.25 * 10 * (cliente.contas[0].saldo + cliente.contas[1].saldo);
  }
  return 0;
}

int atualizarRelatorios(
    Cliente *listaClientes,
    int qtdClientes,
    Cliente **listaClientesAptosEmprestimo,
    int *qtdClientesAptosEmprestimo,
    Cliente **listaClientesSaldoNegativo,
    int *qtdClientesSaldoNegativo,
    Cliente **listaClientesContaSalarioFaixaSaldo,
    int *qtdClientesContaSalarioFaixaSaldo)
{
  int indiceAtualEmprestimo = 0;
  int indiceAtualSaldoNegativo = 0;
  int indiceAtualContaSalarioFaixaSaldo = 0;
  *qtdClientesAptosEmprestimo = 0;
  *qtdClientesSaldoNegativo = 0;
  *qtdClientesContaSalarioFaixaSaldo = 0;

  free(*listaClientesAptosEmprestimo);
  free(*listaClientesSaldoNegativo);
  free(*listaClientesContaSalarioFaixaSaldo);

  *listaClientesAptosEmprestimo = NULL;
  *listaClientesSaldoNegativo = NULL;
  *listaClientesContaSalarioFaixaSaldo = NULL;

  if (qtdClientes <= 0)
  {
    return 0;
  }

  for (int i = 0; i < qtdClientes; i++)
  {

    if (podeFazerEmprestimo(listaClientes[i]))
    {
      (*qtdClientesAptosEmprestimo)++;
    }

    for (int j = 0; j < listaClientes[i].qtdContas; j++)
    {
      if (
          listaClientes[i].contas[j].tipo == CONTA_CORRENTE &&
          listaClientes[i].contas[j].saldo < 0)
      {
        (*qtdClientesSaldoNegativo)++;
      }
      if (
          listaClientes[i].contas[j].tipo == CONTA_SALARIO &&
          (listaClientes[i].contas[j].saldo >= 1000 && listaClientes[i].contas[j].saldo <= 1500))
      {
        (*qtdClientesContaSalarioFaixaSaldo)++;
      }
    }
  }

  if (*qtdClientesAptosEmprestimo > 0)
  {
    *listaClientesAptosEmprestimo = (Cliente *)malloc(sizeof(Cliente) * (*qtdClientesAptosEmprestimo));
    if (*listaClientesAptosEmprestimo == NULL)
    {
      printf("[ERRO]: locacao memoria aptos emprestimo\n");
      return 0;
    }
  }

  if (*qtdClientesSaldoNegativo > 0)
  {
    *listaClientesSaldoNegativo = (Cliente *)malloc(sizeof(Cliente) * (*qtdClientesSaldoNegativo));
    if (*listaClientesSaldoNegativo == NULL)
    {
      printf("[ERRO]: locacao memoria lista saldo negativo conta corrente\n");
      return 0;
    }
  }

  if (*qtdClientesContaSalarioFaixaSaldo)
  {
    *listaClientesContaSalarioFaixaSaldo = (Cliente *)malloc(sizeof(Cliente) * (*qtdClientesContaSalarioFaixaSaldo));
    if (*listaClientesContaSalarioFaixaSaldo == NULL)
    {
      printf("[ERRO]: locacao memoria lista conta salario faixa saldo\n");
      return 0;
    }
  }

  for (int i = 0; i < qtdClientes; i++)
  {

    if (podeFazerEmprestimo(listaClientes[i]))
    {
      (*listaClientesAptosEmprestimo)[indiceAtualEmprestimo] = listaClientes[i];
      indiceAtualEmprestimo++;
    }

    for (int j = 0; j < listaClientes[i].qtdContas; j++)
    {
      if (
          listaClientes[i].contas[j].tipo == CONTA_CORRENTE &&
          listaClientes[i].contas[j].saldo < 0)
      {
        (*listaClientesSaldoNegativo)[indiceAtualSaldoNegativo] = listaClientes[i];
        indiceAtualSaldoNegativo++;
      }
      if (
          listaClientes[i].contas[j].tipo == CONTA_SALARIO &&
          (listaClientes[i].contas[j].saldo >= 1000 && listaClientes[i].contas[j].saldo <= 1500))
      {
        (*listaClientesContaSalarioFaixaSaldo)[indiceAtualContaSalarioFaixaSaldo] = listaClientes[i];
        indiceAtualContaSalarioFaixaSaldo++;
      }
    }
  }
  return 1;
}

char *nomeTipoConta(TipoConta tipo)
{
  switch (tipo)
  {
  case CONTA_CORRENTE:
    return "Conta Corrente";
  case CONTA_POUPANCA:
    return "Conta Poupanca";
  case CONTA_SALARIO:
    return "Conta Salario";
  default:
    return "Desconhecida";
  }
}

char *nomeFezEmprestimo(int valor)
{
  if (valor == 1)
    return "Sim";
  return "Nao";
}

void limparBuffer()
{
  int c;

  while ((c = getchar()) != '\n' && c != EOF)
    ;
}
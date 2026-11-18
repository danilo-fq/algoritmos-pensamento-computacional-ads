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
        Cliente *temp = (Cliente *) malloc(sizeof(Cliente) * qtdTotalClientes);
        
        if(temp == NULL)
        {
          printf("Erro ao alocar memoria na lista de clientes\n");
          break;
        }
        *listaClientes = temp;
      }
      else
      {
        Cliente *temp = (Cliente *) realloc(*listaClientes, sizeof(Cliente) * qtdTotalClientes);
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
  float saldoBanco
)
{
  printf("\n============================================================\n");
  printf("                  SISTEMA DE BANCO DIGITAL\n");
  printf("                     RELATORIO GERAL\n");
  printf("============================================================\n");

  printf("\nRESUMO DO BANCO\n");
  printf("------------------------------------------------------------\n");
  printf("Quantidade de clientes cadastrados:  %d.\n", qtdClientes);
  printf("Saldo total do banco:                R$ %.2f.\n", saldoBanco);

  printf("\n1. CLIENTES APTOS A EMPRESTIMO\n");
  printf("------------------------------------------------------------\n");
  printf("Quantidade encontrada: %d\n", qtdClientesAptosEmprestimo);

  for(int i = 0; i < qtdClientesAptosEmprestimo; i++)
  {
    printf("\n Conta: %d | Nome: %s\n", listaClientesAptosEmprestimo[i].numeroConta, listaClientesAptosEmprestimo[i].nome);
    printf("Limite disponivel para emprestimo: R$ %.2f\n\n", calcularLimiteEmprestimo(listaClientesAptosEmprestimo[i]));
  }

  printf("\n2. CLIENTES COM SALDO NEGATIVO\n");
  printf("   EM CONTA CORRENTE\n");
  printf("------------------------------------------------------------\n");
  printf("Quantidade encontrada: %d\n\n", qtdClientesNegativos);

  for(int i = 0; i < qtdClientesNegativos; i++)
  {
    printf("\n Conta: %d | Nome: %s\n", listaClientesSaldoNegativo[i].numeroConta, listaClientesSaldoNegativo[i].nome);
    printf("Saldo na Conta Corrente: R$ %.2f\n\n", buscaSaldoClientePorTipo(listaClientesSaldoNegativo[i], CONTA_CORRENTE));
  }

  printf("3. CLIENTES COM CONTA SALARIO\n");
  printf("   ENTRE R$ 1.000,00 E R$ 1.500,00\n");
  printf("------------------------------------------------------------\n");
  printf("Quantidade encontrada: %d\n\n", qtdClientesContaSalarioFaixaSaldo);

  for(int i = 0; i < qtdClientesContaSalarioFaixaSaldo; i++)
  {
    printf("\n Conta: %d | Nome: %s\n", listaClientesContaSalarioFaixaSaldo[i].numeroConta, listaClientesContaSalarioFaixaSaldo[i].nome);
    printf("Saldo na Conta Salario: R$ %.2f\n\n", buscaSaldoClientePorTipo(listaClientesContaSalarioFaixaSaldo[i], CONTA_SALARIO));
  }

  printf("============================================================\n");
  printf("                    FIM DO RELATORIO\n");
  printf("============================================================\n");
}

int validarTipoConta(TipoConta tipo)
{
  return (
    tipo == CONTA_CORRENTE ||
    tipo == CONTA_POUPANCA ||
    tipo == CONTA_SALARIO
  );
}

int validarTiposConta(Cliente cliente)
{
  if (cliente.qtdContas <= 0 || cliente.qtdContas > 2)
  {
    printf("\n [ERRO]: Numero de contas invalido. Numero de contas permitidos: 1 ou 2 contas!\n");
    return 0;
  }

  if(
    cliente.qtdContas == 2 && 
    (
      !validarTipoConta(cliente.contas[0].tipo) || 
      !validarTipoConta(cliente.contas[1].tipo)
    )
  )
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
    } else
    {
      return 1;
    } 
  }

  if (
    !validarTipoConta(cliente.contas[0].tipo)
  )
  {
    printf("\n [ERRO]: Tipo de conta desconhecido, utilize uma das opcoes validas! \n");
    return 0;
  }

  return 1;
}

void cadastrarCliente( Cliente *listaClientes, int *qtdClientes, int indiceAtual)
{
  for(int i = indiceAtual; i < (*qtdClientes); i++)
  {
    Cliente novoCliente = {0};
    int validacaoNumeroConta = -1;
    printf("Criando cliente %d:\n", i + 1);
    printf("Nome: ");
    limparBuffer();
    fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin);
    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0';
    do
    {
      printf("Numero da Conta: ");
      int numeroConta = 0;
      int contaExistente = 0;
      validacaoNumeroConta = scanf("%d", &numeroConta);
      if(validacaoNumeroConta == 0)
      {
        printf("[ERRO]: Digite um numero de conta valido");
        break;
      }
      for(int j = 0; j < i; j++)
      {
        if (numeroConta == listaClientes[j].numeroConta)
        {
          contaExistente = 1;
          printf("[ERRO]: Numero da Conta existente!\n");
          limparBuffer();
          validacaoNumeroConta = 0;
          continue;
        }
      }
      if(contaExistente != 1)
      {
        novoCliente.numeroConta = numeroConta;
      }
      else
      {
        validacaoNumeroConta = 0;
      }
    } while (validacaoNumeroConta == 0);

    do
    {
      printf("Numero de tipos de conta desejado (max: 2): ");
      int validacaoQtdContas = scanf("%d", &novoCliente.qtdContas);
      if (novoCliente.qtdContas < 1 || novoCliente.qtdContas > 2 || validacaoQtdContas == 0)
      {
        printf("[ERRO]: Valor invalido ou quantidade de tipo de contas nao permitido!\n");
      }
      else
      {
        do
        {
          int validacaoTipoConta1 = 0;
          int validacaoSaldoConta1 = 0;
          do
          {
            printf("===SELECIONANDO TIPOS DE CONTA===\n");
            printf("1 - CONTA CORRENTE\n");
            printf("2 - CONTA POUPANCA\n");
            printf("3 - CONTA SALARIO\n");
            printf("Selecione o tipo da conta: ");
            validacaoTipoConta1 = scanf("%d", &novoCliente.contas[0].tipo);
            if(validacaoTipoConta1 == 0)
            {
              printf("[ERRO]: Opcao invalida para tipo de conta!\n");
              break;
            }
            printf("Digite o saldo da conta: ");
            validacaoSaldoConta1 = scanf("%f", &novoCliente.contas[0].saldo);
            if(validacaoSaldoConta1 == 0)
            {
              printf("[ERRO]: Opcao invalida para saldo de conta!\n");
              break;
            }
          } while (validacaoTipoConta1 == 0 || validacaoSaldoConta1 == 0);

          if (novoCliente.qtdContas == 2)
          {
            int validacaoTipoConta2 = 0;
            int validacaoSaldoConta2 = 0;
            do
            {
              printf("1 - CONTA CORRENTE\n");
              printf("2 - CONTA POUPANCA\n");
              printf("3 - CONTA SALARIO\n");
              printf("Selecione o tipo da segunda conta: ");
              validacaoTipoConta2 = scanf("%d", &novoCliente.contas[1].tipo);
              if (validacaoTipoConta2 == 0)
              {
                printf("[ERRO]: Opcao invalida para tipo de conta!\n");
                break;
              }
              printf("Digite o saldo da segunda conta: ");
              validacaoSaldoConta2 = scanf("%f", &novoCliente.contas[1].saldo);
              if (validacaoSaldoConta2 == 0)
              {
                printf("[ERRO]: Opcao invalida para saldo de conta!\n");
                break;
              }
            } while (validacaoTipoConta2 == 0 || validacaoSaldoConta2 == 0);
          }
        } while (!validarTiposConta(novoCliente));
      }
    } while (
      (novoCliente.qtdContas < 1 || novoCliente.qtdContas > 2)
    );
    novoCliente.fezEmprestimo = 0;
    listaClientes[i] = novoCliente;
  }
}

float calcularSaldoBanco(Cliente *listaClientes, int qtdClientes)
{
  float total = 0;
  for (int i = 0; i < qtdClientes; i++ )
  {
    for(int j = 0; j < listaClientes[i].qtdContas; j++)
    {
      total += listaClientes[i].contas[j].saldo;
    }
  }
  return total;
}

float buscaSaldoClientePorTipo(Cliente cliente, TipoConta tipo)
{
  float total = 0;
  for (int i = 0; i < cliente.qtdContas; i++ )
  {
    if(cliente.contas[i].tipo == tipo)
    {
      total += cliente.contas[i].saldo;
    }
  }
  return total;
}

int podeFazerEmprestimo(Cliente cliente)
{
  if(cliente.fezEmprestimo == 1)
  {
    return 0;
  }

  if(
    cliente.qtdContas == 2 
  )
  {
    if (
      (cliente.contas[0].tipo == CONTA_CORRENTE && cliente.contas[1].tipo == CONTA_POUPANCA) ||
      (cliente.contas[0].tipo == CONTA_POUPANCA && cliente.contas[1].tipo == CONTA_CORRENTE)
    )
    {
      if (
        (cliente.contas[0].tipo == CONTA_POUPANCA && cliente.contas[0].saldo > 0) ||
        (cliente.contas[1].tipo == CONTA_POUPANCA && cliente.contas[1].saldo > 0)
      )
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
  if(podeFazerEmprestimo(cliente))
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
  int *qtdClientesContaSalarioFaixaSaldo
)
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

  if(qtdClientes <= 0)
  {
    return 0;
  }

  for(int i = 0; i < qtdClientes; i++)
  {

    if (podeFazerEmprestimo(listaClientes[i]))
    {
      (*qtdClientesAptosEmprestimo)++;
    }

    for(int j = 0; j < listaClientes[i].qtdContas; j++)
    {
      if(
        listaClientes[i].contas[j].tipo == CONTA_CORRENTE &&
        listaClientes[i].contas[j].saldo < 0
      )
      {
        (*qtdClientesSaldoNegativo)++;
      }
      if (
        listaClientes[i].contas[j].tipo == CONTA_SALARIO &&
        (listaClientes[i].contas[j].saldo >= 1000 && listaClientes[i].contas[j].saldo <= 1500)
      )
      {
        (*qtdClientesContaSalarioFaixaSaldo)++;
      }
    }
  }

  if(*qtdClientesAptosEmprestimo > 0)
  {
    *listaClientesAptosEmprestimo = (Cliente *) malloc(sizeof(Cliente) * (*qtdClientesAptosEmprestimo));
    if(*listaClientesAptosEmprestimo == NULL)
    {
      printf("[ERRO]: locacao memoria aptos emprestimo\n");
      return 0;
    }
  }

  
  if(*qtdClientesSaldoNegativo > 0)
  {
    *listaClientesSaldoNegativo = (Cliente *) malloc(sizeof(Cliente) * (*qtdClientesSaldoNegativo));
    if(*listaClientesSaldoNegativo == NULL)
    {
      printf("[ERRO]: locacao memoria lista saldo negativo conta corrente\n");
      return 0;
    }
  }


  if(*qtdClientesContaSalarioFaixaSaldo)
  {
    *listaClientesContaSalarioFaixaSaldo = (Cliente *) malloc(sizeof(Cliente) * (*qtdClientesContaSalarioFaixaSaldo));
    if(*listaClientesContaSalarioFaixaSaldo == NULL)
    {
      printf("[ERRO]: locacao memoria lista conta salario faixa saldo\n");
      return 0;
    }
  }
  

  for(int i = 0; i < qtdClientes; i++)
  {

    if (podeFazerEmprestimo(listaClientes[i]))
    {
      (*listaClientesAptosEmprestimo)[indiceAtualEmprestimo] = listaClientes[i];
      indiceAtualEmprestimo++;
    }

    for(int j = 0; j < listaClientes[i].qtdContas; j++)
    {
      if(
        listaClientes[i].contas[j].tipo == CONTA_CORRENTE &&
        listaClientes[i].contas[j].saldo < 0
      )
      {
        (*listaClientesSaldoNegativo)[indiceAtualSaldoNegativo] = listaClientes[i];
        indiceAtualSaldoNegativo++;
      }
      if (
        listaClientes[i].contas[j].tipo == CONTA_SALARIO &&
        (listaClientes[i].contas[j].saldo >= 1000 && listaClientes[i].contas[j].saldo <= 1500)
      )
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
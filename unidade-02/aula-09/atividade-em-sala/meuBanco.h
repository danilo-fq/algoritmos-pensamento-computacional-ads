/*Declarações*/
#ifndef MEU_BANCO
#define MEU_BANCO

typedef enum {
  EMPRESTIMO = 1,
  SALDO_NEGATIVO,
  CONTA_SALARIO_FAIXA_SALDO,
} TipoCondicao;

typedef enum {
  CONTA_CORRENTE = 1,
  CONTA_SALARIO,
  CONTA_POUPANCA,
} TipoConta;
typedef struct {
  char tipoTransacao;
  float valor;
} Transacao;

typedef struct {
  TipoConta tipo;
  float saldo;
} Conta;

typedef struct {
  char nome[20];
  int numeroConta;
  int fezEmprestimo;
  int qtdContas;
  Conta contas[2];
  Transacao historico[5];
} Cliente;

void abrirBanco(Cliente **listaClientes, int *qtdClientes);

void emitirRelatorio(
  int qtdClientes,
  Cliente *listaClientesAptosEmprestimo,
  int qtdClientesAptosEmprestimo,
  Cliente *listaClientesSaldoNegativo,
  int qtdClientesNegativos,
  Cliente *listaClientesContaSalarioFaixaSaldo,
  int qtdClientesContaSalarioFaixaSaldo,
  float saldoBanco
);

int atualizarRelatorios(
  Cliente *listaClientes,
  int qtdClientes,
  Cliente **listaClientesAptosEmprestimo,
  int *qtdClientesAptosEmprestimo,
  Cliente **listaClientesSaldoNegativo,
  int *qtdClientesSaldoNegativo,
  Cliente **listaClientesContaSalarioFaixaSaldo,
  int *qtdClientesContaSalarioFaixaSaldo
);

// void fecharArquivo(FILE *arquivo);
// FILE *abrirArquivo(char *caminho, char *modo);
// void lerArquivo(char *caminho);
// FILE *escreverArquivo(char *caminho, char *texto);

int validarTiposConta(Cliente cliente);
int validarTipoConta(TipoConta tipo);
int podeFazerEmprestimo(Cliente cliente);
int calculaQtdClientesCondicao(Cliente *listaClientes, int qtdClientes, TipoCondicao condicao);

float calcularLimiteEmprestimo(Cliente cliente);
float calcularSaldoBanco(Cliente *listaClientes, int qtdClientes);
float buscaSaldoClientePorTipo(Cliente cliente, TipoConta tipo);

void cadastrarCliente(Cliente *listaClientes, int *qtdClientes, int indiceAtual);
void listarClientesAptosEmprestimo(Cliente *listaClientes, int qtdClientes, Cliente *listaClientesAptosEmprestimo);
void listarClientesSaldoNegativo(Cliente *listaClientes, int qtdClientes, Cliente *listaClientesSaldoNegativo);
void listarClientesContaSalarioFaixaSaldo(Cliente *listaClientes, int qtdClientes, Cliente *listaClientesContaSalario);

char *nomeTipoConta(TipoConta tipo);
char *nomeFezEmprestimo(int valor);

void limparBuffer();

#endif

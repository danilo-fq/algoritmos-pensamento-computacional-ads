/*Declarações*/
#ifndef MEU_BANCO
#define MEU_BANCO

typedef struct {

} Cliente;

typedef struct {
  float valor;
  char tipoTransacao;
} historicoCliente;

void cadastrarCliente(Cliente cliente, Cliente *listaClientes);

int podeFazerEmprestimo(float saldoPoupanca, char tipoDeConta[2]);

#endif;
# Aula 04 — Estruturas Condicionais

## Conteúdo

Nesta aula são estudadas as **estruturas condicionais** da linguagem C, utilizadas para analisar condições e controlar o fluxo de execução dos programas.

### Conceitos abordados

* `if`
* `else`
* `else if`
* `switch`
* `case`
* `default`
* Operadores relacionais
* Operadores lógicos
* Expressões condicionais
* Comparações entre valores
* Tomada de decisões

## Atividades

### 01 — Sistema de classificação de triângulos

O programa deve ler três valores inteiros representando os lados de um triângulo e:

* Verificar se os valores podem formar um triângulo;
* Classificar o triângulo como:

  * Equilátero;
  * Isósceles;
  * Escaleno;
* Determinar se o triângulo é:

  * Acutângulo;
  * Retângulo;
  * Obtusângulo;
* Informar quando os valores não formarem um triângulo.

**Restrição:** não utilizar funções prontas para classificação.

**Arquivo:** `exercicio-01.c`

---

### 02 — Sistema de saque em caixa eletrônico

O programa deve simular um caixa eletrônico que possui notas de:

* R$ 200
* R$ 100
* R$ 50
* R$ 20
* R$ 10
* R$ 5

O usuário informa o valor do saque e o programa deve:

* Verificar se o valor é válido;
* Verificar se é possível realizar o saque;
* Determinar quais notas serão entregues;
* Informar a quantidade de cada nota;
* Informar a quantidade total de cédulas.

**Regra adicional:** o caixa deve preservar pelo menos uma nota de cada denominação disponível.

O programa deve decidir se consegue realizar o saque sem violar essa regra.

**Arquivo:** `exercicio-02.c`

---

### 03 — Análise de três valores

O programa deve ler três números inteiros `A`, `B` e `C` e, **sem ordenar os valores e sem utilizar funções auxiliares**, informar:

* Maior valor;
* Menor valor;
* Valor intermediário;
* Se existem valores repetidos;
* Se os três valores são iguais;
* Se estão em ordem crescente;
* Se estão em ordem decrescente.

**Restrição:** resolver utilizando apenas comparações condicionais.

**Arquivo:** `exercicio-03.c`

---

### 04 — Menu de operações

O programa deve apresentar o seguinte menu:

```text
===== MENU =====
1 - Verificar número par ou ímpar
2 - Verificar se é positivo ou negativo
3 - Calcular o quadrado do número
4 - Sair
```

O usuário deverá escolher uma opção e, quando necessário, informar um número.

O controle do menu deve ser realizado utilizando `switch`.

O programa também deve tratar **opções inválidas**.

**Restrição adicional:** na opção 1, além de informar se o número é par ou ímpar, o programa deve informar se ele é:

* Positivo;
* Negativo;
* Zero.

**Arquivo:** `exercicio-04.c`

---

## Objetivos da aula

Ao finalizar as atividades, espera-se praticar:

* Construção de condições utilizando `if`, `else` e `else if`;
* Utilização de operadores relacionais e lógicos;
* Comparação de múltiplos valores;
* Identificação de diferentes possibilidades em um problema;
* Tomada de decisões dentro de algoritmos;
* Utilização de `switch`, `case` e `default`;
* Validação de entradas;
* Implementação de regras e restrições por meio de condições.

## Estrutura dos arquivos

```text
aula-04/
├── README.md
├── exercicio-01.c
├── exercicio-02.c
├── exercicio-03.c
└── exercicio-04.c
```

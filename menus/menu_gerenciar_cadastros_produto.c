#include "menu_gerenciar_cadastros_produto.h"
#include "../structs/produto.h"
#include "../utils/utilidades.h"
#include <stdio.h>

static void imprimirMenu(void);
static void executarOpcaoMenu(char opcao);

extern void MenuGerenciarCadastrosProduto(void) {
  char opcao;

  do {
    imprimirMenu();
    imprimirPrompt();
    opcao = getOpcao();
    executarOpcaoMenu(opcao);
  } while (opcao != '5');
}

static void imprimirMenu(void) {
  limparTela();
  printf("\n========================================\n");
  printf("          MENU PRODUTO\n");
  printf("========================================\n");

  printf("1 - Cadastrar Produto\n");
  printf("2 - Remover Produto\n");
  printf("3 - Atualizar Produto\n");
  printf("4 - Listar Produto\n");
  printf("5 - Voltar\n");
}
static void executarOpcaoMenu(char opcao) {
  // APENAS FUNÇÕES NESSE NÍVEL
  int id;
  switch (opcao) {
  case '1':
    CadastrarProduto();
    break;

  case '2':
    id = pedirId();
    ExcluirProduto(id);
    break;

  case '3':
    id = pedirId();
    EditarProduto(id);
    break;

  case '4':
    ListarProdutos();
    break;

  case '5':
    break;

  default:
    printf("\nOpcao invalida.");
    pausar();
    break;
  }
}

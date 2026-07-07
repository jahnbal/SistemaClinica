#include "menu_gerenciar_cadastros.h"
#include "../utils/utilidades.h"
#include "menu_gerenciar_cadastros_pet.h"
#include "menu_gerenciar_cadastros_produto.h"
#include "menu_gerenciar_cadastros_veterinario.h"
#include <stdio.h>

static void imprimirMenu(void);
static void executarOpcaoMenu(char opcao);

extern void MenuGerenciarCadastros(void) {
  char opcao;

  do {
    imprimirMenu();
    imprimirPrompt();
    opcao = getOpcao();
    executarOpcaoMenu(opcao);
  } while (opcao != '4');
}

static void imprimirMenu(void) {
  limparTela();
  printf("\n========== GERENCIAR CADASTRO ==========\n");
  printf("1 - Pet\n");
  printf("2 - Produto\n");
  printf("3 - Veterinario\n");
  printf("4 - Voltar\n");
}
static void executarOpcaoMenu(char opcao) {
  switch (opcao) {
  case '1':
    MenuGerenciarCadastrosPet();
    break;

  case '2':
    MenuGerenciarCadastrosProduto();
    break;

  case '3':
    MenuGerenciarCadastrosVeterinario();
    break;

  case '4':
    break;

  default:
    printf("\nOpcao invalida.");
    pausar();
    break;
  }
}

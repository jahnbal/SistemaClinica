#include "../structs/veterinario.h"
#include "../utils/utilidades.h"
#include "menu_gerenciar_cadastros.h"
#include "menu_principal.h"
#include "menu_realizar_atendimento.h"
#include <stdio.h>

static void imprimirMenu(void);
static void executarOpcaoMenu(char opcao);

extern void MenuGerenciarCadastrosVeterinario(void) {
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
  printf("        MENU VETERINARIO\n");
  printf("========================================\n");
  printf("1 - Cadastrar Veterinario\n");
  printf("2 - Remover Veterinario\n");
  printf("3 - Atualizar Veterinario\n");
  printf("4 - Listar Veterinarios\n");
  printf("5 - Voltar\n");
}
static void executarOpcaoMenu(char opcao) {
  int id;
  switch (opcao) {
  case '1':
    CadastrarVeterinario();
    break;

  case '2':
    id = pedirId();
    ExcluirVeterinario(id);
    break;

  case '3':
    id = pedirId();
    EditarVeterinario(id);
    break;

  case '4':
    ListarVeterinarios();
    break;

  case '5':
    break;

  default:
    printf("\nOpcao invalida.\n");
    pausar();
  }
}

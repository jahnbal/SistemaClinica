#include "../structs/pet.h"
#include "../structs/produto.h"
#include "../structs/veterinario.h"
#include "../utils/utilidades.h"
#include "menu_gerenciar_cadastros.h"
#include "menu_principal.h"
#include "menu_realizar_atendimento.h"
#include <stdio.h>

static void imprimirMenu(void);
static void executarOpcaoMenu(char opcao);

extern void MenuBuscar(void) {
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
  printf("\n========== BUSCA ==========\n");
  printf("1 - Buscar Pet\n");
  printf("2 - Buscar Veterinario\n");
  printf("3 - Buscar Produto\n");
  printf("4 - Voltar\n");
}
static void executarOpcaoMenu(char opcao) {
  int id;
  switch (opcao) {
  case '1':
    id = pedirId();
    BuscarPetPorId(id);
    break;

  case '2':
    id = pedirId();
    BuscarVeterinarioPorId(id);
    break;

  case '3':
    id = pedirId();
    BuscarProdutoPorId(id);
    break;

  case '4':
    break;

  default:
    printf("\nOpcao invalida.");
    pausar();
    break;
  }
}

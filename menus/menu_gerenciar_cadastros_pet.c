#include "../structs/pet.h"
#include "../utils/utilidades.h"
#include "menu_gerenciar_cadastros.h"
#include "menu_principal.h"
#include "menu_realizar_atendimento.h"
#include <stdio.h>

static void imprimirMenu(void);
static void executarOpcaoMenu(char opcao);

extern void MenuGerenciarCadastrosPet(void) {
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
  printf("            MENU PET\n");
  printf("========================================\n");
  printf("1 - Cadastrar Pet\n");
  printf("2 - Remover Pet\n");
  printf("3 - Atualizar Pet\n");
  printf("4 - Listar Pets\n");
  printf("5 - Voltar\n");
}
static void executarOpcaoMenu(char opcao) {
  // SÓ FUNÇÕES NESSE NÍVEL
  int id;
  switch (opcao) {
  case '1':
    CadastrarPet();
    break;

  case '2':
    id = pedirId();
    ExcluirPet(id);
    break;

  case '3':
    id = pedirId();
    EditarPet(id);
    break;

  case '4':
    ListarPets();
    break;

  case '5':
    break;

  default:
    printf("\nOpcao invalida.\n");
    pausar();
  }
}

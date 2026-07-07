#include "../utils/utilidades.h"
#include "menu_consultas.h"
#include "menu_principal.h"
#include "menu_venda.h"
#include <stdio.h>

static void imprimirMenu(void);
static void executarOpcao(char opcao);

extern void MenuRealizarAtendimento(void) {
  char opcao;

  do {
    imprimirMenu();
    imprimirPrompt();
    opcao = getOpcao();
    executarOpcao(opcao);
  } while (opcao != '3');
}

static void imprimirMenu(void) {
  limparTela();
  printf("\n=============================\n");
  printf("    REALIZAR ATENDIMENTO\n");
  printf("=============================\n");
  printf("1 - Consultas\n");
  printf("2 - Venda\n");
  printf("3 - Voltar\n");
}
static void executarOpcao(char opcao) {
  switch (opcao) {
  case '1':
    MenuConsultas();
    break;

  case '2':
    MenuVenda();
    break;

  case '3':
    break;

  default:
    printf("Opcao invalidada.\n");
    pausar();
    break;
  }
}

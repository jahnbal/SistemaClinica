#include "menu_gerenciar_cadastros_produto.h"
#include "../structs/produto.c"
#include "../utils/utilidades.h"
#include <stdio.h>

/*

MenuPrincipal()
│
├── imprimirMenuPrincipal()
├── obterOpcao()
└── executarOpcaoMenuPrincipal(opcao)


MenuPrincipal() → controla o fluxo do menu.
imprimirMenuPrincipal() → apenas exibe o menu.
obterOpcao() → captura a opção do usuário.
executarOpcaoMenuPrincipal() → decide qual ação executar.


Para cada função MenuX o padrão é esse. MenuPrincipal está de acordo com o
padrão
{
    char opcao;

    do
    {
        imprimirMenuPrincipal();

        opcao = obterOpcao();

        executarOpcaoMenuPrincipal(opcao);

    } while (opcao != '0');

    return 0;
}
*/
static void imprimirMenu(void);
static void executarOpcaoMenu(char opcao);

extern void MenuGerenciarCadastrosProduto(void) {
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
  switch (opcao) {
  case '1':
    CadastrarProduto();
    break;

  case '2':
    // NDO1: funcao que pega IDs;
    ExcluirProduto();
    break;

  case '3':
    // NDO1 : Funcao que pega IDs;
    EditarProduto();
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

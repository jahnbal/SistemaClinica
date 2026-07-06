#include <stdio.h>
#include "menu_cadastrar_produto.h"
#include "../utils/utilidades.h"

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


Para cada função MenuX o padrão é esse. MenuPrincipal está de acordo com o padrão 
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


extern void MenuCadastrarProduto(void)
{
    char opcao;

    do {
        imprimirMenu();
        imprimirPrompt();
        opcao = getOpcao();
        executarOpcaoMenu(opcao);
    } while(opcao != '4');
}

static void imprimirMenu(void)
{
    limparTela();
    printf("\n========================================\n");
    printf("          MENU PRODUTO\n");
    printf("========================================\n");

    printf("1 - Cadastrar Produto\n");
    printf("2 - Remover Produto\n");
    printf("3 - Atualizar Produto\n");
    printf("4 - Voltar\n");
}
static void executarOpcaoMenu(char opcao)
{
    switch(opcao)
    {
        case '1':
//            cadastrarProduto();
            break;

        case '2':
 //           removerProduto();
            break;

        case '3':
 //           atualizarProduto();
            break;

        case '4':
            break;

        default:
            printf("\nOpcao invalida.");
            pausar();
            break;
    }
}


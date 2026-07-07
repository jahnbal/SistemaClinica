#include <stdio.h>
#include "menu_principal.h"
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
static void executarOpcao(char opcao);


extern void MenuVenda(void)
{
    char opcao;

    do {
        imprimirMenu();
        imprimirPrompt();
        opcao = getOpcao();
        executarOpcao(opcao);
    } while(opcao != '3');
}

static void imprimirMenu(void)
{
    limparTela();
    printf("\n=============================\n");
    printf("        VENDA\n");
    printf("=============================\n");
    printf("1 - Adicionar Produto ao Carrinho\n");
    printf("2 - Finalizar Compra\n");
    printf("3 - Voltar\n");
}
static void executarOpcao(char opcao)
{
    switch(opcao)
    {
        case '1':
            // AdicionarProduto ao carrinho
            break;

        case '2':
            // Finalizar Compra
            break;

        case '3':
            break;

        default:
            printf("Opcao invalidada.\n");
            pausar();
            break;
    }
}


#include <stdio.h>
#include "menu_principal.h"
#include "../utils/utilidades.h"
#include "menu_consultas.h"
#include "menu_venda.h"

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


extern void MenuRealizarAtendimento(void)
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
    printf("    REALIZAR ATENDIMENTO\n");
    printf("=============================\n");
    printf("1 - Consultas\n");
    printf("2 - Venda\n");
    printf("3 - Voltar\n");
}
static void executarOpcao(char opcao)
{
    switch(opcao)
    {
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


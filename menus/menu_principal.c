#include <stdio.h>
#include "menu_principal.h"
#include "menu_atendimento.h"
#include "menu_gerenciar_cadastros.h"
#include "../utils/utilidades.h"
#include "menu_buscar.h"

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


extern void MenuPrincipal(void)
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
    printf(" SISTEMA CLINICA VETERINARIA\n");
    printf("========================================\n");

    printf("1 - Realizar Atendimento\n");
    printf("2 - Gerenciar Cadastros\n");
    printf("3 - Busca\n");
    printf("4 - Sair\n");
}
static void executarOpcaoMenu(char opcao)
{
    switch(opcao)
    {
        case '1':
            MenuRealizarAtendimento();
            break;

        case '2':
            MenuGerenciarCadastros();
            break;

        case '3':
            MenuBuscar();
            printf("Voce escolheu a opcao 3");
            break;

        case '4':
            printf("\nEncerrando sistema...\n");
            break;

        default:
            printf("\nOpcao invalida.");
            pausar();
            break;
    }
}


#include <stdio.h>
#include "menu_principal.h"
#include "menu_realizar_atendimento.h"
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


extern void MenuConsultas(void)
{
    char opcao;

    do {
        imprimirMenu();
        imprimirPrompt();
        opcao = getOpcao();
        executarOpcaoMenu(opcao);
    } while(opcao != '6');
}

static void imprimirMenu(void)
{
    limparTela();
    printf("\n=============================\n");
    printf("          CONSULTAS\n");
    printf("=============================\n");
    printf("1 - Agendar Consulta\n");
    printf("2 - Realizar Consulta\n");
    printf("3 - Cancelar Consulta\n");
    printf("4 - Listar Consultas\n");
    printf("5 - Voltar\n");
}
static void executarOpcaoMenu(char opcao)
{
    switch(opcao)
    {
        case '1':
            // Agendar Consulta
            break;

        case '2':
            // Realizar Consulta
            break;

        case '3':
            // Cancelar Consulta
            break;

        case '4':
            // Listar Consultas

        case '5':
            break;

        default:
            printf("\nOpcao invalida.");
            pausar();
            break;
    }
}


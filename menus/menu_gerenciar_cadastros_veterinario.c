#include <stdio.h>
#include "menu_principal.h"
#include "menu_atendimento.h"
#include "menu_gerenciar_cadastros.h"
#include "../utils/utilidades.h"
#include "../structs/veterinario.h"

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


extern void MenuGerenciarCadastrosVeterinario(void)
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
    printf("        MENU VETERINARIO\n");
    printf("========================================\n");
    printf("1 - Cadastrar Veterinario\n");
    printf("2 - Remover Veterinario\n");
    printf("3 - Atualizar Veterinario\n");
    printf("4 - Listar Veterinarios\n");
    printf("5 - Voltar\n");
}
static void executarOpcaoMenu(char opcao)
{
    int id;
    switch (opcao)
    {
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


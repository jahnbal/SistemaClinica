#include <stdlib.h>
#include <stdio.h>
#include "utilidades.h"

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTela(void)
{
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void imprimirPrompt(void)
{
    printf("\n> ");
}

char getOpcao(void)
{
    char opcao = getchar();

    if (opcao != '\n') limparBuffer();

    return opcao;
}

void pausar(void)
{
    printf("\nPressione Enter para continuar...");
    limparBuffer();
}


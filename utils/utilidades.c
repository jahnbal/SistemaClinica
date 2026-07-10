#include "utilidades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limparBuffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void limparTela(void) {
#if defined(_WIN32) || defined(_WIN64)
  system("cls");
#else
  system("clear");
#endif
}

void imprimirPrompt(void) { printf("\n> "); }

char getOpcao(void) {
  char opcao = getchar();

  if (opcao != '\n')
    limparBuffer();

  return opcao;
}

void pausar(void) {
  printf("\nPressione Enter para continuar...");
  limparBuffer();
}

int lerInteiro(void) {
  int valor;
  while (scanf("%d", &valor) != 1) {
    printf("Entrada inválida. Por favor, digite um número inteiro: ");
    limparBuffer();
  }
  limparBuffer(); // Limpa o buffer após a leitura
  return valor;
}

float lerFloat(void) {
  float valor;
  while (scanf("%f", &valor) != 1) {
    printf("Entrada inválida. Por favor, digite um número decimal: ");
    limparBuffer();
  }
  limparBuffer(); // Limpa o buffer após a leitura
  return valor;
}

int pedirId(void) {
  printf("Digite o ID: ");
  return lerInteiro();
}

void lerString(char *buffer, int tamanho) {
  fgets(buffer, tamanho, stdin);
  buffer[strcspn(buffer, "\n")] = '\0';
}

int ContarDigitos(int numero) {
  int contador = 0;

  // Caso especial: se o número for 0, ele tem 1 dígito
  if (numero == 0) {
    return 1;
  }

  // Se o número for negativo, invertemos para positivo
  if (numero < 0) {
    numero = -numero;
  }

  // Loop para dividir o número por 10 até restar zero
  while (numero > 0) {
    numero /= 10; // Remove o último dígito
    contador++;   // Incrementa a contagem
  }

  return contador;
}

#include "pet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consulta.h"
#include "../utils/utilidades.h"

void PedeDadosParaBusca(Consulta *consulta) {
  printf("Data:\n");
  lerString(consulta->data, sizeof(consulta->data));

  printf("Horario:\n");
  consulta->horario = lerInteiro();

  printf("Veterinario(ID):\n");
  consulta->veterinario.id = lerInteiro();
}

void PreencheDadosConsulta(Consulta *nova) {

  printf("Dados para o Agendamento:\n");

  printf("Nome do animal: ");
  lerString(nova->animal.nome, sizeof(nova->animal.nome));

  printf("\n valor: ");
  nova->valor = lerFloat();

  printf("\nData: ");
  lerString(nova->data, sizeof(nova->data));

  printf("\nHorario: ");
  nova->horario = lerInteiro();

  printf("Id da consulta:");
  nova->id = lerInteiro();
}

ListaConsulta *InicializarLista() {

  ListaConsulta *lista = malloc(sizeof(ListaConsulta));

  lista->inicio = NULL;
  lista->tamanho = 0;

  return lista;
}

int InserirConsulta(ListaConsulta *lista, Consulta consulta) {

  NoConsulta *novo = (NoConsulta *)malloc(sizeof(NoConsulta));
  if (novo == NULL) {
    printf("Erro ao alocar memoria para o novo no.\n");
    return 0;
  }

  novo->dados = consulta;
  novo->proximo = lista->inicio;
  lista->inicio = novo;
  lista->tamanho++;

  return 1;
}

int RemoverConsulta(ListaConsulta *lista, Consulta consulta) {
  NoConsulta *atual = lista->inicio;
  NoConsulta *anterior = NULL;

  while (atual != NULL) {
    int mesmaData = (strcmp(atual->dados.data, consulta.data) == 0);
    int mesmoHorario = (atual->dados.horario == consulta.horario);

    // Mesmo criterio usado em VerificarConflito; ajustar o campo
    // de identificacao do veterinario se necessario
    int mesmoVeterinario =
        (atual->dados.veterinario.id == consulta.veterinario.id);

    if (mesmaData && mesmoHorario && mesmoVeterinario) {
      if (anterior == NULL) {
        lista->inicio = atual->proximo;
      } else {
        anterior->proximo = atual->proximo;
      }

      free(atual);
      lista->tamanho--;
      return 1;
    }

    anterior = atual;
    atual = atual->proximo;
  }

  printf("Consulta nao encontrada.\n");
  return 0;
}
int VerificarConflito(ListaConsulta *lista, Consulta consulta) {
  NoConsulta *atual = lista->inicio;

  while (atual != NULL) {
    int mesmaData = (strcmp(atual->dados.data, consulta.data) == 0);
    int mesmoHorario = (atual->dados.horario == consulta.horario);

    // ajustar para o campo que identifica os vets
    int mesmoVeterinario =
        (atual->dados.veterinario.id == consulta.veterinario.id);

    if (mesmaData && mesmoHorario && mesmoVeterinario) {
      return 1; // conflito encontrado
    }

    atual = atual->proximo;
  }

  return 0;
}

Consulta *BuscarConsulta(ListaConsulta *lista, Consulta consulta) {
  NoConsulta *atual = lista->inicio;

  while (atual != NULL) {
    int mesmaData = (strcmp(atual->dados.data, consulta.data) == 0);
    int mesmoHorario = (atual->dados.horario == consulta.horario);

    // ajustar o identificador do vet aqui se for mudar nas outras funcs
    int mesmoVeterinario =
        (atual->dados.veterinario.id == consulta.veterinario.id);

    if (mesmaData && mesmoHorario && mesmoVeterinario) {
      return &(atual->dados);
    }

    atual = atual->proximo;
  }

  return NULL; // nao encontrada
}

void ListarConsultas(ListaConsulta *lista) {
  if (lista == NULL || lista->inicio == NULL) {
    printf("Nenhuma consulta cadastrada.\n");
    return;
  }

  const char *statusStr[] = {"AGENDADA", "EM_ATENDIMENTO", "FINALIZADA",
                             "CANCELADA"};

  NoConsulta *atual = lista->inicio;

  printf("===== LISTA DE CONSULTAS (%d) =====\n", lista->tamanho);

  while (atual != NULL) {
    Consulta c = atual->dados;

    printf("-----------------------------------\n");
    printf("ID: %d\n", c.id);
    printf("Pet: %s\n", c.animal.nome);
    printf("Veterinario: %s\n", c.veterinario.nome);
    printf("Data: %s | Horario: %02dh00\n", c.data, c.horario);
    printf("Valor: R$ %.2f\n", c.valor);
    printf("Status: %s\n", statusStr[c.status]);

    atual = atual->proximo;
  }
  printf("===================================\n");
}

void LiberarLista(ListaConsulta *lista) {
  NoConsulta *atual = lista->inicio;
  NoConsulta *proximo;

  while (atual != NULL) {
    proximo = atual->proximo;
    free(atual);
    atual = proximo;
  }

  lista->inicio = NULL;
  lista->tamanho = 0;
}

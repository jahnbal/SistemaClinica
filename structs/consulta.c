#include "consulta.h"
#include "../utils/utilidades.h"
#include "pet.h"
#include "veterinario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------------------------------------------------------
 * Implementações locais das buscas por ID nos arquivos binários.
 * Centralizar aqui evita duplicação e mantém pet.c / veterinario.c
 * sem alterações estruturais.
 * --------------------------------------------------------------- */

Pet BuscarPet(int id) {
  Pet resultado;
  resultado.id = -1; // sentinela: não encontrado

  FILE *arq = fopen(ARQUIVO_PETS, "rb");
  if (arq == NULL)
    return resultado;

  Pet tmp;
  while (fread(&tmp, sizeof(Pet), 1, arq) == 1) {
    if (tmp.id == id) {
      resultado = tmp;
      break;
    }
  }

  fclose(arq);
  return resultado;
}

Veterinario BuscarVeterinario(int id) {
  Veterinario resultado;
  resultado.id = -1; // sentinela: não encontrado

  FILE *arq = fopen(ARQUIVO_VETS, "rb");
  if (arq == NULL)
    return resultado;

  Veterinario tmp;
  while (fread(&tmp, sizeof(Veterinario), 1, arq) == 1) {
    if (tmp.id == id) {
      resultado = tmp;
      break;
    }
  }

  fclose(arq);
  return resultado;
}

/* ---------------------------------------------------------------
 * Coleta os dados de busca (chave: data + horário + veterinário).
 * --------------------------------------------------------------- */
void PedeDadosParaBusca(Consulta *consulta) {
  printf("Data (DD/MM/AAAA):\n");
  lerString(consulta->data, sizeof(consulta->data));

  printf("Horario (ex: 9 para 09h00):\n");
  consulta->horario = lerInteiro();

  printf("Veterinario (ID):\n");
  consulta->veterinario.id = lerInteiro();
}

/* ---------------------------------------------------------------
 * Preenche todos os dados de uma nova consulta, vinculando as
 * structs Pet e Veterinario reais a partir dos arquivos.
 * --------------------------------------------------------------- */
void PreencheDadosConsulta(Consulta *nova) {
  printf("\n=== Dados para o Agendamento ===\n");

  // --- Vincular Pet ---
  printf("ID do Pet: ");
  int idPet = lerInteiro();

  Pet pet = BuscarPet(idPet);
  if (pet.id == -1) {
    printf("Pet com ID %d nao encontrado. Agendamento cancelado.\n", idPet);
    nova->id = -1; // sinaliza falha para o chamador
    return;
  }
  nova->animal = pet;

  // --- Vincular Veterinário ---
  printf("ID do Veterinario: ");
  int idVet = lerInteiro();

  Veterinario vet = BuscarVeterinario(idVet);
  if (vet.id == -1) {
    printf("Veterinario com ID %d nao encontrado. Agendamento cancelado.\n", idVet);
    nova->id = -1; // sinaliza falha para o chamador
    return;
  }
  nova->veterinario = vet;

  // --- Demais campos ---
  printf("Data (DD/MM/AAAA): ");
  lerString(nova->data, sizeof(nova->data));

  printf("Horario (ex: 9 para 09h00): ");
  nova->horario = lerInteiro();

  printf("Valor: R$ ");
  nova->valor = lerFloat();

  printf("ID da consulta: ");
  nova->id = lerInteiro();

  nova->status = STATUS_AGENDADA;
}

/* ---------------------------------------------------------------
 * Lista encadeada
 * --------------------------------------------------------------- */

void InicializarLista(ListaConsulta **lista) {
  *lista = malloc(sizeof(ListaConsulta));
  if (*lista) {
    (*lista)->inicio = NULL;
    (*lista)->tamanho = 0;
  }
}

int InserirConsulta(ListaConsulta *lista, Consulta consulta) {
  NoConsulta *novo = malloc(sizeof(NoConsulta));
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
    int mesmaData       = (strcmp(atual->dados.data, consulta.data) == 0);
    int mesmoHorario    = (atual->dados.horario == consulta.horario);
    int mesmoVeterinario = (atual->dados.veterinario.id == consulta.veterinario.id);

    if (mesmaData && mesmoHorario && mesmoVeterinario) {
      if (anterior == NULL)
        lista->inicio = atual->proximo;
      else
        anterior->proximo = atual->proximo;

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
    int mesmaData        = (strcmp(atual->dados.data, consulta.data) == 0);
    int mesmoHorario     = (atual->dados.horario == consulta.horario);
    int mesmoVeterinario = (atual->dados.veterinario.id == consulta.veterinario.id);

    if (mesmaData && mesmoHorario && mesmoVeterinario)
      return 1;

    atual = atual->proximo;
  }

  return 0;
}

Consulta *BuscarConsulta(ListaConsulta *lista, Consulta consulta) {
  NoConsulta *atual = lista->inicio;

  while (atual != NULL) {
    int mesmaData        = (strcmp(atual->dados.data, consulta.data) == 0);
    int mesmoHorario     = (atual->dados.horario == consulta.horario);
    int mesmoVeterinario = (atual->dados.veterinario.id == consulta.veterinario.id);

    if (mesmaData && mesmoHorario && mesmoVeterinario)
      return &(atual->dados);

    atual = atual->proximo;
  }

  return NULL;
}

void ListarConsultas(ListaConsulta *lista) {
  if (lista == NULL || lista->inicio == NULL) {
    printf("Nenhuma consulta cadastrada.\n");
    pausar();
    return;
  }

  NoConsulta *atual = lista->inicio;
  printf("===== LISTA DE CONSULTAS (%d) =====\n", lista->tamanho);

  while (atual != NULL) {
    Consulta c = atual->dados;
    const char *statusStr = (c.status & STATUS_FINALIZADA) ? "FINALIZADA" : "AGENDADA";

    printf("-----------------------------------\n");
    printf("ID: %d\n", c.id);
    printf("Pet: %s (ID %d)\n", c.animal.nome, c.animal.id);
    printf("Veterinario: %s (ID %d)\n", c.veterinario.nome, c.veterinario.id);
    printf("Data: %s | Horario: %02dh00\n", c.data, c.horario);
    printf("Valor: R$ %.2f\n", c.valor);
    printf("Status: %s\n", statusStr);

    atual = atual->proximo;
  }
  printf("===================================\n");
  pausar();
}

void SalvarLista(ListaConsulta *lista) {
  FILE *arq = fopen(ARQUIVO_CONSULTAS, "wb"); // wb sobrescreve para manter consistência
  if (arq == NULL) {
    printf("Erro ao abrir arquivo para escrita.\n");
    return;
  }

  NoConsulta *atual = lista->inicio;
  while (atual != NULL) {
    fwrite(&atual->dados, sizeof(Consulta), 1, arq);
    atual = atual->proximo;
  }

  fclose(arq);
}

void CarregarLista(ListaConsulta *lista) {
  FILE *arq = fopen(ARQUIVO_CONSULTAS, "rb");
  if (arq == NULL)
    return; // arquivo ainda não existe, sem erro

  Consulta dados;
  while (fread(&dados, sizeof(Consulta), 1, arq) == 1) {
    NoConsulta *novo = malloc(sizeof(NoConsulta));
    if (novo == NULL) {
      printf("Erro ao alocar memoria.\n");
      break;
    }

    novo->dados = dados;
    novo->proximo = NULL;

    if (lista->inicio == NULL) {
      lista->inicio = novo;
    } else {
      NoConsulta *atual = lista->inicio;
      while (atual->proximo != NULL)
        atual = atual->proximo;
      atual->proximo = novo;
    }

    lista->tamanho++;
  }

  fclose(arq);
}
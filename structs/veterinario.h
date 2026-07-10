#pragma once

#include <stdio.h>

#define ARQUIVO_VETS "veterinarios.dat"
#define TAM_NOME_VETERINARIO 50

// Cadastra/Exclui/Edita/Lista/Pesquisa

typedef struct {

  int id;
  char nome[TAM_NOME_VETERINARIO];

} Veterinario;

void CadastrarVeterinario();

int VerificaIdIgualVeterinario(int id);

int ExcluirVeterinario(int id);

int EditarVeterinario(int id);

int ListarVeterinarios();

int BuscarVeterinarioPorId(int id);

int VerificaIdIgualVeterinario(int id);

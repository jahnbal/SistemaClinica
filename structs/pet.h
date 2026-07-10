#pragma once

#define ARQUIVO_PETS "pets.dat"
#define TAM_NOME_PET 30

typedef struct {
  char nome[TAM_NOME_PET];
  int id;
  int idade;
  float peso;
} Pet;

void CadastrarPet();

int VerificaIdIgualPet(int id);

int ExcluirPet(int id);

int EditarPet(int id);

int ListarPets();

int BuscarPetPorId(int id);

// Retorna o Pet com o id informado; pet.id == -1 se não encontrado
Pet BuscarPet(int id);
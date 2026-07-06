#include "pet.h"
#include <stdio.h>

/*
Cadastra/Exclui/Edita/Lista/Pesquisa


typedef struct {

  char nome[30];
  int id;
  int idade;
  float peso;
  int id_Cliente; // relação de ownership com o cliente

} Pet;
*/

#define ARQUIVO_PETS "pets.dat"

static void preencherPet(Pet *p)
{
    printf("---- NOVO PET ----\n");
    printf("ID: ");
    scanf("%d", &p->id);

    printf("Nome: ");
    scanf("%s", p->nome);

    printf("Idade: ");
    scanf("%d", &p->idade);

    printf("Peso: ");
    scanf("%f", &p->peso);

    printf("ID do Cliente: ");
    scanf("%d", &p->id_Cliente);
}



static int salvarPet(Pet *p)
{
    FILE *arquivo = fopen(ARQUIVO_PETS, "ab");
    if (arquivo == NULL) {
        perror("[Erro] Arquivo não pode ser aberto.\n");
        return 0;
    }

    fwrite(p, sizeof(Pet), 1, arquivo);
    fclose(arquivo);
    printf("Pet salvo com sucesso!\n");
    return 1;
}


void CadastrarPet()
{
    Pet p;
    preencherPet(&p);
    salvarPet(&p);
} 

void ExcluirPet(int id)
{
    
} 

int EditarPet(int id);

int ListarTodosPets(); 

int BuscarPetPorId(int id);
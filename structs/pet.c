#include "pet.h"
#include "../utils/utilidades.h"
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

static void preencherPet(Pet *p) {
  printf("---- NOVO PET ----\n");
  printf("ID: ");
  do {
    p->id = lerInteiro();

  } while (VerificaIdIgualPet(p->id) != 0);

  printf("Nome: ");
  lerString(p->nome, sizeof(p->nome));

  printf("Idade: ");
  p->idade = lerInteiro();

  printf("Peso: ");
  p->peso = lerFloat();

  printf("ID do Cliente: ");
  p->id_Cliente = lerInteiro();
}

int VerificaIdIgualPet(int id) {
  FILE *arquivo = fopen(ARQUIVO_PETS, "rb");
  if (arquivo == NULL) {
    return 0;
  }

  Pet p;

  while (fread(&p, sizeof(Pet), 1, arquivo) == 1) {
    if (p.id == id) {
      printf("Esse id já foi Cadstrado, tente novamnete\n");
      fclose(arquivo);
      return 1;
    }
  }

  fclose(arquivo);
  return 0;
}

static int salvarPet(Pet *p) {
  FILE *arquivo = fopen(ARQUIVO_PETS, "ab");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    pausar();
    return 0;
  }

  fwrite(p, sizeof(Pet), 1, arquivo);
  fclose(arquivo);
  printf("Pet salvo com sucesso!\n");
  return 1;
}

void CadastrarPet() {
  Pet p;
  preencherPet(&p);
  salvarPet(&p);
  limparBuffer();
}

int ExcluirPet(int id) {
  FILE *arquivo = fopen(ARQUIVO_PETS, "rb");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    pausar();
    return 0;
  }

  FILE *temp = fopen("temp.dat", "wb");
  if (temp == NULL) {
    perror("[Erro] Não foi possível criar arquivo temporário.\n");
    pausar();
    fclose(arquivo);
    return 0;
  }

  Pet p;
  int encontrado = 0;

  while (fread(&p, sizeof(Pet), 1, arquivo) == 1) {
    if (p.id == id) {
      encontrado =
          1; // não copia esse pet para o temp (ou seja, ele é "excluído")
      continue;
    }
    fwrite(&p, sizeof(Pet), 1, temp);
  }

  fclose(arquivo);
  fclose(temp);

  remove(ARQUIVO_PETS); // apaga o arquivo original
  rename("temp.dat",
         ARQUIVO_PETS); // renomeia o temporário para o nome original

  if (encontrado) {
    printf("Pet removido com sucesso!\n");
    pausar();
    return 1;
  } else {
    printf("Pet com ID %d não encontrado.\n", id);
    pausar();
    return 0;
  }
}

int EditarPet(int id) {
  FILE *arquivo = fopen(ARQUIVO_PETS, "r+b");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    pausar();
    return 0;
  }

  Pet p;
  int encontrado = 0;
  long posicao;

  while (fread(&p, sizeof(Pet), 1, arquivo) == 1) {
    if (p.id == id) {
      encontrado = 1;
      posicao = ftell(arquivo) - sizeof(Pet);

      printf("---- EDITAR PET (ID: %d) ----\n", p.id);
      printf("Nome atual: %s\n", p.nome);
      printf("Idade atual: %d\n", p.idade);
      printf("Peso atual: %.2f\n", p.peso);
      printf("ID do Cliente atual: %d\n", p.id_Cliente);

      char opcao;
      do {
        printf("\nO que deseja alterar?\n");
        printf("1 - Nome\n");
        printf("2 - Idade\n");
        printf("3 - Peso\n");
        printf("4 - ID do Cliente\n");
        printf("0 - Finalizar edição\n");
        printf("Escolha: ");
        opcao = getOpcao();

        switch (opcao) {
        case '1':
          printf("Novo nome: ");
          lerString(p.nome, sizeof(p.nome));
          break;
        case '2':
          printf("Nova idade: ");
          p.idade =
              lerInteiro(); // p.idade = lerInteiro(); scanf("%d", &p.idade);
          break;
        case '3':
          printf("Novo peso: ");
          p.peso = lerFloat(); // p.peso = lerFloat();
          break;
        case '4':
          printf("Novo ID do Cliente: ");
          p.id_Cliente = lerInteiro(); // p.id_Cliente = lerInteiro();
          break;
        case '0':
          printf("\nFinalizando edição...\n");
          break;
        default:
          printf("Opção inválida!\n");
          pausar();
          break;
        }
      } while (opcao != '0');

      // Sobrescreve o registro no mesmo lugar
      fseek(arquivo, posicao, SEEK_SET);
      fwrite(&p, sizeof(Pet), 1, arquivo);
      break;
    }
  }

  fclose(arquivo);

  if (encontrado) {
    printf("Pet editado com sucesso!\n");
    pausar();
    return 1;
  } else {
    printf("Pet com ID %d não encontrado.\n", id);
    pausar();
    return 0;
  }
}

int ListarPets() {
  FILE *arquivo = fopen(ARQUIVO_PETS, "rb");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    pausar();
    return 0;
  }

  Pet p;
  int contador = 0;

  printf("\n---- LISTA DE PETS ----\n");

  while (fread(&p, sizeof(Pet), 1, arquivo) == 1) {
    contador++;
    printf("\nID: %d\n", p.id);
    printf("Nome: %s\n", p.nome);
    printf("Idade: %d\n", p.idade);
    printf("Peso: %.2f\n", p.peso);
    printf("ID do Cliente: %d\n", p.id_Cliente);
    printf("------------------------\n");
  }

  fclose(arquivo);

  if (contador == 0) {
    printf("Nenhum pet cadastrado.\n");
    pausar();
    return 0;
  }

  printf("Total de pets: %d\n", contador);
  pausar();
  return contador;
}

int BuscarPetPorId(int id) {
  FILE *arquivo = fopen(ARQUIVO_PETS, "rb");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    pausar();
    return 0;
  }

  Pet p;
  int encontrado = 0;

  while (fread(&p, sizeof(Pet), 1, arquivo) == 1) {
    if (p.id == id) {
      encontrado = 1;
      printf("\n---- PET ENCONTRADO ----\n");
      printf("ID: %d\n", p.id);
      printf("Nome: %s\n", p.nome);
      printf("Idade: %d\n", p.idade);
      printf("Peso: %.2f\n", p.peso);
      printf("ID do Cliente: %d\n", p.id_Cliente);
      printf("-------------------------\n");
      pausar();
      break;
    }
  }

  fclose(arquivo);

  if (!encontrado) {
    printf("Pet com ID %d não encontrado.\n", id);
    pausar();
    return 0;
  }

  return 1;
}

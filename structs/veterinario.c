#include "veterinario.h"
#include "../utils/utilidades.h"
#define ARQUIVO_VETS "veterinarios.dat"

static void preencherVeterinario(Veterinario *v) {
  printf("---- NOVO VETERINÁRIO ----\n");

  do {

    printf("ID(5 digitos): ");

    v->id = lerInteiro();

  } while (VerificaIdIgualVeterinario(v->id) == 1 || ContarDigitos(v->id) != 5);

  printf("Nome: ");
  lerString(v->nome, sizeof(v->nome));
}

int VerificaIdIgualVeterinario(int id) {
  FILE *arquivo = fopen(ARQUIVO_VETS, "rb");
  if (arquivo == NULL) {
    return 0;
  }

  Veterinario f;

  while (fread(&f, sizeof(Veterinario), 1, arquivo) == 1) {
    if (f.id == id) {
      fclose(arquivo);
      return 1;
    }
  }

  fclose(arquivo);
  return 0;
}

static int salvarVeterinario(Veterinario *v) {
  FILE *arquivo = fopen(ARQUIVO_VETS, "ab");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    pausar();
    return 0;
  }

  fwrite(v, sizeof(Veterinario), 1, arquivo);
  fclose(arquivo);
  printf("Veterinário salvo com sucesso!\n");
  return 1;
}

void CadastrarVeterinario() {
  Veterinario v;
  preencherVeterinario(&v);
  salvarVeterinario(&v);
  limparBuffer();
}

int ExcluirVeterinario(int id) {
  FILE *arquivo = fopen(ARQUIVO_VETS, "rb");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    pausar();
    return 0;
  }

  FILE *temp = fopen("temp3.dat", "wb");
  if (temp == NULL) {
    perror("[Erro] Não foi possível criar arquivo temporário.\n");
    pausar();
    fclose(arquivo);
    return 0;
  }

  Veterinario v;
  int encontrado = 0;

  while (fread(&v, sizeof(Veterinario), 1, arquivo) == 1) {
    if (v.id == id) {
      encontrado = 1; // não copia esse veterinário para o temp ou seja exlui
      continue;
    }
    fwrite(&v, sizeof(Veterinario), 1, temp);
  }

  fclose(arquivo);
  fclose(temp);

  remove(ARQUIVO_VETS); // apaga o arquivo original
  rename("temp3.dat",
         ARQUIVO_VETS); // renomeia o temporário para o nome original

  if (encontrado) {
    printf("Veterinário removido com sucesso!\n");
    pausar();
    return 1;
  } else {
    printf("Veterinário com ID %d não encontrado.\n", id);
    pausar();
    return 0;
  }
}

int EditarVeterinario(int id) {
  FILE *arquivo = fopen(ARQUIVO_VETS, "r+b");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    pausar();
    return 0;
  }

  Veterinario v;
  int encontrado = 0;
  long posicao;

  while (fread(&v, sizeof(Veterinario), 1, arquivo) == 1) {
    if (v.id == id) {
      encontrado = 1;
      posicao = ftell(arquivo) - sizeof(Veterinario);

      printf("---- EDITAR VETERINÁRIO (ID: %d) ----\n", v.id);
      printf("Nome atual: %s\n", v.nome);
      printf("ID atual: %d\n", v.id);

      char opcao;
      do {
        printf("\nO que deseja alterar?\n");
        printf("1 - Nome\n");
        printf("2 - ID\n");
        printf("0 - Finalizar edição\n");
        printf("Escolha: ");
        opcao = getOpcao();

        switch (opcao) {
        case '1':
          printf("Novo nome: ");
          lerString(v.nome, sizeof(v.nome));
          break;
        case '2':
          printf("Novo ID: ");
          v.id = lerInteiro();
          break;
        case '0':
          printf("Finalizando edição...\n");
          break;
        default:
          printf("Opção inválida!\n");
          break;
        }
      } while (opcao != '0');

      // Sobrescreve o registro no mesmo lugar
      fseek(arquivo, posicao, SEEK_SET);
      fwrite(&v, sizeof(Veterinario), 1, arquivo);
      break;
    }
  }

  fclose(arquivo);

  if (encontrado) {
    printf("Veterinário editado com sucesso!\n");
    pausar();
    return 1;
  } else {
    printf("Veterinário com ID %d não encontrado.\n", id);
    pausar();
    return 0;
  }
}

int ListarVeterinarios() {
  FILE *arquivo = fopen(ARQUIVO_VETS, "rb");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    pausar();
    return 0;
  }

  Veterinario v;
  int contador = 0;

  printf("\n---- LISTA DE VETERINÁRIOS ----\n");

  while (fread(&v, sizeof(Veterinario), 1, arquivo) == 1) {
    contador++;
    printf("\nID: %d\n", v.id);
    printf("Nome: %s\n", v.nome);
    printf("------------------------\n");
  }

  fclose(arquivo);

  if (contador == 0) {
    printf("Nenhum veterinário cadastrado.\n");
    pausar();
    return 0;
  }

  printf("Total de veterinários: %d\n", contador);
  pausar();
  return contador;
}

int BuscarVeterinarioPorId(int id) {
  FILE *arquivo = fopen(ARQUIVO_VETS, "rb");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    pausar();
    return 0;
  }

  Veterinario v;
  int encontrado = 0;

  while (fread(&v, sizeof(Veterinario), 1, arquivo) == 1) {
    if (v.id == id) {
      encontrado = 1;
      printf("\n---- VETERINÁRIO ENCONTRADO ----\n");
      printf("ID: %d\n", v.id);
      printf("Nome: %s\n", v.nome);
      printf("-------------------------\n");
      pausar();
      break;
    }
  }

  fclose(arquivo);

  if (!encontrado) {
    printf("Veterinário com ID %d não encontrado.\n", id);
    pausar();
    return 0;
  }

  return 1;
}

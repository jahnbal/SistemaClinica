#include "veterinario.h"
#define ARQUIVO_VETS "veterinarios.dat"

static void preencherVeterinario(Veterinario *v)
{
    printf("---- NOVO VETERINÁRIO ----\n");
    printf("ID: ");
    scanf("%d", &v->id);

    printf("Nome: ");
    scanf("%s", v->nome);

}


static int salvarVeterinario(Veterinario *v)
{
    FILE *arquivo = fopen(ARQUIVO_VETS, "ab");
    if (arquivo == NULL) {
        perror("[Erro] Arquivo não pode ser aberto.\n");
        return 0;
    }

    fwrite(v, sizeof(Veterinario), 1, arquivo);
    fclose(arquivo);
    printf("Veterinário salvo com sucesso!\n");
    return 1;
}


void CadastrarVeterinario() 
{
    Veterinario v;
    preencherVeterinario(&v);
    salvarVeterinario(&v);
}

int ExcluirVeterinario(int id) {
  FILE *arquivo = fopen(ARQUIVO_VETS, "rb");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    return 0;
  }

  FILE *temp = fopen("temp3.dat", "wb");
  if (temp == NULL) {
    perror("[Erro] Não foi possível criar arquivo temporário.\n");
    fclose(arquivo);
    return 0;
  }

  Veterinario v;
  int encontrado = 0;

  while (fread(&v, sizeof(Veterinario), 1, arquivo) == 1) {
    if (v.id == id) {
      encontrado =
          1; // não copia esse veterinário para o temp (ou seja, ele é "excluído")
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
    return 1;
  } else {
    printf("Veterinário com ID %d não encontrado.\n", id);
    return 0;
  }
}



int EditarVeterinario(int id);

int ListarTodosVeterinarios(); 

int BuscarVeterinarioPorId(int id);
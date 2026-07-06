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

void ExcluirVeterinario(int id); 

int EditarVeterinario(int id);

int ListarTodosVeterinarios(); 

int BuscarVeterinarioPorId(int id);
#include <stdio.h>
#include <string.h>

#define TAM 5
#define MAX_STR 50

typedef struct {
    char nome[MAX_STR];
    char cor[MAX_STR];
    int tropas;
} Territorio;

int main() {
    Territorio mapa[TAM];

    printf("=== Cadastro de Territorios ===\n");

    for (int i = 0; i < TAM; i++) {
        printf("\n--- Territorio %d ---\n", i + 1);

        printf("Nome do territorio: ");
        fgets(mapa[i].nome, MAX_STR, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; 

        printf("Cor do exercito: ");
        fgets(mapa[i].cor, MAX_STR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); 
    }

    printf("\n\n===== ESTADO ATUAL DO MAPA =====\n");

    for (int i = 0; i < TAM; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do exercito: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }

    return 0;
}

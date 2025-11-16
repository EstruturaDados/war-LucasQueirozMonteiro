#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STR 50
#define N 5   

typedef struct {
    char nome[MAX_STR];
    char cor[MAX_STR];
    int tropas;
} Territorio;


void atacar(Territorio *atacante, Territorio *defensor) {
    int dado_atk = rand() % 6 + 1;   // 1 a 6
    int dado_def = rand() % 6 + 1;

    printf("\n\n🎲 Rolando dados...\n");
    printf("Dado atacante (%s): %d\n", atacante->nome, dado_atk);
    printf("Dado defensor (%s): %d\n", defensor->nome, dado_def);

    if (dado_atk >= dado_def) {
        defensor->tropas -= 1;
        printf("💥 Atacante venceu! %s perde 1 tropa.\n", defensor->nome);

        if (defensor->tropas <= 0) {
            printf("🏳️ %s foi conquistado pelo exército %s!\n",
                   defensor->nome, atacante->cor);
            defensor->tropas = 1; 
            strcpy(defensor->cor, atacante->cor);
        }

    } else {
        printf("🛡️ Defensor resistiu! Nenhuma tropa perdida.\n");
    }
}


void exibirMapa(Territorio *mapa) {
    printf("\n===== ESTADO ATUAL DO MAPA =====\n");
    for (int i = 0; i < N; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}


int main() {
    srand(time(NULL));   


    Territorio *mapa = (Territorio*) calloc(N, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    printf("=== Cadastro dos Territórios ===\n");

    for (int i = 0; i < N; i++) {
        printf("\n--- Território %d ---\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, MAX_STR, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do Exército: ");
        fgets(mapa[i].cor, MAX_STR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); 
    }

    int opcao;

    
    do {
        exibirMapa(mapa);

        printf("\n=================================\n");
        printf("Escolha o território atacante (1-5) ou 0 para sair: ");
        scanf("%d", &opcao);

        if (opcao == 0) break;

        int atk = opcao - 1;

        printf("Escolha o território defensor (1-5): ");
        scanf("%d", &opcao);
        int def = opcao - 1;

        getchar();

        if (atk < 0 || atk >= N || def < 0 || def >= N || atk == def) {
            printf("⚠️ Escolha inválida!\n");
            continue;
        }

        atacar(&mapa[atk], &mapa[def]);

    } while (1);

    printf("\nEncerrando...\n");

    free(mapa);

    return 0;
}

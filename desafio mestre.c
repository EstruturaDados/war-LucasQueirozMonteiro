#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 5
#define MAX_STR 50


typedef struct {
    char nome[MAX_STR];
    char cor[MAX_STR];
    int tropas;
} Territorio;

typedef enum {
    MISSAO_DESTRUIR_VERDE = 1,
    MISSAO_CONQUISTAR_3 = 2
} Missao;



void inicializarTerritorios(Territorio *mapa);
void exibirMapa(const Territorio *mapa);
void atacar(Territorio *atacante, Territorio *defensor);
int contarTerritoriosConquistados(const Territorio *mapa, const char *corJogador);
int verificarMissao(const Territorio *mapa, Missao missao, const char *corJogador);

void menu(Territorio *mapa, Missao missao, const char *corJogador);



void inicializarTerritorios(Territorio *mapa) {
    const char *nomes[N] = {
        "Montanhas Geladas",
        "Floresta Negra",
        "Planicie do Sol",
        "Canyon Vermelho",
        "Costa Azul"
    };

    const char *cores[N] = {
        "Vermelho",
        "Verde",
        "Azul",
        "Amarelo",
        "Roxo"
    };

    for (int i = 0; i < N; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);
        mapa[i].tropas = rand() % 6 + 3;
    }
}



void exibirMapa(const Territorio *mapa) {
    printf("\n===== ESTADO ATUAL DO MAPA =====\n");
    for (int i = 0; i < N; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}



void atacar(Territorio *atacante, Territorio *defensor) {
    int dado_atk = rand() % 6 + 1;
    int dado_def = rand() % 6 + 1;

    printf("\n🎲 Rolando dados...\n");
    printf("Atacante (%s): %d\n", atacante->nome, dado_atk);
    printf("Defensor (%s): %d\n", defensor->nome, dado_def);

    if (dado_atk >= dado_def) {
        defensor->tropas--;
        printf("💥 Atacante venceu! %s perdeu 1 tropa.\n", defensor->nome);

        if (defensor->tropas <= 0) {
            printf("🏳️ %s foi conquistado! Nova cor: %s\n",
                   defensor->nome, atacante->cor);
            defensor->tropas = 1;
            strcpy(defensor->cor, atacante->cor);
        }

    } else {
        printf("🛡️ Defesa bem sucedida!\n");
    }
}



int contarTerritoriosConquistados(const Territorio *mapa, const char *corJogador) {
    int cont = 0;
    for (int i = 0; i < N; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0)
            cont++;
    }
    return cont;
}



int verificarMissao(const Territorio *mapa, Missao missao, const char *corJogador) {

    if (missao == MISSAO_DESTRUIR_VERDE) {
        for (int i = 0; i < N; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0)
                return 0; 
        }
        return 1;
    }

    if (missao == MISSAO_CONQUISTAR_3) {
        if (contarTerritoriosConquistados(mapa, corJogador) >= 3)
            return 1;
        return 0;
    }

    return 0;
}



void menu(Territorio *mapa, Missao missao, const char *corJogador) {
    int opcao;

    while (1) {
        printf("\n===== MENU =====\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 0) {
            printf("Encerrando...\n");
            return;
        }

        if (opcao == 1) {
            exibirMapa(mapa);

            int a, d;
            printf("Território atacante (1-5): ");
            scanf("%d", &a);
            printf("Território defensor (1-5): ");
            scanf("%d", &d);

            a--; d--;

            if (a < 0 || a >= N || d < 0 || d >= N || a == d) {
                printf("Escolha inválida.\n");
                continue;
            }

            atacar(&mapa[a], &mapa[d]);
        }

        else if (opcao == 2) {
            printf("\n🔎 Verificando missão...\n");

            if (verificarMissao(mapa, missao, corJogador)) {
                printf("\n🏆 MISSÃO CUMPRIDA! VOCÊ VENCEU!\n");
                return;
            } else {
                printf("\nAinda não cumpriu a missão.\n");
            }
        }
    }
}



int main() {
    srand(time(NULL));

    Territorio *mapa = calloc(N, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    inicializarTerritorios(mapa);

    
    const char *corJogador = "Vermelho";

    Missao missao = (rand() % 2) + 1;

    printf("===== MISSÃO SORTEADA =====\n");
    if (missao == MISSAO_DESTRUIR_VERDE)
        printf("🎯 Missão: Destruir TODO exército Verde!\n");
    else
        printf("🎯 Missão: Conquistar 3 territórios!\n");

    menu(mapa, missao, corJogador);

    free(mapa);
    return 0;
}

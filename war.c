// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 50
#define MAX_COR 20
#define NUM_TERRITORIOS 5

typedef struct  {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} territorio;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 50
#define MAX_COR 20
#define NUM_TERRITORIOS 5

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// --- Protótipos ---
Territorio* alocarMapa();
void inicializarTerritorios(Territorio *mapa);
void liberarMemoria(Territorio *mapa);
void exibirMenuPrincipal();
void exibirMapa(const Territorio *mapa, int n);
void exibirMissao(int missao);
void faseDeAtaque(Territorio *mapa);
void simularAtaque(Territorio *mapa, int atacante, int defensor);
int sortearMissao();
int verificarVitoria(const Territorio *mapa, int missao);
void limparBufferEntrada();

// --- Funções ---
Territorio* alocarMapa() {
    return (Territorio*) calloc(NUM_TERRITORIOS, sizeof(Territorio));
}

void inicializarTerritorios(Territorio *mapa) {
    const char *nomes[NUM_TERRITORIOS] = {"Brasil", "Argentina", "Chile", "Peru", "Colômbia"};
    const char *cores[NUM_TERRITORIOS] = {"Verde", "Azul", "Vermelho", "Amarelo", "Preto"};
    int tropas[NUM_TERRITORIOS] = {3, 2, 4, 3, 2};

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);
        mapa[i].tropas = tropas[i];
    }
}

void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

void exibirMenuPrincipal() {
    printf("\n=== Menu Principal ===\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missão\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

void exibirMapa(const Territorio *mapa, int n) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d: %s | Exército: %s | Tropas: %d\n",
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void exibirMissao(int missao) {
    printf("\n=== Sua Missão ===\n");
    if (missao == 1) {
        printf("Destruir o exército Verde!\n");
    } else {
        printf("Conquistar 3 territórios!\n");
    }
}

void faseDeAtaque(Territorio *mapa) {
    int atacante, defensor;
    exibirMapa(mapa, NUM_TERRITORIOS);
    printf("Escolha atacante (1-5): ");
    scanf("%d", &atacante);
    printf("Escolha defensor (1-5): ");
    scanf("%d", &defensor);
    limparBufferEntrada();
    simularAtaque(mapa, atacante-1, defensor-1);
}

void simularAtaque(Territorio *mapa, int atacante, int defensor) {
    int dadoAtq = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("\nBatalha: %s (Atacante) vs %s (Defensor)\n",
           mapa[atacante].nome, mapa[defensor].nome);
    printf("Dado Atacante: %d | Dado Defensor: %d\n", dadoAtq, dadoDef);

    if (dadoAtq >= dadoDef) {
        mapa[defensor].tropas--;
        printf("Atacante venceu! Defensor perde 1 tropa.\n");
        if (mapa[defensor].tropas <= 0) {
            printf("Território %s foi conquistado!\n", mapa[defensor].nome);
            strcpy(mapa[defensor].cor, mapa[atacante].cor);
            mapa[defensor].tropas = 1;
        }
    } else {
        printf("Defensor resistiu ao ataque.\n");
    }
}

int sortearMissao() {
    return rand() % 2 + 1;
}

int verificarVitoria(const Territorio *mapa, int missao) {
    if (missao == 1) {
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0) {
                return 0;
            }
        }
        return 1;
    } else {
        int conquistas = 0;
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0) {
                conquistas++;
            }
        }
        return conquistas >= 3;
    }
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função Principal ---
int main() {
    srand(time(NULL));
    Territorio *mapa = alocarMapa();
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    inicializarTerritorios(mapa);
    int missao = sortearMissao();
    exibirMissao(missao);

    int opcao;
    do {
        exibirMenuPrincipal();
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch(opcao) {
            case 1:
                faseDeAtaque(mapa);
                exibirMapa(mapa, NUM_TERRITORIOS);
                break;
            case 2:
                if (verificarVitoria(mapa, missao)) {
                    printf("\n🎉 Missão cumprida! Você venceu!\n");
                    opcao = 0;
                } else {
                    printf("\nMissão ainda não concluída.\n");
                }
                break;
            case 0:
                printf("\nEncerrando jogo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while(opcao != 0);

    liberarMemoria(mapa);
    return 0;
}






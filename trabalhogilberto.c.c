#include <stdio.h>

#define process_max 15
#define nome_max 20
#define tempo_limite 1000

typedef struct {
    char nome[nome_max];
    int chegada;
    int duracao;
    int restante;
    int inicio;
    int fim;
    int espera;
    int retorno;
} Processo;


int nomes_iguais(char a[], char b[]) {
    for (int i = 0; i < nome_max; i++) {
        if (a[i] != b[i]) return 0;
        if (a[i] == '\0') return 1;
    }
    return 1;
}


void copiar_nome(char destino[], char origem[]) {
    int i = 0;
    while (origem[i] != '\0' && i < nome_max - 1) {
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0';
}


void ordenar_por_chegada(Processo processos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processos[j].chegada > processos[j + 1].chegada) {
                Processo temp = processos[j];
                processos[j] = processos[j + 1];
                processos[j + 1] = temp;
            }
        }
    }
}

void escalonador_srtf(Processo processos[], int total) {
    if (total < 2 || total > 15) {
        printf("Número de processos deve estar entre 2 e 15.\n");
        return;
    }

    ordenar_por_chegada(processos, total);

    char linha_tempo[1000][nome_max];
    int tempo_atual = 0, concluido = 0, tempo_total = 0;

    for (int i = 0; i < total; i++) {
        processos[i].restante = processos[i].duracao;
        processos[i].inicio = -1;
    }

    while (concluido < total) {
        int indice_exec = -1;
        int menor_restante = tempo_limite + 1;

        for (int i = 0; i < total; i++) {
            if (processos[i].chegada <= tempo_atual && processos[i].restante > 0) {
                if (processos[i].restante < menor_restante) {
                    menor_restante = processos[i].restante;
                    indice_exec = i;
                }
            }
        }

        if (indice_exec == -1) {
            copiar_nome(linha_tempo[tempo_total++], "ID");
            tempo_atual++;
            continue;
        }

        if (processos[indice_exec].inicio == -1) {
            processos[indice_exec].inicio = tempo_atual;
        }

        copiar_nome(linha_tempo[tempo_total++], processos[indice_exec].nome);
        processos[indice_exec].restante--;
        tempo_atual++;

        if (processos[indice_exec].restante == 0) {
            processos[indice_exec].fim = tempo_atual;
            processos[indice_exec].retorno = processos[indice_exec].fim - processos[indice_exec].chegada;
            processos[indice_exec].espera = processos[indice_exec].retorno - processos[indice_exec].duracao;
            concluido++;
        }
    }

    printf("\n============\n");
    printf("Tempo:  ");
    for (int t = 0; t < tempo_total; t++) {
        printf("%2d ", t);
    }
    printf("\n        ");
    for (int t = 0; t < tempo_total; t++) {
        printf("%2s ", linha_tempo[t]);
    }

    printf("\n\n=== RESUMO DOS PROCESSOS ===\n");
    printf("%-10s %-8s %-8s %-8s %-8s\n", "Processo", "Chegada", "Duração", "Espera", "Retorno");
    for (int i = 0; i < total; i++) {
        printf("%-10s %-8d %-8d %-8d %-8d\n",
               processos[i].nome, processos[i].chegada, processos[i].duracao,
               processos[i].espera, processos[i].retorno);
    }
}

int nome_duplicado(Processo processos[], int n, char* nome) {
    for (int i = 0; i < n; i++) {
        if (nomes_iguais(processos[i].nome, nome)) return 1;
    }
    return 0;
}

int capturar_processos(Processo processos[]) {
    int qtd;

    while (1) {
        printf("Digite o número de processos (entre 2 e 15): ");
        if (scanf("%d", &qtd) != 1 || qtd < 2 || qtd > 15) {
            printf("Número fora do intervalo ou entrada inválida.\n");
            while (getchar() != '\n'); // limpar buffer
        } else {
            break;
        }
    }

    for (int i = 0; i < qtd; i++) {
        printf("\nProcesso %d:\n", i + 1);

        while (1) {
            printf("  Nome: ");
            scanf("%s", processos[i].nome);

            if (processos[i].nome[0] == '\0' || nome_duplicado(processos, i, processos[i].nome)) {
                printf("  Nome inválido ou duplicado. Tente outro.\n");
            } else {
                break;
            }
        }

        while (1) {
            printf("  Tempo de chegada (≥ 0): ");
            printf("  Tempo de duração (> 0): ");
            if (scanf("%d %d", &processos[i].chegada, &processos[i].duracao) != 2 ||
                processos[i].chegada < 0 || processos[i].duracao <= 0 ||
                processos[i].chegada > tempo_limite || processos[i].duracao > tempo_limite) {
                printf("  Valores inválidos. Reinsira.\n");
                while (getchar() != '\n'); 
            } else {
                break;
            }
        }
    }

    return qtd;
}

int main() {
    Processo processos[process_max];
    int total = capturar_processos(processos);
    escalonador_srtf(processos, total);
    return 0;
}

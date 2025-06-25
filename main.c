#include <stdio.h>

#define MAX 15
#define QUANTUM 2

int main() {
    int n;
    char nome[MAX];
    int chegada[MAX], duracao[MAX], restante[MAX], finalizado[MAX];

    printf("Quantos processos (2 a 15)? ");
    scanf("%d", &n);

    if (n < 2 || n > MAX) {
        printf("Número inválido.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        nome[i] = 'A' + i;
        printf("\nProcesso %c:\n", nome[i]);

        printf("Tempo de chegada: ");
        scanf("%d", &chegada[i]);

        printf("Tempo de processamento: ");
        scanf("%d", &duracao[i]);

        restante[i] = duracao[i];
        finalizado[i] = 0;
    }

    int tempo = 0;
    int concluidos = 0;

    printf("\n=== Timeline ===\n");

    while (concluidos < n) {
        int executou = 0;

        for (int i = 0; i < n; i++) {
            if (chegada[i] <= tempo && restante[i] > 0) {
                int tempoExec = (restante[i] < QUANTUM) ? restante[i] : QUANTUM;

                for (int t = 0; t < tempoExec; t++) {
                    printf("Tempo %d: %c\n", tempo, nome[i]);
                    tempo++;
                }

                restante[i] -= tempoExec;

                if (restante[i] == 0) {
                    finalizado[i] = 1;
                    concluidos++;
                }

                executou = 1;
            }
        }

        if (!executou) {
            printf("Tempo %d: [CPU Ociosa]\n", tempo);
            tempo++;
        }
    }

    printf("\nTodos os processos foram finalizados.\n");

    return 0;
}

#include <stdio.h>

#define MAX 15
#define NOME_MAX 20

int main() {
    char nomes[MAX][NOME_MAX];
    int chegada[MAX];
    int duracao[MAX];
    int restante[MAX];
    int inicio[MAX];
    int fim[MAX];
    int espera[MAX];
    int retorno[MAX];
    char linha_tempo[1000][NOME_MAX];

    int n;

    printf("Quantos processos (2 a 15)? ");
    scanf("%d", &n);

    while (n < 2) {
        printf("Mínimo é 2. Digite novamente: ");
        scanf("%d", &n);
    }

    while (n > MAX) {
        printf("Máximo é 15. Digite novamente: ");
        scanf("%d", &n);
    }

    // Entrada dos processos
    int i = 0;
    while (i < n) {
        printf("\nProcesso %d:\n", i + 1);

        printf("  Nome: ");
        scanf("%s", nomes[i]);

        printf("  Tempo de chegada: ");
        scanf("%d", &chegada[i]);

        printf("  Tempo de duracao: ");
        scanf("%d", &duracao[i]);

        restante[i] = duracao[i];
        inicio[i] = -1;
        i++;
    }

    // Execução
    int tempo = 0;
    int total = 0;
    int finalizados = 0;

    while (finalizados < n) {
        int menor = 100000;
        int escolhido = -1;

        int j = 0;
        while (j < n) {
            if (chegada[j] <= tempo && restante[j] > 0 && restante[j] < menor) {
                menor = restante[j];
                escolhido = j;
            }
            j++;
        }

        if (escolhido == -1) {
            // Copiar "ID" para linha_tempo[total]
            linha_tempo[total][0] = 'I';
            linha_tempo[total][1] = 'D';
            linha_tempo[total][2] = '\0';
            tempo++;
            total++;
        } else {
            if (inicio[escolhido] == -1) {
                inicio[escolhido] = tempo;
            }

            // Copiar nomes[escolhido] para linha_tempo[total]
            int k = 0;
            while (nomes[escolhido][k] != '\0' && k < NOME_MAX - 1) {
                linha_tempo[total][k] = nomes[escolhido][k];
                k++;
            }
            linha_tempo[total][k] = '\0';

            restante[escolhido]--;
            tempo++;
            total++;

            if (restante[escolhido] == 0) {
                fim[escolhido] = tempo;
                retorno[escolhido] = fim[escolhido] - chegada[escolhido];
                espera[escolhido] = retorno[escolhido] - duracao[escolhido];
                finalizados++;
            }
        }
    }

    // Exibir linha do tempo
    printf("\nTempo:  ");
    i = 0;
    while (i < total) {
        printf("%2d ", i);
        i++;
    }

    printf("\n       ");
    i = 0;
    while (i < total) {
        printf("%2s ", linha_tempo[i]);
        i++;
    }

    // Exibir resumo
    printf("\n\nResumo:\n");
    printf("Nome\tChegada\tDuracao\tEspera\tRetorno\n");
    i = 0;
    while (i < n) {
        printf("%s\t%d\t\t%d\t\t%d\t%d\n",
               nomes[i], chegada[i], duracao[i], espera[i], retorno[i]);
        i++;
    }

    return 0;
}

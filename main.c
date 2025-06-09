#include <stdio.h> // Biblioteca padrão para entrada e saída (printf, scanf)

#define MAX 15      // Definimos o número máximo de processos como 15
#define QUANTUM 2   // Quantum do Round Robin: cada processo roda no máximo 2 unidades de tempo por vez

int main() {
    int n; // Número de processos informados pelo usuário

    // Vetor de caracteres para armazenar o nome de cada processo (ex: 'A', 'B', 'C'...)
    char nome[MAX];

    // Vetores para armazenar:
    // - tempo de chegada,
    // - tempo total de execução (duração),
    // - tempo restante para terminar,
    // - status de finalização (0 = ainda rodando, 1 = finalizado)
    int chegada[MAX], duracao[MAX], restante[MAX], finalizado[MAX];

    // Solicita ao usuário quantos processos ele quer inserir (entre 2 e 15)
    printf("Quantos processos (2 a 15)? ");
    scanf("%d", &n);

    // Verifica se o número é válido; se não for, encerra o programa com erro
    if (n < 2 || n > MAX) {
        printf("Número inválido.\n");
        return 1;
    }

    // Loop para coletar os dados de cada processo
    for (int i = 0; i < n; i++) {
        // O nome do processo será uma letra sequencial: A, B, C...
        nome[i] = 'A' + i;
        printf("\nProcesso %c:\n", nome[i]);

        // Solicita o tempo de chegada do processo
        printf("Tempo de chegada: ");
        scanf("%d", &chegada[i]);

        // Solicita o tempo de execução (duração)
        printf("Tempo de processamento: ");
        scanf("%d", &duracao[i]);

        // Inicializa o tempo restante com o mesmo valor da duração
        restante[i] = duracao[i];

        // Marca que o processo ainda não foi finalizado
        finalizado[i] = 0;
    }

    // Variável para contar o tempo global do sistema (vai de 0 até o final)
    int tempo = 0;

    // Flag que indica se todos os processos já foram concluídos (0 = não, 1 = sim)
    int todosConcluidos = 0;

    // Imprime o cabeçalho da timeline
    printf("\n=== Timeline ===\n");

    // Loop principal do Round Robin: roda enquanto ainda houver processos não concluídos
    while (!todosConcluidos) {
        todosConcluidos = 1; // Assume que todos foram concluídos (vamos verificar abaixo)
        int algumExecutou = 0; // Flag para saber se algum processo rodou nesse ciclo

        // Percorre todos os processos para ver quem pode rodar agora
        for (int i = 0; i < n; i++) {
            // Se o processo já chegou (chegada <= tempo atual) e ainda tem tempo restante
            if (chegada[i] <= tempo && restante[i] > 0) {
                // Marca que ainda há processos para executar
                todosConcluidos = 0;

                // Decide quanto tempo o processo vai rodar agora (máximo QUANTUM ou o tempo restante)
                int tempoExec = (restante[i] < QUANTUM) ? restante[i] : QUANTUM;

                // Executa o processo por tempoExec unidades de tempo
                for (int t = 0; t < tempoExec; t++) {
                    // Mostra que o processo está rodando nesse tempo
                    printf("Tempo %d: %c\n", tempo, nome[i]);
                    tempo++; // Avança o tempo global do sistema
                }

                // Reduz o tempo restante do processo
                restante[i] -= tempoExec;

                // Se o tempo restante chegou a 0, o processo foi finalizado
                if (restante[i] == 0) {
                    finalizado[i] = 1; // Marca como finalizado
                }

                // Marca que algum processo foi executado nesse ciclo
                algumExecutou = 1;
            }
        }

        // Se nenhum processo rodou nesse tempo (CPU ociosa), avança o tempo
        if (!algumExecutou) {
            printf("Tempo %d: [CPU Ociosa]\n", tempo);
            tempo++; // Avança o tempo mesmo que nada esteja rodando
        }
    }

    // Após sair do loop, todos os processos terminaram
    printf("\nTodos os processos foram finalizados.\n");

    return 0; // Fim do programa
}
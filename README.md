// TrabalhoSO
// Nosso projeto foi criado como uma simulação do algoritmo de escalonamento **SRTF (Shortest Remaining Time First)**, usado em sistemas operacionais para decidir qual processo a CPU deve executar em determinado momento.

// As principais etapas do desenvolvimento foram:

// 1. Entrada de Dados:
  // - O usuário fornece os processos, com nome, tempo de chegada e duração.
  // - Foram adicionadas validações para evitar nomes duplicados, tempos negativos e entradas inválidas.

// 2. Lógica do SRTF:
  // - Os processos são ordenados por tempo de chegada.
  // - A cada unidade de tempo, o processo com o menor tempo restante é executado.
  // - Se não há processos disponíveis, o sistema entra em estado ocioso ("IDLE").

// 3. **Geração do Gráfico de Gantt:**
  // - Uma linha do tempo é exibida mostrando quais processos foram executados em cada unidade de tempo.

// 4. Cálculo de métricas:
   // - São calculados os tempos de espera e de retorno (turnaround) para cada processo.

// 5. Tratamento de Erros:
  // - Impede entradas inválidas como tempos negativos, duração zero e nomes repetidos.

 // O projeto foi totalmente escrito em C, sem bibliotecas externas, com foco em lógica, clareza e simulação fiel do algoritmo SRTF.
 // Feito por Ana, Ludimila, Iago e Gabriel


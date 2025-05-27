# TrabalhoSO
# Nosso projeto foi criado como uma simulação do algoritmo de escalonamento **SRTF (Shortest Remaining Time First)**, usado em sistemas operacionais para decidir qual processo a CPU deve executar em determinado momento.

# As principais etapas do desenvolvimento foram:

# 1. Entrada de Dados:
  # - O usuário fornece os processos, com nome, tempo de chegada e duração.
  # - Foram adicionadas validações para evitar nomes duplicados, tempos negativos e entradas inválidas.

# 2. Lógica do SRTF:
  # - Os processos são ordenados por tempo de chegada.
  # - A cada unidade de tempo, o processo com o menor tempo restante é executado.
  # - Se não há processos disponíveis, o sistema entra em estado ocioso ("IDLE").

# 3. **Geração do Gráfico de Gantt:**
  # - Uma linha do tempo é exibida mostrando quais processos foram executados em cada unidade de tempo.

# 4. Cálculo de métricas:
   # - São calculados os tempos de espera e de retorno (turnaround) para cada processo.

# 5. Tratamento de Erros:
   # - O código trata exceções como `ValueError` e `EOFError`.
   # - Impede entradas inválidas como tempos negativos, duração zero e nomes repetidos.

 # O projeto foi totalmente escrito em C, sem bibliotecas externas, com foco em lógica, clareza e simulação fiel do algoritmo SRTF.
 # Feito por Ana, Ludimila, Iago e Gabriel

def escalonador_srtf(processos):
    total_processos = len(processos)
    if total_processos < 2 or total_processos > 15:
        print("Número de processos deve estar entre 2 e 15.")
        return

    #processos por tempo de chegada
    processos.sort(key=lambda p: p[1])

    nomes = [p[0] for p in processos]
    chegada = [p[1] for p in processos]
    duracao = [p[2] for p in processos]

    restante = duracao[:]
    concluido = 0
    tempo_atual = 0
    linha_tempo = []
    inicio = [-1] * total_processos
    fim = [0] * total_processos
    espera = [0] * total_processos
    retorno = [0] * total_processos

    while concluido < total_processos:
        indice_exec = -1
        menor_restante = float('inf')

        for i in range(total_processos):
            if chegada[i] <= tempo_atual and restante[i] > 0:
                if restante[i] < menor_restante:
                    menor_restante = restante[i]
                    indice_exec = i

        if indice_exec == -1:
            linha_tempo.append("ID")
            tempo_atual += 1
            continue

        if inicio[indice_exec] == -1:
            inicio[indice_exec] = tempo_atual

        linha_tempo.append(nomes[indice_exec])
        restante[indice_exec] -= 1
        tempo_atual += 1

        if restante[indice_exec] == 0:
            concluido += 1
            fim[indice_exec] = tempo_atual
            retorno[indice_exec] = fim[indice_exec] - chegada[indice_exec]
            espera[indice_exec] = retorno[indice_exec] - duracao[indice_exec]

    #grafico
    print("\n============")
    print("Tempo: ", " ".join(f"{t:2}" for t in range(len(linha_tempo))))
    print("       ", " ".join(f"{p:2}" for p in linha_tempo))

    # Resumo dos processos
    print("\n=== RESUMO DOS PROCESSOS ===")
    print(f"{'Processo':10} {'Chegada':8} {'Duração':8} {'Espera':8} {'Retorno':8}")
    for i in range(total_processos):
        print(f"{nomes[i]:10} {chegada[i]:8} {duracao[i]:8} {espera[i]:8} {retorno[i]:8}")


def capturar_processos():
    lista_processos = []
    nomes_usados = set()
    LIMITE_TEMPO = 1000

    while True:
        try:
            qtd = int(input("Digite o número de processos (entre 2 e 15): "))
            if 2 <= qtd <= 15:
                break
            else:
                print("Número fora do intervalo permitido.")
        except (ValueError, EOFError):
            print("Entrada inválida. Digite um número inteiro.")

    for i in range(qtd):
        print(f"\nProcesso {i + 1}:")
        while True:
            nome = input("  Nome: ").strip()
            if not nome:
                print("  O nome não pode estar vazio.")
            elif nome in nomes_usados:
                print("  Nome duplicado. Escolha um nome único.")
            else:
                nomes_usados.add(nome)
                break

        while True:
            try:
                chegada = int(input("  Tempo de chegada (≥ 0): "))
                duracao = int(input("  Tempo de duração (> 0): "))
                if chegada < 0 or duracao <= 0:
                    print("  Os valores devem ser positivos e a duração maior que 0.")
                elif chegada > LIMITE_TEMPO or duracao > LIMITE_TEMPO:
                    print(f"  Os valores devem ser menores que {LIMITE_TEMPO}.")
                else:
                    break
            except (ValueError, EOFError):
                print("  Entrada inválida. Use apenas números inteiros.")

        lista_processos.append((nome, chegada, duracao))

    return lista_processos


#execucao principal


if __name__ == "__main__":
    try:
        processos_usuario = capturar_processos()
        escalonador_srtf(processos_usuario)
    except KeyboardInterrupt:
        print("\nExecução interrompida pelo usuário.")

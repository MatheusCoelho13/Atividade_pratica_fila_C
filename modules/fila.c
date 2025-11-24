#include "fila.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

static int prox_id = 1; // Variável estática para gerar IDs únicos para cada paciente.

// FUNÇÃO PARA RESETAR O ID
void resetar_id() {
    prox_id = 1;
}

// FUNÇÃO PARA CRIAR UMA FILA
Fila *criar_fila() {
    // Aloca memória para a estrutura da fila.
    Fila *fila = (Fila *)malloc(sizeof(Fila)); 
    
    // Verifica se a alocação foi bem sucedida.
    if (fila == NULL) {
        printf("Erro ao alocar memoria para a fila.\n"); 
        exit(1); // Encerra o programa se houver erro de alocação.
    } 
    
    // Inicializa os campos da fila.
    fila->inicio = NULL; // Inicializa o início da fila como NULL (vazia).
    fila->fim = NULL;    // Inicializa o fim da fila como NULL (vazia).
    fila->tamanho = 0;   // Inicializa o tamanho da fila como 0.

    return fila; // Retorna o ponteiro para a fila criada.
}

// FUNÇÃO PARA ADICIONAR UM PACIENTE
paciente adicionar_paciente(const char *nome) {
    // Cria e preenche uma variável do tipo paciente.
    paciente paciente; 
    
    // Atribui o ID gerado ao paciente e incrementa para o próximo.
    paciente.id = prox_id++; 
    
    // Copia o nome passado como parâmetro para o campo nome da struct paciente.
    // Usando snprintf para evitar estouro de buffer (assumindo 'paciente.nome' é um array de char).
    snprintf(paciente.nome, sizeof(paciente.nome), "%s", nome); 
    
    return paciente; // Retorna a struct paciente preenchida.
}

// FUNÇÃO PARA VERIFICAR SE A FILA ESTÁ VAZIA --> RETORNA 1 SE ESTIVER VAZIA E 0 SE NÃO ESTIVER
int lista_vazia(Fila *fila) {
    if (fila == NULL) return 1;
    return (fila->inicio == NULL);
}


// FUNÇÃO PARA LIBERAR A FILA
void liberar_fila(Fila *fila) {
    if (fila->inicio == NULL) {
        free(fila); 
        return;     
    }
    Elemento *atual = fila->inicio; // Ponteiro para percorrer a lista.
    Elemento *prox;

    do {
        prox = atual->prox;
        free(atual);
        atual = prox;
    } while (atual != fila->inicio);

free(fila);
}

// FUNÇÃO PARA ENFILEIRAR UM PACIENTE --> ADICIONAR O PACIENTE NO FINAL DA FILA (FIFO)
void enfileirar(Fila *fila, paciente dados) {
    // Aloca memória para o novo elemento (nó) da lista encadeada.
    Elemento *novo_elemento = (Elemento *)malloc(sizeof(Elemento)); 
    
    // Verifica a alocação de memória.
        if (novo_elemento == NULL) {
        printf("Erro ao alocar memoria para o novo elemento.\n");
        exit(1);
    }

    // Preenche os campos do novo elemento.
    novo_elemento->dados = dados; 

if (fila->inicio == NULL) {
    novo_elemento->prox = novo_elemento;
    fila->inicio = novo_elemento;
    fila->fim = novo_elemento;
} else {
    novo_elemento->prox = fila->inicio;   
    fila->fim->prox = novo_elemento;
    fila->fim = novo_elemento;
}


    fila->tamanho++; // Incrementa o contador de tamanho da fila.
}

// FUNÇÃO PARA DESENFILEIRAR UM PACIENTE --> REMOVER O PACIENTE DO INÍCIO DA FILA (FIFO)
paciente desenfileirar(Fila *fila) {
    // Verifica se é possível remover (fila não vazia).
    if (lista_vazia(fila)) {
    printf("Fila vazia.\n");
    exit(1);
}

    Elemento *temp = fila->inicio;       // Ponteiro para o elemento a ser removido (início).
    paciente dados = temp->dados;        // Armazena os dados do paciente a ser retornado.
    
    if (fila->inicio == fila->fim) {
        // só 1 elemento
        fila->inicio = NULL;         
        fila->fim = NULL;           
    } else {
        fila->inicio = temp->prox;   
        fila->fim->prox = fila->inicio; 
    }


    free(temp);      // Libera a memória do elemento removido.
    fila->tamanho--; // Diminui o tamanho da fila.

    return dados; // Retorna os dados do paciente.
}

// FUNÇÃO PARA OBTER O TAMANHO DA FILA
int tamanho_fila(Fila *fila) {
    if (fila == NULL) return 0;
    return fila->tamanho; // Retorna o tamanho armazenado na estrutura.

}

// FUNÇÃO PARA IMPRIMIR OS DADOS DE UM PACIENTE
void print_paciente(paciente paciente) {
    printf("ID: %d, Nome: %s\n", paciente.id, paciente.nome); 
}

// FUNÇÃO PARA IMPRIMIR A FILA COMPLETA
void imprimir_fila(Fila *fila) {

    if (lista_vazia(fila)) {            // MODIFICADO
        printf("Fila vazia.\n");
        return;
    }

    Elemento *atual = fila->inicio;

    printf("--- Conteudo da Fila (Tamanho: %d) ---\n", fila->tamanho);

    do {
        print_paciente(atual->dados);
        atual = atual->prox;
    } while (atual != fila->inicio);    // MODIFICADO

    printf("-----------------------------------------\n");
}

// FUNÇÃO PARA LIMPAR O BUFFER DE ENTRADA (usado para scanf/leitura de teclado)
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// FUNÇÃO PARA ATENDER O PRÓXIMO PACIENTE SEGUINDO A REGRA DE PRIORIDADE
void atender_proximo_paciente(Fila* fila1, Fila* fila2, Fila* fila3) {
    
    // Variável para armazenar a cópia do paciente atendido
    paciente paciente_atendido; 
    int atendido = 0; 
    
    // 1. Tentar Prioridade ALTA (Fila 3)
    if (!lista_vazia(fila3)) { 
        paciente_atendido = desenfileirar(fila3);
        printf("Atendimento: Paciente de Prioridade ALTA (Fila 3).\n");
        atendido = 1;
    } 
    // 2. Tentar Prioridade MÉDIA (Fila 2)
    else if (!lista_vazia(fila2)) {
        paciente_atendido = desenfileirar(fila2);
        printf("Atendimento: Paciente de Prioridade MEDIA (Fila 2).\n");
        atendido = 1;
    }
    // 3. Tentar Prioridade BAIXA (Fila 1)
    // ATENÇÃO: Havia uma referência incorreta 'f1' no código original, corrigida para 'fila1'.
    else if (!lista_vazia(fila1)) { 
        paciente_atendido = desenfileirar(fila1);
        printf("Atendimento: Paciente de Prioridade BAIXA (Fila 1).\n");
        atendido = 1;
    } 
    // 4. Todas as filas vazias
    else {
        printf("Todas as filas estão vazias. Nenhum paciente para atender.\n");
        return; // Sai da função
    }
    
    // Se um paciente foi encontrado e desenfileirado
    if (atendido) {
        printf("--- Paciente Atendido ---\n");
        print_paciente(paciente_atendido); 
        printf("Paciente removido da fila.\n");
    }
}
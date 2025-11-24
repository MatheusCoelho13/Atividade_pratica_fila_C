#include "fila.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

static int prox_id = 1; // Variável estática para gerar IDs únicos para cada paciente.

// Validação segura de ponteiros
#define VALIDAR_FILA(fila)                                          \
    if ((fila) == NULL)                                             \
    {                                                               \
        4 fprintf(stderr, "ERRO: Fila NULL. Operacao abortada.\n"); \
        return;                                                     \
    }
#define VALIDAR_FILA_INT(fila)                                    \
    if ((fila) == NULL)                                           \
    {                                                             \
        fprintf(stderr, "ERRO: Fila NULL. Operacao abortada.\n"); \
        return -1;                                                \
    }
#define VALIDAR_PONTEIRO(ptr)                                \
    if ((ptr) == NULL)                                       \
    {                                                        \
        fprintf(stderr, "ERRO: Ponteiro NULL detectado.\n"); \
        return -1;                                           \
    }
void validar_id(paciente paciente)
{
    paciente paciente
}
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
    // Validação segura de ponteiro
    if (fila == NULL)
    {
        fprintf(stderr, "ERRO: Tentativa de verificar fila NULL.\n");
        return 1;
    }
    // Retorna 1 (verdadeiro) se o tamanho da fila for 0, caso contrário retorna 0 (falso).
    return fila->tamanho == 0; 
}

// FUNÇÃO PARA VERIFICAR SE A FILA ESTÁ CHEIA --> RETORNA 1 SE ESTIVER CHEIA E 0 SE NÃO ESTIVER
int lista_cheia(Fila *fila)
{
    // Validação segura de ponteiro
    if (fila == NULL)
    {
        fprintf(stderr, "ERRO: Tentativa de verificar fila NULL.\n");
        return 0;
    }
    // Retorna 1 se atingiu o limite máximo de pacientes
    return fila->tamanho >= MAX_PACIENTES_POR_FILA;
}

// FUNÇÃO PARA LIBERAR A FILA COM SEGURANÇA
int liberar_fila(Fila *fila)
{
    // Validação segura de ponteiro
    if (fila == NULL)
    {
        fprintf(stderr, "ERRO: Tentativa de liberar fila NULL.\n");
        return -1;
    }

    Elemento *atual = fila->inicio; // Ponteiro para percorrer a lista.
    int contador = 0;

    // Percorre cada elemento da fila, liberando a memória de cada um.
    while (atual != NULL) {
        Elemento *temp = atual; // Armazena o elemento atual.
        atual = atual->prox;    // Avança para o próximo elemento.
        free(temp);             // Libera a memória do elemento atual.
        contador++;
    }

    // Valida que a estrutura foi liberada corretamente
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    free(fila); // Libera a memória da estrutura da fila (cabeçalho).
    fila = NULL; // Marca como NULL após liberação (boas práticas)

    return contador; // Retorna quantos elementos foram liberados
}

// FUNÇÃO PARA ENFILEIRAR UM PACIENTE --> ADICIONAR O PACIENTE NO FINAL DA FILA (FIFO)
int enfileirar(Fila *fila, paciente dados)
{
    // Validação segura de ponteiro
    if (fila == NULL)
    {
        fprintf(stderr, "ERRO: Tentativa de enfileirar em fila NULL.\n");
        return -1;
    }

    // Verifica se a fila atingiu o limite máximo
    if (lista_cheia(fila))
    {
        fprintf(stderr, "ERRO: Fila cheia! Limite máximo de %d pacientes atingido.\n", MAX_PACIENTES_POR_FILA);
        return FILA_CHEIA;
    }

    // Aloca memória para o novo elemento (nó) da lista encadeada.
    Elemento *novo_elemento = (Elemento *)malloc(sizeof(Elemento)); 
    
    // Verifica a alocação de memória.
    if (novo_elemento == NULL) {
        fprintf(stderr, "ERRO: Falha ao alocar memoria para novo elemento (malloc retornou NULL).\n");
        return -1;
    }
    
    // Preenche os campos do novo elemento.
    novo_elemento->dados = dados; 
    novo_elemento->prox = NULL; // É o último da fila, então o próximo é NULL.

    // Caso 1: A fila NÃO está vazia.
    if (fila->fim != NULL) {
        // O elemento que era o último agora aponta para o novo elemento.
        fila->fim->prox = novo_elemento; 
    }
    
    // O novo elemento passa a ser o fim da fila.
    fila->fim = novo_elemento; 

    // Caso 2: A fila ESTAVA vazia.
    if (fila->inicio == NULL) {
        // O novo elemento é o primeiro e o último.
        fila->inicio = novo_elemento; 
    }

    fila->tamanho++; // Incrementa o contador de tamanho da fila.
    return 0;        // Sucesso
}

// FUNÇÃO PARA DESENFILEIRAR UM PACIENTE --> REMOVER O PACIENTE DO INÍCIO DA FILA (FIFO)
int desenfileirar(Fila *fila, paciente *dados)
{
    // Validação segura de ponteiros
    if (fila == NULL)
    {
        fprintf(stderr, "ERRO: Tentativa de desenfileirar de fila NULL.\n");
        return -1;
    }

    if (dados == NULL)
    {
        fprintf(stderr, "ERRO: Ponteiro de dados NULL. Nao e possivel retornar paciente.\n");
        return -1;
    }

    // Verifica se é possível remover (fila não vazia).
    if (lista_vazia(fila)) {
        fprintf(stderr, "ERRO: Fila vazia. Nao e possivel desenfileirar.\n");
        return FILA_VAZIA;
    }

    // Validação de consistência da fila
    if (fila->inicio == NULL)
    {
        fprintf(stderr, "ERRO: Inconsistencia na fila - inicio é NULL mas tamanho > 0.\n");
        return -1;
    }

    Elemento *temp = fila->inicio;       // Ponteiro para o elemento a ser removido (início).

    // Validação segura antes de acessar dados
    if (temp == NULL)
    {
        fprintf(stderr, "ERRO: Ponteiro de elemento invalido.\n");
        return -1;
    }

    *dados = temp->dados; // Armazena os dados do paciente a ser retornado.

    // O novo início é o próximo elemento.
    fila->inicio = fila->inicio->prox; 

    // Se o início se tornou NULL, significa que a fila ficou vazia.
    if (fila->inicio == NULL) {
        fila->fim = NULL; // O fim também deve ser NULL.
    }

    free(temp);      // Libera a memória do elemento removido.
    fila->tamanho--; // Diminui o tamanho da fila.

    return 0; // Sucesso
}

// FUNÇÃO PARA OBTER O TAMANHO DA FILA
int tamanho_fila(Fila *fila) {
    return fila->tamanho; // Retorna o tamanho armazenado na estrutura.
}

// FUNÇÃO PARA IMPRIMIR OS DADOS DE UM PACIENTE
void print_paciente(paciente paciente) {
    printf("ID: %d, Nome: %s\n", paciente.id, paciente.nome); 
}

// FUNÇÃO PARA IMPRIMIR A FILA COMPLETA COM SEGURANÇA
void imprimir_fila(Fila *fila) {
    // Validação segura de ponteiro
    if (fila == NULL)
    {
        fprintf(stderr, "ERRO: Tentativa de imprimir fila NULL.\n");
        return;
    }

    Elemento *atual = fila->inicio; // Ponteiro para percorrer a lista.
    printf("--- Conteudo da Fila (Tamanho: %d) ---\n", fila->tamanho);

    while (atual != NULL) {
        // Validação segura do elemento
        if (atual == NULL)
        {
            fprintf(stderr, "ERRO: Elemento nulo durante iteracao.\n");
            break;
        }
        print_paciente(atual->dados); // Imprime os dados do paciente.
        atual = atual->prox;          // Avança para o próximo elemento.
    }
    printf("-----------------------------------------\n");
}

// FUNÇÃO PARA LIMPAR O BUFFER DE ENTRADA (usado para scanf/leitura de teclado)
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// FUNÇÃO Para pegar o id do PACIENTE
int pegar_id(paciente paciente)
{
    printf("ID: %d", paciente.id);
    return paciente.id;
}
//  FUNÇÃO PARA ATENDER O PRÓXIMO PACIENTE SEGUINDO A REGRA DE PRIORIDADE COM SEGURANÇA
void atender_proximo_paciente(Fila* fila1, Fila* fila2, Fila* fila3) {
    // Validação segura de todos os ponteiros
    if (fila1 == NULL || fila2 == NULL || fila3 == NULL)
    {
        fprintf(stderr, "ERRO: Uma ou mais filas estao NULL. Operacao abortada.\n");
        return;
    }

    // Variável para armazenar a cópia do paciente atendido
    paciente paciente_atendido;
    int atendido = 0;
    int resultado = -1;

    // 1. Tentar Prioridade ALTA (Fila 3)
    if (!lista_vazia(fila3))
    {
        resultado = desenfileirar(fila3, &paciente_atendido);
        if (resultado == 0)
        {
            printf("Atendimento: Paciente de Prioridade ALTA (Fila 3).\n");
            atendido = 1;
        }
    }
    // 2. Tentar Prioridade MÉDIA (Fila 2)
    else if (!lista_vazia(fila2)) {
        resultado = desenfileirar(fila2, &paciente_atendido);
        if (resultado == 0)
        {
            printf("Atendimento: Paciente de Prioridade MEDIA (Fila 2).\n");
            atendido = 1;
        }
    }
    // 3. Tentar Prioridade BAIXA (Fila 1)
    else if (!lista_vazia(fila1))
    {
        resultado = desenfileirar(fila1, &paciente_atendido);
        if (resultado == 0)
        {
            printf("Atendimento: Paciente de Prioridade BAIXA (Fila 1).\n");
            atendido = 1;
        }
    }
    // 4. Todas as filas vazias
    else
    {
        printf("Todas as filas estao vazias. Nenhum paciente para atender.\n");
        return; // Sai da função
    }

    // Se um paciente foi encontrado e desenfileirado com sucesso
    if (atendido) {
        printf("--- Paciente Atendido ---\n");
        print_paciente(paciente_atendido); 
        printf("Paciente removido da fila.\n");
    }
    else
    {
        fprintf(stderr, "ERRO: Falha ao desenfileirar paciente.\n");
    }
}

// FUNÇÃO PARA LIBERAR TODAS AS FILAS DE FORMA ROBUSTA
int liberar_todas_filas(Fila *f1, Fila *f2, Fila *f3)
{
    int total_liberado = 0;

    if (f1 != NULL)
    {
        int liberado = liberar_fila(f1);
        if (liberado > 0)
        {
            printf("Fila 1 liberada: %d elementos desalocados.\n", liberado);
        }
        total_liberado += (liberado > 0 ? liberado : 0);
    }
    else
    {
        fprintf(stderr, "AVISO: Fila 1 ja estava NULL.\n");
    }

    if (f2 != NULL)
    {
        int liberado = liberar_fila(f2);
        if (liberado > 0)
        {
            printf("Fila 2 liberada: %d elementos desalocados.\n", liberado);
        }
        total_liberado += (liberado > 0 ? liberado : 0);
    }
    else
    {
        fprintf(stderr, "AVISO: Fila 2 ja estava NULL.\n");
    }

    if (f3 != NULL)
    {
        int liberado = liberar_fila(f3);
        if (liberado > 0)
        {
            printf("Fila 3 liberada: %d elementos desalocados.\n", liberado);
        }
        total_liberado += (liberado > 0 ? liberado : 0);
    }
    else
    {
        fprintf(stderr, "AVISO: Fila 3 ja estava NULL.\n");
    }

    printf("Total de %d pacientes foram removidos de memoria.\n", total_liberado);
    return total_liberado;
}
int Gerar_relatorio(Fila *f1, Fila *f2, Fila *f3, paciente paciente)
{

    if (!f1 || !f2 || !f3)
    {
        printf("Erro: fila nula em Gerar_relatorio\n");
        return -1;
    }
    pegar_id(paciente);
    return 0;
    printf("%p", paciente.id);
}
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

static int prox_id = 1; // Variável estática para gerar IDs únicos para cada paciente.
void resetar_id() {
    prox_id = 1;
}
// FUNÇÃO PARA CRIAR UMA FILA
Fila *criar_fila()
{
    Fila *fila = (Fila *)malloc(sizeof(Fila)); // Aloca memória para a fila.
    if (fila == NULL)
    {                                                    // Verifica se a alocação foi bem sucedida.
        printf("Erro ao alocar memoria para a fila.\n"); // Se não foi, imprime uma mensagem de erro e encerra o programa.
        exit(1);                                         // Encerra o programa.
    } // Fim da verificação, continua a inicialização da fila.
    fila->inicio = NULL; // Inicializa o início da fila como NULL.
    fila->fim = NULL;    // Inicializa o fim da fila como NULL.
    fila->tamanho = 0;   // Inicializa o tamanho da fila como 0.

    return fila; // Retorna o ponteiro para a fila criada.
}
// FUNÇÃO PARA ADICIONAR UM PACIENTE À FILA
paciente adicionar_paciente(const char *nome)
{
    // Passa como parâmetro o nome do paciente.
    paciente paciente; // Cria uma variável do tipo paciente.
 
    paciente.id = prox_id++;                                      // Atribui o ID gerado ao campo id da struct paciente.
    snprintf(paciente.nome, sizeof(paciente.nome), "%s", nome); // Copia o nome passado como parâmetro para o campo nome da struct paciente.                                              //Incrementa o ID para o próximo paciente.
    return paciente;                                            // Retorna a struct paciente preenchida.
}

// FUNÇÃO PARA VERIFICAR SE A FILA ESTÁ VAZIA --> RETORNA 1 SE ESTIVER VAZIA E 0 SE NÃO ESTIVER
int lista_vazia(Fila *fila)
{                              // Passa como parâmetro um ponteiro para a fila. (condicional para saber se a fila está vazia)
    return fila->tamanho == 0; // Retorna 1 (verdadeiro) se o tamanho da fila for 0, caso contrário retorna 0 (falso).
}

// FUNÇÃO PARA LIBERAR A FILA
void liberar_fila(Fila *fila)
{
    Elemento *atual = fila->inicio; // Cria um ponteiro para percorrer a fila, começando pelo início.
    while (atual != NULL)
    {                           // Enquanto o ponteiro atual não for NULL, percorrer a fila até que todos os elementos sejam liberados.
        Elemento *temp = atual; // Cria um ponteiro que armazena o elemento atual temporariamente.
        atual = atual->prox;    // Atual aponta para o próximo elemento da fila.
        free(temp);             // Libera a memória do elemento armazenado em temp. -->AQUI QUE LIBERA CADA ELEMENTO DA FILA<--
    }
    free(fila); // Libera a memória da estrutura da fila em si. -->LIXO NA MEMORIA, PRECISA LIBERAR<--
}

// FUNÇÃO PARA ENFILEIRAR UM PACIENTE --> ADICIONAR O PACIENTE NO FINAL DA FILA
void enfileirar(Fila *fila, paciente dados)
{                                                                   // Passa como parâmetro um ponteiro para a fila e os dados do paciente a ser enfileirado.
    Elemento *novo_elemento = (Elemento *)malloc(sizeof(Elemento)); // Aloca memória para um novo elemento da fila.
    if (novo_elemento == NULL)
    {                                                             // Verifica se a alocação foi bem sucedida.
        printf("Erro ao alocar memoria para o novo elemento.\n"); // Se não foi, imprime uma mensagem de erro e encerra o programa.
        exit(1);                                                  // Encerra o programa.
    }
    novo_elemento->dados = dados; // Atribui os dados do paciente ao novo elemento.
    novo_elemento->prox = NULL;   // O próximo elemento do novo elemento é NULL, pois será o último da fila.

    if (fila->fim != NULL)
    {                                    // Se o fim da fila não for NULL, ou seja, se a fila não estiver vazia.
        fila->fim->prox = novo_elemento; // O fim da fila aponta para o novo elemento.
    }
    fila->fim = novo_elemento; // Define o novo elemento como o fim da fila.

    if (fila->inicio == NULL)
    {                                 // Se o início da fila for NULL, ou seja, se a fila estiver vazia.
        fila->inicio = novo_elemento; // Define o novo elemento como o início da fila.
    }

    fila->tamanho++; // Incrementa o tamanho da fila.
}

// FUNÇÃO PARA DESENFILEIRAR UM PACIENTE -->  REMOVER O PACIENTE DO INÍCIO DA FILA
paciente desenfileirar(Fila *fila)
{
    if (lista_vazia(fila))
    {                                                          // Verifica se a fila está vazia.
        printf("Fila vazia. Nao e possivel desenfileirar.\n"); // Se estiver, imprime uma mensagem de erro e encerra o programa.
        exit(1);                                               // Encerra o programa.
    }

    Elemento *temp = fila->inicio;     // Armazena o elemento do início da fila em um ponteiro temporário.
    paciente dados = temp->dados;      // Armazena os dados do paciente do elemento a ser removido.
    fila->inicio = fila->inicio->prox; // Atualiza o início da fila para o próximo elemento. -->AQUI REMOVEMOS O ELEMENTO DA FILA<--

    if (fila->inicio == NULL)
    {                     // Se o início da fila for NULL após a remoção, ou seja, se a fila ficar vazia.
        fila->fim = NULL; // Define o fim da fila como NULL também.
    }

    free(temp);      // Libera a memória do elemento removido.
    fila->tamanho--; // Diminui o tamanho da fila.

    return dados; // Retorna os dados do paciente removido.-->INTERESSANTE COLOCAR UM PRINTF PARA SABER QUAL CLIENTE FOI REMOVIDO<--
}

// FUNÇÃO PARA OBTER O TAMANHO DA FILA
int tamanho_fila(Fila *fila)
{                         // Passa como parâmetro um ponteiro para a fila. -->SERVE PARA SABER QUANTOS PACIENTES TEM NA FILA<--
    return fila->tamanho; // Retorna o tamanho da fila.
}

// FUNÇÃO PARA IMPRIMIR OS DADOS DE UM PACIENTE
void print_paciente(paciente paciente)
{                                                             // Passa como parâmetro uma struct paciente. -->SERVE PARA PASSAR AS INFORMAÇÕES DO PACIENTE<--
    printf("ID: %d, Nome: %s\n", paciente.id, paciente.nome); // Usa printf para imprimir o ID e o nome do paciente.
}

// FUNÇÃO PARA IMPRIMIR A FILA
void imprimir_fila(Fila *fila)
{
    Elemento *atual = fila->inicio; // Cria um ponteiro para percorrer a fila, começando pelo início.
    while (atual != NULL)
    {                                 // Enquanto o ponteiro atual não for NULL, percorre a fila.
        print_paciente(atual->dados); // Usa a função "printpaciente"para imprimir os dados do paciente do elemento atual.
        atual = atual->prox;          // Atualiza o ponteiro atual para o próximo elemento da fila.
    } // Ao final do loop de impressão, o while percorreu toda a fila.
}

void limpar_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct
{           // Define a struct para armazenar os dados do paciente.
    int id; // ID do paciente. -->IDENTIFICAÇÃO DO PACIENTE<--
    char nome[50];
    int prioridade;
} paciente;

typedef struct elemento_fila
{ // Define a struct para os elementos da fila.
    paciente dados;
    struct elemento_fila *prox;
} Elemento;

typedef struct fila
{ // Define a struct para a fila em si. -->CONTROLE DA FILA<--
    Elemento *inicio;
    Elemento *fim;
    int tamanho;
} Fila;

// protótipos das funções
Fila *criar_fila();
void resetar_id(); 
paciente adicionar_paciente(const char *nome);
int lista_vazia(Fila *fila);
void liberar_fila(Fila *fila);
void enfileirar(Fila *fila, paciente dados);
void imprimir_fila(Fila *fila);
int tamanho_fila(Fila *fila);
paciente desenfileirar(Fila *fila);
void print_paciente(paciente paciente);
void limpar_buffer();
void atender_proximo_paciente(Fila* f1, Fila* f2, Fila* f3);

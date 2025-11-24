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

// Constantes de segurança
#define MAX_PACIENTES_POR_FILA 3
#define FILA_CHEIA -1
#define FILA_VAZIA -2

// protótipos das funções
Fila *criar_fila();
void resetar_id(); 
paciente adicionar_paciente(const char *nome);
int lista_vazia(Fila *fila);
int lista_cheia(Fila *fila);
int liberar_fila(Fila *fila);
int enfileirar(Fila *fila, paciente dados);
void imprimir_fila(Fila *fila);
int tamanho_fila(Fila *fila);
int desenfileirar(Fila *fila, paciente *dados);
void print_paciente(paciente paciente);
void limpar_buffer();
void atender_proximo_paciente(Fila* f1, Fila* f2, Fila* f3);
int liberar_todas_filas(Fila *f1, Fila *f2, Fila *f3);
int Gerar_relatorio(Fila *f1, Fila *f2, Fila *f3, paciente paciente );
int pegar_id(paciente paciente);

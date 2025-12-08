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

/* ============================================================
   ESTRUTURA DO GRAFO DO HOSPITAL
============================================================ */

// Estrutura para representar uma aresta (conexão entre setores)
typedef struct no_adjacencia
{
    int destino; // Índice do setor destino
    struct no_adjacencia *prox;
} NoAdjacencia;

// Estrutura para representar um vértice (setor do hospital)
typedef struct
{
    int id;                   // ID do setor
    char nome[50];            // Nome do setor
    NoAdjacencia *adjacentes; // Lista de setores conectados
} VerticeHospital;

// Estrutura principal do grafo
typedef struct
{
    VerticeHospital *vertices; // Array de vértices
    int total_vertices;        // Total de setores no hospital
} GrafoHospital;

// Enums para setores do hospital
enum SetoresHospital
{
    RECEPCAO = 0,
    ADMINISTRACAO = 1,
    ENFERMARIA = 2,
    UTI = 3,
    CENTRO_CIRURGICO = 4,
    FARMACIA = 5,
    ALMOXARIFADO = 6,
    LABORATORIO = 7,
    RAIO_X = 8,
    SAIDA_EMERGENCIA = 9,
    TOTAL_SETORES = 10
};

// Constantes de segurança
#define MAX_PACIENTES_POR_FILA 3
#define FILA_CHEIA -1
#define FILA_VAZIA -2

// Protótipos - Fila
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

// Protótipos - Grafo do Hospital
GrafoHospital *criar_grafo_hospital();
int inserir_vertices_hospital(GrafoHospital *grafo);
int inserir_arestas_hospital(GrafoHospital *grafo);
int adicionar_aresta(GrafoHospital *grafo, int origem, int destino);
void imprimir_grafo_hospital(GrafoHospital *grafo);
void imprimir_setores_conectados(GrafoHospital *grafo, int setor);
int liberar_grafo_hospital(GrafoHospital *grafo);
const char *obter_nome_setor(int setor);
int exibir_tabela_setores();
void bfs(GrafoHospital *grafo, int id_setor_inicial);

// Protótipos - DFS (Busca em Profundidade)
void dfs(GrafoHospital *grafo);
void dfs_visitar(GrafoHospital *grafo, int u, int visitado[], int *tempo);

// Protótipos - Tarjan (pontos de articulação)
void encontrar_pontos_articulacao(GrafoHospital *grafo); 
void tarjan_util(GrafoHospital *grafo, int u, int *tempo, int *disc, int *low, int *parent, int *ap);
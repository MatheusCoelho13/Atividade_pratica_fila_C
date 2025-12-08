#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int prox_id = 1;

// Macros de Validação
#define VALIDAR_FILA(fila) \
    if ((fila) == NULL) { \
        fprintf(stderr, "ERRO: Fila NULL. Operacao abortada.\n"); \
        return; \
    }

#define VALIDAR_FILA_INT(fila) \
    if ((fila) == NULL) { \
        fprintf(stderr, "ERRO: Fila NULL. Operacao abortada.\n"); \
        return -1; \
    }

#define VALIDAR_PONTEIRO(ptr) \
    if ((ptr) == NULL) { \
        fprintf(stderr, "ERRO: Ponteiro NULL detectado.\n"); \
        return -1; \
    }

/* ============================================================
   REMOVIDO → Função inválida que quebrava o arquivo
============================================================ */
// void validar_id(paciente paciente) {}

/* ============================================================
   Resetar ID
============================================================ */
void resetar_id() {
    prox_id = 1;
}

/* ============================================================
   Criar fila
============================================================ */
Fila *criar_fila() {
    Fila *fila = (Fila *) malloc(sizeof(Fila));
    if (!fila) {
        fprintf(stderr, "Erro ao alocar fila.\n");
        exit(1);
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

/* ============================================================
   Criar paciente
============================================================ */
paciente adicionar_paciente(const char *nome) {
    paciente p;
    p.id = prox_id++;
    snprintf(p.nome, sizeof(p.nome), "%s", nome);
    return p;
}

/* ============================================================
   Lista vazia
============================================================ */
int lista_vazia(Fila *fila) {
    return (!fila || fila->inicio == NULL);
}

/* ============================================================
   Lista cheia (agora implementada)
============================================================ */
int lista_cheia(Fila *fila) {
    VALIDAR_FILA_INT(fila);
    return fila->tamanho >= MAX_PACIENTES_POR_FILA;
}

/* ============================================================
   Liberar fila (AGORA RETORNA INT)
============================================================ */
int liberar_fila(Fila *fila) {
    VALIDAR_FILA_INT(fila);

    if (fila->inicio == NULL) {
        free(fila);
        return 0;
    }

    int count = 0;
    Elemento *atual = fila->inicio;
    Elemento *prox;

    do {
        prox = atual->prox;
        free(atual);
        atual = prox;
        count++;
    } while (atual != fila->inicio);

    free(fila);
    return count;
}

/* ============================================================
   Enfileirar
============================================================ */
int enfileirar(Fila *fila, paciente dados) {
    VALIDAR_FILA_INT(fila);

    if (lista_cheia(fila)) {
        fprintf(stderr, "ERRO: Fila cheia.\n");
        return FILA_CHEIA;
    }

    Elemento *novo = malloc(sizeof(Elemento));
    if (!novo) {
        fprintf(stderr, "Erro malloc.\n");
        return -1;
    }

    novo->dados = dados;

    if (fila->inicio == NULL) {
        novo->prox = novo;
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        novo->prox = fila->inicio;
        fila->fim->prox = novo;
        fila->fim = novo;
    }

    fila->tamanho++;
    return 0;
}

/* ============================================================
   Desenfileirar (CORRIGIDO)
============================================================ */
int desenfileirar(Fila *fila, paciente *dados) {
    VALIDAR_FILA_INT(fila);
    VALIDAR_PONTEIRO(dados);

    if (lista_vazia(fila))
        return FILA_VAZIA;

    Elemento *temp = fila->inicio;

    *dados = temp->dados;  // CORRETO

    if (fila->inicio == fila->fim) {
        fila->inicio = NULL;
        fila->fim = NULL;
    } else {
        fila->inicio = temp->prox;
        fila->fim->prox = fila->inicio;
    }

    free(temp);
    fila->tamanho--;
    return 0;
}

/* ============================================================
   Tamanho
============================================================ */
int tamanho_fila(Fila *fila) {
    return fila ? fila->tamanho : 0;
}

/* ============================================================
   Impressões
============================================================ */
void print_paciente(paciente paciente) {
    printf("ID: %d, Nome: %s\n", paciente.id, paciente.nome);
}

void imprimir_fila(Fila *fila) {
    if (lista_vazia(fila)) {
        printf("Fila vazia.\n");
        return;
    }

    Elemento *atual = fila->inicio;
    printf("--- Conteudo da Fila (Tamanho %d) ---\n", fila->tamanho);

    do {
        print_paciente(atual->dados);
        atual = atual->prox;
    } while (atual != fila->inicio);

    printf("-------------------------------------\n");
}

/* ============================================================
   Limpar buffer
============================================================ */
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ============================================================
   Pegar ID
============================================================ */
int pegar_id(paciente paciente) {
    printf("ID: %d\n", paciente.id);
    return paciente.id;
}

/* ============================================================
   Atendimento
============================================================ */
void atender_proximo_paciente(Fila *f1, Fila *f2, Fila *f3) {
    if (!f1 || !f2 || !f3) {
        fprintf(stderr, "ERRO: Filas NULL.\n");
        return;
    }

    paciente pac;
    int r = -1;

    if (!lista_vazia(f3)) r = desenfileirar(f3, &pac);
    else if (!lista_vazia(f2)) r = desenfileirar(f2, &pac);
    else if (!lista_vazia(f1)) r = desenfileirar(f1, &pac);
    else {
        printf("Todas as filas vazias.\n");
        return;
    }

    if (r == 0) {
        printf("Paciente atendido:\n");
        print_paciente(pac);
    }
}

/* ============================================================
   Liberar todas
============================================================ */
int liberar_todas_filas(Fila *f1, Fila *f2, Fila *f3) {
    int total = 0;

    if (f1) total += liberar_fila(f1);
    if (f2) total += liberar_fila(f2);
    if (f3) total += liberar_fila(f3);

    printf("Total liberado: %d elementos.\n", total);
    return total;
}

/* ============================================================
   Relatorio
============================================================ */
int Gerar_relatorio(Fila *f1, Fila *f2, Fila *f3, paciente paciente) {
    if (!f1 || !f2 || !f3) return -1;

    printf("Gerando relatório do paciente:\n");
    print_paciente(paciente);

    return 0;
}

/* ============================================================
   FUNÇÕES DO GRAFO DO HOSPITAL
============================================================ */

// Função para obter o nome do setor
const char *obter_nome_setor(int setor)
{
    switch (setor)
    {
    case RECEPCAO:
        return "Recepcao";
    case ADMINISTRACAO:
        return "Administracao";
    case ENFERMARIA:
        return "Enfermaria";
    case UTI:
        return "UTI";
    case CENTRO_CIRURGICO:
        return "Centro Cirurgico";
    case FARMACIA:
        return "Farmacia";
    case ALMOXARIFADO:
        return "Almoxarifado";
    case LABORATORIO:
        return "Laboratorio";
    case RAIO_X:
        return "Raio-X";
    case SAIDA_EMERGENCIA:
        return "Saida de Emergencia";
    default:
        return "Setor Desconhecido";
    }
}

/* ============================================================
   Exibir Tabela de Setores
============================================================ */
int exibir_tabela_setores()
{
    printf("\n");
    printf("======================================================\n");
    printf("        SETORES DISPONIVEIS DO HOSPITAL             \n");
    printf("======================================================\n\n");

    printf("+----+------------------------------+\n");
    printf("| ID |          SETOR               |\n");
    printf("+----+------------------------------+\n");

    for (int i = 0; i < TOTAL_SETORES; i++)
    {
        printf("| %2d | %-28s |\n", i, obter_nome_setor(i));
    }

    printf("+----+------------------------------+\n\n");

    printf("Digite o numero do setor de destino (0-%d): ", TOTAL_SETORES - 1);

    int setor;
    if (scanf("%d", &setor) != 1)
    {
        limpar_buffer();
        fprintf(stderr, "ERRO: Entrada invalida!\n");
        return -1;
    }
    limpar_buffer();

    if (setor < 0 || setor >= TOTAL_SETORES)
    {
        fprintf(stderr, "ERRO: Setor invalido! Digite um numero entre 0 e %d.\n", TOTAL_SETORES - 1);
        return -1;
    }

    return setor;
}

/* ============================================================
   Criar Grafo do Hospital
============================================================ */
GrafoHospital *criar_grafo_hospital()
{
    GrafoHospital *grafo = (GrafoHospital *)malloc(sizeof(GrafoHospital));
    if (!grafo)
    {
        fprintf(stderr, "ERRO: Falha ao alocar grafo do hospital.\n");
        return NULL;
    }

    grafo->vertices = (VerticeHospital *)malloc(TOTAL_SETORES * sizeof(VerticeHospital));
    if (!grafo->vertices)
    {
        fprintf(stderr, "ERRO: Falha ao alocar vértices do grafo.\n");
        free(grafo);
        return NULL;
    }

    grafo->total_vertices = TOTAL_SETORES;

    // Inicializar todos os vértices
    for (int i = 0; i < TOTAL_SETORES; i++)
    {
        grafo->vertices[i].id = i;
        snprintf(grafo->vertices[i].nome, sizeof(grafo->vertices[i].nome), "%s", obter_nome_setor(i));
        grafo->vertices[i].adjacentes = NULL;
    }

    return grafo;
}

/* ============================================================
   Adicionar Aresta (Conexão entre setores)
============================================================ */
int adicionar_aresta(GrafoHospital *grafo, int origem, int destino)
{
    if (!grafo)
    {
        fprintf(stderr, "ERRO: Grafo NULL.\n");
        return -1;
    }

    if (origem < 0 || origem >= grafo->total_vertices || destino < 0 || destino >= grafo->total_vertices)
    {
        fprintf(stderr, "ERRO: Índice de setor inválido. Origem: %d, Destino: %d\n", origem, destino);
        return -1;
    }

    // Criar novo nó de adjacência
    NoAdjacencia *novo = (NoAdjacencia *)malloc(sizeof(NoAdjacencia));
    if (!novo)
    {
        fprintf(stderr, "ERRO: Falha ao alocar nó de adjacência.\n");
        return -1;
    }

    novo->destino = destino;
    novo->prox = NULL;

    // Inserir no início da lista de adjacência
    if (grafo->vertices[origem].adjacentes == NULL)
    {
        grafo->vertices[origem].adjacentes = novo;
    }
    else
    {
        // Inserir no final para manter ordem
        NoAdjacencia *atual = grafo->vertices[origem].adjacentes;
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = novo;
    }

    return 0;
}

/* ============================================================
   Inserir Vertices do Hospital
============================================================ */
int inserir_vertices_hospital(GrafoHospital *grafo)
{
    if (!grafo)
    {
        fprintf(stderr, "ERRO: Grafo NULL.\n");
        return -1;
    }

    printf("\n=== VERTICES (SETORES DO HOSPITAL) ===\n");
    for (int i = 0; i < grafo->total_vertices; i++)
    {
        printf("[%d] %s\n", i, grafo->vertices[i].nome);
    }
    printf("=====================================\n\n");

    return grafo->total_vertices;
}

/* ============================================================
   Inserir Arestas do Hospital
============================================================ */
int inserir_arestas_hospital(GrafoHospital *grafo)
{
    if (!grafo)
    {
        fprintf(stderr, "ERRO: Grafo NULL.\n");
        return -1;
    }

    int arestas_inseridas = 0;

    // Recepção → Administração, Enfermaria, Saída de Emergência
    arestas_inseridas += adicionar_aresta(grafo, RECEPCAO, ADMINISTRACAO);
    arestas_inseridas += adicionar_aresta(grafo, RECEPCAO, ENFERMARIA);
    arestas_inseridas += adicionar_aresta(grafo, RECEPCAO, SAIDA_EMERGENCIA);

    // Administração → Recepção
    arestas_inseridas += adicionar_aresta(grafo, ADMINISTRACAO, RECEPCAO);

    // Enfermaria → Recepção, UTI, Farmácia, Raio-X, Laboratório
    arestas_inseridas += adicionar_aresta(grafo, ENFERMARIA, RECEPCAO);
    arestas_inseridas += adicionar_aresta(grafo, ENFERMARIA, UTI);
    arestas_inseridas += adicionar_aresta(grafo, ENFERMARIA, FARMACIA);
    arestas_inseridas += adicionar_aresta(grafo, ENFERMARIA, RAIO_X);
    arestas_inseridas += adicionar_aresta(grafo, ENFERMARIA, LABORATORIO);

    // UTI → Enfermaria, Centro Cirúrgico
    arestas_inseridas += adicionar_aresta(grafo, UTI, ENFERMARIA);
    arestas_inseridas += adicionar_aresta(grafo, UTI, CENTRO_CIRURGICO);

    // Centro Cirúrgico → UTI, Farmácia, Almoxarifado, Saída de Emergência
    arestas_inseridas += adicionar_aresta(grafo, CENTRO_CIRURGICO, UTI);
    arestas_inseridas += adicionar_aresta(grafo, CENTRO_CIRURGICO, FARMACIA);
    arestas_inseridas += adicionar_aresta(grafo, CENTRO_CIRURGICO, ALMOXARIFADO);
    arestas_inseridas += adicionar_aresta(grafo, CENTRO_CIRURGICO, SAIDA_EMERGENCIA);

    // Farmácia → Enfermaria, Centro Cirúrgico, Almoxarifado
    arestas_inseridas += adicionar_aresta(grafo, FARMACIA, ENFERMARIA);
    arestas_inseridas += adicionar_aresta(grafo, FARMACIA, CENTRO_CIRURGICO);
    arestas_inseridas += adicionar_aresta(grafo, FARMACIA, ALMOXARIFADO);

    // Almoxarifado → Farmácia, Centro Cirúrgico
    arestas_inseridas += adicionar_aresta(grafo, ALMOXARIFADO, FARMACIA);
    arestas_inseridas += adicionar_aresta(grafo, ALMOXARIFADO, CENTRO_CIRURGICO);

    // Laboratório → Enfermaria
    arestas_inseridas += adicionar_aresta(grafo, LABORATORIO, ENFERMARIA);

    // Raio-X → Enfermaria
    arestas_inseridas += adicionar_aresta(grafo, RAIO_X, ENFERMARIA);

    // Saída de Emergência → Recepção, Centro Cirúrgico
    arestas_inseridas += adicionar_aresta(grafo, SAIDA_EMERGENCIA, RECEPCAO);
    arestas_inseridas += adicionar_aresta(grafo, SAIDA_EMERGENCIA, CENTRO_CIRURGICO);

    return arestas_inseridas;
}

/* ============================================================
   Imprimir Setores Conectados
============================================================ */
void imprimir_setores_conectados(GrafoHospital *grafo, int setor)
{
    if (!grafo || setor < 0 || setor >= grafo->total_vertices)
    {
        fprintf(stderr, "ERRO: Grafo ou índice de setor inválido.\n");
        return;
    }

    printf("\n[%d] %s conectado a:\n", setor, grafo->vertices[setor].nome);

    NoAdjacencia *atual = grafo->vertices[setor].adjacentes;
    if (!atual)
    {
        printf("  (sem conexões)\n");
        return;
    }

    int contador = 0;
    while (atual)
    {
        printf("  -> [%d] %s\n", atual->destino, grafo->vertices[atual->destino].nome);
        atual = atual->prox;
        contador++;
    }
    printf("  Total de conexoes: %d\n", contador);
}

/* ============================================================
   Imprimir Grafo Completo
============================================================ */
void imprimir_grafo_hospital(GrafoHospital *grafo)
{
    if (!grafo)
    {
        fprintf(stderr, "ERRO: Grafo NULL.\n");
        return;
    }

    printf("\n=============================================================\n");
    printf("     ESTRUTURA DO GRAFO DO HOSPITAL - LISTA DE ADJACENCIA\n");
    printf("=============================================================\n\n");

    for (int i = 0; i < grafo->total_vertices; i++)
    {
        imprimir_setores_conectados(grafo, i);
    }

    printf("\n=============================================================\n");
    printf("                   RESUMO DO GRAFO\n");
    printf("  Total de Setores (Vertices): %d\n", grafo->total_vertices);

    int total_arestas = 0;
    for (int i = 0; i < grafo->total_vertices; i++)
    {
        NoAdjacencia *atual = grafo->vertices[i].adjacentes;
        while (atual)
        {
            total_arestas++;
            atual = atual->prox;
        }
    }
    printf("  Total de Conexoes (Arestas): %d\n", total_arestas);
    printf("=============================================================\n\n");
}

/* ============================================================
   Liberar Grafo do Hospital
============================================================ */
int liberar_grafo_hospital(GrafoHospital *grafo)
{
    if (!grafo)
    {
        fprintf(stderr, "ERRO: Grafo NULL.\n");
        return -1;
    }

    int total_liberado = 0;

    // Liberar todas as arestas (nós de adjacência)
    for (int i = 0; i < grafo->total_vertices; i++)
    {
        NoAdjacencia *atual = grafo->vertices[i].adjacentes;
        while (atual)
        {
            NoAdjacencia *temp = atual;
            atual = atual->prox;
            free(temp);
            total_liberado++;
        }
        grafo->vertices[i].adjacentes = NULL;
    }

    // Liberar array de vértices
    if (grafo->vertices)
    {
        free(grafo->vertices);
        grafo->vertices = NULL;
    }

    // Liberar estrutura principal do grafo
    free(grafo);

    printf("Grafo liberado: %d conexões desalocadas.\n", total_liberado);
    return total_liberado;
}

// ==========================================================
// FILA AUXILIAR PARA BFS
// ==========================================================

#define TAM_FILA_BFS TOTAL_SETORES

static int fila_ids[TAM_FILA_BFS];
static int frente = -1;
static int tras = -1;

void enfileirar_id(int id_setor)
{
    // Verifica se está cheia (Fila Circular)
    if ((tras + 1) % TAM_FILA_BFS == frente) return;
    
    // Inicializa a fila se estiver vazia
    if (frente == -1) frente = 0;
    
    tras = (tras + 1) % TAM_FILA_BFS;
    fila_ids[tras] = id_setor;
}

int desenfileirar_id()
{
    if (frente == -1) return -1; // Fila vazia
    
    int id_setor = fila_ids[frente];
    
    // Se era o último elemento
    if (frente == tras) {
        frente = -1;
        tras = -1;
    } else {
        frente = (frente + 1) % TAM_FILA_BFS;
    }
    return id_setor;
}

int fila_vazia_id()
{
    return frente == -1;
}

void resetar_fila_id()
{
    frente = -1;
    tras = -1;
}

// ==========================================================
// FUNÇÃO BFS (Busca em Largura)
// ==========================================================

void bfs(GrafoHospital *grafo, int id_setor_inicial)
{
    if (!grafo || id_setor_inicial < 0 || id_setor_inicial >= grafo->total_vertices)
    {
        fprintf(stderr, "ERRO: Grafo ou setor inicial invalido.\n");
        return;
    }
    
    int visitado[TOTAL_SETORES];
    int distancia[TOTAL_SETORES];
    
    for (int i = 0; i < TOTAL_SETORES; i++)
    {
        visitado[i] = 0;      
        distancia[i] = -1;    
    }
    
    resetar_fila_id();
    
    enfileirar_id(id_setor_inicial);
    visitado[id_setor_inicial] = 1;
    distancia[id_setor_inicial] = 0;
    
    printf("\n======================================================\n");
    printf("BUSCA EM LARGURA (BFS) INICIADA  \n");
    printf("   Setor Inicial: [%d] %s\n", id_setor_inicial, grafo->vertices[id_setor_inicial].nome);
    printf("======================================================\n\n");
    
    printf(" Setores Alcançáveis (Ordem de Nível / Distância):\n");
    
    while (!fila_vazia_id())
    {
        int u = desenfileirar_id(); 
        
        printf("  -> Nivel %d: [%d] %s\n", distancia[u], u, grafo->vertices[u].nome);
        
        NoAdjacencia *atual = grafo->vertices[u].adjacentes;
        
        while (atual)
        {
            int v = atual->destino; 
            
         
            if (visitado[v] == 0)
            {
                visitado[v] = 1;     
                distancia[v] = distancia[u] + 1; 
                enfileirar_id(v);     
            }
            atual = atual->prox;
        }
    }
    
    printf("\n======================================================\n");
  
    printf(" Setores Inalcançáveis (Setores desconectados):\n");
    int inalcancaveis = 0;
    for (int i = 0; i < TOTAL_SETORES; i++) {
        if (distancia[i] == -1) {
            printf("  - [%d] %s\n", i, grafo->vertices[i].nome);
            inalcancaveis++;
        }
    }
    if (inalcancaveis == 0) {
        printf("  - Todos os setores foram alcançados.\n");
    }
    printf("======================================================\n");
}


// ==========================================================
// BUSCA EM PROFUNDIDADE (DFS) - ANÁLISE DE DEPENDÊNCIAS
// ==========================================================

void dfs_visitar(GrafoHospital *grafo, int u, int visitado[], int *tempo) 
{
    // Marca o vértice 'u' como Cinza (Em processo)
    visitado[u] = 1; 
    
    (*tempo)++;
    int tempo_inicial = *tempo; 
    
    printf("   -> Descoberta (Tempo %d): [%d] %s\n", tempo_inicial, u, grafo->vertices[u].nome);
    
    NoAdjacencia *atual = grafo->vertices[u].adjacentes;
    
    // Explora os vizinhos
    while (atual)
    {
        int v = atual->destino; 
        
        if (visitado[v] == 0) // Se o vizinho é Branco (Novo)
        {
            // Chamada recursiva para a profundidade
            dfs_visitar(grafo, v, visitado, tempo);
        }
        else if (visitado[v] == 1) // Se o vizinho é Cinza (Em processo)
        {
            // ALERTA: Retornamos ao nó 'u' a partir do vizinho 'v' que ainda não foi finalizado. Isso é um Ciclo!
            printf("   ⚠️ ALERTA DE DEPENDÊNCIA CIRCULAR (Ciclo): %s -> %s\n", 
                    grafo->vertices[u].nome, grafo->vertices[v].nome);
        }
        // Se visitado[v] == 2 (Preto), ignoramos (já está finalizado)
        
        atual = atual->prox;
    }
    
    // Finaliza o vértice 'u' (o nó e seus descendentes foram completamente explorados)
    // Marca como Preto
    visitado[u] = 2; 
    (*tempo)++;
    int tempo_final = *tempo; 
    
    printf("   <- Finalização (Tempo %d): [%d] %s\n", tempo_final, u, grafo->vertices[u].nome);
}

//=================================================
// Função principal da DFS
//=================================================

void dfs(GrafoHospital *grafo)
{
    if (!grafo) return;
    
    printf("\n======================================================\n");
    printf("BUSCA EM PROFUNDIDADE (DFS) - ANÁLISE DE DEPENDÊNCIAS\n");
    printf("======================================================\n");

    // Inicializa o array de cores/visitas: 0=Branco (Novo), 1=Cinza (Em processo), 2=Preto (Finalizado)
    int visitado[TOTAL_SETORES]; 
    for(int i = 0; i < TOTAL_SETORES; i++) {
        visitado[i] = 0;
    }

    int tempo = 0; // Inicializa o contador de tempo
    
    // Percorre todos os vértices (para lidar com grafos desconexos)
    for (int i = 0; i < TOTAL_SETORES; i++)
    {
        if (visitado[i] == 0) // Se for Branco, inicia a busca neste componente
        {
            printf("\n-- Iniciando DFS no componente do setor %s --\n", grafo->vertices[i].nome);
            dfs_visitar(grafo, i, visitado, &tempo);
        }
    }
    
    printf("\nAnálise DFS concluída. Tempo total: %d unidades.\n", tempo);
    printf("======================================================\n");
}

/* ============================================================
   Tarjan - Encontrar Pontos de Articulacao
   Saída: imprime setores cuja remoção desconecta o grafo.
============================================================ */

void tarjan_util(GrafoHospital *grafo, int u, int *tempo, int *disc, int *low, int *parent, int *ap)
{
    // inicializa discovery time e low
    disc[u] = low[u] = ++(*tempo);
    NoAdjacencia *adj = grafo->vertices[u].adjacentes;
    while (adj)
    {
        int v = adj->destino;
        if (disc[v] == 0)
        {
            parent[v] = u;
            tarjan_util(grafo, v, tempo, disc, low, parent, ap);
            // atualiza low[u]
            if (low[v] < low[u]) low[u] = low[v];
            // condição de ponto de articulação
            if (parent[u] == -1 && ( ( 0 ), 0)) {
            }
            if (parent[u] != -1 && low[v] >= disc[u])
            {
                ap[u] = 1;
            }
        }
        else if (v != parent[u]) // back edge
        {
            if (disc[v] < low[u]) low[u] = disc[v];
        }
        adj = adj->prox;
    }
}

void encontrar_pontos_articulacao(GrafoHospital *grafo) 
{
    if (!grafo)
    {
        fprintf(stderr, "ERRO: Grafo NULL. Nao e possivel executar Tarjan.\n");
        return;
    }

    int n = grafo->total_vertices;

    int *disc = (int *)calloc(n, sizeof(int));
    int *low  = (int *)calloc(n, sizeof(int));
    int *parent = (int *)malloc(n * sizeof(int));
    int *ap = (int *)calloc(n, sizeof(int));

    if (!disc || !low || !parent || !ap)
    {
        fprintf(stderr, "ERRO: Memoria insuficiente para Tarjan.\n");
        free(disc); free(low); free(parent); free(ap);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        disc[i] = 0;
        low[i] = 0;
        parent[i] = -1;
        ap[i] = 0;
    }

    int tempo = 0;
    for (int u = 0; u < n; u++)
    {
        if (disc[u] == 0)
        {
            disc[u] = low[u] = ++tempo;
            NoAdjacencia *adj = grafo->vertices[u].adjacentes;
            int filhos_raiz = 0;

            while (adj)
            {
                int v = adj->destino;

                if (disc[v] == 0)
                {
                    parent[v] = u;
                    filhos_raiz++;
                    tarjan_util(grafo, v, &tempo, disc, low, parent, ap);

                    if (low[v] < low[u]) low[u] = low[v];
                    if (parent[u] != -1 && low[v] >= disc[u]) ap[u] = 1;
                }
                else if (v != parent[u])
                {
                    if (disc[v] < low[u]) low[u] = disc[v];
                }
                adj = adj->prox;
            }

            if (filhos_raiz > 1)
                ap[u] = 1;
        }
    }

    printf("\n======================================================\n");
    printf("RELATORIO DE SETORES CRITICOS (PONTOS DE ARTICULACAO)\n"); 
    printf("======================================================\n"); 

    FILE *arquivo = fopen("setores_criticos.txt", "w");
    if (!arquivo)                                      
    {                                                  
        printf("ERRO ao criar arquivo de setores criticos.\n");
    }                                                  
    else                                               
    {                                                  
        fprintf(arquivo, "RELATORIO DE SETORES CRITICOS\n");
        fprintf(arquivo, "==============================\n\n");
    }                                                  

    int total_criticos = 0;
    for (int i = 0; i < n; i++)
    {
        if (ap[i])
        {
            printf("  - [%d] %s\n", i, grafo->vertices[i].nome);

            if (arquivo)
                fprintf(arquivo, "  - [%d] %s\n", i, grafo->vertices[i].nome);

            total_criticos++;
        }
    }

    if (total_criticos == 0)
    {
        printf("  Nenhum setor crítico identificado.\n");

        if (arquivo)
            fprintf(arquivo, "Nenhum setor critico identificado.\n");
    }
    else
    {
        printf("\n  Total de setores críticos: %d\n", total_criticos);

        if (arquivo)
            fprintf(arquivo, "\nTotal de setores criticos: %d\n", total_criticos); 
    }

    printf("======================================================\n");

    if (arquivo) fclose(arquivo); 
    printf("Arquivo 'setores_criticos.txt' gerado com sucesso.\n");

    free(disc);
    free(low);
    free(parent);
    free(ap);
}

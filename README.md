# 🚑 SOS — Sistema de Atendimento Hospitalar em C

Bem-vindo ao **SOS – Sistema de Organização de Setores e Atendimento**!  
Este projeto simula o funcionamento de um hospital utilizando **Filas por Prioridade e Grafos**, totalmente desenvolvido em **linguagem C**, como parte da disciplina de **Estrutura de Dados**.

Aqui a gente gerencia **pacientes**, **setores do hospital**, **rotas de atendimento** e ainda analisa **setores críticos** que, se caírem, quebram tudo 😈.

---

## 👥 O Time de Guerra

Esse sistema só ficou em pé porque esse grupo simplesmente EXISTE:

* **[Elane]** - Responsável pela implementação da `enfileirar()`, `desenfileirar()`, e detectar pontos críticos.
* **[Bianca]** - Foco na estrutura de controle da Fila (`fila.h`, `criar_fila()`) e implementar DFS análise de dependência
* **[Bruna]** - Desenho da aplicação, `main.c`, documentação (`README.md`) e e implementar BFS para setores alcançáveis.
* **[Matheus Coelho]** - Implementação de utilidades (`liberar_fila()`, `limpar_buffer()`),correção de bugs e implementação de saídas de emergência.

---

## 🧠 Estruturas Utilizadas

| Estrutura | Onde é usada | Finalidade |
|----------|---------------|------------|
| **Fila Dinâmica** | Atendimento de pacientes | Organizar por ordem de chegada |
| **Fila por Prioridade** | Verde, Amarela e Vermelha | Emergência hospitalar |
| **Grafo (Lista de Adjacência)** | Setores do hospital | Representar conexões reais |
| **BFS** | Análise de alcance | Ver setores acessíveis |
| **DFS** | Dependências | Detectar ciclos |
| **Tarjan** | Pontos críticos | Setores que não podem falhar |

---

## 🚦 Sistema de Prioridades

- 🟢 **Verde** — Baixa prioridade  
- 🟡 **Amarela** — Média prioridade  
- 🔴 **Vermelha** — Alta prioridade  

O atendimento sempre respeita a ordem:
> **Vermelha → Amarela → Verde**

---

## 🏥 Setores do Hospital (Grafo)

O hospital possui os seguintes setores:

- Recepção  
- Administração  
- Enfermaria  
- UTI  
- Centro Cirúrgico  
- Farmácia  
- Almoxarifado  
- Laboratório  
- Raio-X  
- Saída de Emergência  

As conexões entre eles são representadas por um **grafo direcionado**.

---

## ⚙️ Funcionalidades do Sistema

✅ Adicionar paciente com prioridade  
✅ Enfileirar automaticamente  
✅ Atender paciente respeitando prioridade  
✅ Exibir filas  
✅ Visualizar o grafo completo  
✅ Executar **BFS** (setores alcançáveis)  
✅ Executar **DFS** (dependências entre setores)  
✅ Executar **Tarjan** (setores críticos)  
✅ Gerar relatório  
✅ Liberar toda a memória corretamente  

---

## 🧪 Algoritmos Implementados

### 🔍 BFS — Busca em Largura
Mostra:
- Ordem de visitação
- Distância de cada setor
- Setores inalcançáveis

---

### 🧠 DFS — Busca em Profundidade
Analisa:
- Dependências entre setores
- Possíveis ciclos no fluxo hospitalar

---

### ⚠️ Tarjan — Pontos de Articulação
Detecta:
- Quais setores, se falharem, **quebram o funcionamento do hospital**
- Exemplo: Enfermaria, UTI, Centro Cirúrgico, etc.

---

## 🗂️ Organização dos Arquivos

```bash
Atividade_pratica_fila_C/
├── main.c
├── modules/
│   ├── fila.c
│   └── fila.h
├── README.md

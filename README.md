# Atividade_pratica_fila_C
# 🚑 SOS Fila de Atendimento: Gerenciamento de Pacientes em C!

Oiee!! Presta atenção no que temos que fazer: A gente pegou a **Atividade Prática 02** de Estrutura de Dados e resolveu encarar a Fila de frente. Sabe aquele sufoco de pronto-socorro? A gente resolveu simular a organização disso tudo no bom e velho **C**! >:D

---

### O Time de Resgate (VAI TOMAAANDO!)

A gente sabe que ninguém faz milagre sozinho, né? Essa galera aqui botou a mão na massa (e nos ponteiros! grazadeus!):

* **[Elane]** - Responsável pela implementação da `enfileirar()` e `desenfileirar()`.
* **[Bianca]** - Foco na estrutura de controle da Fila (`fila.h` e `criar_fila()`).
* **[Bruna]** - Desenho da aplicação, `main.c` e documentação (`README.md`).
* **[Matheus Coelho]** - Implementação de utilidades (`liberar_fila()`, `limpar_buffer()`) e correção de bugs.

### A Missão: Fila FIFO na Veia!

Nossa estrutura de dados escolhida foi a **Fila (Queue)**, porque na vida real (e no nosso código) quem chega primeiro, é atendido primeiro (meio óbvio). É o clássico **FIFO** (*First-In, First-Out*)!

| Estrutura Base | Aplicação Prática | O Lema |
| :--- | :--- | :--- |
| **Fila Dinâmica em C** | **Sistema de Atendimento a Pacientes** | "Primeiro a Chegar, Primeiro a ser Atendido!" |

### Como a Mágica Acontece (Modularização)

Para não virar uma bagunça de código (que eh horrível), separamos tudo em caixinhas. É tipo uma organização fodamente boa:

* **`main.c`**: A porta de entrada! É onde rola o menu interativo e a gente chama as funções da Fila.
* **`fila.h`**: A planta baixa! Contém todas as definições das nossas `structs` (`paciente`, `Elemento`, `Fila`) e a lista de todas as funções que a Fila sabe fazer (os protótipos).
* **`fila.c`**: A cozinha! É aqui que as receitas (funções) são implementadas, com muito `malloc`, `free` e ponteiro pra tudo que é canto! (prof jeanto adora)

#### As Funções Essenciais (A Espinha Dorsal do Projeto)

* `criar_fila()`: A gente abre as portas da clínica.
* `enfileirar()`: Chegou paciente novo! Ele vai direto pro **final** da fila.
* `desenfileirar()`: Chamando o próximo! Remove o paciente que está no **início** e retorna ele pra gente exibir.
* `lista_vazia()`: "Doutor, tem gente na recepção?" Responde se a fila zerou ou não.
* `imprimir_fila()`: Pra gente saber quem está esperando.
* `liberar_fila()`: O momento triste, mas necessário, de passar o rodo (que delícia) na memória (`free` em tudo!).

---

### Quer saber como ficou? Siga o Manuel de Instruzões! ("Manual de Instruções" se você não entendeu kkjjkkj eh meme)

Se você tem o GCC instalado, rodar nosso sistema é moleza.

1.  **Clone o projeto:**
    ```bash
    git clone https://github.com/MatheusCoelho13/Atividade_pratica_fila_C
    cd Atividade_pratica_fila_C 
    ```

2.  **Compile (Dizendo para o GCC juntar as peças):**
    ```bash
    gcc main.c fila.c -o atendimento_pacientes
    ```
    *(Mudei o nome do executável para algo mais divertido!)*

3.  **Execute (A hora da verdade!):**
    ```bash
    ./atendimento_pacientes
    ```

Agora é só usar e abusar com o menu e testar o nosso sistema de filas! (Que realmente ficou muito bom, tá? Isso porque foi meu grupo que fez! >:D)
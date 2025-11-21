#include "./modules/fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int main()
{
    int opcao;
  
    Fila *fila_priori1 = criar_fila(); // Baixa - Verde
    Fila *fila_priori2 = criar_fila(); // Média - Amarelo
    Fila *fila_priori3 = criar_fila(); // Alta - Vermelho

    if (!fila_priori1 || !fila_priori2 || !fila_priori3) {
        printf("Erro fatal: Falha ao inicializar as filas. Encerrando.\n");
        return 1;
    }

    do
    {
        printf("\n Sistema de Gerenciamento de Fila de Pacientes\n");
        printf("--------------------------------------------\n");
        printf("Selecione uma opção:\n");
        printf("1. Adicionar paciente à fila\n");
        printf("2. Atender próximo paciente\n");
        printf("3. Exibir filas de pacientes\n");
        printf("4. Sair\n");
        printf("Opção: ");
     
        if (scanf("%d", &opcao) != 1) {
            limpar_buffer();
            opcao = -1; 
        } else {
            limpar_buffer();
        }

        switch (opcao)
        {
        case 1:
            {
                char nome_adic[50]; 
                paciente pac;
                pac.prioridade = 0; 

                printf("\nAdicionar paciente.\n");
                printf("--------------------------------------------\n");
                printf("Digite o nome do paciente: ");
                
                if (scanf("%49[^\n]", nome_adic) != 1) {
                    limpar_buffer();
                    printf("Leitura do nome falhou.\n");
                    break;
                }
                limpar_buffer(); 

                pac = adicionar_paciente(nome_adic);
                
                printf("Defina nível de prioridade (1 a 3):\n");
                printf("1 - Verde (Baixa);\n2 - Amarelo (Média);\n3 - Vermelho (Alta);\nPrioridade: ");
                
                if (scanf("%d", &pac.prioridade) != 1) { 
                    printf("Prioridade inválida. Paciente não adicionado.\n");
                    limpar_buffer();
                    break;
                }
                limpar_buffer();

                if (pac.prioridade == 3) {
                    enfileirar(fila_priori3, pac);
                    printf("Paciente %s adicionado a fila VERMELHA (Alta).\n", pac.nome);
                } else if (pac.prioridade == 2) {
                    enfileirar(fila_priori2, pac);
                    printf("Paciente %s adicionado a fila AMARELA (Média).\n", pac.nome);
                } else if (pac.prioridade == 1) {
                    enfileirar(fila_priori1, pac);
                    printf("Paciente %s adicionado a fila VERDE (Baixa).\n", pac.nome);
                } else {
                    printf("Prioridade inválida (Use 1, 2 ou 3). Paciente não adicionado.\n");
                }

                printf("\nAperte ENTER para retornar ao menu.\n");
                getchar();
            }
            break;

        case 2:
            printf("\nAtender próximo paciente.\n");
            printf("--------------------------------------------\n");
            
            atender_proximo_paciente(fila_priori1, fila_priori2, fila_priori3); 

            printf("\n--- Próximo Paciente em Espera ---\n");
            

            if (!lista_vazia(fila_priori3)) {
                printf("Próximo atendimento será da Fila VERMELHA:\n");
                print_paciente(fila_priori3->inicio->dados); 
            } else if (!lista_vazia(fila_priori2)) {
                printf("Próximo atendimento será da Fila AMARELA:\n");
                print_paciente(fila_priori2->inicio->dados);
            } else if (!lista_vazia(fila_priori1)) {
                printf("Próximo atendimento será da Fila VERDE:\n");
                print_paciente(fila_priori1->inicio->dados);
            } else {
                printf("Todas as filas estão vazias.\n");
            }
            
            printf("\nAperte ENTER para retornar ao menu.\n");
            getchar();
            break;

        case 3:
            printf("\nExibir filas de pacientes.\n");
            printf("--------------------------------------------\n");

            if (lista_vazia(fila_priori1) && lista_vazia(fila_priori2) && lista_vazia(fila_priori3))
            {
                printf("As filas estão vazias.\n");
            }
            else
            {
                printf("Pacientes na fila de espera (Alta -> Baixa):\n");
                printf("-- VERMELHA (Alta Prioridade) --\n");
                imprimir_fila(fila_priori3);
                printf("-- AMARELA (Média Prioridade) --\n");
                imprimir_fila(fila_priori2);
                printf("-- VERDE (Baixa Prioridade) --\n");
                imprimir_fila(fila_priori1);
            }

            printf("\nAperte ENTER para retornar ao menu.\n");
            getchar();
            break;

        case 4:
         
            liberar_fila(fila_priori1);
            liberar_fila(fila_priori2);
            liberar_fila(fila_priori3);
            printf("\nSaindo do sistema. Até logo!\n");
            return 0; 
        
        default:
            printf("Opção inválida. Tente novamente.\n");
            limpar_buffer();
            break;
        }

    } while (opcao != 4);

    return 0;
}
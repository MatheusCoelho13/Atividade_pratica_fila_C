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

    // Criar grafo do hospital
    GrafoHospital *grafo_hospital = criar_grafo_hospital();
    if (!grafo_hospital)
    {
        printf("Erro fatal: Falha ao criar grafo do hospital. Encerrando.\n");
        return 1;
    }

    // Inserir vértices e arestas do hospital
    inserir_vertices_hospital(grafo_hospital);
    int total_arestas = inserir_arestas_hospital(grafo_hospital);
    printf("Total de conexões inseridas: %d\n\n", total_arestas);

    if (!fila_priori1 || !fila_priori2 || !fila_priori3) {
        printf("Erro fatal: Falha ao inicializar as filas. Encerrando.\n");
        liberar_grafo_hospital(grafo_hospital);
        return 1;
    }

    do
    {
        printf("\n=====================================================\n");
        printf("   Sistema de Gerenciamento de Pacientes\n");
        printf("=====================================================\n");
        printf("Selecione uma opcao:\n");
        printf("1. Adicionar paciente a fila\n");
        printf("2. Atender proximo paciente\n");
        printf("3. Exibir filas de pacientes\n");
        printf("4. Visualizar Grafo do Hospital\n");
        printf("5. Listar Setores Alcançáveis (BFS)\n");
        printf("6. Gerar relatorio \n");
        printf("7. Sair\n");
        printf("8. Detectar setores criticos (Tarjan)\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limpar_buffer();
            opcao = -1;
            printf("Entrada invalida! Digite apenas numeros.\n");
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

                printf("\nAdicionar Paciente\n");                    
                printf("-----------------------------------------------------\n");
                printf("Digite o nome do paciente: ");
                
                if (scanf("%49[^\n]", nome_adic) != 1) {
                    limpar_buffer();
                    printf("Leitura do nome falhou.\n");
                    break;
                }
                limpar_buffer(); 

                pac = adicionar_paciente(nome_adic);
                
                printf("\nSelecione a prioridade:\n");  
                printf("1 - Verde (Baixa)\n");
                printf("2 - Amarelo (Media)\n");
                printf("3 - Vermelho (Alta)\n");
                printf("Prioridade: ");
                
                if (scanf("%d", &pac.prioridade) != 1) { 
                    printf("Prioridade inválida. Paciente não adicionado.\n");
                    limpar_buffer();
                    break;
                }
                limpar_buffer();

                // Exibir tabela de setores e capturar selecao
                int setor_destino = exibir_tabela_setores();
                if (setor_destino == -1)
                {
                    printf("Operacao cancelada. Paciente nao adicionado.\n");
                    break;
                }

                printf("Paciente %s sera encaminhado para: %s\n\n", pac.nome, obter_nome_setor(setor_destino));

                if (pac.prioridade == 3) {
                    if (enfileirar(fila_priori3, pac) == 0)
                    {
                        printf("Paciente %s adicionado a fila VERMELHA (Alta).\n", pac.nome);
                    }
                    else
                    {
                        printf("ERRO: Nao foi possivel adicionar paciente a fila VERMELHA.\n");
                    }
                } else if (pac.prioridade == 2) {
                    if (enfileirar(fila_priori2, pac) == 0)
                    {
                        printf("Paciente %s adicionado a fila AMARELA (Média).\n", pac.nome);
                    }
                    else
                    {
                        printf("ERRO: Nao foi possivel adicionar paciente a fila AMARELA.\n");
                    }
                } else if (pac.prioridade == 1) {
                    if (enfileirar(fila_priori1, pac) == 0)
                    {
                        printf("Paciente %s adicionado a fila VERDE (Baixa).\n", pac.nome);
                    }
                    else
                    {
                        printf("ERRO: Nao foi possivel adicionar paciente a fila VERDE.\n");
                    }
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
        {
            printf("\nVisualizando o Grafo do Hospital...\n");
            printf("--------------------------------------------\n");
            imprimir_grafo_hospital(grafo_hospital);
            printf("\nAperte ENTER para retornar ao menu.\n");
            getchar();
        }
        break;

          /*case 5:
        {
            printf("\nListar Setores Alcançáveis usando BFS\n");
                    printf("--------------------------------------------\n");
            GrafoHospital *grafo = criar_grafo_hospital();
            if (!grafo) return 1;

            inserir_arestas_hospital(grafo);
            imprimir_grafo_hospital(grafo); 

            int setor_inicial = exibir_tabela_setores(); 
            
            if (setor_inicial != -1) {
                bfs(grafo, setor_inicial);
            }
            liberar_grafo_hospital(grafo); 
            
            return 0;
        }
        break; 
        deixei esse comentario gigante aqui pq vai que o codigo que eu substitui está errado, neah*/

        case 5:
        {
            printf("\nAnálise de Dependências (DFS)\n");
            printf("--------------------------------------------\n");
            
            GrafoHospital *grafo = criar_grafo_hospital();
            if (!grafo) break;
            inserir_arestas_hospital(grafo);
            
            dfs(grafo); 

            printf("\nAperte ENTER para retornar ao menu.\n");
            getchar(); 

            liberar_grafo_hospital(grafo); 
        }
        break;

        case 6:
        {
            paciente pac = {0};
            Gerar_relatorio(fila_priori1, fila_priori2, fila_priori3, pac);
        }
        break;

        case 7:
        {
            printf("\nLimpando memoria e encerrando o sistema...\n");
            printf("--------------------------------------------\n");
            liberar_grafo_hospital(grafo_hospital);
            liberar_todas_filas(fila_priori1, fila_priori2, fila_priori3);
            printf("\nSaindo do sistema. Até logo!\n");
            return 0;
        }

        case 8: 

        {
            printf("\nExecutando Tarjan para identificar setores criticos...\n"); 
            encontrar_pontos_articulacao(grafo_hospital);
            printf("\nRelatorio gerado. Aperte ENTER para voltar ao menu.\n");
            getchar(); 
        }
        break;

        default:
            printf("Opção inválida! Tente novamente.\n");
            limpar_buffer();
            break;
        }
        

    } while (opcao != 6);

    return 0;
}
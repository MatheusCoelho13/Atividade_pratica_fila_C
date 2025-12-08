#include "./modules/fila.h" // Caractere invisível removido
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função auxiliar para verificar se todas as filas estão vazias
int todas_filas_vazias(Fila *f1, Fila *f2, Fila *f3) {
    return lista_vazia(f1) && lista_vazia(f2) && lista_vazia(f3);
}

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
        printf("     Sistema de Gerenciamento de Pacientes\n");
        printf("=====================================================\n");
        printf("Selecione uma opcao:\n");
        printf("1. Adicionar paciente a fila\n");
        printf("2. Atender proximo paciente\n");
        printf("3. Exibir filas de pacientes\n");
        printf("4. Visualizar Grafo do Hospital\n");
        printf("5. Listar Setores Alcançáveis (BFS)\n");
        printf("6. Detectar setores criticos (Tarjan)\n");
        printf("7. Analisar Dependencias (DFS)\n");
        printf("8. Gerar relatorio \n");
        printf("9. Sair\n");
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
        case 1: // Adicionar paciente 
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
                    if (enfileirar(fila_priori3, pac) == 0) {
                        printf("Paciente %s adicionado a fila VERMELHA (Alta).\n", pac.nome);
                    } else {
                        printf("ERRO: Nao foi possivel adicionar paciente a fila VERMELHA (Fila cheia ou falha de memoria).\n");
                    }
                } else if (pac.prioridade == 2) {
                    if (enfileirar(fila_priori2, pac) == 0) {
                        printf("Paciente %s adicionado a fila AMARELA (Média).\n", pac.nome);
                    } else {
                        printf("ERRO: Nao foi possivel adicionar paciente a fila AMARELA (Fila cheia ou falha de memoria).\n");
                    }
                } else if (pac.prioridade == 1) {
                    if (enfileirar(fila_priori1, pac) == 0) {
                        printf("Paciente %s adicionado a fila VERDE (Baixa).\n", pac.nome);
                    } else {
                        printf("ERRO: Nao foi possivel adicionar paciente a fila VERDE (Fila cheia ou falha de memoria).\n");
                    }
                } else {
                    printf("Prioridade inválida (Use 1, 2 ou 3). Paciente não adicionado.\n");
                }

                printf("\nAperte ENTER para retornar ao menu.\n");
                getchar();
            }
            break;

        case 2: // Atender próximo paciente
            printf("\nAtender próximo paciente.\n");
            printf("--------------------------------------------\n");

            if (todas_filas_vazias(fila_priori1, fila_priori2, fila_priori3)) {
                printf("Nenhuma fila possui pacientes. Não há pacientes para atender.\n");
            } else {
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
                    printf("Todas as filas restantes estão vazias.\n");
                }
            }

            printf("\nAperte ENTER para retornar ao menu.\n");
            getchar();
            break;

        case 3: // Exibir filas de pacientes
            printf("\nExibir filas de pacientes.\n");
            printf("--------------------------------------------\n");

            if (todas_filas_vazias(fila_priori1, fila_priori2, fila_priori3))
            {
                printf("Todas as filas estão vazias. Nenhum paciente em espera.\n");
            }
            else
            {
                printf("Pacientes na fila de espera (Alta -> Baixa):\n");
                printf("-- VERMELHA (Alta Prioridade, %d pacientes) --\n", tamanho_fila(fila_priori3));
                imprimir_fila(fila_priori3);
                printf("-- AMARELA (Média Prioridade, %d pacientes) --\n", tamanho_fila(fila_priori2));
                imprimir_fila(fila_priori2);
                printf("-- VERDE (Baixa Prioridade, %d pacientes) --\n", tamanho_fila(fila_priori1));
                imprimir_fila(fila_priori1);
            }

            printf("\nAperte ENTER para retornar ao menu.\n");
            getchar();
            break;

        case 4: // Visualizar Grafo do Hospital
        {
            if (!grafo_hospital || grafo_hospital->total_vertices == 0) {
                 printf("Grafo do hospital não inicializado ou sem setores.\n");
                 break;
            }
            printf("\nVisualizando o Grafo do Hospital...\n");
            printf("--------------------------------------------\n");
            imprimir_grafo_hospital(grafo_hospital);
            printf("\nAperte ENTER para retornar ao menu.\n");
            getchar();
        }
        break;

        case 5: // Listar Setores Alcançáveis (BFS)
        {
            if (!grafo_hospital || grafo_hospital->total_vertices == 0) {
                 printf("Grafo do hospital não inicializado ou sem setores para busca.\n");
                 break;
            }

            int setor_partida;
            exibir_tabela_setores();
            printf("Digite o ID do setor de partida para BFS: ");
            if (scanf("%d", &setor_partida) == 1) {
                limpar_buffer();
                // Verificação de ID válido (assumindo que 0 a TOTAL_SETORES-1 são válidos)
                if (setor_partida >= 0 && setor_partida < 10) {
                     printf("\nExecutando Busca em Largura (BFS) a partir do setor %s...\n", obter_nome_setor(setor_partida));
                     bfs(grafo_hospital, setor_partida);
                } else {
                    printf("ID de setor inválido (fora do intervalo 0-9).\n");
                }
            } else {
                limpar_buffer();
                printf("ID de setor inválido.\n");
            }
            printf("\nAperte ENTER para retornar ao menu.\n");
            getchar();
        }
        break;

        case 6: // Detectar setores criticos (Tarjan)
        {
            if (!grafo_hospital || grafo_hospital->total_vertices == 0) {
                 printf("Grafo do hospital não inicializado ou sem setores para análise de criticidade.\n");
                 break;
            }
            printf("\nExecutando Tarjan para identificar setores criticos...\n");
            encontrar_pontos_articulacao(grafo_hospital);
            printf("\nRelatorio gerado. Aperte ENTER para voltar ao menu.\n");
            getchar();
        }
        break;

        case 7: // Analisar Dependencias (DFS)
        {
            if (!grafo_hospital || grafo_hospital->total_vertices == 0) {
                 printf("Grafo do hospital não inicializado ou sem setores para análise de dependências.\n");
                 break;
            }
            printf("\nExecutando DFS para analise de dependencias...\n");
            dfs(grafo_hospital);
            printf("\nAperte ENTER para voltar ao menu.\n");
            getchar();
        }
        break;

        case 8: // Gerar relatorio
        {
            if (todas_filas_vazias(fila_priori1, fila_priori2, fila_priori3)) {
                printf("Não é possível gerar relatório de pacientes pois todas as filas estão vazias.\n");
            } else {
                 printf("\nGerando relatório de filas...\n");
                 paciente pac = {0};
                 Gerar_relatorio(fila_priori1, fila_priori2, fila_priori3, pac);
                 printf("Relatório concluído.\n");
            }

            printf("\nAperte ENTER para voltar ao menu.\n");
            getchar();
        }
        break;

        case 9: // Sair
        {
            printf("\nLimpando memoria e encerrando o sistema...\n");
            printf("--------------------------------------------\n");
            liberar_grafo_hospital(grafo_hospital);
            liberar_todas_filas(fila_priori1, fila_priori2, fila_priori3);
            printf("\nSaindo do sistema. Até logo!\n");
            return 0;
        }

        default:
            printf("Opção inválida! Tente novamente.\n");
            limpar_buffer();
            break;
        }


    } while (opcao != 9);

    return 0;
}
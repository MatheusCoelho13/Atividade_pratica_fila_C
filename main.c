#include "./modules/fila.h"
#include <stdio.h>
        case 5:
        {
            printf("\nListar Setores Alcançáveis usando BFS\n");
            printf("--------------------------------------------\n");
            GrafoHospital *grafo = criar_grafo_hospital();
            if (!grafo) break;

            inserir_arestas_hospital(grafo);
            imprimir_grafo_hospital(grafo); 

            int setor_inicial = exibir_tabela_setores(); 
            
            if (setor_inicial != -1) {
                bfs(grafo, setor_inicial);
            }
            liberar_grafo_hospital(grafo); 
        }
        break;

        case 6:
        {
            paciente pac = {0};
            Gerar_relatorio(fila_priori1, fila_priori2, fila_priori3, pac);
            printf("\nRelatorio global da fila ordenada unica:\n");
            printf("  Total enfileirados: %d\n", obter_total_enfileirados());
            printf("  Total atendidos: %d\n", obter_total_atendidos());
            printf("  Tempo medio de espera (s): %.2f\n", obter_media_tempo_espera());
            printf("  Pico de tamanho da fila: %d\n", obter_max_tamanho_fila());
            printf("\nAperte ENTER para retornar ao menu.\n");
            getchar();
        }
        break;

        case 8:
        {
            char nome_adic[50];
            paciente pac;
            printf("\nAdicionar Paciente (fila ordenada)\n");
            printf("-----------------------------------------------------\n");
            printf("Digite o nome do paciente: ");
            if (scanf("%49[^
        printf("7. Sair\n");
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
            if (enfileirar_ordenado(fila_prioritaria, pac) == 0) {
                printf("Paciente %s adicionado na fila ordenada com prioridade %d.\n", pac.nome, pac.prioridade);
            } else {
                printf("ERRO: Não foi possivel adicionar paciente na fila ordenada.\n");
            }
            printf("\nAperte ENTER para retornar ao menu.\n");
            getchar();
        }
        break;

        case 9:
        {
            printf("\nFila ordenada por prioridade:\n");
            imprimir_fila(fila_prioritaria);
            printf("\nAperte ENTER para retornar ao menu.\n");
            getchar();
        }
        break;

        case 10:
        {
            paciente pac;
            int r = desenfileirar(fila_prioritaria, &pac);
            if (r == 0) {
                printf("Paciente atendido (fila ordenada):\n");
                print_paciente(pac);
            } else {
                printf("Fila ordenada vazia. Nada a atender.\n");
            }
            printf("\nAperte ENTER para retornar ao menu.\n");
            getchar();
        }
        break;

        case 11:
        {
            char nome_busca[50];
            printf("\nBuscar paciente na fila ordenada\n");
            printf("Nome: ");
            if (scanf("%49[^
        printf("Opcao: ");
                limpar_buffer();
                printf("Leitura falhou.\n");
                break;
            }
            limpar_buffer();
            int pos = buscar_paciente(fila_prioritaria, nome_busca);
            if (pos >= 0) printf("Paciente '%s' encontrado na posicao %d da fila ordenada.\n", nome_busca, pos);
            else printf("Paciente '%s' nao encontrado na fila ordenada.\n", nome_busca);
            printf("\nAperte ENTER para retornar ao menu.\n");
            getchar();
        }
        break;

        case 12:
        {
            const char *nome_arq = "fila_ordenada_export.txt";
            if (exportar_fila(fila_prioritaria, nome_arq) == 0) {
                printf("Fila ordenada exportada para '%s'\n", nome_arq);
            } else {
                printf("Falha ao exportar fila ordenada.\n");
            }
            printf("\nAperte ENTER para retornar ao menu.\n");
            getchar();
        }
        break;

        case 7:
        {
            printf("\nLimpando memoria e encerrando o sistema...\n");
            printf("--------------------------------------------\n");
            liberar_grafo_hospital(grafo_hospital);
            liberar_todas_filas(fila_priori1, fila_priori2, fila_priori3);
            liberar_fila(fila_prioritaria);
            printf("\nSaindo do sistema. Até logo!\n");
            return 0;
        }
        default:
            printf("Opção inválida! Tente novamente.\n");
            limpar_buffer();
            break;
        }

    } /* fim do while(1) */

    return 0;
}

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

          case 5:
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

      /*  case 6:
        {
            paciente pac = {0};
            Gerar_relatorio(fila_priori1, fila_priori2, fila_priori3, pac);
        }
        break; */

        case 6:
        {
            // Item 3: Chamamos a função completa que está em fila.c.
            // Usamos NULL para o último parâmetro (fila_unica) porque não o estamos usando.
            printf("\nGerando Relatório Estatístico...\n");
            printf("--------------------------------------------\n");
            Gerar_relatorio_estendido(fila_priori1, fila_priori2, fila_priori3, NULL); 
            printf("--------------------------------------------\n");
            
            // Item 7 (UX): Adiciona pausa para o usuário conseguir ler o relatório.
            printf("\nAperte ENTER para retornar ao menu.\n");
            getchar(); 
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
        default:
            printf("Opção inválida! Tente novamente.\n");
            limpar_buffer();
            break;
        }

    } while (opcao != 6);

    return 0;
}
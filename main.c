#include "./modules/fila.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
   
    int opcao;
    Fila *fila_cliente = criar_fila();

    do
    {
        printf("Sistema de Gerenciamento de Fila de Pacientes\n");
        printf("--------------------------------------------\n");
        printf("Selecione uma opção:\n");
        printf("1. Adicionar paciente à fila\n");
        printf("2. Atender próximo paciente\n");
        printf("3. Exibir fila de pacientes\n");
        printf("4. Sair\n");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao)
        {
        case 1:
            // Código para adicionar paciente à fila
            {
                char nome;
                paciente pac = adicionar_paciente(nome);

                printf("Adicionar paciente.\n");
                printf("--------------------------------------------\n");
                printf("Digite o nome do paciente: ");
                scanf("%49[^\n]", pac.nome);
                limpar_buffer();

                enfileirar(fila_cliente, pac);
                printf("Paciente adicionado à fila com sucesso!\n");
                limpar_buffer();

                printf("Aperte ENTER para retornar ao menu.\n");
                getchar();

                break;
}
        case 2:
            // Código para atender próximo paciente

            printf("Atender próximo paciente.\n");
            printf("--------------------------------------------\n");

            if (lista_vazia(fila_cliente))
            {
                printf("A fila está vazia. Nenhum paciente para atender.\n\n");
            }
            else
            {
                paciente atendido = desenfileirar(fila_cliente);
                printf("Paciente atendido:\n");
                print_paciente(atendido);
                
                printf("Paciente removido da fila com sucesso!\n\n");
                printf("Proximo paciente na fila:\n");
                if (!lista_vazia(fila_cliente))
                {
                    paciente proximo = fila_cliente->inicio->dados;
                    print_paciente(proximo);
                }else
                printf("\n");
            }

            printf("Aperte ENTER para retornar ao menu.\n");
            getchar();

            break;

        case 3:
            // Código para exibir fila de pacientes

            printf("Exibir fila de pacientes.\n");
            printf("--------------------------------------------\n");

            if (lista_vazia(fila_cliente))
            {
                printf("A fila está vazia.\n");
            }
            else
            {
                printf("Pacientes na fila de espera:\n");
                imprimir_fila(fila_cliente);
            }

            printf("Aperte ENTER para retornar ao menu.\n");
            getchar();

            break;

        case 4:
            // Código para sair

            printf("Saindo do sistema. Até logo!\n");
            exit(0);

            break;

        default:
            break;
        }

    } while (opcao != 4);
    printf("Opção inválida. Tente novamente.\n");

    return 0;
}
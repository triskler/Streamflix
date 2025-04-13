#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "interface.h"
#include "arquivos.h"
#include "interacoes.h"
#include "listas.h"
#include "favoritos.h"
#include "relatorios.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    exibirMensagemBoasVindas();

    char nome_arquivo[256] = {0};
    CSVData *dados = NULL;

    solicitarNomeArquivo(nome_arquivo, sizeof(nome_arquivo));

    if(strlen(nome_arquivo) == 0) {
        printf("\nNenhum arquivo especificado. Encerrando...\n");
        return 1;
    }

    dados = carregarCSV(nome_arquivo);

    if(dados) {
        int opcao;
        char input[10];
        do {
            printf("\n=== MENU PRINCIPAL ===");
            printf("\n1. Exibir conteúdo");
            printf("\n2. Adicionar título");
            printf("\n3. Remover título");
            printf("\n4. Editar título");
            printf("\n5. Pesquisar");
            printf("\n6. Registrar interação");
            printf("\n7. Gerenciar playlists");
            printf("\n8. Favoritos");
            printf("\n9. Relatórios");
            printf("\n10. Sair");
            printf("\nEscolha: ");

            fgets(input, sizeof(input), stdin);
            opcao = atoi(input);

            switch(opcao) {
                case 1:
                    exibirConteudoCSV(dados);
                    break;
                case 2:
                    adicionarNovoTitulo(nome_arquivo);
                    liberarDadosCSV(dados);
                    dados = carregarCSV(nome_arquivo);
                    break;
                case 3:
                    removerTitulo(dados, nome_arquivo);
                    break;
                case 4:
                    editarTitulo(dados, nome_arquivo);
                    break;
                case 5:
                    pesquisarConteudo(dados);
                    break;
                case 6: {
                    char user_id[50];
                    printf("ID do usuário: ");
                    fgets(user_id, sizeof(user_id), stdin);
                    user_id[strcspn(user_id, "\n")] = '\0';
                    registrarInteracao(dados, user_id);
                    break;
                }
                case 7: {
                    char user_id[50];
                    printf("ID do usuário: ");
                    fgets(user_id, sizeof(user_id), stdin);
                    user_id[strcspn(user_id, "\n")] = '\0';
                    gerenciarPlaylists(user_id, dados);
                    break;
                }
                case 8: {
                    char user_id[50];
                    printf("ID do usuário: ");
                    fgets(user_id, sizeof(user_id), stdin);
                    user_id[strcspn(user_id, "\n")] = '\0';

                    printf("\n1. Ver favoritos\n2. Marcar favorito\nEscolha: ");
                    fgets(input, sizeof(input), stdin);
                    int subopcao = atoi(input);

                    if(subopcao == 1) {
                        mostrarFavoritos(user_id, dados);
                    } else if(subopcao == 2) {
                        exibirConteudoCSV(dados);
                        printf("Digite o número do conteúdo: ");
                        fgets(input, sizeof(input), stdin);
                        int escolha = atoi(input);

                        if(escolha < 1 || escolha > dados->num_linhas) {
                            printf("Escolha inválida!\n");
                            break;
                        }

                        char content_id[20];
                        strncpy(content_id, dados->linhas[escolha-1], strcspn(dados->linhas[escolha-1], ","));
                        content_id[strcspn(content_id, ",")] = '\0';
                        marcarFavorito(user_id, content_id);
                    }
                    break;
                }
                case 9:
                    gerarRelatorios(dados);
                    break;
                case 10:
                    printf("\nSaindo...\n");
                    break;
                default:
                    printf("\nOpção inválida! Tente novamente.\n");
            }
        } while(opcao != 10);

        liberarDadosCSV(dados);
    }

    #ifdef _WIN32
    system("pause");
    #endif

    return 0;
}
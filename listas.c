#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listas.h"
#include "interface.h"

static int gerarIDUnico() {
    return rand() % 9000 + 1000; // Gera ID entre 1000-9999
}

void criarPlaylist(const char *user_id) {
    Playlist nova;
    printf("\nNome da nova playlist: ");
    fgets(nova.nome, 50, stdin);
    nova.nome[strcspn(nova.nome, "\n")] = '\0';

    sprintf(nova.playlist_id, "PL%d", gerarIDUnico());
    strcpy(nova.user_id, user_id);

    // Salvar playlist
    FILE *file = fopen(PLAYISTS_CSV, "a");
    if(file) {
        fprintf(file, "%s,%s,%s\n", nova.playlist_id, nova.user_id, nova.nome);
        fclose(file);
        printf("Playlist criada com sucesso! ID: %s\n", nova.playlist_id);
    }
}

void adicionarConteudoPlaylist(const char *playlist_id, CSVData *conteudos) {
    exibirConteudoCSV(conteudos);

    int escolha;
    printf("\nDigite o número do conteúdo para adicionar: ");
    scanf("%d", &escolha);
    getchar();

    if(escolha < 1 || escolha > conteudos->num_linhas) {
        printf("Escolha inválida!\n");
        return;
    }

    // Obter ID do conteúdo
    char *linha = conteudos->linhas[escolha-1];
    char content_id[20];
    strncpy(content_id, linha, strcspn(linha, ","));
    content_id[strcspn(content_id, ",")] = '\0';

    // Registrar na playlist
    FILE *file = fopen(PLAYIST_CONTENTS_CSV, "a");
    if(file) {
        fprintf(file, "%s,%s\n", playlist_id, content_id);
        fclose(file);
        printf("Conteúdo adicionado à playlist!\n");
    }
}

void mostrarPlaylistsUsuario(const char *user_id) {
    FILE *file = fopen(PLAYISTS_CSV, "r");
    if(!file) return;

    printf("\n=== SUAS PLAYLISTS ===\n");
    char linha[100];
    while(fgets(linha, sizeof(linha), file)) {
        char id[10], uid[10], nome[50];
        sscanf(linha, "%[^,],%[^,],%[^\n]", id, uid, nome);

        if(strcmp(uid, user_id) == 0) {
            printf("ID: %s | Nome: %s\n", id, nome);
        }
    }
    fclose(file);
    printf("======================\n");
}

void gerenciarPlaylists(const char *user_id, CSVData *conteudos) {
    mostrarPlaylistsUsuario(user_id);

    printf("\n1. Criar nova playlist\n2. Adicionar conteúdo\nEscolha: ");
    int opcao;
    scanf("%d", &opcao);
    getchar();

    if(opcao == 1) {
        criarPlaylist(user_id);
    } else if(opcao == 2) {
        char playlist_id[10];
        printf("Digite o ID da playlist: ");
        fgets(playlist_id, 10, stdin);
        playlist_id[strcspn(playlist_id, "\n")] = '\0';
        adicionarConteudoPlaylist(playlist_id, conteudos);
    }
}
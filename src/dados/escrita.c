// src/dados/escrita.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escrita.h"

// Função para salvar o catálogo em um arquivo CSV
void salvar_catalogo(const char *nome_arquivo, Catalogo *catalogo) {
    FILE *file = fopen(nome_arquivo, "w");
    if (!file) {
        perror("Erro ao abrir o arquivo para salvar o catálogo");
        return;
    }

    for (int i = 0; i < catalogo->quantidade; i++) {
        fprintf(file, "%s,%s,%d,%s,%d\n",
                catalogo->filmes[i].titulo,
                catalogo->filmes[i].categoria,
                catalogo->filmes[i].duracao,
                catalogo->filmes[i].classificacao_etaria,
                catalogo->filmes[i].numero_visualizacoes);
    }

    fclose(file);
}

// Função para salvar o histórico de usuários em um arquivo CSV
void salvar_historico(const char *nome_arquivo, SistemaUsuarios *sistema) {
    FILE *file = fopen(nome_arquivo, "w");
    if (!file) {
        perror("Erro ao abrir o arquivo para salvar o histórico de usuários");
        return;
    }

    for (int i = 0; i < sistema->quantidade; i++) {
        fprintf(file, "%s,%d", sistema->usuarios[i].nome, sistema->usuarios[i].interacoes);
        for (int j = 0; j < sistema->usuarios[i].quantidade_historico; j++) {
            fprintf(file, ",%s", sistema->usuarios[i].historico[j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
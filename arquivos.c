#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivos.h"

CSVData* carregarCSV(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(!arquivo) {
        printf("Erro ao abrir o arquivo: %s\n", nome_arquivo);
        return NULL;
    }

    CSVData *dados = malloc(sizeof(CSVData));
    dados->num_linhas = 0;
    dados->linhas = NULL;

    char buffer[TAMANHO_LINHA];

    while(fgets(buffer, sizeof(buffer), arquivo)) {
        char **novo = realloc(dados->linhas, (dados->num_linhas + 1) * sizeof(char*));
        if(!novo) {
            printf("Erro de alocação de memória!\n");
            liberarDadosCSV(dados);
            fclose(arquivo);
            return NULL;
        }

        dados->linhas = novo;
        buffer[strcspn(buffer, "\r\n")] = '\0';
        dados->linhas[dados->num_linhas] = strdup(buffer);

        if(!dados->linhas[dados->num_linhas]) {
            printf("Erro ao alocar memória para a linha!\n");
            liberarDadosCSV(dados);
            fclose(arquivo);
            return NULL;
        }

        dados->num_linhas++;
    }

    fclose(arquivo);
    return dados;
}

void liberarDadosCSV(CSVData *dados) {
    if(dados) {
        for(int i = 0; i < dados->num_linhas; i++) {
            free(dados->linhas[i]);
        }
        free(dados->linhas);
        free(dados);
    }
}

void salvarCSV(const CSVData *dados, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if(!arquivo) {
        printf("Erro ao abrir arquivo para escrita!\n");
        return;
    }

    for(int i = 0; i < dados->num_linhas; i++) {
        fprintf(arquivo, "%s\n", dados->linhas[i]);
    }

    fclose(arquivo);
}
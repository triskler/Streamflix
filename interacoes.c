#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interacoes.h"
#include "interface.h"

void logInteracao(const char *user_id, const char *content_id, Acao acao) {
    FILE *arquivo = fopen(INTERACOES_CSV, "a");
    if(!arquivo) {
        arquivo = fopen(INTERACOES_CSV, "w");
        fprintf(arquivo, "user_id,content_id,acao,timestamp\n");
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);

    const char *acao_str;
    switch(acao) {
        case PLAY: acao_str = "PLAY"; break;
        case PAUSE: acao_str = "PAUSE"; break;
        case FINISH: acao_str = "FINISH"; break;
    }

    fprintf(arquivo, "%s,%s,%s,%s\n", user_id, content_id, acao_str, timestamp);
    fclose(arquivo);
}

void registrarVisualizacao(CSVData *dados, int indice) {
    char *linha = dados->linhas[indice];
    char *fields[5];
    char *token = strtok(linha, ",");

    for(int i = 0; i < 5 && token != NULL; i++) {
        fields[i] = token;
        token = strtok(NULL, ",");
    }

    int views = atoi(fields[4]) + 1;

    char nova_linha[256];
    snprintf(nova_linha, sizeof(nova_linha), "%s,%s,%s,%s,%d",
             fields[0], fields[1], fields[2], fields[3], views);

    free(dados->linhas[indice]);
    dados->linhas[indice] = strdup(nova_linha);
}

void registrarInteracao(CSVData *dados, const char *user_id) {
    if(!dados || dados->num_linhas == 0) {
        printf("Nenhum conteúdo disponível!\n");
        return;
    }

    exibirConteudoCSV(dados);

    int escolha;
    printf("\nDigite o número do conteúdo: ");
    scanf("%d", &escolha);
    getchar();

    if(escolha < 1 || escolha > dados->num_linhas) {
        printf("Escolha inválida!\n");
        return;
    }

    printf("\n1. Play\n2. Pause\n3. Finish\nAção: ");
    int acao;
    scanf("%d", &acao);
    getchar();

    char content_id[50];
    strncpy(content_id, dados->linhas[escolha-1], strcspn(dados->linhas[escolha-1], ","));
    content_id[strcspn(content_id, ",")] = '\0';

    switch(acao) {
        case 1:
            logInteracao(user_id, content_id, PLAY);
            break;
        case 2:
            logInteracao(user_id, content_id, PAUSE);
            break;
        case 3:
            logInteracao(user_id, content_id, FINISH);
            registrarVisualizacao(dados, escolha-1);
            break;
        default:
            printf("Ação inválida!\n");
    }
}
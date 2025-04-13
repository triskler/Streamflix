#include "relatorios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Funções de comparação para qsort
int compararVisualizacoes(const void *a, const void *b) {
    return ((ConteudoPopular*)b)->visualizacoes - ((ConteudoPopular*)a)->visualizacoes;
}

int compararCategorias(const void *a, const void *b) {
    return ((CategoriaPopular*)b)->total - ((CategoriaPopular*)a)->total;
}

int compararUsuarios(const void *a, const void *b) {
    return ((UsuarioAtivo*)b)->interacoes - ((UsuarioAtivo*)a)->interacoes;
}

void mostrarConteudosPopulares(CSVData *conteudos) {
    if(!conteudos || conteudos->num_linhas == 0) {
        printf("\nNenhum conteúdo disponível para análise!\n");
        return;
    }

    ConteudoPopular *ranking = malloc(conteudos->num_linhas * sizeof(ConteudoPopular));
    int count = 0;

    for(int i = 0; i < conteudos->num_linhas; i++) {
        char linha[256];
        strcpy(linha, conteudos->linhas[i]);

        char *fields[5];
        char *token = strtok(linha, ",");
        for(int j = 0; j < 5 && token != NULL; j++) {
            fields[j] = token;
            token = strtok(NULL, ",");
        }

        if(fields[0] && fields[4]) {
            strncpy(ranking[count].id, fields[0], 20);
            ranking[count].visualizacoes = atoi(fields[4]);
            count++;
        }
    }

    qsort(ranking, count, sizeof(ConteudoPopular), compararVisualizacoes);

    printf("\n=== TOP 10 CONTEÚDOS MAIS VISTOS ===\n");
    int limite = (count > 10) ? 10 : count;
    for(int i = 0; i < limite; i++) {
        printf("%2d. %-15s - %6d visualizações\n",
              i+1, ranking[i].id, ranking[i].visualizacoes);
    }
    free(ranking);
}

void mostrarCategoriasPopulares(CSVData *conteudos) {
    if(!conteudos || conteudos->num_linhas == 0) {
        printf("\nNenhum conteúdo disponível para análise!\n");
        return;
    }

    CategoriaPopular *categorias = NULL;
    int num_categorias = 0;

    for(int i = 0; i < conteudos->num_linhas; i++) {
        char linha[256];
        strcpy(linha, conteudos->linhas[i]);

        char *fields[5];
        char *token = strtok(linha, ",");
        for(int j = 0; j < 5 && token != NULL; j++) {
            fields[j] = token;
            token = strtok(NULL, ",");
        }

        if(fields[2] && fields[4]) {
            int encontrada = 0;
            for(int k = 0; k < num_categorias; k++) {
                if(strcmp(categorias[k].categoria, fields[2]) == 0) {
                    categorias[k].total += atoi(fields[4]);
                    encontrada = 1;
                    break;
                }
            }

            if(!encontrada) {
                num_categorias++;
                categorias = realloc(categorias, num_categorias * sizeof(CategoriaPopular));
                strncpy(categorias[num_categorias-1].categoria, fields[2], 50);
                categorias[num_categorias-1].total = atoi(fields[4]);
            }
        }
    }

    qsort(categorias, num_categorias, sizeof(CategoriaPopular), compararCategorias);

    printf("\n=== CATEGORIAS MAIS POPULARES ===\n");
    int limite = (num_categorias > 5) ? 5 : num_categorias;
    for(int i = 0; i < limite; i++) {
        printf("%2d. %-20s - %6d visualizações\n",
              i+1, categorias[i].categoria, categorias[i].total);
    }
    free(categorias);
}

void mostrarUsuariosAtivos() {
    FILE *file = fopen(INTERACOES_CSV, "r");
    if(!file) {
        printf("\nNenhuma interação registrada ainda!\n");
        return;
    }

    UsuarioAtivo *usuarios = NULL;
    int num_usuarios = 0;
    char linha[100];

    while(fgets(linha, sizeof(linha), file)) {
        char user_id[20];
        sscanf(linha, "%[^,],", user_id);

        int encontrado = 0;
        for(int i = 0; i < num_usuarios; i++) {
            if(strcmp(usuarios[i].user_id, user_id) == 0) {
                usuarios[i].interacoes++;
                encontrado = 1;
                break;
            }
        }

        if(!encontrado) {
            num_usuarios++;
            usuarios = realloc(usuarios, num_usuarios * sizeof(UsuarioAtivo));
            strncpy(usuarios[num_usuarios-1].user_id, user_id, 20);
            usuarios[num_usuarios-1].interacoes = 1;
        }
    }
    fclose(file);

    qsort(usuarios, num_usuarios, sizeof(UsuarioAtivo), compararUsuarios);

    printf("\n=== TOP 10 USUÁRIOS MAIS ATIVOS ===\n");
    int limite = (num_usuarios > 10) ? 10 : num_usuarios;
    for(int i = 0; i < limite; i++) {
        printf("%2d. %-15s - %4d interações\n",
              i+1, usuarios[i].user_id, usuarios[i].interacoes);
    }
    free(usuarios);
}

void gerarRelatorios(CSVData *conteudos) {
    printf("\n=== RELATÓRIOS STREAMFLIX ===\n");
    mostrarConteudosPopulares(conteudos);
    mostrarCategoriasPopulares(conteudos);
    mostrarUsuariosAtivos();
    printf("===============================\n");
    #ifdef _WIN32
    system("pause");
    #endif
}
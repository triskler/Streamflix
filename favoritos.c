#include <stdio.h>
#include <string.h>
#include "favoritos.h"
#include "interface.h"

void marcarFavorito(const char *user_id, const char *content_id) {
    FILE *file = fopen(FAVORITOS_CSV, "a");
    if(file) {
        fprintf(file, "%s,%s\n", user_id, content_id);
        fclose(file);
        printf("Conteúdo marcado como favorito!\n");
    }
}

void mostrarFavoritos(const char *user_id, CSVData *conteudos) {
    FILE *file = fopen(FAVORITOS_CSV, "r");
    if(!file) return;

    printf("\n=== SEUS FAVORITOS ===\n");
    char linha[100];
    while(fgets(linha, sizeof(linha), file)) {
        char uid[10], cid[10];
        sscanf(linha, "%[^,],%s", uid, cid);

        if(strcmp(uid, user_id) == 0) {
            // Procurar conteúdo correspondente
            for(int i = 0; i < conteudos->num_linhas; i++) {
                if(strstr(conteudos->linhas[i], cid) == conteudos->linhas[i]) {
                    printf("%s\n", conteudos->linhas[i]);
                    break;
                }
            }
        }
    }
    fclose(file);
    printf("======================\n");
}
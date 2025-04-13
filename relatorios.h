#ifndef RELATORIOS_H
#define RELATORIOS_H

#include "arquivos.h"
#include "interacoes.h"

typedef struct {
    char id[20];
    int visualizacoes;
} ConteudoPopular;

typedef struct {
    char categoria[50];
    int total;
} CategoriaPopular;

typedef struct {
    char user_id[20];
    int interacoes;
} UsuarioAtivo;

// Protótipos das funções
int compararVisualizacoes(const void *a, const void *b);
int compararCategorias(const void *a, const void *b);
int compararUsuarios(const void *a, const void *b);
void mostrarConteudosPopulares(CSVData *conteudos);
void mostrarCategoriasPopulares(CSVData *conteudos);
void mostrarUsuariosAtivos();
void gerarRelatorios(CSVData *conteudos);

#endif
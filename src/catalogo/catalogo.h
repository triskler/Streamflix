// src/catalogo/catalogo.h

#ifndef CATALOGO_H
#define CATALOGO_H

typedef struct {
    char titulo[100];
    char categoria[50];
    int duracao; // em minutos
    char classificacao_etaria[10];
    int numero_visualizacoes;
} Filme;

typedef struct {
    Filme *filmes;
    int quantidade;
} Catalogo;

void carregar_catalogo(const char *nome_arquivo, Catalogo *catalogo);
void liberar_catalogo(Catalogo *catalogo);
void adicionar_filme(Catalogo *catalogo, Filme filme);
void remover_filme(Catalogo *catalogo, const char *titulo);
void editar_filme(Catalogo *catalogo, const char *titulo, Filme novo_filme);
void exibir_filmes(Catalogo *catalogo);

#endif // CATALOGO_H
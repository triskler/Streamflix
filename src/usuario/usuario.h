// src/usuario/usuario.h

#ifndef USUARIO_H
#define USUARIO_H

#include "../catalogo/catalogo.h"

typedef struct {
    char nome[100];
    int interacoes; // Número de interações do usuário
    char historico[100][100]; // Histórico de filmes assistidos
    int quantidade_historico; // Quantidade de filmes no histórico
} Usuario;

typedef struct {
    Usuario *usuarios;
    int quantidade;
} SistemaUsuarios;

void registrar_interacao(SistemaUsuarios *sistema, const char *usuario, const char *titulo, const char *acao);
void adicionar_usuario(SistemaUsuarios *sistema, const char *nome);
void exibir_usuarios(SistemaUsuarios *sistema);

#endif // USUARIO_H
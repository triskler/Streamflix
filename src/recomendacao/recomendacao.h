// src/recomendacao/recomendacao.h

#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include "../usuario/usuario.h"
#include "../catalogo/catalogo.h"

void recomendar_filmes(SistemaUsuarios *sistema, const char *usuario, Catalogo *catalogo);

#endif // RECOMENDACAO_H
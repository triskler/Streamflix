#ifndef FAVORITOS_H
#define FAVORITOS_H

#include "arquivos.h"

#define FAVORITOS_CSV "favoritos.csv"

void marcarFavorito(const char *user_id, const char *content_id);
void mostrarFavoritos(const char *user_id, CSVData *conteudos);

#endif
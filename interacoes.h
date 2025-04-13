#ifndef INTERACOES_H
#define INTERACOES_H

#include "arquivos.h"

#define INTERACOES_CSV "interacoes.csv"

typedef enum {PLAY, PAUSE, FINISH} Acao;

void registrarInteracao(CSVData *dados, const char *user_id);
void logInteracao(const char *user_id, const char *content_id, Acao acao);
void registrarVisualizacao(CSVData *dados, int indice);

#endif
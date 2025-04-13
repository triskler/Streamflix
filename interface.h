#ifndef INTERFACE_H
#define INTERFACE_H

#include "arquivos.h"

void exibirMensagemBoasVindas();
void solicitarNomeArquivo(char *buffer, size_t tamanho);
void exibirConteudoCSV(const CSVData *dados);
void adicionarNovoTitulo(const char *nome_arquivo);
void removerTitulo(CSVData *dados, const char *nome_arquivo);
void editarTitulo(CSVData *dados, const char *nome_arquivo);
void pesquisarConteudo(const CSVData *dados);
void exibirResultadosPesquisa(const CSVData *dados, int *indices, int total);

#endif
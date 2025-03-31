// src/utils/utils.c

#include <stdio.h>

// Função para limpar o buffer de entrada
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
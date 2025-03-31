// tests/test_catalogo.c

#include <stdio.h>
#include <assert.h>
#include "catalogo/catalogo.h"

void test_adicionar_filme() {
    Catalogo catalogo;
    catalogo.quantidade = 0;
    catalogo.filmes = malloc(sizeof(Filme) * 10); // Alocação inicial

    Filme filme = {"Filme Teste", "Ação", 120, "12", 0};
    adicionar_filme(&catalogo, filme);

    assert(catalogo.quantidade == 1);
    assert(strcmp(catalogo.filmes[0].titulo, "Filme Teste") == 0);

    free(catalogo.filmes);
}

void run_tests() {
    test_adicionar_filme();
    printf("Todos os testes passaram!\n");
}

int main() {
    run_tests();
    return 0;
}
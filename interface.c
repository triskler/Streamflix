#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

void exibirMensagemBoasVindas() {
    printf("Bem vindo ao StreamFlix!\n");
    printf("Por favor, carregue um arquivo .csv.\n");
}

void solicitarNomeArquivo(char *buffer, size_t tamanho) {
    printf("\nDigite o nome do arquivo CSV: ");
    fflush(stdout);

    if(fgets(buffer, tamanho, stdin)) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
    }
}

void exibirConteudoCSV(const CSVData *dados) {
    if(!dados || dados->num_linhas == 0) {
        printf("\nArquivo vazio ou nao carregado!\n");
        return;
    }

    printf("\n=== CONTEUDO DO ARQUIVO ===\n");
    for(int i = 0; i < dados->num_linhas; i++) {
        printf("Linha %d: %s\n", i+1, dados->linhas[i]);
    }
    printf("===========================\n");
}

void adicionarNovoTitulo(const char *nome_arquivo) {
    char titulo[100], genero[50];
    int ano, id;
    char buffer[100];

    printf("\n--- Novo Titulo ---\n");

    while(1) {
        printf("ID: ");
        fgets(buffer, sizeof(buffer), stdin);
        if(sscanf(buffer, "%d", &id) == 1) break;
        printf("ID invalido! Digite um numero inteiro.\n");
    }

    printf("Titulo: ");
    fgets(titulo, sizeof(titulo), stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    printf("Genero: ");
    fgets(genero, sizeof(genero), stdin);
    genero[strcspn(genero, "\n")] = '\0';

    while(1) {
        printf("Ano: ");
        fgets(buffer, sizeof(buffer), stdin);
        if(sscanf(buffer, "%d", &ano) == 1) break;
        printf("Ano invalido! Digite um numero inteiro.\n");
    }

    FILE *arquivo = fopen(nome_arquivo, "a");
    if(arquivo) {
        fprintf(arquivo, "\n%d;%s;%s;%d", id, titulo, genero, ano);
        fclose(arquivo);
        printf("\nTitulo adicionado com sucesso!\n");
    } else {
        printf("Erro ao abrir o arquivo para adicao!\n");
    }
}

void removerTitulo(CSVData *dados, const char *nome_arquivo) {
    if (!dados || dados->num_linhas == 0) {
        printf("\nNenhum dado carregado para remover!\n");
        return;
    }

    exibirConteudoCSV(dados);

    int linha;
    char buffer[10];
    printf("\nDigite o numero da linha a ser removida: ");
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &linha) != 1 || linha < 1 || linha > dados->num_linhas) {
        printf("Linha invalida!\n");
        return;
    }

    linha--;
    free(dados->linhas[linha]);

    for (int i = linha; i < dados->num_linhas - 1; i++) {
        dados->linhas[i] = dados->linhas[i + 1];
    }

    dados->num_linhas--;
    char **novo = realloc(dados->linhas, dados->num_linhas * sizeof(char *));
    if (dados->num_linhas > 0 && !novo) {
        printf("Erro ao realocar memoria!\n");
        return;
    }
    dados->linhas = novo;

    salvarCSV(dados, nome_arquivo);
    printf("Linha %d removida com sucesso!\n", linha + 1);
}

void editarTitulo(CSVData *dados, const char *nome_arquivo) {
    if (!dados || dados->num_linhas == 0) {
        printf("\nNenhum dado carregado para editar!\n");
        #ifdef _WIN32
        system("pause");
        #endif
        return;
    }

    exibirConteudoCSV(dados);

    int linha;
    char buffer[100];
    printf("\nDigite o numero da linha a editar: ");
    fflush(stdout);
    fgets(buffer, sizeof(buffer), stdin);

    if (sscanf(buffer, "%d", &linha) != 1 || linha < 1 || linha > dados->num_linhas) {
        printf("Linha invalida!\n");
        #ifdef _WIN32
        system("pause");
        #endif
        return;
    }
    linha--;

    // Fazer cópia da linha original
    char *linha_copia = strdup(dados->linhas[linha]);
    char *campos[5] = {0}; // Agora com 5 campos

    // Dividir a cópia em campos usando o delimitador correto
    char *token = strtok(linha_copia, ",");
    for(int i = 0; i < 5 && token != NULL; i++) {
        campos[i] = token;
        token = strtok(NULL, ",");
    }

    // Verificar se todos os campos foram capturados
    if(!campos[0] || !campos[1] || !campos[2] || !campos[3] || !campos[4]) {
        printf("Formato de linha invalido! Verifique o delimitador e numero de campos.\n");
        free(linha_copia);
        #ifdef _WIN32
        system("pause");
        #endif
        return;
    }

    // Mostrar campos atuais
    printf("\nCampos atuais:\n");
    printf("1. Titulo: %s\n", campos[0]);
    printf("2. Categoria: %s\n", campos[1]);
    printf("3. Duracao: %s\n", campos[2]);
    printf("4. Classificacao etaria: %s\n", campos[3]);
    printf("5. Visualizacoes: %s\n", campos[4]);

    // Selecionar campo para editar
    int campo;
    printf("\nDigite o numero do campo a editar (1-5): ");
    fflush(stdout);
    fgets(buffer, sizeof(buffer), stdin);

    if (sscanf(buffer, "%d", &campo) != 1 || campo < 1 || campo > 5) {
        printf("Campo invalido!\n");
        free(linha_copia);
        #ifdef _WIN32
        system("pause");
        #endif
        return;
    }

    // Obter novo valor
    char novo_valor[100];
    printf("Digite o novo valor: ");
    fflush(stdout);
    fgets(novo_valor, sizeof(novo_valor), stdin);
    novo_valor[strcspn(novo_valor, "\n")] = '\0';

    // Atualizar campo específico
    switch(campo) {
        case 1: strncpy(campos[0], novo_valor, strlen(campos[0])); break;
        case 2: strncpy(campos[1], novo_valor, strlen(campos[1])); break;
        case 3: strncpy(campos[2], novo_valor, strlen(campos[2])); break;
        case 4: strncpy(campos[3], novo_valor, strlen(campos[3])); break;
        case 5: strncpy(campos[4], novo_valor, strlen(campos[4])); break;
    }

    // Reconstruir a linha
    char nova_linha[256];
    snprintf(nova_linha, sizeof(nova_linha), "%s,%s,%s,%s,%s",
             campos[0], campos[1], campos[2], campos[3], campos[4]);

    // Atualizar dados
    free(dados->linhas[linha]);
    dados->linhas[linha] = strdup(nova_linha);

    // Salvar alterações
    salvarCSV(dados, nome_arquivo);
    free(linha_copia);

    printf("\nAlteracoes salvas com sucesso!\n");
    #ifdef _WIN32
    system("pause");
    #endif
}

void pesquisarConteudo(const CSVData *dados) {
    if (!dados || dados->num_linhas == 0) {
        printf("\nNenhum dado carregado para pesquisa!\n");
        #ifdef _WIN32
        system("pause");
        #endif
        return;
    }

    int opcao;
    char termo[100];
    int idade;

    printf("\n=== OPCOES DE PESQUISA ===\n");
    printf("1. Pesquisar por titulo\n");
    printf("2. Pesquisar por categoria\n");
    printf("3. Pesquisar por classificacao etaria\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    while(getchar() != '\n'); // Limpar buffer

    // Obter termo de pesquisa
    if(opcao != 3) {
        printf("Digite o termo de pesquisa: ");
        fgets(termo, sizeof(termo), stdin);
        termo[strcspn(termo, "\n")] = '\0';
    } else {
        printf("Digite a idade maxima: ");
        scanf("%d", &idade);
        while(getchar() != '\n');
    }

    // Preparar resultados
    int *indices = malloc(dados->num_linhas * sizeof(int));
    int contador = 0;

    for(int i = 0; i < dados->num_linhas; i++) {
        char linha[256];
        strcpy(linha, dados->linhas[i]);

        char *titulo = strtok(linha, ",");
        char *categoria = strtok(NULL, ",");
        char *duracao = strtok(NULL, ",");
        char *classificacao = strtok(NULL, ",");
        char *visualizacoes = strtok(NULL, ",");

        if(titulo && categoria && classificacao) {
            int match = 0;
            switch(opcao) {
                case 1: // Título
                    match = (strstr(titulo, termo) != NULL);
                    break;
                case 2: // Categoria
                    match = (strstr(categoria, termo) != NULL);
                    break;
                case 3: // Classificação
                    match = (atoi(classificacao) <= idade);
                    break;
            }

            if(match) {
                indices[contador++] = i;
            }
        }
    }

    exibirResultadosPesquisa(dados, indices, contador);
    free(indices);
}

void exibirResultadosPesquisa(const CSVData *dados, int *indices, int total) {
    printf("\n=== RESULTADOS ENCONTRADOS (%d) ===\n", total);
    for(int i = 0; i < total; i++) {
        printf("[%d] %s\n", i+1, dados->linhas[indices[i]]);
    }
    printf("===================================\n");
    #ifdef _WIN32
    system("pause");
    #endif
}
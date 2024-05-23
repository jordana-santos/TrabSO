//ugly: resposta do chat pra como copiar uma matriz pra um vetor

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int nLinhas;
    int nColunas;
    int **matriz;
} Matriz;

// Função para criar uma matriz dinamicamente
Matriz* criarMatriz(int nLinhas, int nColunas) {
    Matriz *m = malloc(sizeof(Matriz));
    m->nLinhas = nLinhas;
    m->nColunas = nColunas;

    // Aloca memória para as linhas
    m->matriz = malloc(nLinhas * sizeof(int *));
    
    // Aloca memória para as colunas em cada linha
    for (int i = 0; i < nLinhas; i++) {
        m->matriz[i] = malloc(nColunas * sizeof(int));
    }
    
    return m;
}

// Função para liberar a memória da matriz
void liberarMatriz(Matriz *m) {
    for (int i = 0; i < m->nLinhas; i++) {
        free(m->matriz[i]);
    }
    free(m->matriz);
    free(m);
}

// Função para ler uma matriz de um arquivo
Matriz* lerMatrizDoArquivo(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    int nLinhas, nColunas;
    
    // Leitura das dimensões da matriz
    if (fscanf(file, "%d %d", &nLinhas, &nColunas) != 2) {
        fprintf(stderr, "Erro ao ler as dimensões da matriz\n");
        fclose(file);
        return NULL;
    }

    // Criação da matriz
    Matriz *m = criarMatriz(nLinhas, nColunas);

    // Leitura dos elementos da matriz
    for (int i = 0; i < nLinhas; i++) {
        for (int j = 0; j < nColunas; j++) {
            if (fscanf(file, "%d", &m->matriz[i][j]) != 1) {
                fprintf(stderr, "Erro ao ler o elemento [%d][%d]\n", i, j);
                liberarMatriz(m);
                fclose(file);
                return NULL;
            }
        }
    }

    fclose(file);
    return m;
}

// Função para imprimir uma matriz
void imprimirMatriz(Matriz *m) {
    for (int i = 0; i < m->nLinhas; i++) {
        for (int j = 0; j < m->nColunas; j++) {
            printf("%d ", m->matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    const char *nomeArquivo = "matriz.txt";
    Matriz *m = lerMatrizDoArquivo(nomeArquivo);

    if (m != NULL) {
        printf("Matriz lida do arquivo:\n");
        imprimirMatriz(m);
        liberarMatriz(m);
    }

    return 0;
}

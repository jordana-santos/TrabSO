#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int **matriz;
    int nLinhas;
    int tipoCalculo; //1:soma, 2:multiplicacao, 3:reducao
} Matriz; 

Matriz AlocarDinamicamente(FILE *arq, char *argv[], Matriz mtz){  
    mtz.nLinhas = atoi(argv[2]);
    mtz.matriz = (int **)malloc(mtz.nLinhas * mtz.nLinhas * sizeof(int));

    for (int i = 0; i < mtz.nLinhas; i++){
        for (int j = 0; j < mtz.nLinhas; j++) {
            fscanf(arq, "%d", &mtz.matriz[i][j]);
        }
    }
    return mtz; 
}

int AbrirArquivo(FILE *arq[], int nArq, char *nomesArq[]){ 
    for (int i = 0; i < nArq; i++){
        arq[i] = fopen(nomesArq[i+3], "r+"); 
        if(arq[i] == NULL){
            printf("Erro ao abrir o arquivo %s \n", nomesArq[i]);
            for (int j = 0; j < i; j++) //fecha arq ja abertos e libera recursos
                fclose(arq[j]); 
            return 1;
        }
    }
    return 1;
} 

void FecharArquivo(FILE *arq[], int numArq){
    for (int i = 0; i < numArq; i++){
        if (arq[i] != NULL)
            fclose(arq[i]);
    }
}

void somaMatriz(Matriz* mtz[]){
    //0: mtzA, 1:mtzB, 3:mtzD
    int soma;
    for (int i = 0; i < mtz[0]->nLinhas; i++){
        for (int j = 0; j < mtz[0]->nLinhas; j++){
            soma = mtz[0]->matriz[i][j] + mtz[1]->matriz[i][j];
            mtz[3]->matriz[i][j] = soma;
        }
    }
    //return *mtz[3];
}

void gravaMatriz(FILE arq[], Matriz mtz){
    for (int i = 0; i < mtz.nLinhas; i++){
        for (int j = 0; j < mtz.nLinhas; j++){
            fprintf(arq, "%d ", mtz.matriz[i][j]);
        }
        printf("\n");
    }
}

void multiplicaMatriz(Matriz* mtz[]){
    //2:mtzC, 3:mtzD, 4:mtzE
    int n = mtz[2]->nLinhas;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                mtz[4]->matriz[i][j] += mtz[2]->matriz[i][k] * mtz[3]->matriz[k][j];
            }
        }
    }
    //return mtz[4];
}

int reduzMatriz(Matriz* mtz){
    int reducao = 0;
    for (int i = 0; i < mtz->nLinhas; i++) {
        for (int j = 0; j < mtz->nLinhas; i++) {
            reducao += mtz->matriz[i][j];
        }
    }
    return reducao;
}

void *treadProcessamento(void *matriz){
    pthread_t id = pthread_self();
    Matriz *mtz = (Matriz*)matriz; 
    if (mtz->tipoCalculo == 1)
        somaMatriz(mtz);
    else if (mtz->tipoCalculo == 2)
        multiplicaMatriz(mtz);
    else 
        reduzMatriz(mtz);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 4){
        printf("Quantidade de argumentos invalida\n");
        return 1;
    }

    int qntThreads = atoi(argv[1]);
    pthread_t idPrincipal = pthread_self(); //captura id da thread principal
    pthread_t outrosId[qntThreads]; 
    
    Matriz *matrizes[5]; //instancias da struct Matriz 
    //0:mtzA, 1:mtzB, 2:mtzC, 3:mtzD, 4:mtzE
    int rc; //review
    int reducao; 
    float tempoSoma, tempoTotal, tempoReducao, tempoMulti;
    int nArq = argc - 3; 
    FILE *arq[nArq];  //lista de arquivos
  
    //passo 1 : leitura das matrizes A e B
    AbrirArquivo(arq, nArq, argv);

    *matrizes[0] = AlocarDinamicamente(arq[0], argv, *matrizes[0]);
    *matrizes[1] = AlocarDinamicamente(arq[1], argv, *matrizes[1]);  
    *matrizes[3] = AlocarDinamicamente(arq[3], argv, *matrizes[3]);
    
    //passo 2 : soma das matrizes A e B
    for (int i = 0; i < qntThreads; i++){
        rc = pthread_create(&outrosId[i], NULL, treadProcessamento, (void *)&matrizes[i]);
    } 
    //T threads do tipo processamento
    
    //passo 3: Gravacao da martriz D
    gravaMatriz(arq[3], *matrizes[3]);
    //1 thread do tipo escrita e 1 thread do tipo leitura

    //passo 4 : Leitura da matriz C
    *matrizes[2] = AlocarDinamicamente(arq[2], argv, *matrizes[2]);
    //1 thread do tipo escrita e 1 thread do tipo leitura
    
    //passo 5 : multiplicacao das matrizes C e D
    *matrizes[4] = AlocarDinamicamente(arq[4], argv, *matrizes[4]);
    multiplicaMatriz(*matrizes);
    //T threads do tipo processamento
    
    //passo 6 : gravacao da matriz E
    gravaMatriz(arq[4], *matrizes[4]);
    //1 thread do tipo escrita e 1 thread do tipo processamento

    //passo 7 : Reducao da matriz E e saida do valo na tela
    reducao = reduzMatriz(matrizes[4]);
    //1 thread do tipo escrita e 1 thread do tipo processamento

    //saidas
    printf("Redução: %d\n", reducao);
    printf("Tempo soma: %.3f segundos.\n", tempoSoma);
    printf("Tempo multiplicação: %.3f segundos.\n", tempoMulti);
    printf("Tempo redução: %.3f segundos.\n", tempoReducao);
    printf("Tempo total: %.3f segundos.\n", tempoTotal);
    

    //liberação de memória
    FecharArquivo(arq, nArq);
    for (int i = 0; i < 5; i++){
        free(matrizes[i]->matriz);
    }

    return 0;
}
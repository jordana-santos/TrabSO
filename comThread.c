#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_t idPrincipal;
pthread_t outrosId[]; //precisa ser uma lista com a quantidade de threads

typedef struct {
    int **matriz;
    int nThread;
    int nLinhas;
} Matriz; 

Matriz AlocarDinamicamente(FILE *arq, char *argv[], Matriz mtz){ 
    mtz.nThread = atoi(argv[1]); 
    mtz.nLinhas = atoi(argv[2]);
    //ta dando um warning em mtz.matriz (assignment to 'int **' from incompatible pointer type 'int *')
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
        else 
            printf("Arquivo %s aberto com sucesso \n", nomesArq[i+3]); //fixme: tirar dps. flag de teste apenas pra verificar se ta abrindo
    }
    return 1;
} 

void FecharArquivo(FILE *arq[], int numArq){
    for (int i = 0; i < numArq; i++){
        if (arq[i] != NULL)
            fclose(arq[i]);
    }
}

Matriz somaMatriz(Matriz mtzA, Matriz mtzB, Matriz mtzD){
    int soma;
    for (int i = 0; i < mtzA.nLinhas; i++){
        for (int j = 0; j < mtzA.nLinhas; j++){
            soma = mtzA.matriz[i][j] + mtzB.matriz[i][j];
            mtzD.matriz[i][j] = soma;
        }
    }
    return mtzD;
}

void gravaMatriz(FILE arq[], Matriz mtz){
    for (int i = 0; i < mtz.nLinhas; i++){
        for (int j = 0; j < mtz.nLinhas; j++){
            fprintf(arq, "%d ", mtz.matriz[i][j]);
        }
        printf("\n");
    }
}

Matriz multiplicaMatriz(Matriz mtzC, Matriz mtzD, Matriz mtzE){
    int n = mtzC.nLinhas;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                mtzE.matriz[i][j] += mtzC.matriz[i][k] * mtzD.matriz[k][j];
            }
        }
    }
    return mtzE;
}

int reduzMatriz(Matriz mtz){
    int reducao = 0;
    for (int i = 0; i < mtz.nLinhas; i++) {
        for (int j = 0; j < mtz.nLinhas; i++) {
            reducao += mtz.matriz[i][j];
        }
    }
    return reducao;
}

int main(int argc, char *argv[]) {
    if (argc < 4){
        printf("Quantidade de argumentos invalida\n");
        return 1;
    }

    idPrincipal = pthread_self(); //captura id da thread principal

    Matriz mtzA, mtzB, mtzC, mtzD, mtzE; //instancias da struct Matriz
    int reducao; 
    float tempoSoma, tempoTotal, tempoReducao, tempoMulti;
    int nArq = argc - 3; 
    FILE *arq[nArq];  //lista de arquivos
  
    //passo 1 : leitura das matrizes A e B
    AbrirArquivo(arq, nArq, argv);

    mtzA = AlocarDinamicamente(arq[0], argv, mtzA);
    mtzB = AlocarDinamicamente(arq[1], argv, mtzB);  
    mtzD = AlocarDinamicamente(arq[3], argv, mtzD);
    
    //passo 2 : soma das matrizes A e B
    somaMatriz(mtzA, mtzB, mtzD);
    //T threads do tipo processamento
    
    //passo 3: Gravacao da martriz D
    gravaMatriz(arq[3], mtzD);
    //1 thread do tipo escrita e 1 thread do tipo leitura

    //passo 4 : Leitura da matriz C
    mtzC = AlocarDinamicamente(arq[2], argv, mtzC);
    //1 thread do tipo escrita e 1 thread do tipo leitura
    
    //passo 5 : multiplicacao das matrizes C e D
    mtzE = AlocarDinamicamente(arq[4], argv, mtzE);
    multiplicaMatriz(mtzC, mtzD, mtzE);
    //T threads do tipo processamento
    
    //passo 6 : gravacao da matriz E
    gravaMatriz(arq[4], mtzE);
    //1 thread do tipo escrita e 1 thread do tipo processamento

    //passo 7 : Reducao da matriz E e saida do valo na tela
    reducao = reduzMatriz(mtzE);
    //1 thread do tipo escrita e 1 thread do tipo processamento

    //saidas
    printf("Redução: %d\n", reducao);
    printf("Tempo soma: %.3f segundos.\n", tempoSoma);
    printf("Tempo multiplicação: %.3f segundos.\n", tempoMulti);
    printf("Tempo redução: %.3f segundos.\n", tempoReducao);
    printf("Tempo total: %.3f segundos.\n", tempoTotal);
    

    //liberação de memória
    FecharArquivo(arq, nArq);
    free(mtzA.matriz);
    free(mtzB.matriz);
    free(mtzC.matriz);
    free(mtzD.matriz);
    free(mtzE.matriz);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **matriz;
    int nThread;
    int nLinhas;
} Matriz; 

Matriz AlocarDinamicamente(FILE *arq, char *argv[], Matriz mtz){ 
    mtz.nThread = atoi(argv[1]); 
    mtz.nLinhas = atoi(argv[2]);
    mtz.matriz = (int *)malloc(mtz.nLinhas * mtz.nLinhas * sizeof(int));

    for (int i = 0; i < mtz.nLinhas; i++){
        for (int j = 0; j < mtz.nLinhas; j++) {
            fscanf(arq, "%d", &mtz.matriz[i][j]);
        }
    }
    
    return mtz; 
}

int AbrirArquivo(FILE *arq[], int nArq, char *nomesArq[]){ 
    for (int i = 0; i < nArq; i++){
        arq[i] = fopen(nomesArq[i+3], "r"); 
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


int main(int argc, char *argv[]) {
    if (argc < 4){
        printf("Quantidade de argumentos invalida\n");
        return 1;
    }

    Matriz mtzA, mtzB, mtzC, mtzD, mtzE; //instancias da struct Matriz
    //int reducao; 
    //float tempoSoma, tempoTotal, tempoRedução, tempoMulti;
    int nArq = argc - 3; 
    FILE *arq[nArq];  //lista de arquivos
  
    //passo 1 
    AbrirArquivo(arq, nArq, argv);

    //alocação em 1 etapa
    AlocarDinamicamente(arq[0], argv, mtzA);
    AlocarDinamicamente(arq[1], argv, mtzB);  
    AlocarDinamicamente(arq[2], argv, mtzC);
    AlocarDinamicamente(arq[3], argv, mtzD);
    AlocarDinamicamente(arq[4], argv, mtzE);
    
    //passo 2
    //T threads do tipo processamento
    
    //passo 3 e 4
    //1 thread do tipo escrita e 1 thread do tipo leitura
    
    //passo 5
    //T threads do tipo processamento
    
    //passo 6 e 7
    //1 thread do tipo escrita e 1 thread do tipo processamento

    //saidas
    /*
    printf("Redução: %d\n", reducao);
    printf("Tempo soma: %.3f segundos.\n", tempoSoma);
    printf("Tempo multiplicação: %.3f segundos.\n", tempoMulti);
    printf("Tempo redução: %.3f segundos.\n", tempoRedução);
    printf("Tempo total: %.3f segundos.\n", tempoTotal);
    */
    

    //liberação de memória
    //fixme: ta dando um warning nos mtz aq ('mtzA.matriz' may be used uninitialized in this function)
    FecharArquivo(arq, nArq);
    free(mtzA.matriz);
    free(mtzB.matriz);
    free(mtzC.matriz);
    free(mtzD.matriz);
    free(mtzE.matriz);

    return 0;
}
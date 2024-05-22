#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int nLinhas;
    int *matriz; //como definir o numero de linhas/colunas?
    int qtdThreads;
} Matriz; 

void AlocarDinamicamente(FILE *arq[], Matriz mtz){ //REVIEW: isso funciona pra tds as matrizes?
     mtz.matriz = (Matriz *) malloc(mtz.nLinhas * mtz.nLinhas * sizeof(Matriz));

}

void AbrirArquivo(FILE *arq[], int nArq, char *nomesArq[]){ 
    for (int i = 0; i < nArq; i++){
        arq[i] = fopen(nomesArq[i+3], "r"); 
        if(arq[i] == NULL){
            printf("Erro ao abrir o arquivo %s \n", nomesArq[i]);
            for (int j = 0; j < i; j++){ //fecha arq ja abertos e libera recursos
                fclose(arq[j]); 
            }
            return 1;
        }
        else 
            printf("Arquivo %s aberto com sucesso \n", nomesArq[i]); //FIXME: flag de teste apenas pra verificar se ta abrindo os arq
    }
}

void FecharArquivo(FILE *arq[]){
    for (int i = 0; i < 3; i++){
        if (arq[i] != NULL)
            fclose(arq[i]);
    }
}

void CopiarParaVetor(FILE *arq[], Matriz mtz){ //arrumar vetor

}


int main(int argc, char *argv[]) {
    if (argc < 4){
        printf("Quantidade de argumentos invalida\n");
        return 1;
    }

    Matriz mtz; //instancia da struct Matriz

    int nThreads = atoi(argv[1]); 
    mtz.nLinhas = atoi(argv[2]); 
    int reducao; 
    float tempoSoma, tempoTotal, tempoRedução, tempoMulti;
    int nArq = argc - 3; 
    FILE *arq[nArq];  //lista de arquivos

    //alocação em 1 etapa
    AlocarDinamicamente(arq, mtz); //como q passa um atrubuto de struct como parametro 
  
    //passo 1 
    AbrirArquivo(arq, nArq, &argv);
    CopiarParaVetor(arq, mtz); 

    
    //passo 2
    //T threads do tipo processamento
    
    //passo 3 e 4
    //1 thread do tipo escrita e 1 thread do tipo leitura
    
    //passo 5
    //T threads do tipo processamento
    
    //passo 6 e 7
    //1 thread do tipo escrita e 1 thread do tipo processamento

    FecharArquivo(arq);
    //saidas
    printf("Redução: %d\n", reducao);
    printf("Tempo soma: %.3f segundos.\n", tempoSoma);
    printf("Tempo multiplicação: %.3f segundos.\n", tempoMulti);
    printf("Tempo redução: %.3f segundos.\n", tempoRedução);
    printf("Tempo total: %.3f segundos.\n", tempoTotal);

    return 0;
}
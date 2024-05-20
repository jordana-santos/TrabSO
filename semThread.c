#include <stdio.h>

typedef struct {
    int *matriz;
    int num;
} matriz;

void AlocarDinamicamente(){
    //alocar matrizes

}

void AbrirArquivo(FILE *arq[], char *nomesArq[]){
    for (int i = 0; i < 3; i++){
        arq[i] = fopen(nomesArq[i], "r"); 
        if(arq[i] == NULL)
            printf("Erro ao abrir o arquivo %s \n", nomesArq[i]);
        else 
            printf("Arquivo %s aberto com sucesso \n", nomesArq[i]); //flag de teste apenas pra verificar se ta abrindo os arq
    }
}

void FecharArquivo(FILE *arq[]){
    for (int i = 0; i < 3; i++){
        if (arq[i] != NULL)
            fclose(arq[i]);
    }
}

void CopiarParaVetor(){
    //fazer a copia no vetor
}


int main(int argc, char *argv[]) {
    int num = 4; //ARRUMAR!!!! // numero de threads
    int reducao;
    float tempoSoma, tempoTotal, tempoRedução, tempoMulti;
    //FILE *arq[] = {"arqMatrizA.txt", "arqMatrizB.txt", "arqMatrizC.txt"}; // ?? não sei como fazer
    FILE *arq[3];


    //alocação em 1 etapa
    AlocarDinamicamente();

    for (int i = 0; i < 2; i++) {
        leitura(arq[i]);
    }

    //passo 1 
    AbrirArquivo(arq, &argv[1]);
    CopiarParaVetor();

    
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
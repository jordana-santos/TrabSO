#include <stdio.h>

typedef struct {
    int *matriz;
    int num;
} matriz;

 void AlocarDinamicamente(){
    //alocar matrizes

}

void AbrirArquivo(){
    //checar arquivo
}

void CopiarParaVetor(){
    //fazer a copia no vetor
}


int main(int argc, char *argv[])
{
    int num = 4; //ARRUMAR!!!! // numero de threads
    int redução;
    float tempoSoma, tempoTotal, tempoRedução, tempoMulti;
    char *arq[] = {"arqMatrizA.txt", "arqMatrizB.txt", "arqMatrizC.txt"}; // ?? não sei como fazer

    //alocação em 1 etapa
    AlocarDinamicamente();

    for (int i = 0; i < 2; i++) {
        leitura(arq[i]);
    }

    //passo 1 
    AbrirArquivo();
    CopiarParaVetor();

    
    //passo 2
    //T threads do tipo processamento
    
    //passo 3 e 4
    //1 thread do tipo escrita e 1 thread do tipo leitura
    
    //passo 5
    //T threads do tipo processamento
    
    //passo 6 e 7
    //1 thread do tipo escrita e 1 thread do tipo processamento


    //saidas
    printf("Redução: %d\n", redução);
    printf("Tempo soma: %.3f segundos.\n", tempoSoma);
    printf("Tempo multiplicação: %.3f segundos.\n", tempoMulti);
    printf("Tempo redução: %.3f segundos.\n", tempoRedução);
    printf("Tempo total: %.3f segundos.\n", tempoTotal);

    return 0;
    
}
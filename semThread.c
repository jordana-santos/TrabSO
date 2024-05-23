#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int matriz; //como definir o numero de linhas/colunas?
    int nThread;
    int nLinhas;
} Matriz; 

Matriz AlocarDinamicamente(FILE *arq[], char *argv[], Matriz mtz){ //todo: copiar a matriz pra um vetor (olha o exemplo.c)
    mtz.matriz = (Matriz *) malloc(mtz.nLinhas * mtz.nLinhas * sizeof(Matriz));
    mtz.nThread = atoi(argv[1]); 
    mtz.nLinhas = atoi(argv[2]);



    return mtz; //review: precisa de ponteiro ou isso ja eh suficiente?
}

void AbrirArquivo(FILE *arq[], int nArq, char *nomesArq[]){ //review: isso abre todos os arq?
    for (int i = 0; i < nArq; i++){
        arq[i] = fopen(nomesArq[i+3], "r"); 
        if(arq[i] == NULL){
            printf("Erro ao abrir o arquivo %s \n", nomesArq[i]);
            for (int j = 0; j < i; j++) //fecha arq ja abertos e libera recursos
                fclose(arq[j]); 
            return 1;
        }
        else 
            printf("Arquivo %s aberto com sucesso \n", nomesArq[i]); //fixme: tirar dps. flag de teste apenas pra verificar se ta abrindo
    }
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

    Matriz mtzA, mtzB, mtzC; //instancias da struct Matriz
    int reducao; 
    float tempoSoma, tempoTotal, tempoRedução, tempoMulti;
    int nArq = argc - 3; 
    FILE *arq[nArq];  //lista de arquivos

    //alocação em 1 etapa
    //review: isso conta como alocacao em 1 etapa?
    AlocarDinamicamente(arq, &argv, mtzA);
    AlocarDinamicamente(arq, &argv, mtzB);  
    AlocarDinamicamente(arq, &argv, mtzC);
  
    //passo 1 
    AbrirArquivo(arq, nArq, &argv);
    
    //passo 2
    //T threads do tipo processamento
    
    //passo 3 e 4
    //1 thread do tipo escrita e 1 thread do tipo leitura
    
    //passo 5
    //T threads do tipo processamento
    
    //passo 6 e 7
    //1 thread do tipo escrita e 1 thread do tipo processamento

    FecharArquivo(arq, nArq);
    //saidas
    printf("Redução: %d\n", reducao);
    printf("Tempo soma: %.3f segundos.\n", tempoSoma);
    printf("Tempo multiplicação: %.3f segundos.\n", tempoMulti);
    printf("Tempo redução: %.3f segundos.\n", tempoRedução);
    printf("Tempo total: %.3f segundos.\n", tempoTotal);

    return 0;
}
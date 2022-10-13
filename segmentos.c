/*
    Alunos: Lucas Santos Rodrigues (20213001521)
            Vinícius Ferreira Pinheiro (20213005208)
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    char arquivo[20];
    FILE *texto;
    int numNum;

    printf("Digite o nome do arquivo: ");
    scanf("%s", arquivo);
    texto = fopen(arquivo, "r+");

    // TAMANHO DO VETOR
    fscanf(texto, "%i", &numNum);

    int vetor[numNum];
    
    //LE VETOR
    for(int i=0; i<numNum; i++){
        fscanf(texto, "%i", &vetor[i]);
    }

    int matrizCont[2][numNum]; // matrizCont[0][numNum] : numero que se repete na sequencia
                               // matrizCont[1][numNum] : quantas vezes esse numero se repete

    matrizCont[0][0] = vetor[0]; // VALOR INICIAL PARA O "FOR"  
    int valorRepetido = vetor[0]; //VALOR INICIAL PARA O "IF" ABAIXO **
    int cont=0, j=0;

    for(int i=0; i<numNum; i++){

        if(vetor[i] == valorRepetido){// CONTA UMA SEQUENCIA DE NUMEROS IGUAIS (PARA i=0 SEMPRE SERÁ VERDADE **) 
            cont++; // CONTA QUANTOS NUMEROS SAO IGUAIS NESSA SEQUENCIA
            matrizCont[1][j] = cont; //REGISTRA NA MATRIZ O NUMERO DE REPETICOES DO NUMERO
        }

        // ACABOU A SEQUENCIA
        else{
            matrizCont[1][j] = cont; //REGISTRA NA MATRIZ O NUMERO DE REPETICOES DO NUMERO
            cont=1; //RESETA O CONT
            j++; // PROXIMA SEQUENCIA
            matrizCont[0][j] = vetor[i];
            matrizCont[1][j] = cont;
            valorRepetido = vetor[i];
        }
    }

    /* 
        PARA PREPARAR PARA LOGICA DE ORDENACAO OS NUMEROS QUE FOREM IGUAIS (SE REPETIREM)
        SERAO ALTERADOS PARA numero=(-numero)-1

        ASSIM O "0" SERA -1, 
        2 sera -3
    */
    for(int i=0; i<j+1; i++){
        if(matrizCont[0][i]>=0){
            for(int k = i+1; k<j+1; k++){
                if(matrizCont[0][i] == matrizCont[0][k] && matrizCont[0][k]>=0){
                    matrizCont[0][k] = (matrizCont[0][k] * -1)-1;
                }
            }
        }
    }

    int matrizOrdenada[2][j+1];   

    for(int i=0; i<j+1; i++){
        if(matrizCont[0][i]>=0){ //NAO REPETE NUMEROS IGUAIS
            cont=1;
            for(int k = 0; k<j+1; k++){ // OBTEM A POSICAO DO NUMERO CONTANDO QUANTOS NUMEROS SAO MENORES QUE O NUMERO NA POSICAO "i "
                if(matrizCont[0][i]>matrizCont[0][k] && matrizCont[0][k] >=0){
                    cont++;
                }
            }

            matrizOrdenada[0][i] = cont; // REGISTRA SUA POSICAO NA MATRIZ
            matrizOrdenada[1][i] = matrizCont[1][i]; // REGISTRA QUANTAS VEZES O NUMERO SE REPETE
            
            /*
                REGISTRA A POSICAO E O NUMERO DE REPETICOES PARA TODAS AS OUTRAS SEQUENCIAS DO MESMO NUMERO "i"
            */
            for(int k = i+1; k<j+1; k++){
                if(abs(matrizCont[0][i]) == abs(matrizCont[0][k])-1){  // 2=(-3)+1 -> 2=2
                    matrizOrdenada[0][k] = cont;
                    matrizOrdenada[1][k] = matrizCont[1][k];
                }
            }
        }
    }

    printf("Matriz:\n");

    for(int i=0; i<j+1; i++){
        printf("%i",matrizOrdenada[0][i]);
        if(i != j){
            printf(" ");
        }
    }

    printf("\n");

    for(int i=0; i<j+1; i++){
        printf("%i",matrizOrdenada[1][i]);
        if(i != j){
            printf(" ");
        }
    }

    printf("\n");

    return 0;
}
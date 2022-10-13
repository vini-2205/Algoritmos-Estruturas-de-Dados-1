/*
    Alunos: Lucas Santos Rodrigues (20213001521)
            Vinícius Ferreira Pinheiro (20213005208)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// verifica se eh viavel
bool isViavel(int numMochilas, int pesoMochila[numMochilas], int valorSolucao[2][numMochilas]){
    bool viavel;
    
    for(int i=0; i<numMochilas; i++){
        if(valorSolucao[0][i] > pesoMochila[i]){
            viavel = false;
            break;
        }
        
        else
            viavel = true;
    }

    return viavel;
}

int main(){
    char arquivo[20];
    FILE *texto;
    int numMochilas, numItens;
    bool viavel;

    printf("Digite o nome do arquivo: ");
    scanf("%s", arquivo);
    texto = fopen(arquivo, "r+");

    fscanf(texto, "%i", &numMochilas);

    // capacidade maxima de peso de cada mochila i
    int pesoMochila[numMochilas];
    for(int i=0; i<numMochilas; i++){
        fscanf(texto, "%i", &pesoMochila[i]);
    }

    fscanf(texto, "%i", &numItens);

    // le o peso e valor de cada item
    int itens [2][numItens];
    for(int i=0; i<numItens; i++){
        fscanf(texto, "%i %i", &itens[0][i], &itens[1][i]); // peso e valor, respectivamente
    }

    // le a solucao do arquivo
    int solucao[numMochilas][numItens];
    for(int i=0; i<numItens; i++){
        for(int j=0; j<numMochilas; j++){
            fscanf(texto, "%i", &solucao[j][i]);
        }
    }

    // valor somado de todas mochilas
    int valorTotal=0;
    // soma pesos e valores da solucao do arquivo
    int valorSolucao [2][numMochilas];
    for(int i=0; i<numMochilas; i++){
        valorSolucao[0][i] = 0;
        valorSolucao[1][i] = 0;
        for(int j=0; j<numItens; j++){
            // se tem o item, = 1
            if(solucao[i][j]){
                valorSolucao[0][i] += itens[0][j]; // soma peso
                valorSolucao[1][i] += itens[1][j]; // soma valor
                valorTotal += itens[1][j]; // soma valor de todas mochilas
            }
        }
    }
    
    // teste viavel
    viavel = isViavel(numMochilas, pesoMochila,valorSolucao);
    
    if(viavel){
        //teste se eh otima

        int solucao[numItens], solucaoReal[numItens];
        int decimal=0, resultadoPeso=0, resultadoValor=0, maximo=0, total=0, possibilidades=pow(2,numItens);
        int binario=0;

        // tenta todas solucoes possiveis
        for(int a=0;a<numMochilas;a++){ 

            //trasnforma decimal para binário e acha o valor e peso da possivel solucao otima
            for(int i=0; i<possibilidades+1; i++){
                binario=decimal;
                for(int j=0;j<numItens;j++){
                    solucao[j]=binario%2;
                    binario=binario/2;
                    if(solucao[j]){
                        resultadoPeso += itens[0][j];
                        resultadoValor += itens[1][j];
                    }
                }

                // se o peso não ultrapassou compara com o máximo atual
                if(resultadoPeso <= pesoMochila[a]){
                    if(resultadoValor > maximo){
                        // salva a solucao maxima encontrada
                        for(int b=0;b<numItens;b++){
                            solucaoReal[b]=solucao[b];
                        }
                        maximo=resultadoValor;
                    }
                }

                decimal++; // proxima possivel solucao otima
                resultadoPeso=0,resultadoValor=0;
            }

            //retira os itens que foram usados na possivel solucao otima
            for(int b=0 ;b<numItens; b++){
                if(solucaoReal[b]){
                    itens[0][b]=0;
                    itens[1][b]=0;
                }
            }

            //soma o máximo encontrado
            total+=maximo;
            maximo=0,decimal=0;
        }

        // eh otima
        if(total==valorTotal){
            printf("Solucao otima.\n");
        }
        else{
            printf("Solucao viavel mas nao otima.\n");
        }
            
    }

    else{
        printf("Solucao inviavel.\n");
    }
}
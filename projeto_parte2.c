/****************

LAED1 - Projeto (Parte II) - Busca por padrão em sequência

Alunos: Lucas Santos Rodrigues (20213001521)
        Vinícius Ferreira Pinheiro (20213005208)

Data: 08/07/22

****************/

#include <stdio.h>
#include <stdlib.h>
#define MAX 10


typedef int TipoChave;
typedef int Tipo;
typedef int NumElementos;
typedef float PontoMedio;

typedef struct {
  TipoChave Chave;
  Tipo Tipo;
  NumElementos NumElementos;
  PontoMedio PontoMedio;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
  int valida;
  int PontoMedioRelativo;
  float soma;
} TipoLista;


void FLVazia(TipoLista *Lista)
{ Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Primeiro;
  Lista -> Primeiro -> Prox = NULL;
}

int Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{ Lista -> Ultimo -> Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Ultimo -> Prox;
  Lista -> Ultimo -> Item = x;
  Lista -> Ultimo -> Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
  TipoApontador q;
  if (Vazia(*Lista) || p == NULL || p -> Prox == NULL) 
  { printf(" Erro Lista vazia ou posicao nao existe\n");
    return;
  }
  q = p -> Prox;
  *Item = q -> Item;
  p -> Prox = q -> Prox;
  if (p -> Prox == NULL) Lista -> Ultimo = p;
  free(q);
}

void Imprime(TipoLista Lista)
{ TipoApontador Aux;
  Aux = Lista.Primeiro -> Prox;
  while (Aux != NULL) 
    { printf("%d ", Aux -> Item.Chave);
      printf("%d\n", Aux -> Item.Tipo);
      Aux = Aux -> Prox;
    }
}

int main(){
    char arquivo[20];
    FILE *texto;
    int linhas, numNum;
    float linhasComPadrao = 0;

    printf("Digite o nome do arquivo: ");
    scanf("%s", arquivo);
    texto = fopen(arquivo, "r+");

    // numero de linhas
    fscanf(texto, "%i", &linhas);

    TipoLista lista[linhas];

    for(int l=0; l<linhas; l++){
        // numero de elementos da linha
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

        for(int i=0; i<numNum && j<numNum; i++){

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
        for(int i=0; i<j; i++){
            if(matrizCont[0][i]>=0){
                for(int k = i+1; k<j; k++){
                    if((k+1 < numNum) && matrizCont[0][i] == matrizCont[0][k] && matrizCont[0][k]>=0){
                        matrizCont[0][k] = (matrizCont[0][k] * -1)-1;
                    }
                }
            }
        }

        int tamanho = j;
        int matrizOrdenada[2][tamanho];   

        // Separa os Seguimentos
        for(int i=0; i<tamanho; i++){
            if(matrizCont[0][i]>=0){ //NAO REPETE NUMEROS IGUAIS
                cont=1;
                for(int k = 0; k<tamanho; k++){ // OBTEM A POSICAO DO NUMERO CONTANDO QUANTOS NUMEROS SAO MENORES QUE O NUMERO NA POSICAO "i "
                    if(matrizCont[0][i]>matrizCont[0][k] && matrizCont[0][k] >=0){
                        cont++;
                    }
                }

                matrizOrdenada[0][i] = cont; // REGISTRA SUA POSICAO NA MATRIZ
                matrizOrdenada[1][i] = matrizCont[1][i]; // REGISTRA QUANTAS VEZES O NUMERO SE REPETE
                
                /*
                    REGISTRA A POSICAO E O NUMERO DE REPETICOES PARA TODAS AS OUTRAS SEQUENCIAS DO MESMO NUMERO "i"
                */
                for(int k = i+1; k<tamanho; k++){
                    if((k+1 < numNum) && abs(matrizCont[0][i]) == abs(matrizCont[0][k])-1){  // 2=(-3)+1 -> 2=2
                        matrizOrdenada[0][k] = cont;
                        matrizOrdenada[1][k] = matrizCont[1][k];
                    }
                }
            }
        }

        FLVazia(&lista[l]);

        // Grava na lista
        for (int i = 0; i < tamanho; i++)
        {
            TipoItem aux;
            aux.Chave = i; // Chave recebe o indice
            aux.Tipo = matrizOrdenada[0][i]; // Tipo recebe o numero repetido
            aux.NumElementos = matrizOrdenada[1][i]; // NumElementos recebe a quantidade de numeros repetidos
            aux.PontoMedio = (matrizOrdenada[1][i] / 2);
            Insere(aux, &lista[l]);
        }

        int ordem1 = 0, ordem2 = 3;
        int ordemCerta1[5] = {1,3,2,3,1};
        TipoApontador aponta;
        aponta = lista[l].Primeiro->Prox;
        lista[l].valida = 0;

        for(int i=0; i<tamanho; i++){ // enquato a lista nao acabar
            if(aponta->Item.Tipo == ordemCerta1[ordem1]){ // verifica se é igual a sequencia
                ordem1++;
                if(aponta->Item.Tipo == 2){
                    lista[l].PontoMedioRelativo = i;
                }
                if (ordem1 == 3){
                    lista[l].valida = 1;
                    break; // encontrou o padrao
                }
            }else if(aponta->Item.Tipo == ordemCerta1[ordem2]){
                ordem2++;
                if(aponta->Item.Tipo == 2){
                    lista[l].PontoMedioRelativo = i;
                }
                if (ordem2 == 5){
                    lista[l].valida = 1;
                    break; // encontrou o padrao
                }
            }else{
                ordem1 = 0;
                ordem2 = 3;
                if(aponta->Item.Tipo == ordemCerta1[ordem1]){
                    ordem1++;
                }else if(aponta->Item.Tipo == ordemCerta1[ordem2]){
                    ordem2++;
                }
            }
            aponta = aponta->Prox; // proximo elemento da lista
        }

        if(ordem1 == 3 || ordem2 == 5){
            linhasComPadrao++;
        }

        if(lista[l].valida){
            float soma = 0;
            for(int i=0; i<lista[l].PontoMedioRelativo; i++){
                soma += matrizOrdenada[1][i];
            }
            soma += (matrizOrdenada[1][lista[l].PontoMedioRelativo]/2);
            lista[l].soma = soma;
        }
        else{
            lista[l].soma = 0;
        }
    }

    
    float porcentagem = (linhasComPadrao/linhas);
    if(porcentagem >= 0.7){
        int direita=0, esquerda=0, reto=0;
        for(int l=0; l<linhas; l++){
            if((lista[l].valida) && (lista[l+1].soma == lista[l].soma)){
                reto++;
            }else if((lista[l].valida) && (lista[l+1].soma > lista[l].soma+10)){
                esquerda++;
            }else if((lista[l].valida) && (lista[l+1].soma < lista[l].soma-10)){
                direita++;
            }
        }

        if((direita>esquerda) && (direita>reto)){
            printf("Resultado: Curva a direita.\n");
        }else if((esquerda>direita) && (esquerda>reto)){
            printf("Resultado: Curva a esquerda.\n");
        }else{
            printf("Resultado: Pista em linha reta.\n");
        }
    }

    else{
        printf("Resultado: Formato da pista nao estimado.\n");
    }

    return 0;
}
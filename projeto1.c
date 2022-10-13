/****************

LAED1 - Projeto (Parte I) - Busca por padrão em sequência

Alunos: Lucas Santos Rodrigues (20213001521)
        Vinícius Ferreira Pinheiro (20213005208)

Data: 30/06/22

****************/
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 10


typedef int TipoChave;
typedef int Tipo;
typedef int NumElementos;
typedef int PontoMedio;

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
    { printf("%d\n", Aux -> Item.Chave);
      Aux = Aux -> Prox;
    }
}

    
int main(){
    char arquivo[20];
    FILE *texto;
    int numNum, ordem = 0; 
    int ordemCerta[5] = {1,3,2,3,1};


    printf("Digite o nome do arquivo: ");
    scanf("%s", arquivo);
    texto = fopen(arquivo, "r+");

    // TAMANHO DO VETOR
    fscanf(texto, "%i", &numNum);
	
    TipoLista lista;
    FLVazia(&lista);

    //LE VETOR
    TipoItem elementoCelula;
    for(int i=0; i<numNum; i++){
        fscanf(texto, "%i", &elementoCelula.Chave);
        if(elementoCelula.Chave == 0){
          elementoCelula.Tipo = 1;
        }
        if(elementoCelula.Chave == 128){
          elementoCelula.Tipo = 2;
        }
        if(elementoCelula.Chave == 255){
          elementoCelula.Tipo = 3;
        }
        Insere(elementoCelula, &lista);
    }

    TipoApontador aponta;
    aponta = lista.Primeiro->Prox;
    while (aponta != NULL){ 
        if(aponta->Item.Tipo == ordemCerta[ordem]){
            ordem++;
            TipoApontador aponta2 = aponta->Prox;
            for (int i=0; i < 4 && aponta2!=NULL; i++, aponta2=aponta2->Prox)
            {
              if(aponta2->Item.Tipo == ordemCerta[i+1]){
                ordem++;
              }
            }
        }

        if (ordem == 5)
        {
          break;
        }

        aponta = aponta->Prox;
        ordem = 0;
    }
    
    if(ordem==5){
        printf("Resultado: Padrao encontrado.\n");
    }
    else{
        printf("Resultado: Padrao nao encontrado.\n");
    }

    return 0;
}
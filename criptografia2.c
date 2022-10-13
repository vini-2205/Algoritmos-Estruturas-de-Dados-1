/*
    Alunos: Lucas Santos Rodrigues (20213001521)
            Vinícius Ferreira Pinheiro (20213005208)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int bindec(int bin){//transformar para binário
    int decimal=0;
    for(int a=0;bin>0;a++){
        decimal = decimal+((bin%10)*pow(2,a));
        bin = bin/10;
    }
    return decimal;
}

int main(){
    FILE *texto;
    char cripto[1001];
    char arquivo[20], bin1[5];
    int bin2,total;
    int decimal,b=1;

    printf("Digite o nome do arquivo: ");
    scanf("%s", arquivo);
    printf("\n--------------------\nMensagem codificada:\n--------------------");
    texto = fopen(arquivo, "r+");

    fscanf(texto,"%s",cripto);//lê toda a linha e armazena em cripto
    fclose(texto);
    printf("\n%s\n", cripto);

    for(int j=0;j<5;j++){//armazena os bin em uma função
        bin1[j]=cripto[j];
    }

    // Binario
    bin2 = atoi(bin1);
    decimal = bindec(bin2);
    total=strlen(cripto);

    for(int a=5;a<total;a++){//retira o digito que ta na posição binária
        if(b==decimal){
            cripto[a]=cripto[a+1];
        }
        else{
            b++;
        }
    }

    // Dividir em blocos
    int num_blocos = ((total-5)/2);
    char blocos[2][num_blocos];
    
    for(int a=5, b=0; b<num_blocos; a+=2,b++){//divide os caracteres na posição de cripto e coloca em uma matriz
    	blocos[0][b] = cripto[a];
    	blocos[1][b] = cripto[a+1];
    }

    //permutar
    char aux[2];
    for(int a=0; a<(num_blocos/2); a+=2){
        //inverte o primeiro bloco com o ultimo, o terceiro com o antepenultimo
        aux[0] = blocos[0][a];
        aux[1] = blocos[1][a];
        blocos[0][a] = blocos[0][(num_blocos-1)-a];
        blocos[1][a] = blocos[1][(num_blocos-1)-a];
        blocos[0][(num_blocos-1)-a] = aux[0];
        blocos[1][(num_blocos-1)-a] = aux[1];
    }
    
    // Espelhar blocos
    int aux2;
    for(int a=0; a<num_blocos; a++){
        aux2 = blocos[0][a];
        blocos[0][a] = blocos[1][a];
        blocos[1][a] = aux2;
    }

    //transformar a matriz de volta para o cripto
    for(int a=5, b=0; a<total; a+=2, b++){
        cripto[a] = blocos[0][b];
        cripto[a+1] = blocos[1][b];
    }

    // pegar os ditios de cripto e voltar 5 posições na tabela ascii
    for(int a=5;a<total;a++){
        if(cripto[a]!='#'){
            for(int b=0; b<5; b++){
                if(cripto[a] == 65 || cripto[a] == 97){
                    cripto[a] += 25;
                }else{
                    cripto[a]--;
                }
            }
        }

        // substitui os '#' por espacos 
        else{
            cripto[a]=' ';
        }
    }

    printf("\n----------------------\nMensagem decodificada:\n----------------------");
    printf("\n");
    for(int a=5;a<total-1;a++){
        printf("%c",cripto[a]);
    }

    return 0;
    
}





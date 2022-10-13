/*
    Alunos: Lucas Santos Rodrigues (20213001521)
            Vinícius Ferreira Pinheiro (20213005208)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int bindec(int bin){
    int decimal=0;
    for(int a=0;bin>0;a++){
        decimal = decimal+((bin%10)*pow(2,a));
        bin = bin/10;
    }
    return decimal;
}

int main(){
    FILE *texto;
    char cripto[5000];
    char arquivo[20],bin[5],arm,arm2;
    int bin1,total;
    int decimal,constante=0,b=1;

    printf("Digite o nome do arquivo: ");
    scanf("%s", arquivo);
    printf("\n--------------------\nMensagem codificada:\n--------------------");
    texto = fopen(arquivo, "r+");

    fscanf(texto, "%s", cripto);
    fclose(texto);
    printf("\n%s\n", cripto);

    for(int j=0;j<5;j++){
        bin[j]=cripto[j];
    }

    // Binario
    bin1=atoi(bin);
    decimal = bindec(bin1);
    total=strlen(cripto);



    // Remover digito
    total=strlen(cripto);
    for(int a=5; a<total; a++){
        if(a==(total-1)){
            cripto[a]='\0';
        }
        
        else{
            if(b==decimal){
                cripto[a]=cripto[a+1];
            }else{
                b++;
            }
        }
    }

    // Permutar
    total=strlen(cripto);
    constante=(total-1);

    for(int a=5; a<(total/2); a=a+4){
                arm=cripto[a];
                arm2=cripto[constante-1];
                cripto[a]=arm2;
                cripto[constante-1]=arm;
                arm=cripto[a+1];
                arm2=cripto[constante];
                cripto[a+1]=arm2;
                cripto[constante]=arm;
                constante=constante-4;
                b=b-4;
        }
    
    // inverte as duplas
    constante=(total-1);
    for(int a=5;a<total;a=a+2){
    	if(a==constante){
    		break;
    	}else{
		arm=cripto[a];
		arm2=cripto[a+1];
		cripto[a]=arm2;
		cripto[a+1]=arm;
        }
    }

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

        else{
            cripto[a]=' ';
        }
    }
    total=strlen(cripto);
    
    printf("\n----------------------\nMensagem decodificada:\n----------------------");
    printf("\n");
    for(int a=5;a<total;a++){
        printf("%c",cripto[a]);
    }
    return 0;
}

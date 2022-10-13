#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    FILE *texto;
    int N, i, j, k, l, quebraLinha1, quebraLinha2, max=0, maxI, maxJ; // (i, j, k, l) entradas para os for's
                                                                      // "quebraLinha" usadas para saltar a linha da matriz
    char arquivo[20];

    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", arquivo);

    texto = fopen(arquivo, "r+");
    fscanf(texto, "%i", &N);
    
    int caixas[N+1][N+1]; // matriz

    // percorre toda matriz
    for(i=0, j=0, quebraLinha1=0; j<=quebraLinha1; j++)
    {   
        fscanf(texto, "%i", &caixas[i][j]);
        //printf("%i ", caixas[i][j]);

        if(caixas[i][j] == 0)
        {
            int soma = 0;
            for(k=0, l=0, quebraLinha2=0; l<=quebraLinha2; l++) // soma todas caixas das linhas acima de caixas[i][j]
            {
                soma += caixas[k][l];

                if(l == quebraLinha2 && k!=(i-1)) // salta a linha e volta para primeira posição da linha
                {
                    quebraLinha2++;
                    k++;
                    l = -1;
                }
            }

            if(soma>max)
            {
                max = soma;
                maxI = i+1;
                maxJ = j+1;
            }
            
        }

        if(j == quebraLinha1 && (!feof(texto))) // salta a linha e volta para primeira posição da linha
        {
            quebraLinha1++;
            i++;
            j = -1;
            //printf("\n");
        }
        
    }

    printf("Resposta: fileira %i, caixa %i.\n", maxI, maxJ);
    fclose(texto);

    return 0;
}
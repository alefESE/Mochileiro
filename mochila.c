#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int max(int a, int b) { return (a > b)? a : b; }
// Retorna o valor maximo que pode ser posto na mochila com a capacidade passada
int mochila(int capacidade, int pesos[], int valores[], int n){
    int i, j;
    int K[n+1][capacidade+1];
    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++){
        for(j = 0; j <= capacidade; j++){
            if(i==0 || j==0)
               K[i][j] = 0;
            else if(pesos[i-1] <= j)
                 K[i][j] = max(valores[i-1]+K[i-1][j-pesos[i-1]], K[i-1][j]);
            else
                 K[i][j] = K[i-1][j];
        }
    }
    return K[n][capacidade];
}

int main(int argc, char **argv){
    if(argc > 2 || argc <= 1){
		printf("modo de uso: mochila <ArquivoDados>.txt\n");
		return 0;
	}
	// problema de buffer
	if(strstr(argv[1], ".txt") == NULL){
		printf("adicione a extensao .txt no fim de \"%s\"\n", argv[1]);
		return 0;
	}
	FILE *arquivo;
	// arquivo nao encontrado
	if((arquivo = fopen(argv[1], "r")) == NULL){
		printf("erro ao abrir arquivo %s\n", argv[1]);
		return 0;
    }
    
    int i = 0, n, m;
    char token[256], c;
    while((c = getc(arquivo)) != EOF){//pega n
        token[i] = c;
        ++i;
        if(c == ' '){
            n = atoi(token);
            i = 0;
            memset(token, '\0', sizeof(token));
            break;
        }else if(c == '\n'){
            printf("Formato do arquivo de entrada incorreto\n");
            fclose(arquivo);
            return 0;
        }
    }

    while((c = getc(arquivo)) != EOF){//pega m
        token[i] = c;
        ++i;
        if(c == '\n'){
            m = atoi(token);
            i = 0;
            memset(token, '\0', sizeof(token));
            break;
        }else if(c == ' '){
            printf("Formato dos dados de entrada incorreto\n");
            fclose(arquivo);
            return 0;
        }
    }

    int pesos[n];
    int valores[n];
    int p = 0, v = 0;//contadores
    i = 0;
    
    while((c = getc(arquivo)) != EOF){//pega pesos
        token[i] = c;
        ++i;
        if(c == ' '){//pega pi
            pesos[p] = atoi(token);
            ++p;
            i = 0;
            memset(token, '\0', sizeof(token));
            do{//pega valores
                c = getc(arquivo);
                token[i] = c;
                ++i;
                if(c == '\n' || EOF){
                    valores[v] = atoi(token);
                    ++v;
                    i = 0;
                    memset(token, '\0', sizeof(token));
                    break;
                }else if(c == ' '){
                    printf("Formato dos dados de entrado incorreto\n");
                    fclose(arquivo);
                    return 0;
                }
            }while(1);
        }
    }

    printf("Valor = %d\n", mochila(m, pesos, valores, n));

    fclose(arquivo);
    return 0;
}

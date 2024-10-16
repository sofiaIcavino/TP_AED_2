#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Facil 10;
#define Medio 20;
#define Dificil 30;

#define BombasF 3;
#define BombasM 6;
#define BombasD 9;


int** alocar_matriz(int tamanho){
	int i=0;
   int** matriz_alocada=(int**)malloc(tamanho*sizeof(int*));
   for(i=0;i<tamanho;i++){
      matriz_alocada[i]= (int*)malloc(tamanho*sizeof(int));
   }

   return matriz_alocada;
}

char** alocarEinicializar_matriz_usuario(int tamanho){
	int i=0,j=0;
   char** matriz_alocada=(char**)malloc(tamanho*sizeof(char*));
   for(i=0;i<tamanho;i++){
      matriz_alocada[i]= (char*)malloc(tamanho*sizeof(char));
   }
   for(i=0;i<tamanho;i++){
      for(j=0;j<tamanho;j++){
         matriz_alocada[i][j]='x';
      }
   }
   return matriz_alocada;
}

void inicializar_matriz(int **matriz,int tamanho){
	int i=0,j=0;
   for(i=0;i<tamanho;i++){
      for(j=0;j<tamanho;j++){
         matriz[i][j]=0;
      }
   }
}
void visualizar_matriz(int **matriz,int tamanho){
	int i=0,j=0;
   for(i=0;i<tamanho;i++){
      for(j=0;j<tamanho;j++){
         if(matriz[i][j]==-1){
           printf("%d ", matriz[i][j]);
         }else{
           printf(" %d ", matriz[i][j]);
         }
      }
      printf("\n");
   }
}
void visualizar_matriz_usuario(char **matriz,int tamanho){
	int i=0,j=0;
   printf("    ");
   for(i=1;i<tamanho+1;i++){
      if(i>=9){
         printf(" %d",i);
      }else{
         printf(" %d ",i);
      }
   }
   printf("\n");

   for(i=0;i<tamanho;i++){
      if(i>=9){
         printf(" %d ",i+1);
      }else{
         printf(" %d  ",i+1);
      }
  
      for( j=0;j<tamanho;j++){
         
         printf(" %c ", matriz[i][j]);
         
      }
      printf("\n");
   }
}

void inserirBombas(int quantBombas,int **matriz,int tamanho){
   int cont=0;
   srand(time(NULL));
   while(cont<quantBombas){
      int linha= rand()%tamanho;
      int coluna= rand()%tamanho;
      if(matriz[linha][coluna]==0){
       matriz[linha][coluna]=-1;
       cont++;
      }
   }
}

int colocarQuantidadeDeBombas(int **matriz, int x, int y, int tamanho){ 
    int quantBombas = 0;

    if (x-1 >= 0 && y-1 >= 0){
      if (matriz[x-1][y-1] == -1){
         quantBombas++;
      }
    }

    if (x-1 >= 0){
      if (matriz[x-1][y] == -1){
         quantBombas++;
      }
    }

    if (x-1 >= 0 && y+1 <= tamanho-1){
        if (matriz[x-1][y+1] == -1){
            quantBombas++;
        }
    }

    if (y+1 <= tamanho-1){
      if (matriz[x][y+1] == -1){
         quantBombas++;
      }
    }

    if (x+1 <= tamanho-1 && y+1 <= tamanho-1){
        if (matriz[x+1][y+1] == -1){
            quantBombas++;
        }
    }

    if (x+1 <= tamanho-1){
        if (matriz[x+1][y] == -1){
            quantBombas++;
        }
    }

    if (x+1 <= tamanho-1 && y-1 >= 0){
        if (matriz[x + 1][y - 1] == -1){
            quantBombas++;
        }
    }

    if (y-1 >= 0){
        if (matriz[x][y-1] == -1){
            quantBombas++;
        }
    }

    return quantBombas++;
}

void montarMatrizDoJogo(int **matriz,int tamanho){
   int i=0,j=0;
   for( i=0;i<tamanho;i++){
      for( j=0;j<tamanho;j++){
         if (matriz[i][j] != -1){
            matriz[i][j] = colocarQuantidadeDeBombas(matriz, i, j, tamanho);
         }
      }
   }
}


void modificar_campo_minado(int **matrizJogo,char **matrizUsuario,int n,int m,int *bomba){
  if(matrizJogo[n][m]==-1){
   *bomba=0;
   matrizUsuario[n][m]='@';
   printf("\n\nBOOH! Ja era... F\n");
  }else{
   matrizUsuario[n][m]=matrizJogo[n][m]+'0';
   printf("\n\nUHU! Sem bomba por aqui!\n");
  }
}

int verificar_Coordenada_Existente(int linha, int coluna,int tam){
   int flagCoordenada=1;
   if(linha>tam-1 || linha<0 || coluna>tam-1 || coluna<0){
      flagCoordenada=0;
   }
   return flagCoordenada;
}

 int main(void){
   int modo=0,tam=0,quantBombas=0,linha,coluna,cont=0,flagbomba=1;

   printf("************ BEM VINDO(A) AO CAMPO MINADO! ************\n");
   printf("Para iniciar o jogo selecione o modo. Digite:\n1 - Facil\n2 - Medio\n3 - Dificil\n");


   while(scanf("%d",&modo),modo<1 || modo>3){
    printf("Modo Indisponivel. Digite:\n1 - Facil\n2 - Medio\n3 - Dificil\n");
   }

   if(modo==1){
      tam=Facil;
      quantBombas=BombasF;
   }else if(modo==2){
       tam=Medio;
       quantBombas=BombasM;
   }else if(modo==3){ 
      tam=Dificil;
      quantBombas=BombasD;
   }

   int **campo_minado= alocar_matriz(tam);
   inicializar_matriz(campo_minado,tam);
   int **copia_campo_minado= alocar_matriz(tam);
   inicializar_matriz(copia_campo_minado,tam);

   inserirBombas(quantBombas,campo_minado,tam);
   montarMatrizDoJogo(campo_minado,tam);

   char **campo_minado_usuario= alocarEinicializar_matriz_usuario(tam);

   //visualizar_matriz(campo_minado,tam);

   int repeticao=(tam*tam)-quantBombas;
   while(cont<repeticao && flagbomba){

      printf("***********************************************\n");
      printf("|Dificuldade: %d        |Quantidade de bombas:%d\n",modo,quantBombas);
      visualizar_matriz_usuario(campo_minado_usuario,tam);

      printf("Digite as coordenadas que deseja verificar:\nEx: x,y\n");
      scanf("%d,%d",&linha,&coluna);
      linha-=1;
      coluna-=1;

      if(verificar_Coordenada_Existente(linha, coluna,tam)==0){
         printf("\n\n-> COORDENADA NAO EXISTE. Digite novamente:");
         system("pause");

      }else{

         if(copia_campo_minado[linha][coluna]==0){
            copia_campo_minado[linha][coluna]=1;
            modificar_campo_minado(campo_minado,campo_minado_usuario,linha,coluna,&flagbomba);
            cont++;
         }else{
            printf("\n\n-> COORDENADA JA SELECIONADA. Digite novamente:");
            system("pause");

         }

      }

     printf("\n");

   }

   visualizar_matriz_usuario(campo_minado_usuario,tam);
   if(flagbomba==0){
      printf("\ngame over\n\n");
   }else{
      printf("\nparabens, vc eh fera\n\n");
   }
   printf("MATRIZ ORIGINAL DO JOGO:\n");
   visualizar_matriz(campo_minado,tam);

   free(campo_minado);
   free(campo_minado_usuario);
   free(copia_campo_minado);

   system("pause");

   return 0;
 }
#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Fazer alocacao das matrizes inteiras de maneira dinamica*/
int** alocar_matriz(int tamanho){
	int i=0;

   int** matriz_alocada=(int**)malloc(tamanho*sizeof(int*));
   if (matriz_alocada == NULL){
    printf("memoria insuficiente\n");
    exit(1);
   }

   for(i=0;i<tamanho;i++){
      matriz_alocada[i]= (int*)malloc(tamanho*sizeof(int));

      if (matriz_alocada[i] == NULL){
        printf("memoria insuficiente\n");
        exit(1);
      }
   }

   return matriz_alocada;
}

/*Função para inserir um valor em determinada coordenada em uma matriz do tipo int*/
void inserir_valor_matriz(int **matriz,int linha,int coluna,int valor){
   matriz[linha][coluna]=valor;
}

/*Função para inserir um valor em determinada coordenada em uma matriz do tipo char*/
void inserir_valor_matriz_char(char **matriz,int linha,int coluna,char valor){
   matriz[linha][coluna]=valor;
}

/*Fazer alocacao e inicializacao(com o caracter x) de matrizes char*/
char** alocarEinicializar_matriz_char(int tamanho){
	int i=0,j=0;
   char** matriz_alocada=(char**)malloc(tamanho*sizeof(char*));
   if (matriz_alocada == NULL){
    printf("memoria insuficiente\n");
    exit(1);
   }

   for(i=0;i<tamanho;i++){
      matriz_alocada[i]= (char*)malloc(tamanho*sizeof(char));
      if (matriz_alocada[i] == NULL){
        printf("memoria insuficiente\n");
        exit(1);
      }
   }

   for(i=0;i<tamanho;i++){
      for(j=0;j<tamanho;j++){
         //Usando a função de inserir_valor_matriz_char para inicializar
         inserir_valor_matriz_char(matriz_alocada,i,j,'x'); 
      }
   }

   return matriz_alocada;
}

/*Funcao para inicializacao das matrizes inteiras com 0*/
void inicializar_matriz(int **matriz,int tamanho){
	int i=0,j=0;

   for(i=0;i<tamanho;i++){
      for(j=0;j<tamanho;j++){
         //Usando a função de inserir_valor_matriz para inicializar
         inserir_valor_matriz(matriz,i,j,0);
      }
   }
}

/*Funcao para realizar a impressao da matriz de inteiros na tela*/
void visualizar_matriz(int **matriz,int tamanho){
	int i=0,j=0;

//Impressao da coordenada Y - as colunas
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
      //Impressao da coordenada X - as linhas
      if(i>=9){
         printf(" %d ",i+1);
      }else{
         printf(" %d  ",i+1);
      }
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

/*Funcao para realizar a impressao da matriz (tipo char) de vizualizacao do usuario na tela,
de maneira que fique intuitiva para o jogador*/
void visualizar_matriz_char(char **matriz,int tamanho){
	int i=0,j=0;

   //Impressao da coordenada Y - as colunas
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
      //Impressao da coordenada X - as linhas
      if(i>=9){
         printf(" %d ",i+1);
      }else{
         printf(" %d  ",i+1);
      }
  
      for( j=0;j<tamanho;j++){
         //Impressao da matriz para o jogador realizar a escolha das coordenadas
         printf(" %c ", matriz[i][j]); 
      }
      printf("\n");
   }

}

//Função responsável por liberar a memória das matrizes inteiras 
void liberar_matriz(int **mat,int linhas){
    for(int i=0;i<linhas;i++){
      free(mat[i]);
   }
   free(mat);
}

//Função responsável por liberar a memória das matrizes formada de caracteres 
void liberar_matriz_char(char **mat,int linhas){
    for(int i=0;i<linhas;i++){
      free(mat[i]);
   }
   free(mat);
}



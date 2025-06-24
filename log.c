#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "log.h"

//Função responsável pela criação do arquivo log.txt
FILE* criar_arquivo(void){
   FILE* arquivo=fopen("log.txt","w");
   if (arquivo == NULL){
       printf("Arquivo não pode ser criado! \n\n");
   }else{
       printf("Arquivo log.txt criado com sucesso! \n\n");
   }
   return arquivo;
}

//Função responsável por abrir o arquivo log.txt
void abrir_arquivo(FILE *arquivo){
arquivo=fopen("log.txt","a");
   if (arquivo == NULL){
       printf("Arquivo não pode ser aberto! \n\n");
   }
}

//Função responsável pelo fechamento do arquivo log.txt
void fechar_arquivo(FILE *arquivo){
   fclose(arquivo);
}

//Função responsável por adicionar um texto no arquivo log.txt
void adicionar_texto_txt(FILE*arquivo,char texto[100]){
   fprintf(arquivo,texto);
}

//Função responsável pela criação da estrutura responsável pela impressão da data e hora
struct tm* criar_Hora(void){
   struct tm *tm;
   time_t seconds;
   time(&seconds);
   tm=localtime(&seconds);
   return tm;
}

/*Função responsável por adicionar a data e hora no arquivo log.txt usando da struct tm
da biblioteca time para realizar a impressão*/
void gravar_DataHora_txt(FILE*arquivo,struct tm *hr){
   fprintf(arquivo,"Data: %d/%d/%d\n",hr->tm_mday,hr->tm_mon+1,hr->tm_year+1900);
   fprintf(arquivo,"Hora: %02d:%02d:%02d\n\n",hr->tm_hour,hr->tm_min,hr->tm_sec);
}

/*Função responsável por adicionar o texto de introdução da partida no log.txt, informando a 
dificuldade e quantidade de bombas*/
void adicionar_texto_introducao_txt(FILE*arquivo,int modo,int quantBombas){
   fprintf(arquivo,"|Dificuldade: %d        |Quantidade de bombas:%d\n\n",modo,quantBombas);
}

/*Função responsável por gravar a matriz (do tipo Char) e a coordenada de cada jogada no arquivo log.txt*/
void gravar_matriz_coordenada_usuario_txt(FILE*arquivo,char **matriz,int tamanho,int linha,int coluna){
	int i=0,j=0;

   fprintf(arquivo,"\n\n");
   //Impressao da coordenada Y - as colunas
   fprintf(arquivo,"    ");
   for(i=1;i<tamanho+1;i++){
      if(i>=9){
         fprintf(arquivo," %d",i);
      }else{
         fprintf(arquivo," %d ",i);
      }
   }
   fprintf(arquivo,"\n");

   for(i=0;i<tamanho;i++){
      //Impressao da coordenada X - as linhas
      if(i>=9){
         fprintf(arquivo," %d ",i+1);
      }else{
         fprintf(arquivo," %d  ",i+1);
      }
  
      for( j=0;j<tamanho;j++){
         fprintf(arquivo," %c ", matriz[i][j]); 
      }
       fprintf(arquivo,"\n");
   }
  fprintf(arquivo,"Coordenada digitada pelo jogador: (%d,%d)\n",linha,coluna);
}


/*Função responsável por gravar a matriz "original" (do tipo Int) do jogo no arquivo log.txt*/
void gravar_matriz_original_txt(FILE*arquivo,int **matriz,int tamanho){
	int i=0,j=0;

   fprintf(arquivo,"\n\nMATRIZ ORIGINAL DO JOGO:\n");
   //Impressao da coordenada Y - as colunas
   fprintf(arquivo,"    ");
   for(i=1;i<tamanho+1;i++){
      if(i>=9){
         fprintf(arquivo," %d",i);
      }else{
         fprintf(arquivo," %d ",i);
      }
   }
   fprintf(arquivo,"\n");

   for(i=0;i<tamanho;i++){
    //Impressao da coordenada X - as linhas
    if(i>=9){
         fprintf(arquivo," %d ",i+1);
      }else{
         fprintf(arquivo," %d  ",i+1);
      }
      for(j=0;j<tamanho;j++){
         if(matriz[i][j]==-1){
           fprintf(arquivo,"%d ", matriz[i][j]);
         }else{
           fprintf(arquivo," %d ", matriz[i][j]);
         }
      }
      fprintf(arquivo,"\n");
   }

}





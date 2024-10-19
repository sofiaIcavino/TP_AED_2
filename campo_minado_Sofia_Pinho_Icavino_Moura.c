#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Facil 10;
#define Medio 20;
#define Dificil 30;

#define BombasF 3;
#define BombasM 6;
#define BombasD 9;

/*Fazer alocação das matrizes inteiras de maneira dinâmica*/
int** alocar_matriz(int tamanho){
	int i=0;

   int** matriz_alocada=(int**)malloc(tamanho*sizeof(int*));
   for(i=0;i<tamanho;i++){
      matriz_alocada[i]= (int*)malloc(tamanho*sizeof(int));
   }

   return matriz_alocada;
}

/*Fazer alocação e inicialização(com o caracter x) da matriz de vizualização do usuário*/
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

/*Função para inicialização das matrizes inteiras com 0*/
void inicializar_matriz(int **matriz,int tamanho){
	int i=0,j=0;

   for(i=0;i<tamanho;i++){
      for(j=0;j<tamanho;j++){
         matriz[i][j]=0;
      }
   }
}

/*Função para realizar a impresão da matriz na tela*/
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

/*Função para realizar a impresão da matriz de vizualização do usuário na tela,
de maneira que fique intuitiva para o jogador*/
void visualizar_matriz_usuario(char **matriz,int tamanho){
	int i=0,j=0;

   //Impressão da coordenada Y - as colunas
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
      //Impressão da coordenada X - as linhas
      if(i>=9){
         printf(" %d ",i+1);
      }else{
         printf(" %d  ",i+1);
      }
  
      for( j=0;j<tamanho;j++){
         //Impressão da matriz para o jogador realizar a escolha das coordenadas
         printf(" %c ", matriz[i][j]); 
      }
      printf("\n");
   }

}


/*Função para inserir as bombas de modo aleatório*/
void inserirBombas(int quantBombas,int **matriz,int tamanho){
   int cont=0;
   srand(time(NULL));

   while(cont<quantBombas){
      int linha= rand()%tamanho; //Gerar uma linha aleatoria
      int coluna= rand()%tamanho; //Gerar uma coluna aleatoria

      /*O if irá verficar se já existe bomba no local escolhido, para que as bombas 
      não sejam geradas no mesmo local.
      Se na coordenada sorteada estiver o valor 0, não tem bomba. Assim, adicionando -1 no local
      da bomba. Quando diferente de zero, quer dizer que há bomba no local e é gerado uma 
      nova coordenada até atingir a quantidade certa de bombas*/
      if(matriz[linha][coluna]==0){
        matriz[linha][coluna]=-1;
        cont++;
      }
   }
}

/*Função verifica quantas bombas tem ao redor da coordenada. Verificando sempre as 8 coordenadas 
que ficam na vizinhança.*/
int colocarQuantidadeDeBombas(int **matriz, int linha, int coluna, int tamanho){ 
    int quantBombas = 0;

    if (linha-1 >= 0 && coluna-1 >= 0){
      if (matriz[linha-1][coluna-1] == -1){
         quantBombas++;
      }
    }
    if (linha-1 >= 0){
      if (matriz[linha-1][coluna] == -1){
         quantBombas++;
      }
    }
    if (linha-1 >= 0 && coluna+1 <= tamanho-1){
        if (matriz[linha-1][coluna+1] == -1){
            quantBombas++;
        }
    }
    if (coluna-1 >= 0){
        if (matriz[linha][coluna-1] == -1){
            quantBombas++;
        }
    }   
    if (coluna+1 <= tamanho-1){
      if (matriz[linha][coluna+1] == -1){
         quantBombas++;
      }
    }
   if (linha+1 <= tamanho-1 && coluna-1 >= 0){
        if (matriz[linha + 1][coluna - 1] == -1){
            quantBombas++;
        }
    }
   if (linha+1 <= tamanho-1){
        if (matriz[linha+1][coluna] == -1){
            quantBombas++;
        }
    }
    if (linha+1 <= tamanho-1 && coluna+1 <= tamanho-1){
        if (matriz[linha+1][coluna+1] == -1){
            quantBombas++;
        }
    }

    return quantBombas++;
}

/*Função responsável por percorrer cada coordenada da matriz, e quando não há bomba no local 
é chamada a função 'colocarQuantidadeDeBombas' para somar quantas bombas tem ao redor 
da coordenada*/
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

/*Função responsável por modificar a matriz do jogador de acordo com as coordenadas selecionadas*/
void modificar_campo_minado(int **matrizJogo,char **matrizUsuario,int n,int m,int *bomba){

   /*Caso a coordenada escolhida seja uma bomba, o ponteiro que aponta para a flagBomba 
   recebe falso. Assim, fazendo com que o jogo encerre.
   */
  if(matrizJogo[n][m]==-1){
   *bomba=0;
   matrizUsuario[n][m]='*';
   printf("\n\nBOOH! Ja era...");
  }else{

   /*Caso contrário, a coordenada selecionada pelo usuário recebe a quantidade de bombas vizinhas.
   Recebida da matriz "original" do jogo, montada logo no início.*/
   matrizUsuario[n][m]=matrizJogo[n][m]+'0';
   printf("\n\nUHU! Sem bomba por aqui!\n");
  }
}

/*Função verifica se a coordenda digitada pelo usuário existe*/
int verificar_Coordenada_Existente(int linha, int coluna,int tam){
   int flagCoordenada=1;

   //Verifica se a linha ou coluna são menores que 0 ou maiores que o tamanho da matriz do jogo
   if(linha>tam-1 || linha<0 || coluna>tam-1 || coluna<0){
      flagCoordenada=0;
   }
   return flagCoordenada;
}

/*Função verifica se a coordenada digitada pelo usuário é repetida.*/
int verificar_Coordenada_Repetida(int linha, int coluna,int ** matriz_copia){
   int flagCoordenada=1;

   /* Toda vez que uma nova coordenada é selecionada a matriz copia recebe 1, ou seja,
   quando o valor da matriz for diferente de 0 a coordenada ja foi selecionada. Retornando falso.*/
   if(matriz_copia[linha][coluna]!=0){
      flagCoordenada=0;
   }

   return flagCoordenada;
}

 int main(void){
   int modo=0,tam=0,quantBombas=0,linha,coluna,cont=0,flagbomba=1,i=0;

   printf("************ BEM VINDO(A) AO CAMPO MINADO! ************\n");
   printf("Para iniciar o jogo selecione o modo. Digite:\n1 - Facil\n2 - Medio\n3 - Dificil\n");


   //Verifca se o usuário coloca o modo diferente de 1,2 e 3
   while(scanf("%d",&modo),modo<1 || modo>3){
    printf("Modo Indisponivel. Digite:\n1 - Facil\n2 - Medio\n3 - Dificil\n");
   }

   /*Ao escolher a dificuldade do jogo, tam recebe a dimensao da matriz e quantBombas recebe 
   a quantidade de bombas de acordo com sua dificuldade*/
   switch (modo)
   {
      case 1:
      tam=Facil;
      quantBombas=BombasF;
      break;

      case 2:
      tam=Medio;
      quantBombas=BombasM;
      break;

      case 3:
      tam=Dificil;
      quantBombas=BombasD;
      break;
   }

   /*Função para alocar e criar a matriz do jogo e em seguida inicializar ela*/
   int **campo_minado= alocar_matriz(tam);
   inicializar_matriz(campo_minado,tam);

   /*Função para alocar, criar e inicializar a matriz copia do jogo, será necessária 
   posteriormente para tratar a execeção se o usuário digitar coordenadaas repetidas*/
   int **copia_campo_minado= alocar_matriz(tam);
   inicializar_matriz(copia_campo_minado,tam);

   /*Função para inserir as bombas de modo aleatório e em seguida montar a matriz do jogo
   calculando os vizinhos da bomba*/
   inserirBombas(quantBombas,campo_minado,tam);
   montarMatrizDoJogo(campo_minado,tam);

   /*Função para alocar, criar e inicializar a matriz de vizualizção do usuário*/
   char **campo_minado_usuario= alocarEinicializar_matriz_usuario(tam);
   

   int quantJogadas=tam*tam-quantBombas; //calcula a quantidade de jogadas do usuário
   while(cont<quantJogadas && flagbomba){

      printf("***********************************************\n");
      printf("|Dificuldade: %d        |Quantidade de bombas:%d\n",modo,quantBombas);
      visualizar_matriz_usuario(campo_minado_usuario,tam);

      printf("Digite as coordenadas que deseja verificar:\nEx: x,y\n");
      scanf("%d,%d",&linha,&coluna);
      linha-=1;
      coluna-=1;

      //Chama a função para verificar se a coordenada digitida pelo usuário existe
      if(verificar_Coordenada_Existente(linha, coluna,tam)==0){
         printf("\n\n-> COORDENADA NAO EXISTE. Digite novamente!\n");
      }else{

         //Chama a função para verificar se a coordenada digitida pelo usuário é repetida
         if(verificar_Coordenada_Repetida(linha, coluna,copia_campo_minado)){

            //Todo nova coordenada selecionada pelo usuário a matriz copia recebe 1
            copia_campo_minado[linha][coluna]=1;

            /*Quando verificada que a coordenada existe e não está repetida, irá modificar 
            o campo minado do usuário*/
            modificar_campo_minado(campo_minado,campo_minado_usuario,linha,coluna,&flagbomba);
            cont++;
         }else{
            printf("\n\n-> COORDENADA JA SELECIONADA. Digite novamente!\n");
         }

      }

     printf("\n");
   }

   /*Quando encerrado as tentativas, verifica se o jogador ganhou ou perdeu, através da flagbomba.
   Mostrando a matriz original do jogo.*/
   if(flagbomba==0){
      printf("\ngame over\n\n");
   }else{
      printf("\nparabens, vc eh fera\n\n");
   }
   printf("MATRIZ ORIGINAL DO JOGO:\n");
   visualizar_matriz(campo_minado,tam);

   for(i=0;i<tam;i++){
      free(campo_minado[i]);
   }
   free(campo_minado);

   for(i=0;i<tam;i++){
      free(campo_minado_usuario[i]);
   }
   free(campo_minado_usuario);

   for(i=0;i<tam;i++){
      free(copia_campo_minado[i]);
   }
   free(copia_campo_minado);

   system("pause");

   return 0;
 }
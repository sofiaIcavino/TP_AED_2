#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include <time.h>
#include "log.h"

#define Facil 10;
#define Medio 20;
#define Dificil 30;

#define BombasF 15;
#define BombasM 60;
#define BombasD 135;

/*Funcao responsavel por configurar o jogo. Ao escolher a dificuldade do jogo, tam recebe 
a dimensao da matriz e quantBombas recebe a quantidade de bombas de acordo com sua dificuldade*/
void dificuldadeJogo(int *modo,int* tam,int *quantBomba){
   switch (*modo)
   {
      case 1:
      *tam=Facil;
      *quantBomba=BombasF;
      break;

      case 2:
      *tam=Medio;
      *quantBomba=BombasM;
      break;

      case 3:
      *tam=Dificil;
      *quantBomba=BombasD;
      break;
   }
}

/*Funcao para inserir as bombas de modo aleatorio*/
void inserirBombas(int quantBombas,int **matriz,int tamanho){
   int cont=0;
   srand(time(NULL));

   while(cont<quantBombas){
      int linha= rand()%tamanho; //Gerar uma linha aleatoria
      int coluna= rand()%tamanho; //Gerar uma coluna aleatoria

      /*O if ira verficar se ja existe bomba no local escolhido, para que as bombas 
      nao sejam geradas no mesmo local.
      Se na coordenada sorteada estiver o valor 0, nao tem bomba. Assim, adicionando -1 no local
      da bomba. Quando diferente de zero, quer dizer que ha bomba no local e eh gerado uma 
      nova coordenada ate atingir a quantidade certa de bombas*/
      if(matriz[linha][coluna]==0){
        inserir_valor_matriz(matriz,linha,coluna,-1);
        cont++;
      }
   }
}

/*Funcao verifica quantas bombas tem ao redor da coordenada. Verificando sempre as 8 coordenadas 
que ficam na vizinhanca, e se elas existem.*/
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

/*Funcao responsavel por percorrer cada coordenada da matriz, e quando nao ha bomba no local 
eh chamada a funcao 'colocarQuantidadeDeBombas' para somar quantas bombas tem ao redor 
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


/*Função do Food Fill responsável por modificar a matriz do jogador usando recursão 
para liberar as minas vizinhas com valores 0 e para quando for diferente de 0, quando 
quando o usuário acerta uma coordenada com valor zero*/
void modificar_campo_minado_recursivo(int **matrizJogo,char **matrizUsuario,int linha,int coluna,int tamanho,int **copiaJogo){
/*A cada nova coordenada descoberta, irá percorrer ao redor da mina (Verificando sempre as
8 coordenadas que ficam na vizinhanca, e se elas existem), caso a mina tenho valor zero será liberada
na matriz do usuário e será chamada denovo a função de modo recursivo e assim sucessivamente, 
parando quando a mina for diferente de 0.
E sempre a matriz copia do jogo recebendo 1 a cada nova coordenada liberada, responsável pela contagem 
de jogadas já realizadas, a partir das coordenadas descobertas.
 */
  
    if (linha-1 >= 0 && coluna-1 >= 0){//Verificando se a coordenada existe
      if (matrizJogo[linha-1][coluna-1] != -1){// Verificando se a coordenada não é uma bomba
        if(matrizUsuario[linha-1][coluna-1]=='x'&& matrizJogo[linha-1][coluna-1]==0){ 
         /*Caso a mina tenha valor zero e ainda nao foi descoberta - ou seja, a matriz de
         visualização do usuário é igual a X -  será liberada essa mina na matriz do usuário 
         e será chamada denovo a função de modo recursivo*/
            matrizUsuario[linha-1][coluna-1]=matrizJogo[linha-1][coluna-1]+'0';
            modificar_campo_minado_recursivo(matrizJogo,matrizUsuario,linha-1,coluna-1,tamanho,copiaJogo);
            copiaJogo[linha-1][coluna-1]=1;
        }else if(matrizUsuario[linha-1][coluna-1]=='x'&& matrizJogo[linha-1][coluna-1]!=0) {
         /*Caso contrário - tenha valor diferente de 0 -, a mina será liberada na matriz do usuário
         e irá parar a recursão. */
            matrizUsuario[linha-1][coluna-1]=matrizJogo[linha-1][coluna-1]+'0';
            copiaJogo[linha-1][coluna-1]=1;
        }
      }
    }
/*E assim sucessivamente para o restante das coordenadas que ficam ao redor da mina.*/

    if (linha-1 >= 0){
      if (matrizJogo[linha-1][coluna] != -1){
         if(matrizUsuario[linha-1][coluna]=='x' && matrizJogo[linha-1][coluna]==0){
            matrizUsuario[linha-1][coluna]=matrizJogo[linha-1][coluna]+'0';
            modificar_campo_minado_recursivo(matrizJogo,matrizUsuario,linha-1,coluna,tamanho,copiaJogo);

            copiaJogo[linha-1][coluna]=1;
        }else if(matrizUsuario[linha-1][coluna]=='x' && matrizJogo[linha-1][coluna]!=0){
            matrizUsuario[linha-1][coluna]=matrizJogo[linha-1][coluna]+'0';

            copiaJogo[linha-1][coluna]=1;
        }
      }
    }

    if (linha-1 >= 0 && coluna+1 <= tamanho-1){
        if (matrizJogo[linha-1][coluna+1] != -1){
        if(matrizUsuario[linha-1][coluna+1]=='x' && matrizJogo[linha-1][coluna+1]==0){
            matrizUsuario[linha-1][coluna+1]=matrizJogo[linha-1][coluna+1]+'0';
            modificar_campo_minado_recursivo(matrizJogo,matrizUsuario,linha-1,coluna+1,tamanho,copiaJogo);

            copiaJogo[linha-1][coluna+1]=1;
        }else if(matrizUsuario[linha-1][coluna+1]=='x' && matrizJogo[linha-1][coluna+1]!=0){
            matrizUsuario[linha-1][coluna+1]=matrizJogo[linha-1][coluna+1]+'0';

            copiaJogo[linha-1][coluna+1]=1;
        }
        }
    }
    if (coluna-1 >= 0){
        if (matrizJogo[linha][coluna-1] != -1){
            
        if(matrizUsuario[linha][coluna-1]=='x' && matrizJogo[linha][coluna-1]==0){
            matrizUsuario[linha][coluna-1]=matrizJogo[linha][coluna-1]+'0';
            modificar_campo_minado_recursivo(matrizJogo,matrizUsuario,linha,coluna-1,tamanho,copiaJogo);

            copiaJogo[linha][coluna-1]=1;
        }else if(matrizUsuario[linha][coluna-1]=='x' && matrizJogo[linha][coluna-1]!=0){
            matrizUsuario[linha][coluna-1]=matrizJogo[linha][coluna-1]+'0';

            copiaJogo[linha][coluna-1]=1;
        }

        }
    }  

    if (coluna+1 <= tamanho-1){
      if (matrizJogo[linha][coluna+1] != -1){
        
        if(matrizUsuario[linha][coluna+1]=='x' && matrizJogo[linha][coluna+1]==0){
            matrizUsuario[linha][coluna+1]=matrizJogo[linha][coluna+1]+'0';
            modificar_campo_minado_recursivo(matrizJogo,matrizUsuario,linha,coluna+1,tamanho,copiaJogo);

            copiaJogo[linha][coluna+1]=1;
        }else if(matrizUsuario[linha][coluna+1]=='x' && matrizJogo[linha][coluna+1]!=0){
            matrizUsuario[linha][coluna+1]=matrizJogo[linha][coluna+1]+'0';
            copiaJogo[linha][coluna+1]=1;
        }

      }
    }

   if (linha+1 <= tamanho-1 && coluna-1 >= 0){
        if (matrizJogo[linha + 1][coluna - 1] != -1){
            
        if(matrizUsuario[linha+1][coluna-1]=='x' && matrizJogo[linha+1][coluna-1]==0){
            matrizUsuario[linha+1][coluna-1]=matrizJogo[linha+1][coluna-1]+'0';
            modificar_campo_minado_recursivo(matrizJogo,matrizUsuario,linha+1,coluna-1,tamanho,copiaJogo);

            copiaJogo[linha+1][coluna-1]=1;
        }else if(matrizUsuario[linha+1][coluna-1]=='x' && matrizJogo[linha+1][coluna-1]!=0){
            matrizUsuario[linha+1][coluna-1]=matrizJogo[linha+1][coluna-1]+'0';
            copiaJogo[linha+1][coluna-1]=1;
        }

        }
    }

   if (linha+1 <= tamanho-1){
        if (matrizJogo[linha+1][coluna] != -1){
            
        if(matrizUsuario[linha+1][coluna]=='x' && matrizJogo[linha+1][coluna]==0){
            matrizUsuario[linha+1][coluna]=matrizJogo[linha+1][coluna]+'0';
            modificar_campo_minado_recursivo(matrizJogo,matrizUsuario,linha+1,coluna,tamanho,copiaJogo);
            
            copiaJogo[linha+1][coluna]=1;
        }else if(matrizUsuario[linha+1][coluna]=='x' && matrizJogo[linha+1][coluna]!=0){
            matrizUsuario[linha+1][coluna]=matrizJogo[linha+1][coluna]+'0';

            copiaJogo[linha+1][coluna]=1;
        }

        }
    }

    if (linha+1 <= tamanho-1 && coluna+1 <= tamanho-1){
        if (matrizJogo[linha+1][coluna+1] != -1){
            
        if(matrizUsuario[linha+1][coluna+1]=='x' && matrizJogo[linha+1][coluna+1]==0){
            matrizUsuario[linha+1][coluna+1]=matrizJogo[linha+1][coluna+1]+'0';
            modificar_campo_minado_recursivo(matrizJogo,matrizUsuario,linha+1,coluna+1,tamanho,copiaJogo);

            copiaJogo[linha+1][coluna+1]=1;
        }else if(matrizUsuario[linha+1][coluna+1]=='x' && matrizJogo[linha+1][coluna+1]!=0){
            matrizUsuario[linha+1][coluna+1]=matrizJogo[linha+1][coluna+1]+'0';

            copiaJogo[linha+1][coluna+1]=1;
        }

        }
    }
  }


//Funcao responsavel por modificar a matriz do jogador de acordo com as coordenadas selecionadas
void modificar_campo_minado(int **matrizJogo,char **matrizUsuario,int n,int m,int *bomba,int tamanho,int **copiaJogo){

   /*Caso a coordenada escolhida seja uma bomba, o ponteiro que aponta para a flagBomba 
   recebe falso. Assim, fazendo com que o jogo encerre.*/
   
  if(matrizJogo[n][m]==-1){
   *bomba=0;
   matrizUsuario[n][m]='B';
  }else{

   /*Caso contrario, se a coordenada selecionada pelo usuario for diferente de 0 recebe a 
   quantidade de bombas vizinhas. Recebida da matriz "original" do jogo, montada logo no inicio.
   */
   if(matrizJogo[n][m]!=0){
   matrizUsuario[n][m]=matrizJogo[n][m]+'0';
   }else{
   /*Se a coordenada selecionada for igual a 0, será chamada a função 'modificar_campo_minado_recursivo',
   responsável pelo Flood fill usando recursão para liberar as minas vizinhas com valores 0, e será 
   liberada também a coordenada selecionada pelo usuário.*/
   matrizUsuario[n][m]=matrizJogo[n][m]+'0';
   modificar_campo_minado_recursivo(matrizJogo,matrizUsuario,n,m,tamanho,copiaJogo);
   }

   printf("\n\nUHU! Sem bomba por aqui!\n");
  }
}




/*Funcao verifica se a coordenada digitada pelo usuario existe*/
int verificar_Coordenada_Existente(int linha, int coluna,int tam){
   int flagCoordenada=1;

   //Verifica se a linha ou coluna sao menores que 0 ou maiores que o tamanho da matriz do jogo
   if(linha>tam-1 || linha<0 || coluna>tam-1 || coluna<0){
      flagCoordenada=0;
   }
   return flagCoordenada;
}

/*Funcao verifica se a coordenada digitada pelo usuário eh repetida.*/
int verificar_Coordenada_Repetida(int linha, int coluna,int ** matriz_copia){
   int flagCoordenada=1;

   /* Toda vez que uma nova coordenada eh selecionada a matriz copia recebe 1, ou seja,
   quando o valor da matriz for diferente de 0 a coordenada ja foi selecionada. Retornando falso.*/
   if(matriz_copia[linha][coluna]!=0){
      flagCoordenada=0;
   }

   return flagCoordenada;
}


/*Função responsável por calcular a quantidade de jogadas ja realizadas a partir da contagem das minas
que ja foram descobertas. Pois a Matriz Copia do jogo sempre recebe um 1 a cada mina liberada.
Assim, a função irá retornar a quantidade de jogadas para a variável contadora no main, responsável 
pelo criterio de parada do jogo (fundamental para caso a jogador ganhe).
*/
int calcular_Quantidade_Jogadas(int **matriz,int tamanho){
    int cont=0,i,j;

    for(i=0;i<tamanho;i++){
      for(j=0;j<tamanho;j++){
        if(matriz[i][j]!=0){
            cont++;
        }
      }
    }


    return cont;
}


 int main(void){
   int modo=0,tam=0,quantBombas=0,linha,coluna,cont=0,flagbomba=1;


   //Função para a criação do arquivo log.txt
   FILE* arquivo = criar_arquivo();

   //Função responsável por gravar um texto no arquivo log.txt
   adicionar_texto_txt(arquivo,"Início do jogo: \n");

   //Uso da struct tm da biblioteca time para realizar a impressão da data e hora do jogo
   struct tm *tm=criar_Hora();

   //Função responsável por gravar a data e hora no arquivo log.txt
   gravar_DataHora_txt(arquivo,tm);
   //Função responsável por fechar o arquivo log.txt
   fechar_arquivo(arquivo);


   printf("************ BEM VINDO(A) AO CAMPO MINADO! ************\n");
   printf("Para iniciar o jogo selecione o modo. Digite:\n1 - Facil\n2 - Medio\n3 - Dificil\n");

   //Verifica se o usuario coloca o modo diferente de 1,2 e 3
   while(scanf("%d",&modo),modo<1 || modo>3){
    printf("Modo Indisponivel. Digite:\n1 - Facil\n2 - Medio\n3 - Dificil\n");
   }

   //Configurar o campo minado de acordo com a dimensao da matriz e a quantidade de bombas
   dificuldadeJogo(&modo,&tam,&quantBombas);


   abrir_arquivo(arquivo);
   //Função para gravar texto de introdução, com a dificuldade e quantidade de bombas da partida
   adicionar_texto_introducao_txt(arquivo,modo,quantBombas);
   adicionar_texto_txt(arquivo,"Histórico completo da partida do usuário: \n");
   fechar_arquivo(arquivo);


   /*Funcao para alocar e criar a matriz do jogo e em seguida inicializar ela*/
   int **campo_minado= alocar_matriz(tam);
   inicializar_matriz(campo_minado,tam);

   /*Funcao para alocar, criar e inicializar a matriz copia do jogo, necessaria 
   posteriormente para tratar a exececao se o usuario digitar coordenadaas repetidas*/
   int **copia_campo_minado= alocar_matriz(tam);
   inicializar_matriz(copia_campo_minado,tam);

   /*Funcao para inserir as bombas de modo aleatorio e em seguida montar a matriz do jogo
   calculando os vizinhos da bomba*/
   inserirBombas(quantBombas,campo_minado,tam);
   montarMatrizDoJogo(campo_minado,tam);

   /*Funcao para alocar, criar e inicializar a matriz de visualizacao do usuario*/
   char **campo_minado_usuario= alocarEinicializar_matriz_char(tam);

   int quantJogadas=tam*tam-quantBombas; //calcula a quantidade de jogadas do usuario
   while(cont<quantJogadas && flagbomba){

      printf("***********************************************\n");
      printf("|Dificuldade: %d        |Quantidade de bombas:%d\n",modo,quantBombas);
      visualizar_matriz_char(campo_minado_usuario,tam);

      printf("Digite as coordenadas que deseja verificar. Ex: x,y\n");
      scanf("%d,%d",&linha,&coluna);
      linha-=1;
      coluna-=1;

      //Chama a funcao para verificar se a coordenada digitada pelo usuario existe
      if(verificar_Coordenada_Existente(linha, coluna,tam)==0){
         printf("\n\n-> COORDENADA DIGITADA NAO EXISTE. Digite novamente!\n");

        /*Gravar no arquivo a coordenada digitada pelo usuário avisando que a coordenada não existe,
        mostrando a matriz do jogo.*/
        abrir_arquivo(arquivo);
        gravar_matriz_coordenada_usuario_txt(arquivo,campo_minado_usuario,tam,linha+1,coluna+1);
        adicionar_texto_txt(arquivo,"Feedback dado ao usuário: \n");
        adicionar_texto_txt(arquivo,"-> COORDENADA DIGITADA NÃO EXISTE. Digite novamente!\n(Jogador teve que digitar uma nova coordenada).\n");
        fechar_arquivo(arquivo);
      }else{

         //Chama a funcao para verificar se a coordenada digitada pelo usuário eh repetida
         if(verificar_Coordenada_Repetida(linha, coluna,copia_campo_minado)){

            //Todo nova coordenada selecionada no jogo a matriz copia recebe 1
            inserir_valor_matriz(copia_campo_minado,linha,coluna,1);

            /*Quando verificada que a coordenada existe e nao esta repetida, ira modificar 
            o campo minado do usuario. 
            Dentro dessa função será chamada a função responsável pelo Flood Fill, caso 
            o usuário acerte uma coordenada com valor zero. 

            E também será passado a matriz copia do jogo como parametro, pois quando for chamada a função 
            recursiva, será necessária para gravar os locais que ja foram descobertos pelo Flood Fill
            (Todo nova coordenada descoberta na recursão a matriz copia recebe 1),
            que futuramente a matriz copia será necessária para descobrir a quantidade de jogadas ja realizadas.
            */
            modificar_campo_minado(campo_minado,campo_minado_usuario,linha,coluna,&flagbomba,tam,copia_campo_minado);
            
            abrir_arquivo(arquivo);
            /*Função responsável por gravar a matriz e as coordenadas de cada jogada no arquivo log.txt*/
            gravar_matriz_coordenada_usuario_txt(arquivo,campo_minado_usuario,tam,linha+1,coluna+1);
            fechar_arquivo(arquivo);

            /*Função responsável por calcular a quantidade de jogadas a partir da matriz copia que recebe
            1 para toda coordenada ja liberada pelo jogo.
            Assim, cont receberá a quantidade certas de jogadas ja realizadas.  
            Auxiliando a variável cont no seu critério de parada no while.
            */
            cont=calcular_Quantidade_Jogadas(copia_campo_minado,tam);

         }else{
            printf("\n\n-> COORDENADA DIGITADA JA DESCOBERTA. Digite novamente!\n");

        /*Gravar no arquivo a coordenada digitada pelo usuário avisando que a coordenada ja havia sido descoberta
        -ou seja é uma coordenada que já estava disponível para o jogador visualizar-,
         mostrando também a matriz do jogo.*/
            abrir_arquivo(arquivo);
            gravar_matriz_coordenada_usuario_txt(arquivo,campo_minado_usuario,tam,linha+1,coluna+1);
            adicionar_texto_txt(arquivo,"Feedback dado ao usuário: \n");
            adicionar_texto_txt(arquivo,"-> COORDENADA DIGITADA JÁ DESCOBERTA. Digite novamente!\n(Jogador teve que digitar uma nova coordenada).\n");
            fechar_arquivo(arquivo);
         }

      }

     printf("\n");
   }

   /*Quando encerrado as tentativas, verifica se o jogador ganhou ou perdeu, atraves da flagbomba.
   Mostrando a matriz original do jogo.*/
   visualizar_matriz_char(campo_minado_usuario,tam);
   abrir_arquivo(arquivo);

   if(flagbomba==0){
      printf("\ngame over\n\n");
      adicionar_texto_txt(arquivo,"Feedback dado ao usuário: \ngame over");
      adicionar_texto_txt(arquivo,"\n\nRESULTADO: JOGADOR PERDEU!\n");
   }else{
      printf("\nparabens, vc eh fera\n\n");
      adicionar_texto_txt(arquivo,"Feedback dado ao usuário: \nparabens, vc eh fera");
      adicionar_texto_txt(arquivo,"\n\nRESULTADO: JOGADOR GANHOU!\n");
   }
   printf("MATRIZ ORIGINAL DO JOGO:\n");

   gravar_matriz_original_txt(arquivo,campo_minado,tam);
   visualizar_matriz(campo_minado,tam);


   liberar_matriz(campo_minado,tam);
   liberar_matriz_char(campo_minado_usuario,tam);
   liberar_matriz(copia_campo_minado,tam);
   fechar_arquivo(arquivo);

   return 0;
 }
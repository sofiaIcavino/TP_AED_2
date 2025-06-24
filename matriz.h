/*Fazer alocacao das matrizes inteiras de maneira dinamica*/
int** alocar_matriz(int tamanho);


/*Fazer alocacao e inicializacao(com o caracter x) de matrizes char*/
char** alocarEinicializar_matriz_char(int tamanho);

/*Função para inserir um valor em determinada coordenada em uma matriz do tipo int*/
void inserir_valor_matriz(int **matriz,int linha,int coluna,int valor);

/*Função para inserir um valor em determinada coordenada em uma matriz do tipo char*/
void inserir_valor_matriz_char(char **matriz,int linha,int coluna,char valor);

/*Funcao para inicializacao das matrizes inteiras com 0*/
void inicializar_matriz(int **matriz,int tamanho);


/*Funcao para realizar a impressao da matriz de inteiros na tela*/
void visualizar_matriz(int **matriz,int tamanho);


/*Funcao para realizar a impressao da matriz (tipo char) de vizualizacao do usuario na tela,
de maneira que fique intuitiva para o jogador*/
void visualizar_matriz_char(char **matriz,int tamanho);


//Função responsável por liberar a memória das matrizes do tipo int
void liberar_matriz(int **mat,int linhas);


//Função responsável por liberar a memória das matrizes formada de caracteres 
void liberar_matriz_char(char **mat,int linhas);

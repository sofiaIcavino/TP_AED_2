//Função responsável pela criação do arquivo log.txt
FILE* criar_arquivo(void);

//Função responsável por abrir o arquivo log.txt
void abrir_arquivo(FILE *arquivo);

//Função responsável pelo fechamento do arquivo log.txt
void fechar_arquivo(FILE *arquivo);

//Função responsável por adicionar um texto no arquivo log.txt
void adicionar_texto_txt(FILE*arquivo,char texto[100]);

//Função responsável pela criação da estrutura responsável pela impressão da data e hora
struct tm* criar_Hora(void);

/*Função responsável por adicionar a data e hora no arquivo log.txt usando da struct tm
da biblioteca time para realizar a impressão*/
void gravar_DataHora_txt(FILE*arquivo,struct tm *hr);

/*Função responsável por adicionar o texto de introdução da partida no log.txt, informando a 
dificuldade e quantidade de bombas*/
void adicionar_texto_introducao_txt(FILE*arquivo,int modo,int quantBombas);

/*Função responsável por gravar a matriz (do tipo Char) e a coordenada de cada jogada no arquivo log.txt*/
void gravar_matriz_coordenada_usuario_txt(FILE*arquivo,char **matriz,int tamanho,int linha,int coluna);

/*Função responsável por gravar a matriz resposta do jogo no arquivo log.txt*/
void gravar_matriz_original_txt(FILE*arquivo,int **matriz,int tamanho);
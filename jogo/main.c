#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define BOLA 0
#define CRUZ 1
#define VAZIO 2
#define UNDERLINE 3


char intToSimb(int aNum)
{
 
  char res;
  switch(aNum)
  {
    case 0:
    res = 'O';
    break;
    case 1:
    res = 'X';
    break;
    case 2:
    res = ' ';
    break;
    case 3:
    res = '_';
    break;
    default:
    res='E';

  }
  
  return res;
}//como a matriz esta no formato inteiro na hora de imprimir ela eh necessario substituir os inteiros
// pelo Simbolos selecionados pelos autores


int coodernadaAtoI(char *aAlphanumerico) {
  int res = (int)aAlphanumerico[1];
  res = res - 49; // ASCII para inteiro
  res = 7 - res;  // inverter a ordem
  return res;
} // essa funcao pega uma coordenada alphanumerica como de xadrez e retorna a
  // posicao "i" na matriz


int coodernadaAtoJ(char *aAlphanumerico) {
  // valor inteiro de A = 65
  int res = (int)aAlphanumerico[0]; // transforma em um inteiro
  res = res - 65; // ASCII para inteiro ex:A->0,B->1,C->2...H->7
  return res;
} // essa funcao pega uma coordenada alphanumerica como de xadrez e retorna a
  // posicao "j" na matriz
bool movimentoLegal(int **tabuleiro, char *aMovimento)
{
  
  int tam = strlen(aMovimento);
  bool res=false;
  if(tam==2)//unico tamanho aceitavel
  {
  int intValueI=(int)aMovimento[0];
  int intValueJ=(int)aMovimento[1];
  if(intValueI >= 65 &&intValueI <= 72)//valores possiveis do primeiro caractere
  {
    if(intValueJ>=49&&intValueJ<=56)//valores possiveis do segundo caractere
    {
      res = true;
    }
  }
  }
  if(!res)
  {
      printf("\natencao:notacão invalida,digite novamente.\n");
  }
  return res;
}//essa funcao decide se o movimento sugerido pelo usuario é um movimento legal
// com as regras do othelo

int **comerHorizontal(char *aAlphanum,int **aTabuleiro,int aSimbolo )
{
  int i = coodernadaAtoI(aAlphanum);
  int j = coodernadaAtoJ(aAlphanum);
  
  
  int simboloOposto = (aSimbolo+1) % 2;//X->O,O->X // 0 ->1,1->0
  printf("\nSimbolo %d, Simbolo Oposto %d\n",aSimbolo,simboloOposto);
  int ateEsq = 0;
  int ateDir = 0;
  for(int jDireita  = j+1;(aTabuleiro[i][jDireita])!=aSimbolo;jDireita++)
  {
    printf("\nOlhando casa direita:%d , %d\n", i,jDireita);
    if(jDireita>=8||aTabuleiro[i][jDireita]==VAZIO)
    {
      ateDir=0;
      break;
    }
    ateDir++;

  }
    printf("\nFoi visto tantas casas a direita %d\n", ateDir);

    for(int jEsquerda = j-1;(aTabuleiro[i][jEsquerda])!=aSimbolo;jEsquerda--)
  {
    printf("\nOlhando casa esquerda :%d , %d\n", i,jEsquerda);
    if(jEsquerda<=0||aTabuleiro[i][jEsquerda]==VAZIO)
    {
      ateEsq=0;
      break;
    }
    ateEsq++;

  }
    printf("\nFoi visto tantas casas a esquerda %d\n", ateEsq);

  
  for(int ce = 1;ce<(ateEsq+1);ce++)
  {
    printf("\nOlhando casa esquerda :%d , %d\n", i,(j-ce));
    aTabuleiro[i][(j-ce)]=aSimbolo;  
  }
  for(int cd = 1;cd<(ateDir+1);cd++)
  {
    printf("\nOlhando casa DIreita :%d , %d\n", i,(j+cd));
    printf("\nSimbolo :%d\n", simboloOposto);


    aTabuleiro[i][(j+cd)]=aSimbolo;  
  }
  return aTabuleiro;
}


int **comerVertical(char *aAlphanum,int **aTabuleiro,int aSimbolo )
{
  int i = coodernadaAtoI(aAlphanum);
  int j = coodernadaAtoJ(aAlphanum);
  
  
  int simboloOposto = (aSimbolo+1) % 2;//X->O,O->X // 0 ->1,1->0
  printf("\nSimbolo %d, Simbolo Oposto %d\n",aSimbolo,simboloOposto);
  int ateBaixo = 0;
  int ateCima = 0;
  for(int iCima  = i+1;(aTabuleiro[iCima][j])!=aSimbolo;iCima++)
  {
    printf("\nOlhando casa emcima:%d , %d\n", iCima,j);
    if(iCima>=8||aTabuleiro[iCima][j]==VAZIO)
    {
      ateCima=0;
      break;
    }
    ateCima++;

  }
    printf("\nFoi visto tantas casas a emcima %d\n", ateCima);

    for(int iBaixo = i-1;(aTabuleiro[iBaixo][j])!=aSimbolo;iBaixo--)
  {
    printf("\nOlhando casa abaixo :%d , %d\n", iBaixo,j);
    if(iBaixo<=0||aTabuleiro[iBaixo][j]==VAZIO)
    {
      ateBaixo=0;
      break;
    }
    ateBaixo++;

  }
    printf("\nFoi visto tantas casas a abaixo %d\n", ateBaixo);

  
  for(int cb = 1;cb<(ateBaixo+1);cb++)
  {
    printf("\nOlhando casa abaixo :%d , %d\n", (i-cb),j);
    aTabuleiro[(i-cb)][j]=aSimbolo;  
  }
  for(int ca = 1;ca<(ateCima+1);ca++)
  {
    printf("\nOlhando casa emcima :%d , %d\n", (i+ca),j);
    printf("\nSimbolo :%d\n", simboloOposto);


    aTabuleiro[(i+ca)][j]=aSimbolo;  
  }
  return aTabuleiro;
}
/*int **comerDiagonal(char *aAlphanum, int **aTabuleiro, int aSimbolo)
{
  aTabuleiro=comerDiagonalDir(aAlphanum,aTabuleiro,aSimbolo);
  aTabuleiro=comerDiagonalEsq(aAlphanum,aTabuleiro,aSimbolo);
  return aTabuleiro;

}*/ 
int **comerPecas(char *aAlphanum, int **aTabuleiro, int aSimbolo)
{
  aTabuleiro=comerHorizontal(aAlphanum,aTabuleiro,aSimbolo);
  aTabuleiro=comerVertical(aAlphanum,aTabuleiro,aSimbolo);
  //aTabuleiro=comerDiagonal(aAlphanum,aTabuleiro,aSimbolo);

  
  return aTabuleiro;
}
int **createTabuleiro(int m, int n)
{
  // A pointer to a pointer to an int is used to store the pointer to our
  // 2D array of ints
  int **matrix;

  // malloc() is used to allocate space to store an array of pointers to ints
  // of length m... each element in this array will point to one of the 'm'
  // number of rows in our 2D array.  matrix will thus store the memory address
  // of the first elemetn in this array, but we can also think of it as a
  // pointer to our 2D array.  We use sizeof(int *) to get the size in bytes
  // of a pointer to an int, and multiply this by the number of elements
  // needed in our array (m) to allocate space for an array able to store
  // this amount of pointers to ints.
  matrix = malloc(sizeof(int *) * m);

  // Next we allocate space for each row of ints in our 2D array, where each
  // element in our array of pointers to ints as given by matrix[i] is set to
  // point to one of these rows.  sizeof(int) will give us the number of bytes
  // that it takes to store an int, and we multiply this by the number of
  // ints stored at each row (n, i.e. the number of columns), to have malloc()
  // allocate enough space to store a row of ints of this size.
  for (int i = 0; i < m; i++)
    matrix[i] = malloc(sizeof(int) * n);

  // Set the element in the 2D array at each row/column index to the fill value
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      matrix[i][j] = VAZIO;

  // Return the pointer to our 2D array... effectively returning the memory
  // address of the first element in the array of pointers to ints (i.e. the
  // array of pointers to each row of data).
  return matrix;
}//essa funcao utiliza de ponteiros para poder usar dinamicamente uma matriz
void drawTabuleiro(int **aTabuleiro) {
  printf("-------------------------\n");
  for (int i = 0; i < 8; i++) {
    printf("-%d-------\b", (8 - i));
    for (int j = 0; j < 8; j++) {
      
      printf("|%c|\b",intToSimb(aTabuleiro[i][j])) ;
    }
    printf("\n");
  }
  printf("---------\b A B C D E F G H \n-------------------------\n");
}// essa funcao imprime a matriz do tabuleiro do jogo no console 
int **userUpdateDrawTabuleiro(int **aTabuleiro, int aVezCruzBola)
{
  
  char ent[2];
  char simbolo = intToSimb(aVezCruzBola);
  int vez = aVezCruzBola;
  
  do{
  printf("\nEh a vez de:%c .Digite um movimento:\n",simbolo);
  scanf("%s",ent);
  }while(!movimentoLegal(aTabuleiro,ent));
  int i = coodernadaAtoI(ent);
  int j = coodernadaAtoJ(ent);
  
  aTabuleiro[i][j]=vez;
  aTabuleiro=comerPecas(ent,aTabuleiro,vez);
  drawTabuleiro(aTabuleiro);
  return aTabuleiro;

}// essa funcao permite que usuario coloque uma peca no tabuleiro 



int **updateTabuleiro(char* aAlphanum, int **aTabuleiro, int aSimbolo)
{
  int i = coodernadaAtoI(aAlphanum);
  int j = coodernadaAtoJ(aAlphanum);
  aTabuleiro[i][j]=aSimbolo;
  drawTabuleiro(aTabuleiro);
  return aTabuleiro;

}// essa funcao pega a coordenada em notacao de xadrez
//e altera a peca de lugar


int **setupTabuleiro(int **aTabuleiro)
{
  //No othelo comeca com uma cruz em e4 e d5 e bol em e5 e d4
  int i = coodernadaAtoI("E4");
  int j = coodernadaAtoJ("E4");
  aTabuleiro[i][j]=CRUZ;
  i = coodernadaAtoI("E5");
  j = coodernadaAtoJ("E5");
  aTabuleiro[i][j]=BOLA;
  i = coodernadaAtoI("D4");
  j = coodernadaAtoJ("D4");
  aTabuleiro[i][j]=BOLA;
  i = coodernadaAtoI("D5");
  j = coodernadaAtoJ("D5");
  aTabuleiro[i][j]=CRUZ;
  drawTabuleiro(aTabuleiro);
  return aTabuleiro;

}// essa funcao pega o tabuleiro vaizo e  retorna o tabuleiro com as pecas iniciais


int main() {
  // criar tabuleiro
  int **tabuleiro;
  tabuleiro = createTabuleiro(8,8);
  tabuleiro = setupTabuleiro(tabuleiro);
  int vez = BOLA;
  //jogo
  
  for(int i = 0; i<10;i++)
  {
    userUpdateDrawTabuleiro(tabuleiro,vez);
    vez=(vez+1)%2;
  }
//finalizar
// Free the memory that was allocated for each row in the 2D array
  for (int i = 0; i < 8; i++)
    free(tabuleiro[i]);

  // Free the memory that was allocated for the array of pointers to each
  // row in our 2D array
  free(tabuleiro);
  
  // teste discord 3
  return 0;
}
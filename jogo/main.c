#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define BOLA 0
#define CRUZ 1
#define VAZIO 2
#define UNDERLINE 3
#define TEMPORARIO 4 


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
    case 4:
    res = 'T';
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

int **comerHorizontal(int ai, int aj,int **aTabuleiro,int aSimbolo )
{
  
  int ateEsq = 0;
  int ateDir = 0;
  
  for(int jDireita  = aj;(aTabuleiro[ai][jDireita])!=aSimbolo;jDireita++)
  {
    //printf("\nDireita:Olhando simbolo %d na casa:(%d,%d)",aTabuleiro[ai][jDireita],ai,jDireita); 
    if((jDireita+1)>=8||aTabuleiro[ai][jDireita]==VAZIO)
    {
      ateDir=0;
      break;
    }
    //printf("\nDireita:Olhando simbolo %d na casa:(%d,%d)",aTabuleiro[ai][jDireita],ai,jDireita); 

    ateDir++;
  }
  for(int jEsquerda = aj;(aTabuleiro[ai][jEsquerda])!=aSimbolo;jEsquerda--)
  {
    //printf("\nEsquerda: Olhando simbolo %d na casa:(%d,%d)",aTabuleiro[ai][jEsquerda],ai,jEsquerda); 
    if((jEsquerda-1)<=-1||aTabuleiro[ai][jEsquerda]==VAZIO)
    {
      ateEsq=0;
      break;
    }
    //printf("\nEsquerda: Olhando simbolo %d na casa:(%d,%d)",aTabuleiro[ai][jEsquerda],ai,jEsquerda); 

    ateEsq++;
  }
  for(int ce = 1;ce<(ateEsq+1);ce++)
  {
    aTabuleiro[ai][(aj-ce)]=aSimbolo;  
  }
  for(int cd = 1;cd<(ateDir+1);cd++)
  {
    aTabuleiro[ai][(aj+cd)]=aSimbolo;  
  }
  return aTabuleiro;
}


int **comerVertical(int ai,int aj,int **aTabuleiro,int aSimbolo )
{
  
  int atebaixo=0;
  int atecima=0;
  
  for(int ibaixo  = ai;(aTabuleiro[ibaixo][aj])!=aSimbolo;ibaixo++)
  {
    if((ibaixo+1)>=8||aTabuleiro[ibaixo][aj]==VAZIO)
    {
      atebaixo=0;
      break;
    }
    atebaixo++;
  }
  for(int icima = ai;(aTabuleiro[icima][aj])!=aSimbolo;icima--)
  {
    if((icima-1)<=-1||aTabuleiro[icima][aj]==VAZIO)
    {
      atecima=0;
      break;
    }
    atecima++;
  }
  for(int cc = 1;cc<(atecima+1);cc++)
  {
    aTabuleiro[(ai-cc)][aj]=aSimbolo;  
  }
  for(int cb = 1;cb<(atebaixo+1);cb++)
  {
    aTabuleiro[(ai+cb)][aj]=aSimbolo;  
  }
  return aTabuleiro;
}
int **comerDiagonalBack_Slash(int ai,int aj,int **aTabuleiro,int aSimbolo)
{
  int atebaixodir=0;
  int atecimaesq=0;
  int ibaixo  = ai;
  int jdireita=aj;
  for(ibaixo;(aTabuleiro[ibaixo][jdireita])!=aSimbolo;ibaixo++)
  {
    if((ibaixo+1)>=8||(jdireita+1)>=8||aTabuleiro[ibaixo][jdireita]==VAZIO)
    {
      atebaixodir=0;
      break;
    }
    atebaixodir++;
    jdireita++;
  }
  int icima = ai;
  int jesquerda=aj;
  for(icima;(aTabuleiro[icima][jesquerda])!=aSimbolo;icima--)
  {
    if((icima-1)<=-1||(jesquerda-1)<=-1||aTabuleiro[icima][jesquerda]==VAZIO)
    {
      atecimaesq=0;
      break;
    }
    atecimaesq++;
    jesquerda--;
  }
  for(int cce = 1;cce<(atecimaesq+1);cce++)
  {
    aTabuleiro[(ai-cce)][(aj-cce)]=aSimbolo;  
  }
  for(int cbd = 1;cbd<(atebaixodir+1);cbd++)
  {
    aTabuleiro[(ai+cbd)][(aj+cbd)]=aSimbolo;  
  }
  return aTabuleiro;
}
int **comerDiagonalFoward_Slash(int ai,int aj,int **aTabuleiro,int aSimbolo)
{
  int atebaixoesq=0;
  int atecimadir=0;
  int ibaixo  = ai;
  int jesquerda=aj;
  for(ibaixo;(aTabuleiro[ibaixo][jesquerda])!=aSimbolo;ibaixo++)
  {
    printf("\nDireita:Olhando simbolo %c na casa:(%d,%d)",intToSimb(aTabuleiro[ibaixo][jesquerda]),ibaixo,jesquerda);
    if((ibaixo+1)>=8||(jesquerda-1)<=-1||aTabuleiro[ibaixo][jesquerda]==VAZIO)
    {
      atebaixoesq=0;
      break;
    }
    printf("\nDireita:Olhando simbolo %d na casa:(%d,%d)",aTabuleiro[ibaixo][jesquerda],ibaixo,jesquerda);

    atebaixoesq++;
    jesquerda--;
  }
  int icima = ai;
  int jdireita=aj;
  for(icima;(aTabuleiro[icima][jdireita])!=aSimbolo;icima--)
  {
    if((icima-1)<=-1||(jdireita+1)>=8||aTabuleiro[icima][jdireita]==VAZIO)
    {
      atecimadir=0;
      break;
    }
    atecimadir++;
    jdireita++;
  }
  for(int cbe = 1;cbe<(atebaixoesq+1);cbe++)
  {
    aTabuleiro[(ai+cbe)][(aj-cbe)]=aSimbolo;  
  }
  for(int ccd = 1;ccd<(atecimadir+1);ccd++)
  {
    aTabuleiro[(ai-ccd)][(aj+ccd)]=aSimbolo;  
  }
  return aTabuleiro;
}
int **comerDiagonal(int ai,int aj, int **aTabuleiro, int aSimbolo)
{
  aTabuleiro=comerDiagonalFoward_Slash(ai,aj,aTabuleiro,aSimbolo);//             diagonal-> /
  aTabuleiro=comerDiagonalBack_Slash(ai,aj,aTabuleiro,aSimbolo);//\*   diagonal-> \     \*
  return aTabuleiro;

} 
int **comerPecas(char *aAlphanum, int **aTabuleiro, int aSimbolo)
{
  //lembrando que o simbolo jogado so é colocado no final de comer todas as pecas
  //isso eh feito para que o loop comeca na casa jogada e nao quebre o i ou j for colocado 
  //dentro da array
  
  int i = coodernadaAtoI(aAlphanum);
  int j = coodernadaAtoJ(aAlphanum);
  aTabuleiro[i][j]=TEMPORARIO;
  aTabuleiro=comerHorizontal(i,j,aTabuleiro,aSimbolo);
  aTabuleiro=comerVertical(i,j,aTabuleiro,aSimbolo);
  aTabuleiro=comerDiagonal(i,j,aTabuleiro,aSimbolo);
  aTabuleiro[i][j]=aSimbolo;

  
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
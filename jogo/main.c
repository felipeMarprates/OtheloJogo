#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>//upperLetter
#define BOLA 0
#define CRUZ 1
#define VAZIO 2
#define UNDERLINE 3
#define TEMPORARIO 4 
/*Lista de coisas pra fazer
1-> Comentar mais o codigo
2-> Criar Funcao que conta quantos Simbolos tem no tabuleiro
3-> Melhorar movimentolegal
4-> Criar rodadas*/

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
bool existeEsseMovimento(char *aMovimento)
{
  int tam = strlen(aMovimento);
  bool existeEsseMovimento=false;
  if(tam==2)//unico tamanho aceitavel
  {
  int intValueI=(int)aMovimento[0];
  int intValueJ=(int)aMovimento[1];
  if(intValueI >= 65 &&intValueI <= 72)//valores possiveis do primeiro caractere
  {
    if(intValueJ>=49&&intValueJ<=56)//valores possiveis do segundo caractere
    {
      existeEsseMovimento = true;
    }
  }
  }
  if(!existeEsseMovimento)
  {
      printf("\notacao invalida,digite novamente.\n");
  }
  return existeEsseMovimento;
}
bool essaCasaEstaVaga( int ai, int aj,int **aTabuleiro)
{
  bool essaCasaEstaVaga = false;
  if(aTabuleiro[ai][aj]==VAZIO)
  {
    essaCasaEstaVaga= true;
  }
  if(essaCasaEstaVaga==false)
  {
    printf("\nEsta casa esta ocupada,digite novamente.\n");
  }
  return essaCasaEstaVaga;
}
bool esseMovimentoComePeca(int ai, int aj,int **aTabuleiro,int aSimbolo)
{
  return true;
}
bool movimentoLegal(int **aTabuleiro, char *aMovimento)
{
  int i = coodernadaAtoI(aMovimento);
  int j = coodernadaAtoJ(aMovimento);
  bool movimentoLegal = false;
  if(existeEsseMovimento(aMovimento) && essaCasaEstaVaga(i,j,aTabuleiro) && esseMovimentoComePeca(i,j,aTabuleiro,VAZIO))
  {
    movimentoLegal = true;
  }
  return movimentoLegal;
}//essa funcao decide se o movimento sugerido pelo usuario é um movimento legal
// com as regras do othelo

int **comerHorizontal(int ai, int aj,int **aTabuleiro,int aSimbolo )
{
  
  int ateEsq = 0;
  int ateDir = 0;
  int simboloOposto=(aSimbolo+1)%2;
  int count;
  
  for(count  = aj+1;(count+1<8) && ((aTabuleiro[ai][count])==simboloOposto);count++)
  {
    //teste ->printf("\nDireita: Olhando simbolo %d na casa:(%d,%d)",aTabuleiro[ai][count],ai,count); 
    ateDir++;
  }
  for(count = aj-1;(count-1>-1) && ((aTabuleiro[ai][count])==simboloOposto);count--)
  {
    //printf("\nEsquerda: Olhando simbolo %d na casa:(%d,%d)",aTabuleiro[ai][count],ai,count); 
    ateEsq++;
  }
  int indexUltimoSimboloAEsq =  aj-(ateEsq+1);
  int indexUltimoSimboloADir =  aj+(ateDir+1);

  if(indexUltimoSimboloAEsq>-1)//index valido
  {
    if(aTabuleiro[ai][indexUltimoSimboloAEsq]==aSimbolo)// os simbolos opostos estao no meio de dois simbolos ex:XOOX
    {
      for(count = 1;count<(ateEsq+1);count++)
      {
        aTabuleiro[ai][(aj-count)]=aSimbolo;  
      }
    }
  }
  if(indexUltimoSimboloADir<8)//index valido
  {
    if(aTabuleiro[ai][indexUltimoSimboloADir]==aSimbolo)
    {
      for(count = 1;count<(ateDir+1);count++)
      {
        aTabuleiro[ai][(aj+count)]=aSimbolo;  
      }
    }
  }
  return aTabuleiro;
}


int **comerVertical(int ai,int aj,int **aTabuleiro,int aSimbolo )
{
  
  int atebaixo=0;
  int atecima=0;
  int simboloOposto=(aSimbolo+1)%2;
  int count;
  
  for(count  = ai+1;((count+1)<8) && ((aTabuleiro[count][aj])==simboloOposto);count++)
  {
    //printf("\nBaixo: Olhando simbolo %d na casa:(%d,%d)",aTabuleiro[count][aj],count,aj); 
    atebaixo++;
  }
  for(count = ai-1;((count-1)>-1) && (aTabuleiro[count][aj]==simboloOposto);count--)
  {
    //printf("\nAlto: Olhando simbolo %d na casa:(%d,%d)",aTabuleiro[count][aj],count,aj); 
    atecima++;
  }
  int indexUltimoSimboloAcima  = ai-(atecima+1);
  int indexUltimoSimboloAbaixo = ai+(atebaixo+1);
  if(indexUltimoSimboloAcima>-1)//index valido
  {
    if(aTabuleiro[indexUltimoSimboloAcima][aj]==aSimbolo)
    {
      for(count = 1;count<(atecima+1);count++)
      {
        aTabuleiro[(ai-count)][aj]=aSimbolo;  
      }
    }
  }
  if(indexUltimoSimboloAbaixo<8)
  {
    if(aTabuleiro[indexUltimoSimboloAbaixo][aj]==aSimbolo)
    {
      for(count = 1;count<(atebaixo+1);count++)
      {
        aTabuleiro[(ai+count)][aj]=aSimbolo;  
      }
    }
  }
  return aTabuleiro;
}
int **comerDiagonalBack_Slash(int ai,int aj,int **aTabuleiro,int aSimbolo)
{
  int atebaixodir=0;
  int atecimaesq=0;
  int simboloOposto=(aSimbolo+1)%2;
  int countI,countJ;
  for(countI=ai+1,countJ=aj+1;((countI+1)<8) && ((countJ+1)<8) && (aTabuleiro[countI][countJ]==simboloOposto);countI++,countJ++)
  {
    //printf("\nBaixo e direita: Olhando simbolo %d na casa:(%d,%d)",aTabuleiro[countI][countJ],countI,countJ); 
    atebaixodir++;
  }

  for(countI=ai-1,countJ=aj-1;((countI-1)>-1)&&((countJ-1)>-1) && (aTabuleiro[countI][countJ]==simboloOposto);countI--,countJ--)
  {
    //printf("\ncima e Esquerda: Olhando simbolo %d na casa:(%d,%d)",aTabuleiro[countI][countJ],countI,countJ); 
    atecimaesq++;
  }
  int indexUltimoSimboloAEsq   = aj-(atecimaesq+1);
  int indexUltimoSimboloADir   = aj+(atebaixodir+1);
  int indexUltimoSimboloAcima  = ai-(atecimaesq+1);
  int indexUltimoSimboloAbaixo = ai+(atebaixodir+1);
  if(indexUltimoSimboloAbaixo<8&&indexUltimoSimboloADir<8)//index valido
  {
    if(aTabuleiro[indexUltimoSimboloAbaixo][indexUltimoSimboloADir]==aSimbolo)
    {
      for(countI = 1;countI<(atebaixodir+1);countI++)
      {
        aTabuleiro[(ai+countI)][(aj+countI)]=aSimbolo;  
      }
    }
  }
  if(indexUltimoSimboloAcima>-1&&indexUltimoSimboloAEsq>-1)//index valido
  {
    if(aTabuleiro[indexUltimoSimboloAcima][indexUltimoSimboloAEsq]==aSimbolo)
    {
      for(countI = 1;countI<(atecimaesq+1);countI++)
      {
        aTabuleiro[(ai-countI)][(aj-countI)]=aSimbolo;  
      }
    }
  }
  return aTabuleiro;
}
int **comerDiagonalFoward_Slash(int ai,int aj,int **aTabuleiro,int aSimbolo)
{
  int atebaixoesq=0;
  int atecimadir=0;
  int simboloOposto=(aSimbolo+1)%2;
  int countI,countJ;
  for(countI=ai+1,countJ=aj-1;((countI+1)<8) && ((countJ-1)>-1) && (aTabuleiro[countI][countJ]==simboloOposto);countI++,countJ--)
  {
    //printf("\nBaixo e Esquerda: Olhando simbolo %d na casa:(%d,%d)",aTabuleiro[countI][countJ],countI,countJ); 
    atebaixoesq++;
  }

  for(countI=ai-1,countJ=aj+1;((countI-1)>-1) && ((countJ+1)<8) && (aTabuleiro[countI][countJ]==simboloOposto);countI--,countJ++)
  {
    //printf("\ncima e Direita: Olhando simbolo %d na casa:(%d,%d)",aTabuleiro[countI][countJ],countI,countJ); 
    atecimadir++;
  }
  int indexUltimoSimboloAEsq   = aj-(atebaixoesq+1);
  int indexUltimoSimboloADir   = aj+(atecimadir+1);
  int indexUltimoSimboloAcima  = ai-(atecimadir+1);
  int indexUltimoSimboloAbaixo = ai+(atebaixoesq+1);
  if(indexUltimoSimboloAbaixo<8&&indexUltimoSimboloAEsq>-1)
  {
    if(aTabuleiro[indexUltimoSimboloAbaixo][indexUltimoSimboloAEsq]==aSimbolo)
    {
      for(countI = 1;countI<(atebaixoesq+1);countI++)
      {
        aTabuleiro[(ai+countI)][(aj-countI)]=aSimbolo;  
      }
    }
  }
  if(indexUltimoSimboloAcima>-1&&indexUltimoSimboloADir<8)
  {
    if(aTabuleiro[indexUltimoSimboloAcima][indexUltimoSimboloADir]==aSimbolo)
    {
      for(countI = 1;countI<(atecimadir+1);countI++)
      {
        aTabuleiro[(ai-countI)][(aj+countI)]=aSimbolo;  
      }
    }
  }
  return aTabuleiro;
}
int **comerDiagonal(int ai,int aj, int **aTabuleiro, int aSimbolo)
{
  aTabuleiro=comerDiagonalFoward_Slash(ai,aj,aTabuleiro,aSimbolo);//   diagonal-> /
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
  aTabuleiro=comerHorizontal(i,j,aTabuleiro,aSimbolo);
  aTabuleiro=comerVertical(i,j,aTabuleiro,aSimbolo);
  aTabuleiro=comerDiagonal(i,j,aTabuleiro,aSimbolo);
  aTabuleiro[i][j]=aSimbolo;

  
  return aTabuleiro;
}
int **createTabuleiro(int m, int n)
{
  int **matrix;
  matrix = malloc(sizeof(int *) * m);
  for (int i = 0; i < m; i++)
  {
    matrix[i] = malloc(sizeof(int) * n);
  }
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      matrix[i][j] = VAZIO;
    }
  }
  return matrix;
}//essa funcao utiliza de ponteiros para poder usar dinamicamente uma matriz
void printTabuleiro(int **aTabuleiro) {
  printf(" ----------------------------------\n");
  printf("|----------------------------------|\n");
  

  for (int i = 0; i < 8; i++) {
    printf("|-------%d--", (8 - i));
    for (int j = 0; j < 8; j++) {
      
      printf("|%c|\b",intToSimb(aTabuleiro[i][j])) ;
    }
    printf("|-------|\n");
  }
  printf("|----------------------------------|\n");
  printf("|-----------\b|A B C D E F G H|-------|\n");
  printf(" ---------------------------------- \n");
}// essa funcao imprime a matriz do tabuleiro do jogo no console 
int **userUpdatePrintTabuleiro(int **aTabuleiro, int aVezCruzBola)
{
  
  char ent[2];
  char simbolo = intToSimb(aVezCruzBola);
  int vez = aVezCruzBola;
  
  do{
  printf("\nEh a vez de:%c .Digite um movimento:\n",simbolo);
  scanf("%s",ent);
  ent[0] = toupper(ent[0]);//Colocar em letra maiscula
  }while(!movimentoLegal(aTabuleiro,ent));
  int i = coodernadaAtoI(ent);
  int j = coodernadaAtoJ(ent);
  
  
  aTabuleiro=comerPecas(ent,aTabuleiro,vez);
  printTabuleiro(aTabuleiro);
  return aTabuleiro;

}// essa funcao permite que usuario coloque uma peca no tabuleiro 



int **updateTabuleiro(int ai,int aj, int **aTabuleiro, int aSimbolo)
{
  aTabuleiro[ai][aj]=aSimbolo;
  printTabuleiro(aTabuleiro);
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
  printTabuleiro(aTabuleiro);
  return aTabuleiro;

}// essa funcao pega o tabuleiro vaizo e  retorna o tabuleiro com as pecas iniciais


int main() {
  // criar tabuleiro
  int **tabuleiro;
  tabuleiro = createTabuleiro(8,8);
  setupTabuleiro(tabuleiro);
  int vez = BOLA;
  //jogo
  
  for(int i = 0; i<10;i++)
  {
    userUpdatePrintTabuleiro(tabuleiro,vez);
    vez=(vez+1)%2;
  }
//finalizar
// Free the memory that was allocated for each row in the 2D array
  for (int i = 0; i < 8; i++)
  {
    free(tabuleiro[i]);
  }
  // Free the memory that was allocated for the array of pointers to each
  // row in our 2D array
  free(tabuleiro);
  return 0;
}
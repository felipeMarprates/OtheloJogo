/*
Integrantes:
Felipe Vilas Boas Marprates 15574822
Marcos Paulo Rocha Baltazar
Mikael Floriano da Silva
*/


#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>//upperLetter

// Definições de constantes para representar peças no tabuleiro
#define BOLA 0
#define CRUZ 1
#define VAZIO 2
#define UNDERLINE 3
#define TEMPORARIO 4 
/*Lista de coisas pra fazer

1-> Criar Lista de movimentos disponiveis

*/


// -------------------dicionario -------------------
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

// Structs para representar peças e contagem de peças
typedef struct{
  int i;
  int j;
  int simb;
}Peca;//essa struct é para simplificar o codigo ja que os elementos sempre estao associados uns aos outros
typedef struct{
  int bolas;
  int cruzes;
}NumDe;//essa struct é pra armazenar num de bolas e num de cruzes
//------------------- XXXX ----------------------\\

//-----traducao alphanumerico to I e J, e I e J to alphanumerico-------\\

int coordernadaAtoI(char *aAlphanumerico) {
  return (int)aAlphanumerico[1] - 49;
} // essa funcao pega uma coordenada alphanumerica como de xadrez e retorna a

int coordernadaAtoJ(char *aAlphanumerico) {
  return (int)aAlphanumerico[0] - 65;
} // essa funcao pega uma coordenada alphanumerica como de xadrez e retorna a

char coordenadaItoA1(int ai) {
  return (char)(ai + 49);
}//essa funcao pega uma coordenada de matriz I e retorna a posicao 1 da string Alphanumerica utilizada no console

char coordenadaJtoA0(int aj) {
  return (char)(aj + 65);
} //essa funcao pega uma coordenada de matriz I e retorna a posicao 0 da string Alphanumerica utilizada no console



//------------------- XXXXX -----------//

//------------------- Checar se o movimento é legal ----------


bool existeEsseMovimento(char *aMovimento)
{
  
  int tam = strlen(aMovimento);
  if(tam==2)//unico tamanho aceitavel
  {
    int intValueI=(int)aMovimento[0];
    int intValueJ=(int)aMovimento[1];
    if(intValueI >= 65 &&intValueI <= 72)//valores possiveis do primeiro caractere
    {
      if(intValueJ>=49&&intValueJ<=56)//valores possiveis do segundo caractere
      {
        return true;
      }
    }
  }
  
  return false;
}//esse funcao determina se o movimento é um dos 64 movimentos existentes no othelo
bool essaCasaEstaVaga( int ai, int aj,int **aTabuleiro)
{
  if(aTabuleiro[ai][aj]==VAZIO)
  {
    return true;
  }

  return false;
}//essa funcao verifica se o jogador esta jogando em uma casa que ja esta ocupada

int quantasPecasEsseMovimentoComeNaDir(int ai, int aj,int **aTabuleiro,int aSimbolo)
{
  int pecasComidas = 0;
  int count;  
  int simboloOposto=!aSimbolo;
  for(count  = aj+1;(count+1<8) && ((aTabuleiro[ai][count])==simboloOposto);count++)
  {
    pecasComidas++;
  }
  count = aj+1+pecasComidas;
  if(count<8&&(aTabuleiro[ai][count])==aSimbolo)//index valido e  se depois que ele saiu do loop é um simbolo contrario
  {
    return pecasComidas;
  }
  return 0;
}
int quantasPecasEsseMovimentoComeNaEsq(int ai, int aj,int **aTabuleiro,int aSimbolo)
{
  int pecasComidas = 0;
  int count;  
  int simboloOposto=(aSimbolo+1)%2;
  for(count  = aj-1;(count-1>-1) && ((aTabuleiro[ai][count])==simboloOposto);count--)
  {
    pecasComidas++;
  }
  count = aj-1-pecasComidas;//nao sei pq eu preciso igualar isso na minha opniao ja deceria ser isso ???
  if(count>-1&&(aTabuleiro[ai][count])==aSimbolo)//index valido e  se depois que ele saiu do loop é um simbolo contrario
  {
  return pecasComidas;
  }
  return 0;
}
int quantasPecasEsseMovimentoComeEmCima(int ai, int aj,int **aTabuleiro,int aSimbolo)
{
  int pecasComidas = 0;
  int count; 
  int aSimboloOposto=!aSimbolo; 
  for(count  = ai-1;(count-1>-1) && ((aTabuleiro[count][aj])==aSimboloOposto);count--)
  {
    pecasComidas++;
  }
  count= ai-1-pecasComidas;
  if(count>-1&&(aTabuleiro[count][aj])==aSimbolo)//index valido e  se depois que ele saiu do loop é um simbolo contrario
  {
  return pecasComidas;
  }
  return 0;
}
int quantasPecasEsseMovimentoComeEmBaixo(int ai, int aj,int **aTabuleiro,int aSimbolo)
{
  int pecasComidas = 0;
  int count;
  int aSimboloOposto=!aSimbolo;  
  for(count  = ai+1;(count+1<8) && ((aTabuleiro[count][aj])==aSimboloOposto);count++)
  {
    pecasComidas++;
  }
  count= ai+1+pecasComidas;

  if(count<8&&(aTabuleiro[count][aj])==aSimbolo)//index valido e  se depois que ele saiu do loop é um simbolo contrario
  {
  return pecasComidas;
  }
  return 0;
}
int quantasPecasEsseMovimentoComeNaDiagonalBaiDir(int ai, int aj,int **aTabuleiro,int aSimbolo)
{
  int pecasComidas = 0;
  int counti,countj;  
  int aSimboloOposto=!aSimbolo;
  for(counti= ai+1,countj=aj+1;(counti+1<8)&&(countj+1<8) && ((aTabuleiro[counti][countj])==aSimboloOposto);counti++,countj++)
  {
    pecasComidas++;
  }
  counti= ai+1+pecasComidas;
  countj= aj+1+pecasComidas;
  if(counti<8&&countj<8&&(aTabuleiro[counti][countj])==aSimbolo)//index valido e  se depois que ele saiu do loop é um simbolo contrario
  {
  return pecasComidas;
  }
  return 0;
}
int quantasPecasEsseMovimentoComeNaDiagonalBaiEsq(int ai, int aj,int **aTabuleiro,int aSimbolo)
{
  int pecasComidas = 0;
  int counti,countj;
  int aSimboloOposto=!aSimbolo;  
  for(counti  = ai+1, countj=aj-1;((counti+1)<8)&&((countj-1)>-1) && ((aTabuleiro[counti][countj])==aSimboloOposto);counti++,countj--)
  {
    pecasComidas++;
  }
  counti= ai+1+pecasComidas;
  countj= aj-1-pecasComidas;
  if(counti<8&&countj>-1&&(aTabuleiro[counti][countj])==aSimbolo)//index valido e  se depois que ele saiu do loop é um simbolo contrario
  {
  return pecasComidas;
  }
  return 0;
}
int quantasPecasEsseMovimentoComeNaDiagonalCimEsq(int ai, int aj,int **aTabuleiro,int aSimbolo)
{
  int pecasComidas = 0;
  int counti,countj;  
  int aSimboloOposto=!aSimbolo;
  for(counti  = ai-1, countj=aj-1;(counti-1>-1)&&(countj-1>-1) && ((aTabuleiro[counti][countj])==aSimboloOposto);counti--,countj--)
  {
    //printf("\ncima e Esquerda: Olhando simbolo %d na casa:(%d,%d) = contador = %d\n",aTabuleiro[counti][countj],counti,countj,pecasComidas); 
 
    pecasComidas++;
  }
  counti= ai-1-pecasComidas;
  countj= aj-1-pecasComidas;
  if(counti>-1&&countj>-1&&(aTabuleiro[counti][countj])==aSimbolo)//index valido e  se depois que ele saiu do loop é um simbolo contrario
  {
  return pecasComidas;
  }
  return 0;
}
int quantasPecasEsseMovimentoComeNaDiagonalCimDir(int ai, int aj,int **aTabuleiro,int aSimbolo)
{
  int pecasComidas = 0;
  int counti,countj;  
  int aSimboloOposto=!aSimbolo;
  for(counti  = ai-1,countj=aj+1;(counti-1>-1)&&(countj+1<8) && ((aTabuleiro[counti][countj])==aSimboloOposto);counti--,countj++)
  {
    pecasComidas++;
  }
  counti= ai-1-pecasComidas;
  countj= aj+1+pecasComidas;
  if(counti>-1&&countj<8&&(aTabuleiro[counti][countj])==aSimbolo)//index valido e  se depois que ele saiu do loop é um simbolo contrario
  {
  return pecasComidas;
  }
  return 0;
}

int esseMovimentoComeQuantasPeca(int ai,int aj,int **aTabuleiro,int aSimbolo)
{
  int numeroTotal = 0;
  //printf("%d",numeroTotal);
  numeroTotal += quantasPecasEsseMovimentoComeEmBaixo(ai, aj,aTabuleiro,aSimbolo);
  //printf("%d",numeroTotal);
  numeroTotal += quantasPecasEsseMovimentoComeEmCima(ai, aj,aTabuleiro,aSimbolo);
  //printf("%d",numeroTotal);
  numeroTotal += quantasPecasEsseMovimentoComeNaDir(ai, aj,aTabuleiro,aSimbolo);
  //printf("%d",numeroTotal);
  numeroTotal += quantasPecasEsseMovimentoComeNaEsq(ai, aj,aTabuleiro,aSimbolo);
  //printf("%d",numeroTotal);
  numeroTotal += quantasPecasEsseMovimentoComeNaDiagonalBaiDir(ai, aj,aTabuleiro,aSimbolo);
 // //printf("%d",numeroTotal);
  numeroTotal += quantasPecasEsseMovimentoComeNaDiagonalBaiEsq(ai, aj,aTabuleiro,aSimbolo);
  //printf("%d",numeroTotal);
  numeroTotal += quantasPecasEsseMovimentoComeNaDiagonalCimDir(ai, aj,aTabuleiro,aSimbolo);
  //printf("%d",numeroTotal);
  numeroTotal += quantasPecasEsseMovimentoComeNaDiagonalCimEsq(ai, aj,aTabuleiro,aSimbolo);


  return numeroTotal;
}//essa funcao verifica se o jogador esta jogando em uma casa que altera o simbolos de outras pecas

bool existeUmMovimentoLegal(int **aTabuleiro, int aSimbolo)
{//
  for(int i = 0;i < 8; i++)
  {
    for(int j = 0; j< 8; j++)
    {
      if(aTabuleiro[i][j]==VAZIO && esseMovimentoComeQuantasPeca(i,j,aTabuleiro,aSimbolo)!=0)
      {
        return true;
      }
    }
  }
  return false;
}
bool movimentoLegal(int **aTabuleiro, char *aMovimento,int aSimboloOposto)
{
  //mudanca de notacao
  int i = coordernadaAtoI(aMovimento);
  int j = coordernadaAtoJ(aMovimento);
  //checagem de todas condicoes
  if(existeEsseMovimento(aMovimento) && essaCasaEstaVaga(i,j,aTabuleiro) && esseMovimentoComeQuantasPeca(i,j,aTabuleiro,aSimboloOposto))
  {
    return true;
  }
  if(aMovimento[0]=='G'&&aMovimento[1]=='G')
  {
    return true;//esse input é usado quando o usuario deseja parar de jogar
                //Logo para sair doop loop isso precisa ser verdadeiro;
  }
  
  printf("\nMovimento ilegal. Digite novamente:\n");
  return false;
}//essa funcao decide se o movimento sugerido pelo usuario é um movimento legal
// com as regras do othelo
//------------------- XXXXXXXX -----------//
//-----------------Funcoes olhar casas-----\\
//------------------- XXXXXXXX -----------//
//-----------------Funcao contar pecas-----\\

NumDe *updateNumDePecaJogada(Peca aPeca,NumDe* aNumde,bool aJogou)
{
  //printf("simbolo %c, valor adicionado %d",intToSimb(aPeca.simb),aJogou);
    if(aPeca.simb==CRUZ)
    {
      aNumde->cruzes+=((int) aJogou);
    }
    else
    {
      aNumde->bolas +=((int) aJogou);
    }
  return aNumde;
}
//Esta função atualiza a contagem das peças do jogo (bolas e cruzes)
//com base na jogada do jogador. Ela incrementa a contagem da peça do jogador
//(bola ou cruz) com base em se eles colocaram uma peça no tabuleiro.
NumDe *updateNumDePecas(Peca aPeca,NumDe* aNumde,int aValorAdd)
{
  //printf("simbolo %c, valor adicionado %d",intToSimb(aPeca.simb),aValorAdd);
    if(aPeca.simb==CRUZ)
    {
      aNumde->cruzes+=aValorAdd;
      aNumde->bolas -=aValorAdd;

    }
    else
    {
      aNumde->cruzes-=aValorAdd;
      aNumde->bolas +=aValorAdd;
    }
  return aNumde;
}//Esta função atualiza a contagem das peças do jogo após uma jogada,
// considerando o valor a ser adicionado à contagem
//------------------- XXXXXXXX -----------//

//---------------- Funcoes "Comer" ------//

int **comerHorizontal(Peca aPeca,int **aTabuleiro, NumDe* aNumde)
{
  //declaracão
   
  int simboloOposto=(aPeca.simb+1)%2;
  int count;
 
  int ateDir = quantasPecasEsseMovimentoComeNaDir(aPeca.i,aPeca.j,aTabuleiro,aPeca.simb);
  int ateEsq = quantasPecasEsseMovimentoComeNaEsq(aPeca.i,aPeca.j,aTabuleiro,aPeca.simb);
  
  for(count = 1;count<(ateEsq+1);count++)
  {
    aTabuleiro[aPeca.i][(aPeca.j-count)]=aPeca.simb;  
  }
  aNumde= updateNumDePecas(aPeca,aNumde,ateEsq);
  for(count = 1;count<(ateDir+1);count++)
  {
  aTabuleiro[aPeca.i][(aPeca.j+count)]=aPeca.simb;  
  }
  aNumde = updateNumDePecas(aPeca,aNumde,ateDir);
 
  return aTabuleiro;
}
int **comerVertical(Peca aPeca,int **aTabuleiro,NumDe* aNumde)
{
  
  
  int simboloOposto=(aPeca.simb+1)%2;
  int count;
  int atebaixo = quantasPecasEsseMovimentoComeEmBaixo(aPeca.i,aPeca.j,aTabuleiro,aPeca.simb);
  int atecima  = quantasPecasEsseMovimentoComeEmCima(aPeca.i,aPeca.j,aTabuleiro,aPeca.simb);
      for(count = 1;count<(atecima+1);count++)
      {
        aTabuleiro[(aPeca.i-count)][aPeca.j]=aPeca.simb;  
      }
      aNumde = updateNumDePecas(aPeca,aNumde,atecima);


      for(count = 1;count<(atebaixo+1);count++)
      {
        aTabuleiro[(aPeca.i+count)][aPeca.j]=aPeca.simb;  
      }
      aNumde = updateNumDePecas(aPeca,aNumde,atebaixo);
 
  return aTabuleiro;
}
int **comerDiagonalBack_Slash(Peca aPeca,int **aTabuleiro,NumDe* aNumde)
{
  
  int simboloOposto=(aPeca.simb+1)%2;
  int countI,countJ;
  int atecimaesq  = quantasPecasEsseMovimentoComeNaDiagonalCimEsq(aPeca.i,aPeca.j,aTabuleiro,aPeca.simb);
  int atebaixodir = quantasPecasEsseMovimentoComeNaDiagonalBaiDir(aPeca.i,aPeca.j,aTabuleiro,aPeca.simb);

  for(countI = 1;countI<(atebaixodir+1);countI++)
  {
    aTabuleiro[(aPeca.i+countI)][(aPeca.j+countI)]=aPeca.simb;  
  }
  aNumde = updateNumDePecas(aPeca,aNumde,atebaixodir);
 
  for(countI = 1;countI<(atecimaesq+1);countI++)
  {
    aTabuleiro[(aPeca.i-countI)][(aPeca.j-countI)]=aPeca.simb;  
  }
  aNumde = updateNumDePecas(aPeca,aNumde,atecimaesq);

  
  return aTabuleiro;
}
int **comerDiagonalFoward_Slash(Peca aPeca,int **aTabuleiro,NumDe* aNumde)
{
  int atebaixoesq=0;
  int atecimadir=0;
  int countI,countJ;
  atebaixoesq = quantasPecasEsseMovimentoComeNaDiagonalBaiEsq(aPeca.i,aPeca.j,aTabuleiro,aPeca.simb);
  atecimadir  = quantasPecasEsseMovimentoComeNaDiagonalCimDir(aPeca.i,aPeca.j,aTabuleiro,aPeca.simb);

  for(countI = 1;countI<(atebaixoesq+1);countI++)
  {
    aTabuleiro[(aPeca.i+countI)][(aPeca.j-countI)]=aPeca.simb;  
  }
  aNumde = updateNumDePecas(aPeca,aNumde,atebaixoesq);
  for(countI = 1;countI<(atecimadir+1);countI++)
  {
    aTabuleiro[(aPeca.i-countI)][(aPeca.j+countI)]=aPeca.simb;  
  }
  aNumde = updateNumDePecas(aPeca,aNumde,atecimadir);
  
  return aTabuleiro;
}
int **comerDiagonal(Peca aPeca, int **aTabuleiro,NumDe* aNumde)
{
  aTabuleiro=comerDiagonalFoward_Slash(aPeca,aTabuleiro,aNumde);//   diagonal-> /
  aTabuleiro=comerDiagonalBack_Slash(aPeca,aTabuleiro,aNumde);//\*   diagonal-> \     \*
  return aTabuleiro;

} 
int **comerPecas(Peca aPeca, int **aTabuleiro, NumDe *aNumde)
{
  
  aTabuleiro=comerHorizontal(aPeca,aTabuleiro,aNumde);
  aTabuleiro=comerVertical(aPeca,aTabuleiro,aNumde);
  aTabuleiro=comerDiagonal(aPeca,aTabuleiro,aNumde);
  
  aTabuleiro[aPeca.i][aPeca.j]=aPeca.simb;

  
  return aTabuleiro;
}//A função executa a lógica de captura em diferentes direções 
//(horizontal, vertical e diagonal) para garantir que todas as peças 
//do oponente que precisam ser viradas para a cor do jogador sejam 
//corretamente atualizadas no tabuleiro.
//------------------- xxxxx------

//funcoes de mudar o estado do tabuleiro

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
  printf(" ------------------------------------\n");
  printf("|------------\b|A B C D E F G H|--------|\n");
  printf("|------------------------------------|\n");
  

  for (int i = 0; i < 8; i++) {
    printf("|--------%d--", (i+1));
    for (int j = 0; j < 8; j++) {
      
      printf("|%c|\b",intToSimb(aTabuleiro[i][j])) ;
    }
    printf("|--------|\n");
  }
  printf("|------------------------------------|\n");
  return;
}// essa funcao imprime a matriz do tabuleiro do jogo no console 
int **userUpdatePrintTabuleiro(int **aTabuleiro, int aVezCruzBola, NumDe* aNumde, char ent[2])
{
  if(ent[0]=='G'&&ent[1]=='G')
  {
    return aTabuleiro;
  }

  Peca peca;
  char simbolo = intToSimb(aVezCruzBola);
  peca.simb = aVezCruzBola;
 

 
  peca.i = coordernadaAtoI(ent);
  peca.j = coordernadaAtoJ(ent);
  

  aNumde = updateNumDePecaJogada(peca,aNumde,true);
  aTabuleiro=comerPecas(peca,aTabuleiro,aNumde);
  
  printTabuleiro(aTabuleiro);
  return aTabuleiro;

}// essa funcao permite que usuario coloque uma peca no tabuleiro 



int **updateTabuleiro(Peca aPeca, int **aTabuleiro)
{
  aTabuleiro[aPeca.i][aPeca.j]=aPeca.simb;
  return aTabuleiro;

}// essa funcao pega a coordenada 
//e altera a peca de lugar


int **setupTabuleiro(int **aTabuleiro)
{
  //No othelo comeca com uma cruz em e4 e d5 e bol em e5 e d4
  int i = coordernadaAtoI("E4");
  int j = coordernadaAtoJ("E4");
  aTabuleiro[i][j]=CRUZ;
  i = coordernadaAtoI("E5");
  j = coordernadaAtoJ("E5");
  aTabuleiro[i][j]=BOLA;
  i = coordernadaAtoI("D4");
  j = coordernadaAtoJ("D4");
  aTabuleiro[i][j]=BOLA;
  i = coordernadaAtoI("D5");
  j = coordernadaAtoJ("D5");
  aTabuleiro[i][j]=CRUZ;
  
  printTabuleiro(aTabuleiro);
  return aTabuleiro;

}// essa funcao pega o tabuleiro vaizo e  retorna o tabuleiro com as pecas iniciais
//------------------- XXXXX ----------// 
void acabarJogo(NumDe numde)
{
  if(numde.bolas>numde.cruzes)
  {
    printf("\n\n\n\nO ganhou!!\n\n\n\n\n");
  }else if(numde.bolas==numde.cruzes)
  {
    printf("\n\n\n\nEmpate!\n\n\n\n\n");
  }else
  {
    printf("\n\n\n\nX ganhou!!\n\n\n\n\n");

  }
  return;

}
void iniciarJogo(int **aTabuleiro,int aVez)
{
  //declaracoes
  char ent[2];
  NumDe numde;
  numde.bolas=2;
  numde.cruzes=2;
  int simbolo = aVez;//como vai entrar num loop é preciso de outra variavel

  do
  {
   
  printf("|-----------|O =%2d|---|X =%2d|--------| \n",numde.bolas,numde.cruzes);
  printf(" ------------------------------------ \n");
    
    //verificar se o jogador tem algum movimento legal
    if(!existeUmMovimentoLegal(aTabuleiro,simbolo))
    {
      //se nao tiver pula o turno do jogador
      simbolo=(simbolo+1)%2;
      if(!existeUmMovimentoLegal(aTabuleiro,simbolo))
      {
        //se ambos nao tem movimento entao acabou jogo
        acabarJogo(numde);
        break;
      }else
      {
        printf("Sem movimentos, turno pulado...\n");
      }
      
    }
    
    printf("Vez de:%c.Digite um movimento:\n",intToSimb(simbolo));
    //Verificar se o movimento é legal
    do
    {
      scanf("%s",ent);
      ent[0] = toupper(ent[0]);//Colocar em letra maiscula

    }while(!movimentoLegal(aTabuleiro,ent,simbolo));
    //fim da verificacao
  //peca sendo colocada no tabuleiro
  aTabuleiro = userUpdatePrintTabuleiro(aTabuleiro,simbolo,&numde,ent);
  simbolo=(simbolo+1)%2;

  }while(ent[0]!='G'||ent[1]!='G');
  return;

}//Essa função inicia o jogo de Othello 
//gerenciando o loop do jogo, no qual os jogadores
//alternam fazendo jogadas até que um jogador decida 
//encerrar o jogo. 
//  Ela solicita jogadas aos jogadores,
//  verifica a legalidade das jogadas,
//  atualiza o tabuleiro e 
//  alterna os turnos dos jogadores até que o jogo seja concluído.
int main() 
{
  // Declaracoes de variaveis principais
  int **tabuleiro;
  int simboloIncial = BOLA;
  Peca movimentosPossiveis[64];
  //Criacao do Tabuleiro e Organizar Posicao Inical das Pecas
  tabuleiro = createTabuleiro(8,8);
  tabuleiro = setupTabuleiro(tabuleiro);
  //jogo
  iniciarJogo(tabuleiro,BOLA);
//finalizar
//-liberando espaco da array
  for (int i = 0; i < 8; i++)
  {
    free(tabuleiro[i]);
  }
  free(tabuleiro);
//fim do programa
  return 0;
}
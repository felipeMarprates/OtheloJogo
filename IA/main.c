/*
lista de coisas pra fazer ia
getMoves()
makeMove(move)                  V
evaluate()
currentPlayer() just a variable V
isGameOver()                    V

*/

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <main.c>


// Definições de constantes para representar peças no tabuleiro
#define BOLA 0
#define CRUZ 1
#define VAZIO 2
#define UNDERLINE 3
#define TEMPORARIO 4 
#define NONE -1
#define INFINITY 10000
// Dicionario
typedef struct{
    int i;
    int k;
    int simb;
}Move
typedef struct{
    Move move;
    int score;
}Best
typedef struct{
    int circles;
    int crosses;
    int rounds;
}Numberof


int **copyMatrices(int **oldBoard)
{
    int **newBoard;
    int i,k;
    newBoard = malloc(sizeof(int *) * 8);
    for (i = 0; i < 8; i++)
    { 
        newBoard[i] = malloc(sizeof(int) * 8);
    }
    for(i = 0;i < 8;i++)
    {
        for(k = 0; k < 8;k++)
        {
            newBoard[i][k] = oldBoard[i][k];
        }
    }
    return newBoard;
}
bool anyMoves(int **aBoard, Move aMove)
{
    
  for(int i = 0;i < 8; i++)
  {
    for(int j = 0; j< 8; j++)
    {
      if(aTabuleiro[i][j]==VAZIO && esseMovimentoComeQuantasPeca(i,j,aBoard,aMove.simb))
      {
        return true;
      }
    }
  }
  return false;
}
int **makeMove(int **aBoard, Move aMove, Numberof * aNumberof)
{
    int **newBoard;
    newBoard=copyMatrices(aBoard);
    newBoard[aMove.i][aMove.k]=aMove.simb;//isso ta errado
    return newBoard;
}

bool isGameOver(int **aTabulereiro)
{
    if(anyMoves(aTabuleiro,BOLA)||anyMoves(aTabuleiro,CRUZ))
    {
        return false;
    }
    return true;
}

Best minimax(int **aBoard, Numberof aNumberof,int aCurrentPlayer, int initialPlayer, int maxDepth, int currentDepth)
{
    // ver se acabou a recursividade
    if(isGameOver(aBoard)||currentDepth==maxDepth)
    {
        Best this;
        this.score = evaluate(aNumberof);
        this.move = NONE;
        return this;
    }
    Best best;
    best.Move = NONE;
    if(aCurrentPlayer==initialPlayer)
    {
        best.score= -INFINITY;
    }
    else
    {
        best.score=INFINITY;
    }
    int numPossibleMoves;
    Move *possibleMoves = getMoves(aBoard, currentPlayer, &numPossibleMoves);
    //ir para cada movimento
    for(int i =0;i<numPossibleMoves;i++)
    {
        int **newBoard = makeMove(aBoard,possibleMoves[i],aNumberof);
        //recursao
        Best current;
        current =minimax(newBoard,aNumberof,aCurrentPlayer,initialPlayer,maxDepth,currentDepth+1);
        //update no melhor score
        if(aCurrentPlayer==initialPlayer)
        {
            if(current.score>best.score)
            {
                best.score=current.score;
                best.move = current.score;
            }
        }
        else
        {
            if(current.score<best.score)
            {
                best.score=current.score;
                best.move = current.score;
            }
        }
    }
    //retorna o melhor e o melhor movimento
    return best;
}
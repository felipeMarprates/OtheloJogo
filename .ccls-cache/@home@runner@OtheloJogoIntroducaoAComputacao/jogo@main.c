#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void drawTabuleiro(char aTabuleiro[8][8]) {
  printf("-------------------------\n");
  for (int i = 0; i < 8; i++) {
    printf("-%d-------\b", (8 - i));
    for (int j = 0; j < 8; j++) {
      printf("|%c|\b", aTabuleiro[i][j]);
    }
    printf("\n");
  }
  printf("---------\b A B C D E F G H \n-------------------------\n");
}
void turno(bool bolasCruz) {}
int coodernadaAtoJ(char *aAlphanumerico) {
  // valor inteiro de A = 65
  int res = (int)aAlphanumerico[0]; // transforma em um inteiro
  res = res - 65; // ASCII para inteiro ex:A->0,B->1,C->2...H->7
  return res;

} // essa funcao pega uma coordenada alphanumerica como de xadrez e retorna a
  // posicao "i" na matriz
int coodernadaAtoI(char *aAlphanumerico) {
  int res = (int)aAlphanumerico[1];
  res = res - 49; // ASCII para inteiro
  res = 7 - res;  // inverter a ordem
  return res;

} // essa funcao pega uma coordenada alphanumerica como de xadrez e retorna a
  // posicao "j" na matriz
int main() {
  // criar tabuleiro
  char tabuleiro[8][8];
  bool fimDoJogo = false;
  bool bolas = true;
  for (int l = 0; l < 8; l++) {
    for (int c = 0; c < 8; c++) {
      tabuleiro[l][c] = ' ';
    }
  }
  printf("\n%d\n", '1');
  drawTabuleiro(tabuleiro);
  int ti = coodernadaAtoI("H8");
  int tj = coodernadaAtoJ("H8");
  tabuleiro[ti][tj] = 'x';
  drawTabuleiro(tabuleiro);

  do {
    turno(bolas);
    bolas = (bolas + 1) % 2; // alternar turno entre bolas e cruz

  } while (fimDoJogo);
  ;
  // teste discord
  return 0;
}
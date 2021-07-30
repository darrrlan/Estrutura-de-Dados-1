#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

//Tipo carta
typedef struct{
  char naipe;
  char simbolo;
  bool jogada;
} Carta;

int main() {

  /* baralho é uma matriz de cartas - 4 naipes, 13 símbolos */
  Carta baralho[4][13];

  /* precisamos:
  1 - inicializar as cartas, todas não foram jogadas
  2 - selecionar aleatoriamente 5 cartas para o jogador 1 (imprimir)
  3 - selecionar aleatoriamente outras 5 cartas para o jogador 2 (imprimir)
  */

  /* inicializando baralho */
  int i, j;
  char simbolos[13] = {'A','2','3','4','5','6','7','8','9','D','J','Q','K'};
  char naipes[4] = {'P','E','C','O'};

  for(i = 0; i < 4; i ++){
    for(j = 0; j < 13; j++) {
      baralho[i][j].naipe = naipes[i];
      baralho[i][j].simbolo = simbolos[j];
      baralho[i][j].jogada = false;
    }
  }

  /* Imprimindo baralho */
  for(i = 0; i < 4; i ++){
    for(j = 0; j < 13; j++) {
      printf("[%c %c j:%d]", baralho[i][j].simbolo,
             baralho[i][j].naipe, baralho[i][j].jogada);
    }
    printf("\n");
  }

  /* inicializa o gerador de numeros aleatorios
  https:www.tutorialspoint.com/c_standard_library/c_function_srand.htm
  */
  time_t t;
  srand((unsigned) time(&t));

  /* distribuição das cartas
    - 5 para jogador 1*/
  int cont = 0;
  int linha, coluna;

  printf("\n--------------\n");
  printf("Jogador 1: \n");
  printf("--------------\n");

  while(cont != 5) {

    /* gerar linha e coluna aleatoria (sortear carta) */
    linha  = rand() & 3;  // [0-3]
    coluna = rand() & 12; // [0-12]

    if(baralho[linha][coluna].jogada == false) {
      baralho[linha][coluna].jogada = true;
      printf("[%c %c]", baralho[linha][coluna].simbolo,
             baralho[linha][coluna].naipe);
      cont++;
    }
  }

  /* distribuição das cartas
    - 5 para jogador 2*/
  printf("\n--------------\n");
  printf("Jogador 2: \n");
  printf("--------------\n");

  cont = 0;

  while(cont != 5) {

    /* gerar linha e coluna aleatoria (sortear carta) */
    linha  = rand() & 3;  // [0-3]
    coluna = rand() & 12; // [0-12]

    if(baralho[linha][coluna].jogada == false) {
      baralho[linha][coluna].jogada = true;
      printf("[%c %c]", baralho[linha][coluna].simbolo,
             baralho[linha][coluna].naipe);
      cont++;
    }
  }
  printf("\n--------------\n");
  return(0);
}

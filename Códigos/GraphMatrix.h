#ifndef GraphMatrix_h
#define GraphMatrix_h

#include <stdbool.h>

// tamanho da matriz a priori
#define MAXTAM 6

typedef struct {
  int vertices;
  int matrix[MAXTAM][MAXTAM];
  bool isDirected;
} GraphMatrix;

// funcoes de manipulacao do TDA

//---------------------------------------------------------
// inicializar
//---------------------------------------------------------
void initGraphMatrix(GraphMatrix *graph, bool isDirected) {
  
  // indica se vai ser direcionado ou nao direcionado
  graph->isDirected = isDirected;
  
  // indica a quantidade de vertices
  graph->vertices = MAXTAM;
  
  //inicializa a matriz com 0s
  for(int i =0; i < MAXTAM; i++) {
    for(int j = 0; j < MAXTAM; j++) {
      graph->matrix[i][j] = 0;
    }
  }
}
//---------------------------------------------------------
// imprime
//---------------------------------------------------------
void printGraphMatrix(GraphMatrix *graph) {
  
  printf("---------------\n");
  printf(" *** graph *** \n");
  printf("---------------\n");
  
  printf("\t ");
  for(int k = 0; k < MAXTAM; k++) {
    printf("%d ", k);
  }
  printf("\n");
  
  for(int i =0; i < MAXTAM; i++) {
    printf("%d: | ", i);
    for(int j = 0; j < MAXTAM; j++) {
      printf("%d ", graph->matrix[i][j]);
    }
    printf("\n");
  }
  printf("---------------\n");
}

//---------------------------------------------------------

// insercao de uma aresta
void insertEdgeGraphMatrix(GraphMatrix *graph, int v1,
                           int v2) {
  
  // grafos direcionados / não-direcionados
  graph->matrix[v1][v2] = 1;
  
  // grafo não-direcionado
  if(!graph->isDirected) {
    graph->matrix[v2][v1] = 1;
  }
}

// remove/desliga uma aresta
void removeEdgeGraphMatrix(GraphMatrix *graph, int v1,
                           int v2) {
  
  // grafos direcionados / não-direcionados
  graph->matrix[v1][v2] = 0;
  
  // grafo não-direcionado
  if(!graph->isDirected) {
    graph->matrix[v2][v1] = 0;
  }
}

// verifica se dois verteces sao adjacentes
bool isAdjacent(GraphMatrix *graph, int v1, int v2) {
  return(graph->matrix[v1][v2] == 1);
}

// retorna os adjacentes de um vertice
// vetor[]

// destrutor

#endif /* GraphMatrix_h */

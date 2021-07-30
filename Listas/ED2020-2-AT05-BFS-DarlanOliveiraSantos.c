#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
  int rotulo;
  int pai;
  int cor;
  int custo;
}VerticeInfo;

typedef struct {
  int vertices;
  int **matrix;
  bool isDirected;
  VerticeInfo Vinfo[1000];
} GraphMatrix;


struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};

// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;
};

// A structure to represent a graph. A graph
// is an array of adjacency lists.
// Size of array will be V (number of vertices
// in graph)
struct Graph
{
    int V;
    VerticeInfo Vinfo[20];
    struct AdjList* array;
};

// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
     (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph =
        (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists.  Size of
    // array will be V
    graph->array =
      (struct AdjList*) malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty by
    // making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{

    // Add an edge from src to dest.  A new node is
    // added to the adjacency list of src.  The node
    // is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest);

      newNode->next = graph->array[src].head;
     graph->array[src].head = newNode;

    // // Since graph is undirected, add an edge from
    // // dest to src also
    //  newNode = newAdjListNode(src);
    // newNode->next = graph->array[dest].head;
    // graph->array[dest].head = newNode;
}

// A utility function to print the adjacency list
// representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}
bool isAdjacentLista(struct Graph* graph,int u,int x){

      struct AdjListNode* pCrawl = graph->array[u].head;
      while(pCrawl){
        if (pCrawl != NULL && pCrawl->dest == x){
        return 1;
      }
        pCrawl = pCrawl->next;
      }
  return 0;

  }

//   void destroylist(struct Graph* graph){
//     int v;
//     if (graph->V != 0) {
//       int v;
//       for (v = 0; v < graph->V; ++v)
//       {
//           struct AdjListNode* pCrawl = graph->array[v].head;
//           struct AdjListNode* aux;
//           printf("\n Adjacency list of vertex %d\n head ", v);
//           while (pCrawl)
//           {
//               aux = pCrawl;
//               pCrawl = aux->next;
//               printf("-> %d", aux->dest);
//
//           }
//           printf("\n");
//       }
//
//   }
// }


//=============================================================================
typedef struct NodeQueue *Pointer;

typedef struct NodeQueue{
    int item;
    Pointer next;
} NodeQueue;

typedef struct {
    Pointer start;
    Pointer end;
    int size;
} DynamicQueue;

void initQueue(DynamicQueue *queue) {
  queue->start = NULL;
  queue->end = NULL;
  queue->size = 0;
}

int isEmpty(DynamicQueue *queue) {
  return(queue->size == 0);
}
void enqueue(int x, DynamicQueue *queue) {
  Pointer aux;
  aux = (Pointer) malloc(sizeof(NodeQueue));
  aux->item = x;

  // first
  if(isEmpty(queue)) {
    queue->start = queue->end = aux;
    aux->next = NULL;
  } else {
    aux->next = queue->end->next;
    queue->end->next = aux;
    queue->end = queue->end->next;
  }
  queue->size++;
}
int dequeue(DynamicQueue *queue) {
  if(isEmpty(queue)) {
    printf("Erro: elemento nao foi inserido, porque a fila esta cheia.\n");
  } else {
      int x = queue->start->item;

    Pointer aux;
    aux = queue->start;
    queue->start = queue->start->next;
    free(aux);
    queue->size--;
    return x;
  }
}
void printQueue(DynamicQueue *queue) {
  printf("Fila = {");
  Pointer ptr;
  for(ptr = queue->start; ptr != NULL; ptr = ptr->next) {
    printf("%d ", ptr->item);
  }
  printf("}\n");
}

//---------------------------------------------------------
//---------------------------------------------------------

void initGraphMatrix(GraphMatrix *graph, int V, bool isDirected) {

  int i, j;

  graph->isDirected = isDirected;
  graph->vertices = V;

  // matrix memmory allocation
  //graph->Vinfo = malloc (graph->vertices * sizeof (VerticeInfo *));
  graph->matrix = malloc (graph->vertices * sizeof (int*)) ;
  for (i=0; i < graph->vertices; i++) {
    graph->matrix[i] = malloc (graph->vertices * sizeof (int)) ;
  }


  // initialize matrix with 0s
  for(i = 0; i < graph->vertices; i++) {
    for(j = 0; j < graph->vertices; j++) {
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
  for(int k = 0; k < graph->vertices; k++) {
    printf("%d ", k);
  }
  printf("\n");

  for(int i =0; i < graph->vertices; i++) {
    printf("%d: | ", i);
    for(int j = 0; j < graph->vertices; j++) {
      printf("%d ", graph->matrix[i][j]);
    }
    printf("\n");
  }
  printf("---------------\n");
}

//---------------------------------------------------------
//---------------------------------------------------------

bool insertEdgeGraphMatrix(GraphMatrix *graph, int v1, int v2) {\

  if(v1 >= 0 && v1 < graph->vertices &&
     v2 >= 0 && v2 < graph->vertices) {
    graph->matrix[v1][v2] = 1;
    if(!graph->isDirected) {
      graph->matrix[v2][v1] = 1;
    }
    return true;
  }
  return false;
}

//---------------------------------------------------------
//---------------------------------------------------------
bool removeEdgeGraphMatrix(GraphMatrix *graph, int v1, int v2) {

  if(v1 >= 0 && v1 < graph->vertices &&
     v2 >= 0 && v2 < graph->vertices) {
    graph->matrix[v1][v2] = 0;
    if(!graph->isDirected) {
      graph->matrix[v2][v1] = 0;
    }
    return true;
  }
  return false;
}

//---------------------------------------------------------
//---------------------------------------------------------

bool isAdjacent(GraphMatrix *graph, int v1, int v2) {
  return(graph->matrix[v1][v2] == 1);
}

//---------------------------------------------------------
//---------------------------------------------------------

void destroyGraphMatrix(GraphMatrix *graph) {
  for (int i = 0; i < graph->vertices; i++) {
     free(graph->matrix[i]) ;
  }
  free(graph->matrix);
}

void printfBFS(GraphMatrix *graph,FILE *arq2){
  for (int i = graph->vertices-1; i > -1; i--) {
    fprintf(arq2,"%id[%i]\n",graph->Vinfo[i].rotulo+1,graph->Vinfo[i].custo);
  }
}

void bfs(GraphMatrix *graph, int start){

  int v;
  //inicializando as informações de todos os vertices
  for (int i = 0; i < graph->vertices ; i++) {
    graph->Vinfo[i].rotulo = i;
     graph->Vinfo[i].cor = 0; //{0 = branco, 1 = cinza, 2 = preto}
     graph->Vinfo[i].pai = -1; //{-1 = NULL}
     graph->Vinfo[i].custo = 999;
//
}
//   //inicializando verticefirstial
  graph->Vinfo[start].cor = 1 ;//{0 = branco, 1 = cinza, 2 = preto}
  graph->Vinfo[start].custo = 0;

  //inicializando a fila
  DynamicQueue f;
  initQueue(&f);
  enqueue(start,&f);


  while(f.size != 0){
    int u = dequeue(&f);
    for (int i = 0 ; i < graph->vertices; i++) {
      if(isAdjacent(graph,u,i)){
        v = i;
        if(graph->Vinfo[v].cor == 0){
          graph->Vinfo[v].cor = 1;
          graph->Vinfo[v].custo = graph->Vinfo[u].custo + 1;
          graph->Vinfo[v].pai = graph->Vinfo[u].rotulo;
          enqueue(v,&f);
          // se for branco, se for
          //atualizar cor para cinza
          //atualizar co custo
          //atualizar Pai
          //
        }
      }
      graph->Vinfo[u].cor = 2;
    }
  }
}
void printfBFSLista(struct Graph *graph,FILE *arq2){
  for (int i = graph->V-1; i > -1; i--) {
    fprintf(arq2,"%id[%i]\n",graph->Vinfo[i].rotulo+1,graph->Vinfo[i].custo);
  }
}
void bfsLista(struct Graph *graph, int start){

  int v;
  //inicializando as informações de todos os vertices
  for (int i = 0; i < graph->V ; i++) {
    graph->Vinfo[i].rotulo = i;
     graph->Vinfo[i].cor = 0; //{0 = branco, 1 = cinza, 2 = preto}
     graph->Vinfo[i].pai = -1; //{-1 = NULL}
     graph->Vinfo[i].custo = 999;
//
}
//   //inicializando verticefirstial
  graph->Vinfo[start].cor = 1 ;//{0 = branco, 1 = cinza, 2 = preto}
  graph->Vinfo[start].custo = 0;

//  inicializando a fila
  DynamicQueue f;
  initQueue(&f);
  enqueue(start,&f);


  while(f.size != 0){
    int u = dequeue(&f);
    for (int i = 0 ; i < graph->V; i++) {
      if(isAdjacentLista(graph,u,i)){
        v = i;
        if(graph->Vinfo[v].cor == 0){
          graph->Vinfo[v].cor = 1;
          graph->Vinfo[v].custo = graph->Vinfo[u].custo + 1;
          graph->Vinfo[v].pai = graph->Vinfo[u].rotulo;
          enqueue(v,&f);
          // se for branco, se for
          //atualizar cor para cinza
          //atualizar co custo
          //atualizar Pai
          //
        }
      }
      graph->Vinfo[u].cor = 2;
    }
 }
}


//---------------------------------------------
//---------------------------------------------
int main(int argc, const char * argv[]){
  if(argc != 3){
    printf("Numero de parametros nao e o correto\n");
    return 1;
  }
    FILE *arq1,*arq2;
    int valor,v1,v2,aux = 1;
    char c,b;
    char d[5],numeros[200],numeros1[200];;
    char *pt;
    int maiorvalor = -99;

    arq1 = fopen(argv[1],"r");
    arq2 = fopen(argv[2],"wt");
    //fprintf(arq2, "oiiii");
    //confere se está abrindo os arquivos
    if(arq1	==	NULL || arq2 == NULL){
      printf("Ocorreu um erro no arquivo\n");
      system("pause");
      exit(1);
    }

    c = getc(arq1);
    fscanf(arq1,"\n");
    if(c == EOF || c != 'M' && c != 'L'){
      printf("Arquivo de leitura vazio ou não esta na forma esperada\n");
      fclose(arq1);
      fclose(arq2);
      exit(1);
    }
    // pega as informações do aqr
    b = getc(arq1);
    fscanf(arq1,"\n");
    fscanf(arq1,"%s\n",numeros);
    fscanf(arq1,"%s\n",d);
    strcpy(numeros1,numeros);

  //  ver quantos vertices tem
    pt = strtok(numeros,"(,)");
    while(pt != NULL){
      valor = atoi(pt);
      if (valor > maiorvalor){
        maiorvalor = valor;
      }
      pt = strtok (NULL, "(,)");
    }
    //incia o grafo
    GraphMatrix g;
    initGraphMatrix(&g,maiorvalor,1);

    struct Graph* graph = createGraph(maiorvalor);

    //pega os adjacentes
    pt = strtok(numeros1,"(,");
    while(pt != NULL){
      if (aux%2 != 0) {
        v1 = atoi(pt);
        aux++;
      }else{
        v2 = atoi(pt);
        if(c == 'M'){
        insertEdgeGraphMatrix(&g,v1-1,v2-1);
      }
      if(c == 'L'){
        addEdge(graph, v1-1, v2-1);
      }
        aux++;
      }
      pt = strtok (NULL, ",()");
    }
    valor = atoi(d);
    if (c == 'M') {
      bfs(&g,valor-1);
      printfBFS(&g,arq2);
    }
     if(c == 'L'){
    bfsLista(graph,valor-1);
    printfBFSLista(graph,arq2);
  }
  printf("Finalizado\n");
  //destroylist(graph);
destroyGraphMatrix(&g);
fclose(arq1);
fclose(arq2);

  return 0;
}

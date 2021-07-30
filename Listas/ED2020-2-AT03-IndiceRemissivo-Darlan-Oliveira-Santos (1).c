#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// deixar os ponteiros explicitos
typedef struct NoArvore *PtrNoArvore;

typedef struct NoLista* PtrNoLista;
// no lista
typedef struct NoLista{
  int chave; // elemento contido
  PtrNoLista proximo;//ptr proximo da lista
} NoLista;

typedef struct {
  PtrNoLista inicio;//inicio da lista
  int tamanho;//tamanho da lista
} ListaDinamica;


// no arvore
typedef struct NoArvore{
  char chave[30]; //elemento contido
  ListaDinamica lista; // uma estrutura de dados, uma lista
  PtrNoArvore filhoDireita;  //ptr sub-arvore direita
  PtrNoArvore filhoEsquerda; //ptr sub-arvore esquerda
} NoArvore;

// ---------------------------------------------
// funcoes para manipular o tipo de Lista
// ---------------------------------------------

// inicializacao da lista
void iniciaListaDinamica(ListaDinamica *lista) {
  //inicio
  lista->inicio = NULL;
  //tamanho
  lista->tamanho = 0;
}

  //confere se a lista está fazia
bool estaVaziaListaDinamica(ListaDinamica *lista) {
  return (lista->tamanho == 0);
  //return(lista->inicio == NULL);
}

// insercao de elementos na lista
void inserirListaDinamica(ListaDinamica *lista, int elemento) {

  // 1. Criar o ponteiro (Novo)
  PtrNoLista novo;
  // 2. Aloca memoria para Novo
  novo =(PtrNoLista)malloc(sizeof(NoLista));
  // 3. copia o valor do elemento p chave do Novo no
  novo->chave = elemento;

  // Situação #1: Lista esta Vazia , ou
  // se o elemento que a gente quer inserir é menor do que o primeiro
  if(estaVaziaListaDinamica(lista) || elemento < lista->inicio->chave) {

    //printf("situacao 1 \n");
    // 4. proximo do novo aponta para nulo (inicio)
    novo->proximo = lista->inicio;
    // 5. Inicio aponta para o novo no
    lista->inicio = novo;
    // 6. incrementa o contador


  } // Situacao # (Lista nao esta vazia)
  else {

   //printf("situacao 2 \n");
    // aux = percorre a lista p gente (encontrar o ponto de insercao - posicao)
    PtrNoLista aux;

    // 4. percorrer e encontrar o ponto de insercao (aux)
    aux = lista->inicio;
    while((aux->proximo!= NULL) && (elemento > aux->proximo->chave)) {
      aux = aux->proximo;
      //printf("andou ...\n");
    }
    //printf("Aux = %d \n", aux->chave);

    // 5. proximo Novo aponta proximo Aux
    novo->proximo = aux->proximo;
    // 6. proximo do Aux aponta para Novo
    aux->proximo = novo;

  }
  // 7. incrementa o contador
  lista->tamanho = lista->tamanho + 1; //++
  //rintf("----------------------\n");
}
  //imprimi elemntos da lista
  void imprimirListaDinamica(ListaDinamica *lista,FILE *arq2) {
    int x=-1;//variável auxíliar

    PtrNoLista percorre;
    //percorretoda a lista toda
    for(percorre = lista->inicio; percorre != NULL; percorre = percorre->proximo) {
      // para não imprimir indices repetidos
      if(x != percorre->chave){
        //escreve no arquivo de saida
        fprintf(arq2, ",%d",percorre->chave);
        // x recebe o novo valor
      x = percorre->chave;
    }
  }
  fprintf(arq2,"\n");
  }
//
void iniciaArvore(PtrNoArvore *arvore) {
  *arvore = NULL;
}

// ---------------------------------------------
// funcoes para manipular o tipo de arvore
// ---------------------------------------------

//verifica se arvore está vazia
bool estaVaziaArvore(PtrNoArvore *arvore) {
  return(*arvore == NULL);
}

// insercao (bool)
bool insereArvore(PtrNoArvore *arvore, char x[]) {
  // ...

  // etapa 1 - criterio de parada (arvore == NULL)
  // encontrei um ponto de insercao
  if(*arvore == NULL) {
    // 1. alocar memoria para um novo nó
    // 2. atribuir a (arvore) apontar p novo nó
    (*arvore) = malloc(sizeof(NoArvore));
    // (*arvore) = (PtrNoArvore*) malloc(sizeof(NoArvore));
    // 3. filho da direita e filho da esquerda = NULL
    //(*arvore)->filhoDireita = (*arvore)->filhoEsquerda = NULL;
    (*arvore)->filhoDireita  = NULL;
    (*arvore)->filhoEsquerda = NULL;
    // 4. no->chave = elemento = x
    strcpy((*arvore)->chave,x);
    //inicia a lista
    iniciaListaDinamica(&(*arvore)->lista);

    return true;
  }

  // etapa 2 - nao inserir chaves repetidas dentro da arv
  // criterio de parada da recursao
  if(strcmp((*arvore)->chave,x) == 0) {
  // arvore->chave == x
  // nao faz nada, só retorna
    return false;
  }

  // etapa 3 - criterio de recursao
  // percuro recursivo - no arvore
  if(strcmp((*arvore)->chave,x)>0) {
    // arvore->chave > x --> recursao p filho esquerda
    return(insereArvore(&(*arvore)->filhoEsquerda,x));
  } else {
    // arvore->chave < x --> recursao p filho direita
    return(insereArvore(&(*arvore)->filhoDireita,x));
  }
}

// ---------------------------------------------
// funcoes de percurso de arvore
// ---------------------------------------------

// pre-ordem
void impressaoEmOrdem(PtrNoArvore *arvore,FILE *arq2) {
  //  1. imprime o valor contido no nó corrente
  if((*arvore) == NULL) return;
  //  2. chama recursivo p filho esquerda
  impressaoEmOrdem(&(*arvore)->filhoEsquerda,arq2);
  //imprimi o elemento contido na chave no aquivo de saida
  fprintf(arq2,"%s",(*arvore)->chave);
  //chamar a função para imprimir a lista neste no de arvore
  imprimirListaDinamica(&(*arvore)->lista,arq2);
  //  3. chama recursivo p filho direita
  impressaoEmOrdem(&(*arvore)->filhoDireita,arq2);
}

bool procuraArvore(PtrNoArvore *arvore,char x[], int num) {

  // c1 - nao achei o elemento/ ele nao exista na arvore
  if(*arvore == NULL) return (false);

  // c2 - cheguei em um nó cujo valor é o que eu quero
  if(strcmp((*arvore)->chave,x)==0){

    inserirListaDinamica(&(*arvore)->lista,num);

    return (true);
  }
  // ajustes a mais ... r1, r2, r3, r4

  // recursao - percorrer arvore
  if(strcmp((*arvore)->chave,x)>0) {
    // arvore->chave > x --> recursao p filho esquerda
    return(procuraArvore(&(*arvore)->filhoEsquerda, x, num));
  } else {
    // arvore->chave < x --> recursao p filho direita
    return(procuraArvore(&(*arvore)->filhoDireita, x, num));
  }
}
void destroiArvore(PtrNoArvore *node) {
  // percurso
  //percorrer a arvore e desalocar memoria de traz p frente
  if((*node) != NULL) {
    destroiArvore(&(*node)->filhoEsquerda);
    destroiArvore(&(*node)->filhoDireita);
    free(*node);
    (*node) = NULL;
  }
}

// ---------------------------------------------
// main e teste de funcoes
// ---------------------------------------------

  int main(int argc, const char * argv[]) {

  if(argc != 3){
    printf("Numero de parametros nao e o correto\n");
    return 1;
  }
  FILE *arq1,*arq2;
  char texto[200];
  int indice=0;
  char *pt;
  char c;

  //aberturas dos arquivos
  arq1 = fopen(argv[1],"r");
  arq2 = fopen(argv[2],"wt");

  //confere se está abrindo os arquivos
  if(arq1	==	NULL || arq2 == NULL){
    printf("Ocorreu um erro no arquivo\n");
    system("pause");
    exit(1);
  }

  //analisa se o arquivo está vazio
  c = getc(arq1);
  if(c == EOF){
    printf("Arquivo de leitura vazio\n");
    fclose(arq1);
    fclose(arq2);
    exit(1);
  }
  //volta para posição inicial
  fseek(arq1,0,SEEK_SET);
  // uso da arvore na main
  PtrNoArvore raiz;

  // inicializacao da arvore binaria de busca
  iniciaArvore(&raiz);

    //if para analisar se o arq está na forma esperada
    if(fscanf(arq1,"<termos:%s",texto)){

    //todas a lestra ficam em minúsculas
    strlwr(texto);

    //quebra o texto com os delimitadores
    pt = strtok(texto, ">");
    pt = strtok(pt,",");
    while(pt){
      //copia a string de pt para texto
      strcpy(texto,pt);
      //insere na arvore
      insereArvore(&raiz,texto);

        pt = strtok(NULL, ",");
    }

    //pega uma linha do arquivo, até ser diferente de NULL
    while(fgets(texto,200,arq1) != NULL){
      //trasnforma tudo em minúsculas
      strlwr(texto);
      //quebra a variável com os delimitadores
      pt = strtok (texto," ,.-\n");
      while (pt != NULL)
      {
        //cada vez que aparecer a palavra <page, incremneta o indice
        if (strncmp(pt,"<page",5)==0) {
          //número de indicie remerssível
          indice++;
        }
        //copia a string de pt para texto
        strcpy(texto,pt);
          //procura se a palavra está na arvore, se sim adiciona o indice remersivel na lista
          if(procuraArvore(&raiz,texto,indice)){
          }
        pt = strtok (NULL, " ,.-\n(){}[]");
      }
      }
      //imprime em ordem alfabética no arquivo e com os indices
      impressaoEmOrdem(&raiz,arq2);
      //libera a memória da arvore e da lista
      destroiArvore(&raiz);
    }else{
      printf("Arquivo de texto, diferente do que esperado\n");
    }
    //fechar os arquivos
    fclose(arq1);
    fclose(arq2);
  return 0;
  }

// ---------------------------------------------
// ---------------------------------------------

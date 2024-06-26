#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// ---------------------------------------------
// Definindo os tipos necessarios para implementar
// uma arvore binaria de busca
// ---------------------------------------------

// deixar os ponteiros explicitos
typedef struct NoArvore *PtrNoArvore;

// no arvore
typedef struct NoArvore{
  int chave;                 //elemento contido
  PtrNoArvore filhoDireita;  //ptr sub-arvore direita
  PtrNoArvore filhoEsquerda; //ptr sub-arvore esquerda
} NoArvore;

// ---------------------------------------------
// funcoes para manipular o tipo de arvore
// ---------------------------------------------

// inicializacao da arvore
void iniciaArvore(PtrNoArvore *arvore) {
  *arvore = NULL;
}

//verifica se arvore está vazia
bool estaVaziaArvore(PtrNoArvore *arvore) {
  return(*arvore == NULL);
}

// insercao (bool)
bool insereArvore(PtrNoArvore *arvore, int x) {
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
    (*arvore)->chave = x;
    return true;
  }
  
  // etapa 2 - nao inserir chaves repetidas dentro da arv
  // criterio de parada da recursao
  if((*arvore)->chave == x) {
  // arvore->chave == x
  // nao faz nada, só retorna
    return false;
  }
    
  // etapa 3 - criterio de recursao
  // percuro recursivo - no arvore
  if((*arvore)->chave > x) {
    // arvore->chave > x --> recursao p filho esquerda
    return(insereArvore(&(*arvore)->filhoEsquerda, x));
  } else {
    // arvore->chave < x --> recursao p filho direita
    return(insereArvore(&(*arvore)->filhoDireita, x));
  }
}

// ---------------------------------------------
// funcoes de percurso de arvore
// ---------------------------------------------

// pre-ordem
void impressaoPreOrdem(PtrNoArvore *arvore) {
  //  1. imprime o valor contido no nó corrente
  if((*arvore) == NULL) return;
  printf("%d ", (*arvore)->chave);
  //  2. chama recursivo p filho esquerda
  impressaoPreOrdem(&(*arvore)->filhoEsquerda);
  //  3. chama recursivo p filho direita
  impressaoPreOrdem(&(*arvore)->filhoDireita);
}

//pos-ordem
void impressaoPosOrdem(PtrNoArvore *arvore) {
  if((*arvore) == NULL) return;
  //  2. chama recursivo p filho esquerda
  impressaoPosOrdem(&(*arvore)->filhoEsquerda);
  //  3. chama recursivo p filho direita
  impressaoPosOrdem(&(*arvore)->filhoDireita);
  //  1. imprime o valor contido no nó corrente
  printf("%d ", (*arvore)->chave);
}

// EXERCICIO: em-ordem

// EXERCICIO: em nivel
// Fila = {}
// Em nivel: 3, 2, 17, 1, 8, 20, -3, 12

// Percurso em nivel
// 1. enfileira a raiz
// 2. enqto fila != vazio
//      desenfileira = x, imprime
//      enfileira (esq)
//      enfileira (dir)

// ---------------------------------------------
// Consulta/pesquisa de elementos
// ---------------------------------------------

bool procuraArvore(PtrNoArvore *arvore, int x) {
  
  // c1 - nao achei o elemento/ ele nao exista na arvore
  if(*arvore == NULL) return (false);
  
  // c2 - cheguei em um nó cujo valor é o que eu quero
  if((*arvore)->chave == x) return (true);
  // ajustes a mais ... r1, r2, r3, r4
  
  // recursao - percorrer arvore
  if((*arvore)->chave > x) {
    // arvore->chave > x --> recursao p filho esquerda
    return(procuraArvore(&(*arvore)->filhoEsquerda, x));
  } else {
    // arvore->chave < x --> recursao p filho direita
    return(procuraArvore(&(*arvore)->filhoDireita, x));
  }
}

// ---------------------------------------------
// Funcoes auxiliares para remocao
// ---------------------------------------------

//tmp = getMinAux(&(*node)->filhoDireita);

// ---------------------------------------------
// ---------------------------------------------

PtrNoArvore getMaxAux(PtrNoArvore *node) {
  
  PtrNoArvore ret;
  // criterio de parada da recursao
  // se filho direita do node == NULL
  // eu achei o maior elemento
  if((*node)->filhoDireita == NULL) {
    ret = (*node);
    // ajuste para remocao funcionar
    // remover o elemento da sub-arvore de node
    (*node) = (*node)->filhoEsquerda;
    return(ret);
  }
  return(getMaxAux(&(*node)->filhoDireita));
}

// ---------------------------------------------
// ---------------------------------------------

bool removeArvore(PtrNoArvore *node, int x) {
  
  // se node == NULL, nao tem quem remover
  // return (false)
  if((*node) == NULL) {
    printf("Warning: elemento %d não existe na árvore\n", x);
    return(false);
  }
  
  // Achei quem eu quero remover
  // se node->chave == x
  if((*node)->chave == x) {
   
    //criar uma variavel temp para desalocar memoria
    PtrNoArvore tmp = (*node);

    // caso 01 - sub-arvore esquerda do node é nula (direita nao)
    if((*node)->filhoEsquerda == NULL && (*node)->filhoDireita !=NULL) {
      (*node) = (*node)->filhoDireita;
    }
    
    // caso 02 - sub-arvore direita do node é nula (esquerda nao)
    else if((*node)->filhoEsquerda != NULL && (*node)->filhoDireita == NULL) {
      (*node) = (*node)->filhoEsquerda;
    }
    // caso 03 - no folha (direita como esquerda sao nulos)
    else if((*node)->filhoDireita == NULL && (*node)->filhoEsquerda == NULL) {
      (*node) = NULL;
    }
    // *** caso 04 - direita e esquerda nao sao nulos
    else {
//      tmp = getMaxAux(sub-arvore esquerda);
      tmp = getMaxAux(&(*node)->filhoEsquerda);
//      tmp = getMinAux(&(*node)->filhoDireita);
      (*node)->chave = tmp->chave;
    }
    
    printf("Elemento %d removido com sucesso\n", x);
    free(tmp);
    return(true);
  }
  
  // passos de recursao
  if((*node)->chave > x) {
    return (removeArvore(&(*node)->filhoEsquerda, x));
  } else {
    return(removeArvore(&(*node)->filhoDireita, x));
  }
}

// ---------------------------------------------
// ---------------------------------------------
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
  
  // uso da arvore na main
  PtrNoArvore raiz;
  
  // inicializacao da arvore binaria de busca
  iniciaArvore(&raiz);
  
  // esta vazia!
  if(estaVaziaArvore(&raiz)) {
    printf("- Arvore está vazia!\n");
  } else {
    printf(" - Existe elemento dentro da árvore\n");
  }
  
  insereArvore(&raiz, 3);
  insereArvore(&raiz, 2);
  insereArvore(&raiz, 1);
  insereArvore(&raiz, 17);
  insereArvore(&raiz, 20);
  insereArvore(&raiz, -3);
  insereArvore(&raiz, 8);
  insereArvore(&raiz, 12);
  
  //            3
  //       2         17
  //    1       8        20
  //-3             12
  
  printf("Pre-ordem ={");
  impressaoPreOrdem(&raiz);
  printf("}\n");
  
  removeArvore(&raiz, 5);
  printf("Pre-ordem ={");
  impressaoPreOrdem(&raiz);
  printf("}\n");
    
  // remover uma folha
  removeArvore(&raiz, -3);
  //            3
  //       2         17
  //    1       8        20
  //              12
  //
  // 3, 2, 1, 17, 8, 12, 20
  printf("Pre-ordem ={");
  impressaoPreOrdem(&raiz);
  printf("}\n");
  
  // remocao c sub-arvore direita nula
  //            3
  //       1         17
  //            8        20
  //              12
  removeArvore(&raiz, 2);
  //3, 1, 17, 8, 12, 20
  printf("Pre-ordem ={");
  impressaoPreOrdem(&raiz);
  printf("}\n");
  
  // remocao c sub-arvore esquerda nula
  //            3
  //       1         17
  //             12      20
  // 3, 1, 17, 12, 20
  removeArvore(&raiz, 8);
  printf("Pre-ordem ={");
  impressaoPreOrdem(&raiz);
  printf("}\n");
  
  // remocao com sub-arvores nao nulas
  //            1
  //                 17
  //             12      20
  // 1, 17, 12, 20
  removeArvore(&raiz, 3);
  printf("Pre-ordem ={");
  impressaoPreOrdem(&raiz);
  printf("}\n");
  //            1
  //                 12
  //                     20
  // 1, 12, 20
  removeArvore(&raiz, 17);
  printf("Pre-ordem ={");
  impressaoPreOrdem(&raiz);
  printf("}\n");
  
  destroiArvore(&raiz);
  if(estaVaziaArvore(&raiz)) {
    printf("- Arvore está vazia!\n");
  } else {
    printf(" - Existe elemento dentro da árvore\n");
  }
  
//  int vet[] = {3, 17, 12, -4};
//  int i;
//  for(i = 0; i < 4; i++) {
//    if(procuraArvore(&raiz, vet[i])){
//      printf("Elemento %d existe\n", vet[i]);
//    } else {
//      printf("Elemento %d nao existe\n", vet[i]);
//    }
//  } // v v v f
//

  
//  Pre-ordem = {3, 2, 1, -3, 17, 8, 12, 20}
//  Pos-ordem = {-3, 1, 2, 12, 8, 20, 17, 3}
  // em-ordem = {-3, 1, 2, 3, 8, 12, 17, 20}
//
//  printf("Pre-ordem ={");
//  impressaoPreOrdem(&raiz);
//  printf("}\n");
  
//  printf("Pre-ordem ={");
//  impressaoPosOrdem(&raiz);
//  printf("}\n");
  
  // esta vazia!
//  }
  
  return 0;
}

// ---------------------------------------------
// ---------------------------------------------


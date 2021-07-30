#ifndef hashArray_h
#define hashArray_h

# include <stdbool.h>
# include <stdio.h>


// IMplementação

// capacidade total da
// - tabela hash com resolução de colisoes por
// enderação aberto

#define M 7 //23

typedef struct {
  int chave;
  char info[100];
} HashItem;

typedef struct {
  HashItem* array[M];
  int contador; // quantidade de elementos
} HashArray;

//---------------------------------------------------
//---------------------------------------------------

void iniciaTabela(HashArray *tabela) {
  int i;
  for(i = 0; i < M; i++) {
    tabela->array[i] = NULL;
  }
  tabela->contador = 0;
}

//---------------------------------------------------
//---------------------------------------------------
int hash(int chave) {
  return(chave % M);
}

//---------------------------------------------------
//---------------------------------------------------

bool estaCheiaTabela(HashArray *tabela) {
  return(tabela->contador == M);
}

//---------------------------------------------------
//---------------------------------------------------

bool inserirTabela(HashArray *tabela, HashItem *item){
  
  // qual posicao para se inserir
  int pos = hash(item->chave);
  
  // fazer teste para verificar colisao
  if(tabela->array[pos] != NULL) {
    // já tem elemento -> colisao, nao insere
    printf(" - Colisão. Já existe elemento nessa posição.\n");
    
    //TODO: tratamento de colisoes
    
    return(false);
  } else {
    // senao tem colisao, insere
    tabela->array[pos] = item;
    tabela->contador++;
    return(true);
  }
}

//---------------------------------------------------
//---------------------------------------------------

bool removerTabela(HashArray *tabela, int chave){
  // qual posicao para se remover
  int pos = hash(chave);
  
  if(tabela->array[pos] == NULL) {
    return false;
  }
  
  if(tabela->array[pos]->chave == chave) {
    tabela->array[pos] = NULL;
    tabela->contador --;
    return true;
  } else {
    printf("Não tem elemento para remover");
    return false;
  }
  
//  TOOD: tratamento de colisoes
}

//---------------------------------------------------
//---------------------------------------------------
bool procuraTabela(HashArray *tabela, int chave){

  // qual posicao para se inserir
  int pos = hash(chave);
  
  // se existe elemento dentro da posicao retornada
  if(tabela->array[pos] == NULL) {
    return false;
  }
  
  return(tabela->array[pos]->chave == chave);
  
//  TODO: melhorar para funcionar com sondagem linear/quadrática
}


//---------------------------------------------------
//---------------------------------------------------
void imprimirTabela(HashArray *tabela){
  int i;
  printf("=============================\n");
  printf("           Tabela            \n");
  printf("=============================\n");

  for(i = 0; i < M; i++) {
      
  if(tabela->array[i] != NULL) {
    printf(" [%d](%d,%s)\n", i, tabela->array[i]->chave, tabela->array[i]->info);
    } else {
      printf(" [%d] ~~ \n", i);
    }
  }
  printf("=============================\n");
}

//---------------------------------------------------
//---------------------------------------------------

// destrutor
// resolver colisoes

#endif /* hashArray_h */

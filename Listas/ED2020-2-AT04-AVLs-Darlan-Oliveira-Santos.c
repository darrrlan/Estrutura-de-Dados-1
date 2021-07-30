#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// -------------------------------
/* Ziviani */
typedef struct NoAVL *PtrNoAVL;

typedef struct NoAVL {
  int chave;
  PtrNoAVL dir;
  PtrNoAVL esq;
  //fator de balanceamento
  int altura;
} NoAVL;

// -------------------------------
// -------------------------------

void iniciaAVL(PtrNoAVL *node) {
 *node = NULL;
}
// -------------------------------
// -------------------------------

void emOrdem(PtrNoAVL *node) {
  if((*node) == NULL) return;
  emOrdem(&(*node)->esq);
  printf("%d ", (*node)->chave);
  emOrdem(&(*node)->dir);
}
// -------------------------------
// -------------------------------

bool estaVaziaAVL(PtrNoAVL *node) {
  return((*node) == NULL);
}
// -------------------------------
// -------------------------------

int alturaArvoreAVL(PtrNoAVL node) {
  if(node == NULL) {
    return (0);
  } else {
    return ((node)->altura);
  }
}
// -------------------------------
// -------------------------------
void givelLevel(PtrNoAVL *node, int level,FILE *arq2){

  if((*node) == NULL) return;
  if(level == 1){
  int ae = alturaArvoreAVL((*node)->esq);
  int ad = alturaArvoreAVL((*node)->dir);
  fprintf(arq2,"%d (%d),",(*node)->chave, ad-ae);
}
  else if(level>1){
    givelLevel(&(*node)->esq, level-1,arq2);
    givelLevel(&(*node)->dir, level-1,arq2);
  }
}
// -------------------------------
// -------------------------------

void printLevel(PtrNoAVL *node,FILE *arq2)
{
  int h = 1 + (*node)->altura;
  for (int i = 0; i < h; i++) {
    givelLevel(&(*node),i,arq2);
    fprintf(arq2,"\n");
  }
}
// -------------------------------
// -------------------------------
int atualizaAltura(PtrNoAVL esq, PtrNoAVL dir) {

  int ae = alturaArvoreAVL(esq);
  int ad = alturaArvoreAVL(dir);

  if(ae > ad) {
    return(ae + 1);
  } else {
    return(ad + 1);
  }
}
// -------------------------------
// -------------------------------

void rotacaoSimplesDireita(PtrNoAVL *node) {

  PtrNoAVL u = (*node)->esq;
  (*node)->esq = u->dir;
  u->dir = (*node);

  //atualizar a altura dos nós modificados (node, u)
  (*node)->altura = atualizaAltura((*node)->esq, (*node)->dir);
  u->altura = atualizaAltura(u->esq, u->dir);

  //autualizacao da referencia do node
  (*node) = u;
}
// -------------------------------
// -------------------------------

void rotacaoSimplesEsquerda (PtrNoAVL *node) {

  PtrNoAVL u = (*node)->dir;
  (*node)->dir = u->esq;
  u->esq = (*node);

  //atualizar a altura dos nós modificados (node, u)
  (*node)->altura = atualizaAltura((*node)->esq, (*node)->dir);
  u->altura = atualizaAltura(u->esq, u->dir);

  //autualizacao da referencia do node
  (*node) = u;
}
// -------------------------------
// -------------------------------

void rotacaoDuplaEsquerda (PtrNoAVL *node) {

  PtrNoAVL u, v;
  u = (*node)->dir;
  v = u->esq;

  (*node)->dir = v->esq;
  u->esq = v->dir;
  v->esq = (*node);
  v->dir = u;

  //atualizar a altura dos nós modificados (node, u, v)
  (*node)->altura = atualizaAltura((*node)->esq, (*node)->dir);
  u->altura = atualizaAltura(u->esq, u->dir);
  v->altura = atualizaAltura(v->esq, v->dir);

  //autualizacao da referencia do node
  (*node) = v;
}
// -------------------------------
// -------------------------------

void rotacaoDuplaDireita (PtrNoAVL *node) {

  PtrNoAVL u, v;
  u = (*node)->esq;
  v = u->dir;

  (*node)->esq = v->dir;
  u->dir = v->esq;

  v->dir = (*node);
  v->esq = u;

  //atualizar a altura dos nós modificados (node, u, v)
  (*node)->altura = atualizaAltura((*node)->esq, (*node)->dir);
  u->altura = atualizaAltura(u->esq, u->dir);
  v->altura = atualizaAltura(v->esq, v->dir);

  //autualizacao da referencia do node
  (*node) = v;
}

// -------------------------------
// -------------------------------

void AplicarRotacoes(PtrNoAVL *node) {

  int ad = alturaArvoreAVL((*node)->dir);

  int ae = alturaArvoreAVL((*node)->esq);
  // Verificar se é rotacao para direita
  if(ae > ad) {
    PtrNoAVL temp = (*node)->esq;
    int temp_ad = alturaArvoreAVL(temp->dir);
    int temp_ae = alturaArvoreAVL(temp->esq);
    // temp_ae > ou >= temp_ad
    if(temp_ae >= temp_ad) {
      rotacaoSimplesDireita(&(*node));
    } else {
      rotacaoDuplaDireita(&(*node));
    }
  }
  // Senao é rotacao para esquerda
  else { //(ad > ae)
    PtrNoAVL tmp2 = (*node)->dir;
    int tmp2_ad = alturaArvoreAVL(tmp2->dir);
    int tmp2_ae = alturaArvoreAVL(tmp2->esq);
    if(tmp2_ad >= tmp2_ae){
      rotacaoSimplesEsquerda(&(*node));
    } else {
      rotacaoDuplaEsquerda(&(*node));
    }
  }
}
// -------------------------------
// -------------------------------

// *** Inserção
bool InserirAVL(PtrNoAVL *node, int x) {

  //1. condicao final da recusao (positiva)
  if((*node) == NULL) {
    (*node) = (PtrNoAVL)malloc(sizeof(NoAVL));
    (*node)->dir = (*node)->esq = NULL;
    (*node)->chave = x;
    (*node)->altura = 1;
    return true;
  }

  //2. elemento ja existe
  if((*node)->chave == x) return false;

  bool auxiliar;

  // 3. Laço de chamadas recusivas
  if(x < (*node)->chave) {
    auxiliar = InserirAVL(&(*node)->esq, x);
  } else {
    auxiliar = InserirAVL(&(*node)->dir, x);
  }

  // Daqui para baixo começa o codigo só tem na AVL
  // 4. Se o auxiliar for falso, nao houve mudança na arvore
  if(!auxiliar) return (false);

  // Se houve modificacao na arvore
  // Precisamos checar o desbalanceamento
  int ae; // altura da sub-arvore da esquerda
  int ad; // altura da sub-arvore da direita

  // 5. Calculando as alturas das sub-arvores
  ae = alturaArvoreAVL((*node)->esq);
  ad = alturaArvoreAVL((*node)->dir);

  // 6. Verificando desbalanceamento
  if((ad - ae) == +2 || (ad - ae) == -2) {
    // desbalancemaneto
    AplicarRotacoes(&(*node));
  }

  //7. ajuste da altura do no corrente
  (*node)->altura = atualizaAltura((*node)->esq, (*node)->dir);
  return(true);
}
PtrNoAVL getMaxAux(PtrNoAVL *node) {

  PtrNoAVL ret;
  // criterio de parada da recursao
  // se filho direita do node == NULL
  // eu achei o maior elemento
  if((*node)->dir == NULL) {
    ret = (*node);
    // ajuste para remocao funcionar
    // remover o elemento da sub-arvore de node
    (*node) = (*node)->esq;
    return(ret);
  }
  return(getMaxAux(&(*node)->dir));
}
PtrNoAVL getMinAux(PtrNoAVL *node) {

  PtrNoAVL ret;
  // criterio de parada da recursao
  // se filho direita do node == NULL
  // eu achei o maior elemento
  if((*node)->esq == NULL) {
    ret = (*node);
    // ajuste para remocao funcionar
    // remover o elemento da sub-arvore de node
    (*node) = (*node)->dir;
    return(ret);
  }
  return(getMaxAux(&(*node)->esq));
}


bool remocaoAVL(PtrNoAVL *node,int valor,char z){
  //1.confere se o node é nulo
  if((*node)==NULL) return(false);

  //2.se node->chave existe
  if((*node)->chave == valor){
    PtrNoAVL tmp = (*node);
    //2.1 verifica se é folha esquerda
    if((*node)->esq == NULL){
      (*node) = (*node)->dir;
    //2.2verifica se é folha direita
    }else if ((*node)->dir == NULL){
      (*node) = (*node)->esq;
      //2.3 ver se é no meio da arvore
    }else{
      if( z == 'e'){
      tmp = getMaxAux(&(*node)->esq);
    }else{
      tmp = getMinAux(&(*node)->dir);
    }
      (*node)->chave= tmp->chave;

    }
    free(tmp);
    return(true);
  }
  bool auxiliar;
    //3.Laço de chamadas recusivas
    if(valor < (*node)->chave){
      auxiliar = remocaoAVL(&(*node)->esq,valor,z);
    }else{
      auxiliar = remocaoAVL(&(*node)->dir,valor,z);
    }
    //4.Se o auxiliar for falso, nao houve mudança na arvore
    if(!auxiliar) return(false);

  // 5. Calculando as alturas das sub-arvores
    int Ae = alturaArvoreAVL((*node)->esq);
    int Ad = alturaArvoreAVL((*node)->dir);
    // 6. Verificando desbalanceamento
    if((Ae - Ad) >= +2 || (Ae - Ad) <= -2){
      AplicarRotacoes(&(*node));
    }
    //7. ajuste da altura do no corrente
    (*node)->altura = atualizaAltura((*node)->dir, (*node)->esq);
    return(true);
}
void destroiAVL(PtrNoAVL *node) {
  // percurso
  //percorrer a arvore e desalocar memoria de traz p frente
  if((*node) != NULL) {
    destroiAVL(&(*node)->esq);
    destroiAVL(&(*node)->dir);
    free(*node);
    (*node) = NULL;
  }
}

// -------------------------------
// -------------------------------

int main(int argc, const char * argv[]) {

  if(argc != 3){
    printf("Numero de argumento incompativel\n");
    return 1;
  }
  // raiz, acesso a estrutura de dados
  FILE *arq1,*arq2;
  char x[100],y[100],z;
  int valor;
  char *pt;
  arq1 = fopen(argv[1],"r");
  arq2 = fopen(argv[2],"wt");
  //confere se está abrindo os arquivos
  if(arq1	==	NULL || arq2 == NULL){
    printf("Ocorreu um erro no arquivo\n");
    system("pause");
    exit(1);
  }

  //analisa se o arquivo está vazio
  z = getc(arq1);
    if(z == EOF){
      printf("Arquivo de leitura vazio\n");
      fclose(arq1);
      fclose(arq2);
      exit(1);
    }
    //volta para posição inicial
  fseek(arq1,0,SEEK_SET);

  PtrNoAVL raiz;
  iniciaAVL(&raiz);

  fscanf(arq1,"%s\n",x);
  fscanf(arq1,"%s\n",y);
  z = getc(arq1);

  if((z == 'e'|| z =='d')){//confere se o arquivo está no padrão esperado
    pt = strtok(x," ,");
      while(pt != NULL){
        valor = atoi(pt);
        InserirAVL(&raiz,valor);
        pt = strtok (NULL, " ,");
      }
      fprintf(arq2, "[*]antes");
      printLevel(&raiz,arq2);
      fprintf(arq2,"\n");

      pt = strtok(y," ,");
        while(pt != NULL){
          valor = atoi(pt);
          remocaoAVL(&raiz,valor,z);
          pt = strtok (NULL, " ,");
        }
        fprintf(arq2, "[*]depois");
        printLevel(&raiz,arq2);

  }else{
    fprintf(arq2, "Arquivo inválido!");
    fclose(arq1);
    fclose(arq2);
    exit(1);
  }
  destroiAVL(&raiz);
  fclose(arq1);
  fclose(arq2);

  return 0;
}

// -------------------------------
// -------------------------------

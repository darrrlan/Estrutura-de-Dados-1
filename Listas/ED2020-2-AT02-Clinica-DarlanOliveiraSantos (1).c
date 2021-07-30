//  main.c
//  Listas

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

//------------------------------------------------------------------------------
// Lista duplamente encadeada
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// As struct
//------------------------------------------------------------------------------
typedef struct NoLista* PtrNoLista;

typedef struct{
  int codigo;
  char nome[100];
  char sexo;
  float peso;
  char altura[3];

} objeto;

typedef struct NoLista{
  objeto chave;
  PtrNoLista proximo;
  PtrNoLista anterior;
  // PtrNoLista anterior; // duplamente encadeada
} NoLista;

typedef struct {
  PtrNoLista inicio;
  int tamanho;
} ListaDinamica;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Inicia a lista
//------------------------------------------------------------------------------
void iniciaListaDinamica(ListaDinamica *lista) {
  //inicio
  lista->inicio = NULL;
  //tamanho
  lista->tamanho = 0;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Confere se a lista está fazia
//------------------------------------------------------------------------------
bool estaVaziaListaDinamica(ListaDinamica *lista) {
  return (lista->tamanho == 0);
  //return(lista->inicio == NULL);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// volta o tamanho da lista
//------------------------------------------------------------------------------
int tamanhoListaDinamica(ListaDinamica *lista) {
  return(lista->tamanho);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Imprimi a lista de forma crecente ou decrecente
//------------------------------------------------------------------------------
void imprimirListaDinamica(ListaDinamica *lista, FILE *arq2, char c) {

  PtrNoLista percorre;
  PtrNoLista percorre2;
  //pecorre toas as posições da lista
  for(percorre = lista->inicio; percorre != NULL; percorre = percorre->proximo) {
    if(c == '1'){//se no arquivo escolher o número 1, então imprimi e ordem crescente
    fprintf(arq2,"{%d, %s, %c, %g, %s}\n", percorre->chave.codigo,percorre->chave.nome,
    percorre->chave.sexo,percorre->chave.peso,percorre->chave.altura);
  }
  percorre2 = percorre;
  }
  if(c == '2'){// se ecolher dois vai percorrer toda a lista e
    //depois vai voltar pelo anterior para imprimeir em oderm decerecente
    for (percorre2; percorre2 != NULL; percorre2 = percorre2->anterior) {
    fprintf(arq2,"{%d, %s, %c, %g, %s}\n", percorre2->chave.codigo,percorre2->chave.nome,
    percorre2->chave.sexo,percorre2->chave.peso,percorre2->chave.altura);
  }
  }
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Inserir elementos na lista
//------------------------------------------------------------------------------
void inserirListaDinamica(ListaDinamica *lista, objeto paciente) {


  // 1. Criar o ponteiro (Novo)
  PtrNoLista novo;
  // 2. Aloca memoria para Novo
  novo =(PtrNoLista)malloc(sizeof(NoLista));
  // 3. copia o valor do elemento p chave do Novo no
  novo->chave = paciente;

  // Situação #1: Lista esta Vazia , ou
  // se o elemento que a gente quer inserir é menor do que o primeiro
  if(estaVaziaListaDinamica(lista) || paciente.codigo < lista->inicio->chave.codigo) {
    // 4. proximo do novo aponta para nulo (inicio)
    novo->proximo = lista->inicio;
    // 5. anterior de novo aponta pra nulo
    novo->anterior = NULL;
    if(estaVaziaListaDinamica(lista)){
      lista->inicio = novo;//7. se a lista for vazia a lista inicio recebe o novo
  }else{//se não
    //8. lista inicio anterior recebe o novo
    lista->inicio->anterior = novo;
    //9. lista inicio recebe o novo
    lista->inicio = novo;
    }


  } // Situacao # (Lista nao esta vazia)
  else {

   //printf("situacao 2 \n");
    // aux = percorre a lista p gente (encontrar o ponto de insercao - posicao)
    PtrNoLista aux;
    // 4. percorrer e encontrar o ponto de insercao (aux)
    aux = lista->inicio;
    while((aux->proximo!= NULL) && (paciente.codigo > aux->proximo->chave.codigo)) {
      aux = aux->proximo;
      //printf("andou ...\n");
    }
    //printf("Aux = %d \n", aux->chave);
    // 5. proximo Novo aponta proximo Aux
    novo->proximo = aux->proximo;
    // 6. proximo do Aux aponta para Novo
    aux->proximo = novo;
    if(novo->proximo != NULL){//se proximo for difente de nulo
      // 7. novo proximo anterior aponta pra novo
    novo->proximo->anterior = novo;
  }//se não
    novo->anterior = aux;
    //8. novo anterior recebe aux
  }
  // 9. incrementa o contador
  lista->tamanho = lista->tamanho + 1; //++
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Pesquisar elementos na lista
//------------------------------------------------------------------------------
bool pesquisaListaDinamica(ListaDinamica *lista, int consulta,FILE *arq) {

  if(estaVaziaListaDinamica(lista))
    return false;

  PtrNoLista percorre = lista->inicio;
  while(percorre != NULL && consulta > percorre->chave.codigo) {
    percorre = percorre->proximo;
  }
  // 1 - cheguei nulo
  // 2 - cheguei > consulta
  // 3 - achei

  // 1, e 2
  if(percorre == NULL || percorre->chave.codigo > consulta) {
    return false;
  }
  fprintf(arq,"{%d, %s, %c, %g, %s}\n", percorre->chave.codigo,percorre->chave.nome,
  percorre->chave.sexo,percorre->chave.peso,percorre->chave.altura);


  // 3
  return true;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Pesquisar elementos na lista
//------------------------------------------------------------------------------

void removeDaLista(ListaDinamica *lista, int chave, FILE *arq){
  //ver se lista não está vazia e se o elemento que queremos que seja
  //retirado exista na lista
  if(!estaVaziaListaDinamica(lista) && pesquisaListaDinamica(lista, chave,arq)){
    if(chave == lista->inicio->chave.codigo){//se estiver no inicio da lista
      //1. declara um ponterio do tipo PtrNoLista e temp recebe lista inicio
      PtrNoLista temp = lista->inicio;
      //2. lista inicio recebe o lista inicio proximo
      lista->inicio = lista->inicio->proximo;
      //3. lista inicio anterio recebe nulo
      lista->inicio->anterior = NULL;
      //4. lista tamanho é decrementada
      lista->tamanho--;
      //5. desalocamos a memoria de temp
      free(temp);

    }else{//se não

      //1. declaramosum ponteiro do tipo PtrNoLista com o inicio da lista
      PtrNoLista aux = lista->inicio;
      //2. um ponteiro do tipo PtrNoLista
      PtrNoLista destroi;
      //3. while que pecorre até o numero
      while(aux->proximo != NULL && chave > aux->proximo->chave.codigo){
        //4.aux recebe aux proximo
        aux = aux->proximo;
      }
      //5. destroi recebe aux proximo
      destroi = aux->proximo;
      //6. aux proximo recebe aux proximo do proximo
      aux->proximo = aux->proximo->proximo;
      //7. ver se aux proximo e diferente de nulo
      if(aux->proximo != NULL){
        //8. aux porixmo do anterio recebe aux
      aux->proximo->anterior = aux;
      }//se não
      //9. desalocamos a memoria de destroi
      free(destroi);
      //10. lista tamanho é decrementada
      lista->tamanho--;
    }
  }
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// destroi a lista dinamica
//------------------------------------------------------------------------------

void destruirListaDinamica(ListaDinamica *lista){
  //1. recebe o tamanho da lista
  int tamanho = tamanhoListaDinamica(lista);
  //2. um while que continua rodar at-e tamanho for igual 0
  do{
  //3. declaramosum ponteiro do tipo PtrNoLista com o inicio da lists
  PtrNoLista temp = lista->inicio;
  //4. lista inicio proximo tem que ser difente de nulo
  if(lista->inicio->proximo !=NULL){
  //5.lista inicio recebe lista inicio proximo
  lista->inicio = lista->inicio->proximo;
}//se nãon
  //6. lista inicio anterior recebe nulo
  lista->inicio->anterior = NULL;
  //7. decrementa lista tamanho
  lista->tamanho--;
  //8. decrementa o tamanho
  tamanho--;
  //9. desaloca a memoria de tempo
  free(temp);
}while(tamanho != 0 );

}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// main
//------------------------------------------------------------------------------

int main(int argc,char * argv[]){

  if(argc >0){
  ListaDinamica listinha;
  iniciaListaDinamica(&listinha);
  FILE *arq1, *arq2;
  char texto;
  int pesquisa;
  char c;


  arq1 = fopen(argv[1],"r");//abre arquivo
  arq2 = fopen(argv[2],"wt");
//==============================================================================
//confere se o arquivo está abrindo
//==============================================================================
  if(arq1	==	NULL || arq2 == NULL){
    printf("Ocorreu um erro no arquivo");
    system("pause");
    exit(1);
  }
//==============================================================================
//confere se o arquivo está vazio
//==============================================================================
    c = getc(arq1);
    if(c == EOF){
      printf("Arquivo de leitura vazio\n");
      fclose(arq1);
      fclose(arq2);
      exit(1);
    }
    fseek(arq1,0,SEEK_SET);
//==============================================================================
//==============================================================================

//==============================================================================
//Inserir o conteúdo na lista e confere se
//e a opção 1,2,3 ou se o arquivo está errado
//==============================================================================
  objeto dados;//struct de objetos
  do{
      c = getc(arq1);
  if(c == '{'){
      //guarda as informções na struct
     fscanf(arq1,"%i,%100[^,],%c,%f,%3[^}]}\n",&dados.codigo,&dados.nome,&dados.sexo,
     &dados.peso,&dados.altura);
     //insere na lista
     inserirListaDinamica(&listinha,dados);

  }else if( c == '1'){
    //imprimi a lista em ordem crescente no arquivo
    imprimirListaDinamica(&listinha,arq2,c);
    //destroi a lista
    destruirListaDinamica(&listinha);

  }else if( c == '2'){
    //imprimi a lista em ordem decrescente no arquivo
    imprimirListaDinamica(&listinha,arq2,c);
    //destroi a lista
    destruirListaDinamica(&listinha);
  }else if( c == '3'){
    //pega o número que vai ser pesquisado na lista
  fscanf(arq1,"%i",&pesquisa);
    //se o numero estiver na lista, vai imprimir no arquivo
  if(pesquisaListaDinamica(&listinha,pesquisa,arq2)){
    printf("O codigo foi encontrado e escrito no arquivo\n");
    //se não, apresenta uma mensagem de que não foi encontrado
  }else{
    printf("Codigo não foi encontrado\n");
  }
    //destroi a lista
    destruirListaDinamica(&listinha);
  }
  //caso o arquivo de entrada esteja fora do padrão esperado
  else if (c != '\n' && c != EOF){
  printf("arquivo de entrada esta fora do padrão esperado\n");
  fclose(arq1);
  fclose(arq2);
  exit(1);
  }
  }while(c != EOF);
  //fecha os arquivos
  fclose(arq1);
  fclose(arq2);
  }else{
  printf("Falta argumentos \n");
  }

  return 0;
  }

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

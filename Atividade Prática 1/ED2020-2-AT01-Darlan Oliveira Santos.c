//Bibliotecas
  #include <stdio.h>
  #include <stdlib.h>
  #include <stdbool.h>
  #include <ctype.h>
  #include <string.h>

  #define MAXTAM 10
//==============================================================================
//Função para converter de decimal para binario
long int bin(const int num){
  if( num == 0){
    return 0;
  }
  return bin(num/2)*10+num%2;
}
//==============================================================================
//Função para fechar os aquivos
void fechaArquivo(FILE *arquivo1,FILE *arquivo2){
  fclose(arquivo1);
  fclose(arquivo2);
}
//==============================================================================
//Pilha PilhaEstatica
//==============================================================================
  typedef struct {
    int array[MAXTAM];
    int topo;
  } pilhaEstatica;

//==============================================================================
  void iniciaPilhaE(pilhaEstatica *pilha) {
    pilha->topo = 0;//inicia a pilhaEstatica
  }//iniciaPilhaE
//==============================================================================
  bool estaVaziaE(pilhaEstatica *pilha) {
    if(pilha->topo == 0)//confere se a pilha está vazia
      printf("A pilha esta vazia\n");
  }//estaVaziaE
//==============================================================================
  bool estaCheiaE(pilhaEstatica *pilha) {
    if(pilha->topo == MAXTAM)//confere se a pilha está cheia
      printf("A pilha esta cheia\n");
  }//estaCheiaE
//==============================================================================
  void empilhaE(int item, pilhaEstatica *pilha) {
    if(!(pilha->topo == MAXTAM)){// confere se está cheia, se não tover ele empilha o número
      pilha->array[pilha->topo] = item;
      pilha->topo++;
    }else{
      printf("A pilha esta cheia");
    }//else
  }//empilhaE
//==============================================================================
  int desempilhaE(pilhaEstatica *pilha) {
    if(!(pilha->topo == 0)){//confere se está vazia, se não tiver ele desempilha o número
      int item = pilha->array[pilha->topo-1];
      pilha->topo--;
      return item;
    }else{
    printf("A pilha esta cheia\n");
    }//else
  }//desempilhaE
//==============================================================================
  void tamanhoPilhaE(pilhaEstatica *pilha) {
    printf("O tamanho da pilha eh: %i\n",pilha->topo);// imprime o tamnho da pilha usando o topo
  }//tamanhoPilhaE

  int topoE(pilhaEstatica *pilha) {
    return pilha->array[pilha->topo-1];//mostra o número do topo
  }//topoE
//==============================================================================
  void imprimePilhaE(pilhaEstatica *pilha) {//imprime a pilha
    printf("\n{ ");
      for (int i = 0; i < pilha->topo; i++) {
        printf("%i, ", pilha->array[i]);
      }
    printf("}\n");
  }//imprimePilhaE
//==============================================================================
//Pilha PilhaDinamica
//==============================================================================
  typedef struct NoPilha *PtrNoPilha;

  typedef struct NoPilha{
    int obj;
    PtrNoPilha proximo;
  } NoPilha;

  typedef struct {
    PtrNoPilha topo;
    int tamanho;
  } PilhaDinamica;


  void  iniciaPilhaD (PilhaDinamica * p){// inicia PilhaDinamica
    p->topo = NULL;//topo inicia NULL
    p->tamanho = 0;//tamanho igual 0
  }//iniciaPilhaD
//==============================================================================
  bool estaVaziaD(PilhaDinamica *p){
    if(p->topo == NULL)// ver se o topo é igual a nulo,se for está vazia
      printf("A pilha esta vazia\n");
  }//estaVaziaD
//==============================================================================
  void empilhaD(int num, PilhaDinamica *p){//empilha um número na pilha
    PtrNoPilha aux;
    aux = (PtrNoPilha) malloc(sizeof(NoPilha));
    aux->obj = num;//aux recebe o número
    aux->proximo = p->topo;//o porixmo recebe o topo
    p->topo = aux;//e o topo recebe o aux
    p->tamanho++;//e aumenta 1 no tamanho
  }//empilhaD
//==============================================================================
  int desempilhaD(PilhaDinamica *p){
    if(!(p->topo == NULL)){//se o topo for diferente de nulo, desempilha um número
      PtrNoPilha aux;//pronteiro para um nó de pilha
      aux = p->topo;//aux recebe topo
      int num = aux->obj;//num recebe o número que vai ser desenpilhado
      p->topo = aux->proximo;//topo recebe o proximo do aux
      free(aux);//libera a memoria
      p->tamanho--;//tamanho menos 1
      return num;//retorn o número para main
      }//if
    printf("Pilha esta vazia\n");
  }//desempilhaD
//==============================================================================
  void tamanhoPilhaD(PilhaDinamica *p){//mostra o tamanho da pilha
    printf("tamanho da pilha eh: %i\n",p->tamanho);
  }//tamanhoPilhaD
//==============================================================================
  void topoD(PilhaDinamica *p){
    PtrNoPilha aux;//ponteiro nó de pilha
    aux = p->topo;//aux recebe proximo
    printf("O elemento do topo eh: %i\n",aux->obj);//mostra o nomero do topo
  }//topoD
//==============================================================================
  void imprimePilhaD(PilhaDinamica *p){
    PtrNoPilha aux;//ponteiro nó de pilha
    printf("{ ");
      for(aux = p->topo ; aux !=NULL; aux = aux->proximo){// uma condição
        printf("%i ",aux->obj);//printa os numero da pilha
      }//for
    printf("}\n" );
  }//imprimePilhaD
//==============================================================================
  void destruirpilhaD(PilhaDinamica *p){
    while(!(p->topo == NULL)){// isso acontece enquanto topo for diferente de null
      PtrNoPilha aux;//ponteiro nó de pilha
      aux = p->topo;//aux recebe topo
      p->topo = aux->proximo;//topo recebe proximo
      free(aux);//libera memoria
      p->tamanho--;//tamanho menos 1
    }//while
  }//destruirpilhaD
//==============================================================================
  int main(int argc, char *argv[]){

    if(argc>2){
    char variavel;
    char texto[200];
    int result,leitura,tamanho,num;
    FILE *arq1, *arq2;

    arq1 = fopen(argv[1],"rt");//abre arquivo
    arq2 = fopen(argv[2],"wt");//abr aquivo
//==============================================================================
//confere se o arquivo está abrindo
      if(arq1	==	NULL || arq2 == NULL){
        printf("Ocorreu um erro no arquivo");
        system("pause");
        exit(1);
      }
//==============================================================================

      variavel = getc(arq1);
//==============================================================================
// Confere se tem letras ou números com vírgula depois da primeira linha
//==============================================================================
      while(fgets(texto,200,arq1) != NULL){
        tamanho = strlen(texto);
      }
      for (int i = 0; i < tamanho; i++) {
      if(ispunct(texto[i])||isalpha(texto[i])){
        printf("Warning:\nPode ter um numero com virgula\nPode ter uuma letra depois da primeira linha\nO arquivo esta vazio");
        fechaArquivo(arq1,arq2);
        exit(1);
      }//if
    }//for
    fseek(arq1,1,SEEK_SET);// volto pro inicio na posição 1
//==============================================================================
//PilhaDinamica
//==============================================================================
      if(variavel=='d'){
        PilhaDinamica p;
        iniciaPilhaD(&p);
        do{
          result = fscanf(arq1, "%i", &leitura);
          if(result != EOF){
            empilhaD(leitura,&p);
            imprimePilhaD(&p);
          }
        }while(result != EOF);
        do{
        num = desempilhaD(&p);
        fprintf(arq2,"%ld", bin(num));//print no arquivo
        fprintf(arq2,"\n");//print arquivo
        }while(p.topo != NULL);
//==============================================================================
//PilhaEstatica
//==============================================================================
      }else if(variavel == 'e'){
        pilhaEstatica p;
        iniciaPilhaE(&p);
        do{
          result = fscanf(arq1, "%i", &leitura);
          if(result != EOF){
            empilhaE(leitura,&p);
            imprimePilhaE(&p);
          }
        }while(result != EOF);

        do{
          num = desempilhaE(&p);//desempilha e sauva o número na função
          fprintf(arq2,"%ld", bin(num));//print no arquivo
          fprintf(arq2,"\n");//print no arquivo
        }while(p.topo > 0);

      }else{
        printf("Erro na variavel\n");
        printf("Nao eh nem Pilha Estatica e nem Pilha Dinamica\n" );
      }//else
      fechaArquivo(arq1,arq2);
    }else{
      printf("Falta argumentos\n");
    }//else
    return 0;

  }//main

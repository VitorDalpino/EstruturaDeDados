#include <conio.h>
#include <stdio.h>
#include <locale.h>


typedef struct no{
  int item;
  struct no *esquerda;
  struct no *direita;
} No;

typedef struct {
  No *raiz;
} Arvore;


Arvore criarArvore();
void adicionar(Arvore *arvore, int valor);

int main(){
    setlocale(LC_ALL, "Portuguese");

    Arvore binaria = criarArvore();

    adicionar(&binaria, 10);
    adicionar(&binaria, 5);
    adicionar(&binaria, 11);
    adicionar(&binaria, 3);
    adicionar(&binaria, 9);
    adicionar(&binaria, 1);
    adicionar(&binaria, 13);
    adicionar(&binaria, 4);

    printf("\n\n\n");
    imprimirCrescente(&binaria);
}

No* criarNo(int valor){
   printf("Criando um no com o valor %d", valor);

   No *no = (No*) malloc(sizeof(No));

   no->item = valor;
   no->esquerda = NULL;
   no->direita = NULL;

   return no;
}

Arvore criarArvore(){
    Arvore a;
    a.raiz = NULL;
    return a;
}

No* adicionarNo(No *no, int valor){
    if ( no == NULL ){
       No* novo = criarNo(valor);
       return novo;
    }

    if ( valor == no->item ) {
        printf("Já existe: %d", valor);
    }else {
         if ( valor < no->item ){
             no->esquerda = adicionarNo(no->esquerda, valor);
         }else{
             no->direita = adicionarNo(no->direita, valor);
         }
    }

}

void adicionar(Arvore *arvore, int valor){
    if ( arvore->raiz == NULL ){
        arvore->raiz = criarNo(valor);
    }else{
        adicionarNo(arvore->raiz, valor);
    }
}



void imprimirCrescente(Arvore *arvore){
    emOrdem(arvore->raiz);
}

void emOrdem(No *no){
    if ( no == NULL ){
        //printf("Nó vazio");
        return;
    }else {
        //printf("Nó da Esquerda");
        emOrdem(no->esquerda);

        printf("%d  ", no->item);

        //printf("Nó da Direita");
        emOrdem(no->direita);
    }
}
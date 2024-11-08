#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct NO;
typedef struct NO* ARVLLRB;
int cor(struct NO* H);
void trocaCor(struct NO* H);
struct NO* rotacionaEsquerda(struct NO* A);
struct NO* rotacionaDireita(struct NO* A);
struct NO* insereNo(struct NO* H, int valor, int* resp);
int remove_ArvLLRB(ARVLLRB* raiz, int valor);
struct NO* remove_NO(struct NO* H, int valor);
struct NO* balancear(struct NO* H);
int consulta_ArvLLRB(struct NO* raiz, int valor);
struct NO* move2EsqRED(struct NO* H);
struct NO* move2DirRED(struct NO* H);
struct NO* removerMenor(struct NO* H);
struct NO* procuraMenor(struct NO* atual);

int main() {
int op, valor, resultado;
ARVLLRB raiz = NULL;

do {
cout << "Menu - Arvore Rubro-Negra\n";
cout << "1. Inserir elemento\n";

cout << "2. Remover elemento\n";
cout << "3. Consultar elemento\n";
cout << "4. Sair\n";
cout << "Escolha uma opcao: ";
cin >> op;

switch (op) {
case 1:
cout << "Digite o valor a ser inserido: ";
cin >> valor;
int sucesso;
raiz = insereNo(raiz, valor, &sucesso);
if (sucesso == 1)
cout << "Elemento inserido com sucesso!\n";
else
cout << "Erro ao inserir elemento ou elemento ja existe.\n";
break;

case 2:
cout << "Digite o valor a ser removido: ";
cin >> valor;
resultado = remove_ArvLLRB(&raiz, valor);
if (resultado == 1)
cout << "Elemento removido com sucesso!\n";
else
cout << "Elemento nao encontrado para remocao.\n";
break;

case 3:
cout << "Digite o valor a ser consultado: ";
cin >> valor;

resultado = consulta_ArvLLRB(raiz, valor);
if (resultado == 1)
cout << "Elemento encontrado na arvore.\n";
else
cout << "Elemento nao encontrado.\n";
break;

case 4:
cout << "Saindo...\n";
break;

default:
cout << "Opcao invalida! Tente novamente.\n";
break;
}
} while (op != 4);

return 0;
}

struct NO {
int info;
struct NO* esq;
struct NO* dir;
int cor;
};

#define RED 1
#define BLACK 0

int cor(struct NO* H) {

if (H == NULL)
return BLACK;
else
return H->cor;
}

void trocaCor(struct NO* H) {
H->cor = !H->cor;
if (H->esq != NULL)
H->esq->cor = !H->esq->cor;
if (H->dir != NULL)
H->dir->cor = !H->dir->cor;
}

struct NO* rotacionaEsquerda(struct NO* A) {
struct NO* B = A->dir;
A->dir = B->esq;
B->esq = A;
B->cor = A->cor;
A->cor = RED;
return B;
}

struct NO* rotacionaDireita(struct NO* A) {
struct NO* B = A->esq;
A->esq = B->dir;
B->dir = A;
B->cor = A->cor;
A->cor = RED;
return B;
}

struct NO* insereNo(struct NO* H, int valor, int* resp) {
if (H == NULL) {
struct NO* novo = (struct NO*)malloc(sizeof(struct NO));
if (novo == NULL) {
*resp = 0;
return NULL;
}

novo->info = valor;
novo->cor = RED;
novo->dir = NULL;
novo->esq = NULL;
*resp = 1;
return novo;
}

if (valor == H->info) {
*resp = 0;
} else {
if (valor < H->info)
H->esq = insereNo(H->esq, valor, resp);
else
H->dir = insereNo(H->dir, valor, resp);
}

if ((cor(H->dir) == RED && cor(H->esq) == BLACK))
H = rotacionaEsquerda(H);

if (cor(H->esq) == RED && cor(H->esq->esq) == RED)
H = rotacionaDireita(H);

if (cor(H->esq) == RED && cor(H->dir) == RED)
trocaCor(H);

return H;
}

int remove_ArvLLRB(ARVLLRB* raiz, int valor) {
if (consulta_ArvLLRB(*raiz, valor)) {
struct NO* h = *raiz;
*raiz = remove_NO(h, valor);
if (*raiz != NULL)
(*raiz)->cor = BLACK;
return 1;
} else
return 0;
}

struct NO* remove_NO(struct NO* H, int valor) {
if (valor < H->info) {
if (cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK)
H = move2EsqRED(H);

H->esq = remove_NO(H->esq, valor);
} else {
if (cor(H->esq) == RED)
H = rotacionaDireita(H);

if (valor == H->info && (H->dir == NULL)) {
free(H);
return NULL;

}

if (cor(H->dir) == BLACK && cor(H->dir->esq) == BLACK)
H = move2DirRED(H);

if (valor == H->info) {
struct NO* x = procuraMenor(H->dir);
H->info = x->info;
H->dir = removerMenor(H->dir);
} else
H->dir = remove_NO(H->dir, valor);
}
return balancear(H);
}

struct NO* balancear(struct NO* H) {
if (cor(H->dir) == RED)
H = rotacionaEsquerda(H);

if (H->esq != NULL && cor(H->esq) == RED && cor(H->esq->esq) == RED)
H = rotacionaDireita(H);

if (cor(H->esq) == RED && cor(H->dir) == RED)
trocaCor(H);

return H;
}

int consulta_ArvLLRB(struct NO* raiz, int valor) {
while (raiz != NULL) {
if (valor == raiz->info)

return 1;
else if (valor < raiz->info)
raiz = raiz->esq;
else
raiz = raiz->dir;
}
return 0;
}

struct NO* move2EsqRED(struct NO* H) {
trocaCor(H);
if (cor(H->dir->esq) == RED) {
H->dir = rotacionaDireita(H->dir);
H = rotacionaEsquerda(H);
trocaCor(H);
}
return H;
}

struct NO* move2DirRED(struct NO* H) {
trocaCor(H);
if (cor(H->esq->esq) == RED) {
H = rotacionaDireita(H);
trocaCor(H);
}
return H;
}

struct NO* removerMenor(struct NO* H) {
if (H->esq == NULL) {
free(H);

return NULL;
}

if (cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK) {
H = move2EsqRED(H);
}

H->esq = removerMenor(H->esq);
return balancear(H);
}

struct NO* procuraMenor(struct NO* atual) {
struct NO *no1 = atual;
struct NO *no2 = atual->esq;
while (no2 != NULL) {
no1 = no2;
no2 = no2->esq;
}
return no1;
}
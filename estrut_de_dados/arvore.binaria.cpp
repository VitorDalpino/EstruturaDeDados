// Trabalho estrutura de dados II – vitor mussi dalpino 839827 //
#include <iostream>
#include <queue>
#include <map>

using namespace std;

struct No {
int dado;
int contagem;
No* esquerda;
No* direita;

// Construtor sem a sintaxe ':'
No(int val) {
dado = val;
contagem = 1;
esquerda = NULL;
direita = NULL;
}
};

class ArvoreBinaria {
private:
No* raiz;

void emOrdem(No* no) {
if (no == NULL) return;

emOrdem(no->esquerda);
cout << no->dado << "(" << no->contagem << ") ";
emOrdem(no->direita);
}

void preOrdem(No* no) {
if (no == NULL) return;
cout << no->dado << "(" << no->contagem << ") ";
preOrdem(no->esquerda);
preOrdem(no->direita);
}

void posOrdem(No* no) {
if (no == NULL) return;
posOrdem(no->esquerda);
posOrdem(no->direita);
cout << no->dado << "(" << no->contagem << ") ";
}

No* inserir(No* no, int val) {
if (no == NULL) return new No(val);
if (val == no->dado) {
no->contagem++;
} else if (val < no->dado) {
no->esquerda = inserir(no->esquerda, val);
} else {
no->direita = inserir(no->direita, val);
}
return no;
}

No* excluirNo(No* no, int val) {
if (no == NULL) return no;
if (val < no->dado) {
no->esquerda = excluirNo(no->esquerda, val);
} else if (val > no->dado) {
no->direita = excluirNo(no->direita, val);
} else {
if (no->contagem > 1) {
no->contagem--;
return no;
}
if (no->esquerda == NULL) {
No* temp = no->direita;
delete no;
return temp;
} else if (no->direita == NULL) {
No* temp = no->esquerda;
delete no;
return temp;
}
No* temp = minValorNo(no->direita);
no->dado = temp->dado;
no->contagem = temp->contagem;
no->direita = excluirNo(no->direita, temp->dado);
}
return no;
}

No* minValorNo(No* no) {
No* atual = no;
while (atual && atual->esquerda != NULL)

atual = atual->esquerda;
return atual;
}

int altura(No* no) {
if (no == NULL) return 0;
int alturaEsquerda = altura(no->esquerda);
int alturaDireita = altura(no->direita);
return max(alturaEsquerda, alturaDireita) + 1;
}

int contarNos(No* no) {
if (no == NULL) return 0;
return contarNos(no->esquerda) + contarNos(no->direita) + 1;
}

int contarFolhas(No* no) {
if (no == NULL) return 0;
if (no->esquerda == NULL && no->direita == NULL) return 1;
return contarFolhas(no->esquerda) + contarFolhas(no->direita);
}

void mostrarFolhas(No* no) {
if (no == NULL) return;
if (no->esquerda == NULL && no->direita == NULL) {
cout << no->dado << " ";
}
mostrarFolhas(no->esquerda);
mostrarFolhas(no->direita);
}

void maisFrequente(No* no, map<int, int>& frequencia) {
if (no == NULL) return;
frequencia[no->dado] += no->contagem;
maisFrequente(no->esquerda, frequencia);
maisFrequente(no->direita, frequencia);
}

public:
ArvoreBinaria() : raiz(NULL) {}

void mostrarArvore() {
emOrdem(raiz);
cout << endl;
}

void fazerPercursos() {
cout << "Em ordem: ";
emOrdem(raiz);
cout << endl;
cout << "Pre ordem: ";
preOrdem(raiz);
cout << endl;
cout << "Pos ordem: ";
posOrdem(raiz);
cout << endl;
}

void incluirElemento(int val) {
raiz = inserir(raiz, val);
}

void excluirElemento(int val) {
raiz = excluirNo(raiz, val);
}

void mostrarAltura() {
cout << "Altura: " << altura(raiz) << endl;
}

void quantidadeElementos() {
cout << "Quantidade de elementos: " << contarNos(raiz) << endl;
}

void quantidadeFolhas() {
cout << "Quantidade de folhas: " << contarFolhas(raiz) << endl;
cout << "Folhas: ";
mostrarFolhas(raiz);
cout << endl;
}

void numeroMaisFrequente() {
map<int, int> frequencia;
maisFrequente(raiz, frequencia);
int maxFreq = 0;
for (auto& par : frequencia) {
if (par.second > maxFreq) {
maxFreq = par.second;
}
}
cout << "Numero(s) mais frequente(s): ";
for (auto& par : frequencia) {
if (par.second == maxFreq) {

cout << par.first << " ";
}
}
cout << endl;
}
};

int main() {
ArvoreBinaria arvore;
int opcao, valor;

do {
cout << "Menu:\n";
cout << "1. Mostrar a arvore\n";
cout << "2. Fazer os percursos\n";
cout << "3. Incluir elemento\n";
cout << "4. Excluir elemento\n";
cout << "5. Mostrar a altura\n";
cout << "6. Quantidade de elementos\n";
cout << "7. Quantidade de folhas\n";
cout << "8. Mostrar numero(s) mais frequente(s)\n";
cout << "9. Sair\n";
cout << "Escolha uma opcao: ";
cin >> opcao;

switch (opcao) {
case 1:
arvore.mostrarArvore();
break;
case 2:
arvore.fazerPercursos();

break;
case 3:
cout << "Digite o valor a ser incluido: ";
cin >> valor;
arvore.incluirElemento(valor);
break;
case 4:
cout << "Digite o valor a ser excluido: ";
cin >> valor;
arvore.excluirElemento(valor);
break;
case 5:
arvore.mostrarAltura();
break;
case 6:
arvore.quantidadeElementos();
break;
case 7:
arvore.quantidadeFolhas();
break;
case 8:
arvore.numeroMaisFrequente();
break;
case 9:
cout << "Saindo...\n";
break;
default:
cout << "Opcao invalida!\n";
}
} while (opcao != 9);

return 0;
}
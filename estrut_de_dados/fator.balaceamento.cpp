#include <conio.h> 
#include <stdio.h> 
#include <locale.h> 
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* esquerda;
    No* direita;

    No(int val) {
        valor = val;
        esquerda = nullptr;
        direita = nullptr;
    }
};

int altura(No* no) {
    if (no == nullptr) {
        return 0;
    }
    return 1 + max(altura(no->esquerda), altura(no->direita));
}

No* rotacaoEsquerda(No* raiz) {
    No* novaRaiz = raiz->direita;
    No* filhoEsquerda = novaRaiz->esquerda;

    novaRaiz->esquerda = raiz;
    raiz->direita = filhoEsquerda;

    return novaRaiz;
}

No* rotacaoDireita(No* raiz) {
    No* novaRaiz = raiz->esquerda;
    No* filhoDireita = novaRaiz->direita;

    novaRaiz->direita = raiz;
    raiz->esquerda = filhoDireita;

    return novaRaiz;
}

No* rotacaoEsquerdaDireita(No* raiz) {
    raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
    return rotacaoDireita(raiz);
}

No* rotacaoDireitaEsquerda(No* raiz) {
    raiz->direita = rotacaoDireita(raiz->direita);
    return rotacaoEsquerda(raiz);
}

No* balancear(No* raiz) {
    if (raiz == nullptr) return raiz;

    int fb = altura(raiz->esquerda) - altura(raiz->direita);

    if (fb < -1) {
        if (altura(raiz->direita->esquerda) <= altura(raiz->direita->direita)) {
            raiz = rotacaoEsquerda(raiz);
        } else {
            raiz = rotacaoDireitaEsquerda(raiz);
        }
    } else if (fb > 1) {
        if (altura(raiz->esquerda->direita) <= altura(raiz->esquerda->esquerda)) {
            raiz = rotacaoDireita(raiz);
        } else {
            raiz = rotacaoEsquerdaDireita(raiz);
        }
    }

    return raiz;
}

No* inserir(No* raiz, int valor) {
    if (raiz == nullptr) {
        return new No(valor);
    }
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else {
        raiz->direita = inserir(raiz->direita, valor);
    }
    return balancear(raiz);
}

int calcularFatorBalanceamento(No* raiz) {
    int profundidadeDesbalanceada = altura(raiz);
    raiz = balancear(raiz);
    int profundidadeBalanceada = altura(raiz);
    return profundidadeBalanceada - profundidadeDesbalanceada;
}

int main() {
    No* raiz = nullptr;

    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 3);
    raiz = inserir(raiz, 7);

    int fatorBalanceamento = calcularFatorBalanceamento(raiz);
    
    cout << "Fator de balanceamento: " << fatorBalanceamento << endl;

    return 0;
}
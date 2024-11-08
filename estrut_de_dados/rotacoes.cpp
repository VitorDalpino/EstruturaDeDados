NO* rotacaoEsquerda(No *raiz){
   No* aux;
   No* filho;
   
   aux = raiz->direita;
   filho = aux->esquerda;
   
   aux->esquerda = raiz;
   raiz->direita = filho;
   
   return aux;
}

NO* rotacaoDireita(No *raiz){
   No* aux;
   No* filho;
   
   aux = raiz->esquerda;
   filho = aux->direita;
   
   aux->direita = raiz;
   raiz->esquerda = filho;
   
   return aux;
}
No*  balancear(No* raiz){
   int fb   = fatorDeBalanceamento(raiz);
   int fbD  = fatorDeBalanceamento(raiz->direita);
   int fbE  = fatorDeBalanceamento(raiz->esquerda);
   
   //Exemplo1
   if ( fb < -1 ) && ( fbD <= 0){
      raiz = rotacaoEsquerda(raiz);
   }else if ( fb >1 ) && ( fbE >= 0 ){
      raiz = rotacaoDireita(raiz);
   }else if ( fb >1) && ( fbE < 0 ){
      raiz = rotacaoEsquerdaDireita(raiz)
   }else if ( db < -1 ) && (fbD > 0){
      raiz = rotacaoDireitaEsquerda(raiz);
   }else{
      //Balanceada!!!
   }
 
   //Exemplo2  
   if ( fb < -1 ) {
      if ( fbD <= 0) {
         raiz = rotacaoEsquerda(raiz);
      }else{
         raiz = rotacaoDireitaEsquerda(raiz);
      }
   }else if ( fb >1 )
      if ( fbE >= 0 ){
          raiz = rotacaoDireita(raiz)
      }else{
         raiz = rotacaoEsquerdaDireita(raiz)
      }
   }else{
      //Balanceada!!!
   }

   return raiz;  
}
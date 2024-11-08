#include <conio.h>
#include <stdio.h>
#include <locale.h>

void mudar(int *a, int *b);

int main(){
    //Vai ajustar a questão de acentuação
    setlocale(LC_ALL, "Portuguese");

   int a = 10;
   int b = 55;

   printf("A: %d\n", a);
   printf("B: %d\n", b);


   printf("\n================\n");
   mudar(&a, &b);
   printf("\n================\n");

   printf("A: %d\n", a);
   printf("B: %d\n", b);

   printf("\n================\n");
   printf("================\n");


   ////
   int  teste = 100;
   int *aponta = &teste;

   printf("teste = %d (é o valor da variável)\n", teste);
   printf("&teste = %p (é o endereço dessa variável) \n", &teste);

   printf("aponta = %p (é o valor do ponteiro(variável) )\n", aponta);
   printf("&aponta = %p (é o endereço desse ponteiro(variável))\n", &aponta);

   printf("*(&aponta) = %p (é o endereço apontado)\n", *(&aponta));
   printf("*(*(&aponta)) = %d(é o valor que está na variável apontada pelo ponteiro)\n", *(*(&aponta)));
}


void mudar(int *arg1, int *b){

    printf("\nValores antes de mudar: \n")    ;
    printf("A: %d\n", *arg1);
    printf("B: %d\n", *b);
    int c = *arg1;
    *arg1 = *b;
    *b = c;

    printf("\nValores após mudar:\n")    ;
    printf("A: %d\n", *arg1);
    printf("B: %d\n", *b);
}
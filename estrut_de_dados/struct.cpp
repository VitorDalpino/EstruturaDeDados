#include <conio.h>
#include <stdio.h>
#include <locale.h>

struct Ponto2D
{
    int x;
    int y;
};

typedef struct
{
    int x;
    int y;
    int z;
} Ponto3D;

typedef struct
{
   struct Ponto2D  *p1;
   struct Ponto2D  *p2;
} Reta


void imprimirPonto2D(struct Ponto2D p);

void imprimirPonto3D(Ponto3D p);
void duplicarPosicao(Ponto3D p);
void duplicarPosicaoReferencia(Ponto3D *p);


int main(){
    setlocale(LC_ALL, "Portuguese");

    struct Ponto2D a;
    a.x = 10;
    a.y = 20;

    Ponto3D b;
    b.x = 15;
    b.y = 25;
    b.z = 150;

    //printf("\nO seu Ponto1 está em [%d, %d]", a.x, a.y);
    imprimirPonto2D(a);


    printf("\Ponto 3D");

    imprimirPonto3D(b);
    duplicarPosicao(b);
    printf("\Mas agora????");
    imprimirPonto3D(b);


    printf("\Mas agora por Referencia????");
    duplicarPosicaoReferencia(&b);
    imprimirPonto3D(b);

}


void imprimirPonto2D(struct Ponto2D p){
    printf("\nO seu Ponto está em [%d, %d]", p.x, p.y);
}

void imprimirPonto3D(Ponto3D p) {
    printf("\nO seu Ponto está em [%d, %d, %d]", p.x, p.y, p.z);
}

void duplicarPosicao(Ponto3D p){
   p.x *= 2;
   p.y *= 2;
   p.z *= 2;

   imprimirPonto3D(p);
}

void duplicarPosicaoReferencia(Ponto3D *p){
   //(*p)  mesma coisa p->
   p->x *= 2;
   p->y *= 2;
   p->z *= 2;

   imprimirPonto3D(*p);
}
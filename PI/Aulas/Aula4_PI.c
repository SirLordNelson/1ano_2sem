#include <stdio.h>
/*
Matéria:

int *p; refere-se ao endereço de p
int x;
p = &x; está a ser pedido o conteúdo de x (& direciona para o endereço de x)
*p == 10; * refere-se ao conteúdo do endereço
*/


// Ficha 3 //

// Exercício 1 //

// Alínea a //
int main () {
    int x [15] = {1, 2, 3, 4, 5,
                  6, 7, 8, 9,10,
                  11,12,13,14,15};
    int *y, *z, i;
    y = x; // y corresponde ao endereço onde está guardado x[0]
    z = x+3;
   for (i=0; i<5; i++) {
        printf ("%d %d %d\n", x[i], *y, *z);
        y = y+1; z = z+2;
    }
}
Resolução:
1 1 4
2 2 6
3 3 8
4 4 10
5 5 12

// Alínea b //
int main () {
    int i, j, *a, *b;

    i=3; j=5;
    a = b = 42;
    a = &i; b = &j;
    i++; // até aqui *a == i == 4 
    j = i + *b; // 4 + 5 = 9
    b = a;
    j = j + *b; // 9 + 4 = 13
    printf ("%d\n", j);

    return 0;
}
Resolução:
13


// Exercício 2 //
void swapM (int *x, int *y){
    int w = *x;
    *x = *y;
    *y = w;
}

int main(){
    int a, b;
    a = 3;
    b = 5;
    swapM(&a, &b);
    printf("%d %d\n", a, b);
    return 0;
}

// Exercício 3 //
void swap(int v[], int i, int j){
    int t = v[i];
    v[i] = v[j];
    v[j] = t;
}

// Exercício 4 //
void soma(int v[], int N){
    int r = 0;
    int i = 0;
    while(i < N){
        r += *(v + i);// * refere-se ao conteúdo de (v + i), enquanto que este corresponde ao endereço onde está gravado o valor v[i]
    }
    return 0;
}

// Exercício 5 //
void inverteArray (int v[], int N){
    int i, j;
    i = 0;
    j = N - 1;
    while(i < j){
        swap(v, i, j);
        i++;
        j--;
    }
}

// Exercício 6 //
int maximum (int v[], int N, int *m){
    if(N <= 0)
        return 1; // está a dizer que algo de errado não está certo
    *m = v[0];
    for(int i; i < N; i++){
        if(v[i] > *m){
            *m = v[i];
        }
    }
    return 0;
}
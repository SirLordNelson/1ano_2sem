#include <stdio.h>

int adiciona(int x, int y) {
    return x + y;
}

int main () {
    int x = adiciona(2, 3);
    printf("%d\n", x);
    return 0;
}

// Ficha 1 //


// Grupo 1 //

// Exercício 1 //
int main () {
    int x, y;
    x = 3;
    y = x+1;
    x = x*y;
    y = x + y;
    printf("%d %d\n", x, y);
    return 0;
}

// Exercício 2 //
int main () {
    int x, y;
    x = 0;
    printf ("%d %d\n", x, y);
    return 0;
}

// Exercício 3 //
int main () {
    char a, b, c;
    a = 'A'; 
    b = ' '; 
    c = '0';
    printf ("%c %d\n", a, a);
    a = a+1; 
    c = c+2;
    printf ("%c %d %c %d\n", a, a, c, c);
    c = a + b;
    printf ("%c %d\n", c, c);
    return 0;
}

// Exercício 4 //
int main () {
    int x, y;
    x = 200; 
    y = 100;
    x = x+y; 
    y = x-y; 
    x = x-y;
    printf ("%d %d\n", x, y);
    return 0;
}


// Grupo 2 //

// Exercício 1 //

// Alínea a //
int main () {
    int x, y;
    x = 3; 
    y = 5;
    if (x > y)
    y = 6;
    printf ("%d %d\n", x, y);
    return 0;
}

// Alínea b //
int main () {
    int x, y;
    x = y = 0;
    while (x != 11) { // != traduz-se em "diferente" //
        x = x+1;
        y += x; // o que traduz: y = y + x //
    }
    printf ("%d %d\n", x, y);
    return 0;
}

// Alínea c //
int main () {
    int i;
    for (i=0; (i<20) ; i++) // "i++" traduz-se na soma de mais um elemento //
    if (i%2 == 0) {
        putchar ('_'); // % traduz-se resto da divisão inteira //
    } else {
         putchar ('#');
    } putchar ('\n');
    return 0;
}

// Alínea d //
void f (int n) {
    while (n>0) {
        if (n%2 == 0) putchar ('0');
        else putchar ('1');
        n = n/2;
    }
    putchar ('\n');
}

int main () {
    int i;
    for (i=0;(i<16);i++)
        f (i);
    return 0;
}
#include <stdio.h>

// Ficha 2 //

// Exercício 1 //

float multInt1 (int n, float m){
    int r = 0; // r conterá o resultado de n*m
    int i = 0; // conta o nº de vezes que já somamos m
    while (i < n) {
        r = r + m;
        i++; // atualizamos o i para indicar que somamos m mais uma vez
    }
    return r;
}

// Exercício 2 //

float multInt2 (int n, float m){
    int r;
    while (n >= 0){
        if (n % 2 == 1)
            r += m;
        n = n / 2;
        m = m * 2;
    }
    return r;
}

// Exercício 3 //

Primeira forma de fazer:

int mdc1 (int a, int b){
    int maior, menor, i, r;
    if (a > b){
        menor = b;
        maior = a;
    } else {
        menor = a;
        maior = b;
    }
    for (i = 1; i <= menor; i++){
        if (menor % i == 0 && maior % i == 0){
            r = i;
        }
    }
    return r;
}

Segunda forma de fazer:

int mdc1 (int a, int b){
    int maior, menor, r;
    if (a > b){
        menor = b;
        maior = a;
    } else {
        menor = a;
        maior = b;
    }
    for (r = menor; menor % r != 0 || maior % r != 0, r--) {} // ou seja, o código para qnd (menor % r == 0) && (maior % r == 0) //
    return r;
}

// Exercício 4 //

// Resolução do stor:

int mdc2 (int a, int b){
    while (a != 0 && b != 0){
        if (a > b) a = a - b;
        else b = b - a;
    }
    return a + b;
}

// Minha versão: (duvido que esteja bem)

int mdc2 (int a, int b){
    int maior, menor;
    if (a > b){
        menor = b;
        maior = a;
    } else {
        menor = a;
        maior = b;
    }
    while (maior > menor){
        maior = maior - menor;
        if (maior < menor) {
        menor = menor - maior;
        }
    }
    return menor;
}

// Exercício 5 //

int mdc2 (int a, int b){
    while (a != 0 && b != 0){
        if (a > b) a = a % b;
        else b = b % a;
    }
    return a + b;
}

// Exercício 6 //

// Alínea a //

int fib1 (int n){
    int r;
    if (n < 2) r = 1;
    else {
        r = fib1 (n - 1) + fib1 (n - 2);
    }
    return r;
}

// Alínea b //

int fib2 (int n){
    if (n < 2)
        return 1;
    int a = 0;
    int b = 1;
    int r;
    for (int i = 2; i <= n; i++){
        r = a + b;
        a = b;
        b = r;
    }
    return r;
}
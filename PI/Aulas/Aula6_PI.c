#include <stdio.h>

typedef struct aluno {
    int numero;
    char nome[100];
    int miniT [6];
    float teste;
} Aluno;

// Ficha 5 //

// Exercício 2 //
int procuraNum (int num, Aluno t[], int N){
    int f = N - 1; // não estou a contar o "\0"

    while(i <= f){
        int m = (i + f) / 2;
        if (t[m].numero == num) { // o aluno foi encontrado
            return m;
        } else if (t[m].numero < num) { // o número do aluno é maior
            i = m + 1;
        } else { // o número do aluno é menor
            f = m - 1;
        }
    }

    return -1; // Number Not Found
}

// Exercício 3 //
void ordenaPorNum (Aluno t[], int N){
    int aux;

    for(int i = 0; i < N; i++){
        aux = t[i].numero;
        for(int j = i; j > 0 && t[j-1].numero > aux; j--) t[j].numero = t[j-1].numero;
        t[j].numero = aux;
    }
}
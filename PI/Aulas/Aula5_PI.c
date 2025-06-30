#include <stdio.h>

// Ficha 4 //

// Exercício 1 //

// Alínea 1 //
int contaVogais(char *s){
    int r = 0;
    int i;
    for(i = 0; s[i] != '\0'; i++){
        if(eVogal s[i]) r++;
    }
    return r;
}

int eVogal(char c){
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

// Alínea 2 //
// Primeira forma de resolver //
int retiraVogaisRep(char *s){
    char aux[strlen(s) + 1];
    int i, conta = 0;
    for(i = 0; s[i] 1= '\0'; i++){
        if(eVogal (s[i]) && s[i] == s[i + 1]) conta++; // "conta" vai contar quantas vogais são removidas
        else{
            aux[i - conta] = s[i];
        }
    }
    aux[i - conta] = '\0';
    for(j = 0; aux[j] != '\0': j++) s[j] = aux[j];
    s[j] = '\0';
    return conta;
}

int strlen(char *s){
    int r = o;
    for(int i = 0; s[i] != '\0'; i++) r++
    return r;
}

// Segunda forma de resolver //
int retiraVogaisRep2(char *s){
    int conta = 0;
    for(int i = 0; s[i] != '\0'; i++){
        if(eVogal s[i] && s[i + 1] == s[i]) conta++;
        else{
            s[i - conta] = s[i];
        }
    }
    s[i - conta] = '\0';
    return conta;
}

// Exercício 2 //

// Alínea 1 //
int ordenado (int v[], int N){
    int r = 1; // guarda a resposta
    for(int i = 0; i < N - 1 && r == 1; i++){
        if(v[i] < v[i + 1]) return 1; // 1 (ou podia ser qq outro valor) corresponde a verdadeiro
        else{
            return 0; // 0 correponde a falso
        }
    }
    return r;
}
#include <stdio.h>
#include <stdlib.h>

// Exercício 1 //7
#define Max 10
typedef struct {
    int sp;
    int values [Max];
} *SStack;

// Alínea a //
void SinitStack (SStack s){
    (*s).sp = 0; // é o mesmo que (s -> sp = 0)
}

// Alínea b //
int SisEmpty (SStack s){
    return s->sp == 0;
}

// Alínea c //
int Spush (SStack s, int x){
    if((*s).sp == Max) return 1;
   
    s->values[s->sp] = x;
    s->sp++;
    return 0;
}

// Alínea d //
int Spop (SStack s, int *x){
    if(SisEmpty(s)) return 1;

    *x = s->values[s->sp-1]; // conteúdo do end x
    s->sp = s->sp-1;
    return 0;
}

// Exercício 3 //

typedef struct dinStack {
    int size; // guarda o tamanho do array values
    int sp;
    int *values;
} *DStack;

malloc(sizeof(int) * 5); // devolve o endereço de um novo bloco de memória

void initStack(DStack s){
    s->sp = 0;
    s->size = 5;
    s->values = malloc(sizeof(sp) * 5);
}

int isEmpty(DStack s){
    return s->sp == 0;
}

int push(DStack s, int x){
    if((*s).sp == Max) return 1;
   
    s->values[s->sp] = x;
    s->sp++;
    return 0;
}

int pop (DStack s, int *x){
    if(SisEmpty(s)) return 1;

    *x = s->values[s->sp-1]; // conteúdo do end x
    s->sp = s->sp-1;
    return 0;
}
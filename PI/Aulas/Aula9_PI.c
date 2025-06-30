#include <stdio.h>

//Ficha 9//

typedef struct nodo {
int valor;
struct nodo *esq, *dir;
} * ABin;

ABin newABin (int r, ABin e, ABin d) {
    ABin a = malloc (sizeof(struct nodo));
    if (a!=NULL) {
        a->valor = r; a->esq = e; a->dir = d;
    }
return a;
}

//Exercício 1//
//Alínea a//
int altura (ABin a){
    int r;
    if(a == NULL) r = 0;
    else{
        int te, rd;
        re = altura(a->esq);
        rd = altura(a->dir);
        return 1 + maior(re,rd);
    }
}

//Alínea b//
int nFolhas (ABin a){
    int folhas;
    if(a == NULL) folhas = 0;
    else if(a->esq == NULL && a->dir == NULL) folhas = 1;
    else folhas = nFolhas(a->esq) + nFolhas(a->dir);
    return folhas;
}

//Alínea c//
ABin maisEsquerda (ABin a){
    while(a != NULL && a->esq != NULL){
        a = a->esq;
    }
    return a;
}

//Alínea d//
void imprimeNivel (ABin a, int l){
    if(a == NULL) return 0;
    if(l == 0) printf("%d", a->valor);
    else{
        imprimeNivel(a->esq, l-1);
        imprimeNivel(a->dir, l-1);
    }
}

//Alíne e//
int procuraE (ABin a, int x){
    if(a == NULL) return 0;
    if(a->valor == x) return 1;
    else{
        if(procuraE(a->esq, x) == 1) return 1;
        else return procuraE(a->dir, x);
    }
}

//usamos recursividade qnd queremos andar pela árvore esquerda e direita
//se quisermos andar por uma só árvore, usamos ciclos
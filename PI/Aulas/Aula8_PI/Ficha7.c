#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>
#include <assert.h>

typedef struct celula{
    char *palavra;
    int ocorr;
    struct celula *prox;
}* Palavras;

/*
__0x1000_______          ___0x1010______
|palavra="ola"|          |palavra="ole"|
|ocorr=2      |          |ocorr=1      |
|prox=0x1010  |  ---->   |prox=NULL    |  ---->  *
|_____________|          |_____________|

       ______________
0x1050 |0x1000       |
       |_____________|
0x1040 |             |
       |_____________|
0x1030 |             |
       |_____________|
0x1020 |             |
       |_____________|
0x1010 |palavra="ole"|
       |...          |
       |_____________|
0x1000 |palavra="ola"|
       |...          |
       |_____________|




Correção do enunciado

1. void libertaLista (Palavras l) que liberta todo o espaço (da heap) ocupado pela lista de
palavras.
2. int quantasP (Palavras l) que calcula quantas palavras (diferentes) existem armazenadas.




=>while   =>  p!=NULL
=>for     =>  p->prox!=NULL
*/


//1
void libertalista(Palavras l){
    while(l!=NULL){
        Palavras temp=l;
        l=l->prox;
        free(temp);
    }  
}


//2
int quantasP (Palavras l){
    int i;
    Palavras temp=l;
    for(i=0;l!=NULL;i++,l=l->prox);
    l=temp;
    return i;
}

int quantasP2 (Palavras l){
    int i;
    Palavras temp=l;
    while(temp!=NULL){
        i++;
        temp=temp->prox;
    }
    return i;
}
/*
int x = 5

printf  x - conteudo
printf *x - erro
printf &x - endereço onde tá o 5


int *y

printf  y - endereço
printf *y - conteudo
printf &y - erro
*/


//3

void listaPal (Palavras l){
    Palavras temp=l;
    while(l!=NULL){
        printf("%s: %d ocorrencias", l->palavra,l->ocorr);
        l=l->prox;
        l=l->prox;
    }
}


//4

char *ultimo(Palavras l){
    Palavras temp=l;
    if(l==NULL) return NULL;
    while(l->prox!=NULL){
        l=l->prox;
    }
    return temp -> palavra;
}


char *ultimo2(Palavras l){
    Palavras temp=l;
    char *pal;
    if(l==NULL) return NULL;
    while(temp!=NULL){
        pal=temp->palavra;
        temp=temp->prox;
    }
    return pal;
}


//5

Palavras acrescentaInicio (Palavras l, char *p){
    Palavras nova=malloc(sizeof(struct celula));
    if(nova==NULL) return l;
    nova->palavra=p;
    nova->ocorr=1;
    l=nova;
    return nova;
}
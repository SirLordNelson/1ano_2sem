#include <stdio.h>

typedef struct lligada {
    int valor;
    struct lligada *prox;
} *LInt;

//Exercício 1//
int length (LInt a){
    int acc;
    for(acc = 0; a; a = a->prox; acc++); // o "a" é um ponteiro de um nó que será usado na parte seguinte do for para apontar para o ponteiro seguinte
    return acc;
}

//Exercício 2//
void freeL (LInt a){
    LInt next;
    while (a){ //continua enquanto "a" não for nulo
        next = a->prox; //"next" armazena o próximo nó
        a->prox = NULL; //escrevemos isto, pq podia dar erro devido à possibilidade de haver mais alguma coisa depois do nó
        free(a); //liberta o nó
        a = next; //avança para o próximo nó
    }
}

//Exercício 3//
void imprimeL (LInt a){
    while (a){
        wprintf("%d\n", a->valor); //é importante ter o "a->valor", pois se for só o "a" estou a indicar o endereço de memória, e não o valor
        a = a->prox;
    }
}

//Exercício 4//
LInt reverseL(LInt l){
    LInt r, ant, next;
    r = l;
    ant = NULL;
    if (l && l->prox){ //vê se a lista tem mais de 2 nós
        while (r && r->prox){ //enquanto houver nós em "r" e "r" não for o último, vai indo
            next = r->prox; //dizemos que o "next" é o próximo valor
            r->prox = ant; //indicamos o início da lista, que começará com "NULL"
            ant = r; //atualizamos o valor de "ant" para "r"
            r = next; //avançamos para o próximo
        }
        r->prox = ant; //indica o último elemento da lista como o primeiro da nova lista
    }
    return r;
}

//Exercício 5//
void insertOrd(LInt *a, int x){ //"*a" é um ponteiro para a cabeça de uma lista ligada
    LInt p, r, ant;
    ant = NULL;
    p = *a; //"p" torna-se o primeiro elemento da lista
    if (!p){ //neste if vai ser criado um novo nó com o x como primeiro e único valor
        *a = malloc(sizeof(struct lligada)); //serve para indicar ao ponteiro o que é suposto receber
        (*a)->valor = x;
        (*a)->prox = NULL;
    }
    else{
        while (p && p->valor < x){ //vamos percorrendo a lista até chegarmos onde nos interessa
            ant = p;
            p = p->prox;
        }
        r = malloc(sizeof(struct lligada)); //está a criar a memória que poderá vir a ser necessária para ser preenchida por x
        r->valor = x;
        if (ant){ //significa que não estamos no início da lista
            r->prox = p; //organizamos primeiro o p e depois o r, pq o r estará entre o ant e o p
            ant->prox = r;
        }
        else{ //significa que estamos no início da lista
            r->prox = p;
            (*a) = r; //torna "r" o novo primeiro nó da lista
        }
    }
}

//Exercício 6//
int removeOneOrd (LInt *a, int x){
    LInt p, ant;
    int r = 1;
    ant = NULL;
    p = *a;
    if(p){ //verifica se a lista está vazia
        while(p && p->valor != x){ //procura pelo elemento x
            ant = p;
            p = p->prox;
        }
        if(p && p->valor == x){ //o x foi encontrado
            ant->prox = p->prox; //estamos a saltar o valor que vai ser eliminado para que o x possa tomar o lugar do p
            free(p);
            r = 0; //indica que a remoção foi bem sucedida
        } if(!ant && p->prox == x){ //x é o primeiro elemento da lista
            p = p->prox;
            free(*a);
            *a = p; //estamos a fazer com que o apontador aponte de novo para o novo início da lista
            r = 0;
        }
    }
    return r;
}

//Exercício 7//
void merge (LInt *r, LInt a, LInt b){
    if(!a) *r = b;
    else if(!b) *r = a;
    else if(a->valor < b->valor){
        *r = a; //o valor de a ficou guardado na lista r
        merge(&(*r)->prox, a->prox, b); //vamos comparar o próximo valor de a com o de b
    }
    else{
        *r = b;
        merge(&(*r)->prox, a, b->prox); //o "&(*r)" serve para indicar que o que vai mudar é o pŕoximo endereço de memória de r
    }
}

//Exercício 8//
void splitQS (LInt l, int x, LInt *mx, LInt *Mx){
    if(l){
        if(l->valor < x){
            *mx = malloc(sizeof(struct lligada)); //serve para indicar ao ponteiro o que é suposto receber
            (*mx)->valor = l->valor;
            splitQS(l->prox, x, &(*mx)->prox, Mx);
        }
        else{
            *Mx = malloc(sizeof(struct lligada));
            (*Mx)->valor = l->valor;
            splitQS(l->prox, x, mx, &(*Mx)->prox);
        }
    }
}

//Exercício 9//
LInt parteAmeio(LInt *l){
    LInt ant, pt;
    ant = NULL;
    for (int tam = 0, *l; pt; pt = pt->prox, tam++);
    pt = *l;
    for (int i = 0; *l && i < tam / 2; i++){
        ant = *l; //serve para guardar a primeira metade de l antes de ser dividida
        *l = (*l)->prox;
    }
    if (ant) ant->prox = NULL; // vai separar as duas listas com um NULL
    else pt = NULL;
    return pt; //pt é a segunda lista
}

//Exercício 10//
int removeAll(LInt *l, int x){
    LInt ant, pt;
    int r = 0;
    if(*l){
        ant = NULL;
        pt = *l;
        while(pt){ //enquanto pt não for nulo
            if(ant && pt->valor == x){ //não é o primeiro elemento da lista
                ant->prox = pt->prox; //estamos a saltar o pt para o eliminarmos mais tarde
                free(pt);
                pt = ant; //nas linhas 160 a 162 estamos a reajustar a lista depois de eliminarmos o pt
                ant = pt;
                pt = pt->prox;
                ++r; //é igual se for "r++"
            }
            else if(pt->valor == x){ //é o primeiro elemento da lista
                pt = (*l)->prox; //estamos a definir o pt para o próximo elemento da lista
                free(*l);
                *l = pt; //redefinição da lista após o elemento ter sido eliminado
                ++r;
            }
            else{ //este "else" acontece se o "x" não for igual ao pt e assim avançamos para o próximo elemento
                ant = pt;
                pt = pt->prox;
            }
        }
    }
    return r;
}

//Exercício 11//
int removeDups (LInt *l){
    LInt ant, pt, pr;
    if(*l){
        pt = *l;
        while(pt){
            ant = pt; //serve para indicar que o ant antecede sempre o pt
            pr = pt->prox;
            while(pr){
                if(pt->valor == pr->valor){
                    ant->prox = pr->prox;
                    free(pr);
                    pr = ant->prox; //serve para indicar que o pr vai tomar a posição do pt
                }
                else{ //avança para o próximo elemento
                    ant = pr;
                    pr = pr->prox;
                }
            }
        }
    }
    return *l;
}

//Exercício 12//
int removeMaiorL (LInt *l){
    LInt ant, pt;
    ant = NULL;
    int maior;
    maior = (*l)->valor;
    for(pt = *l; pt; pt = pt->prox){
        if(pt->valor > maior) maior = pt->valor;
    }
    if(ant){ // se não for o primeiro elemento da lista
        ant->prox = pt->prox;
        free(pt);
    }
    else{
        pt = pt->prox;
        free(*l);
        *l = pt;
    }
    return maior;
}

//Exercício 13//
void init (LInt *l){
    LInt pt, ant;
    if(*l){
        pt = *l;
        ant = NULL;
        for(; pt->prox; ant = pt, pt = pt->prox);
        if(ant){
            free(pt);
            ant->prox = NULL;
        }
    }
}

//Exercício 14//
void appendL (LInt *l, int x){
    LInt pt, new;
    for(pt = *l; pt && pt->prox; pt = pt->prox); //a segunda parte do for tem haver se pt ou pt->prox forem NULL
    new = malloc(sizeof(struct lligada)); //o new saca como deve funcionar
    new->valor = x;
    new->prox = NULL;
    if(!pt) *l = new; //se a lista estava vazia, agora passou de estar
    else pt->prox = new;
}

//Exercício 15//
void concatL (LInt *a, LInt b){
    LInt pt;
    if(*a){
        pt = *a;
        for(; pt->prox; pt = pt->prox);
        pt->prox = *b;
    } else *a = b;
}

//Exercício 16//
LInt cloneL(LInt l){
    LInt r = NULL;
    if(l){
        r = malloc(sizeof(struct lligada));
        r->valor = l->valor;
        r->prox = cloneL(l->prox);
    }
    return r;
}

//Exercício 17//
LInt cloneRev (LInt l){
    LInt r;
    while(l){
        LInt pt = malloc(sizeof(struct lligada));
        pt->valor = l->valor;
        pt->prox = r;
        r = pt;
        pt = pt->prox;
    }
    return r;
}

//Exercício 18//
int maximo (LInt l){
    int max = l->valor;
    l = l->prox;
    for(; l; l = l->prox){
        if(l->valor < max) max = l->valor;
    }
    return max;
}

//Exercício 19//
int take (int n, LInt *l){
    int cmp = 0;
    LInt pt = *l;
    LInt temp;
    while(pt && pt->valor == n){
        temp = pt;
        pt = pt->prox;
        free(temp);
        cmp++;
    }
    *l = pt; //atualiza o ponteiro para o início da lista
    if(pt){ //chama recursivamente take para continuar removendo elementos
        cmp += take(n, &pt);
    }
    return cmp;
}

//Exercício 20//
int drop (int n, LInt *l){
    int nd;
    LInt next;
    for(nd = 0; *l && (*l)->prox && n>0; n--){
        next = (*l)->prox;
        free(*l);
        *l = next;
        nd++;
    }if(*l && !(*l)->prox && n>0){
        ++nd;
        free(*l);
    }
    return nd;
}

//Exercício 21//
LInt Nforward (LInt l, int n){
    for(; l && n>0; n--, l = l->prox);
    return l;
}

//Exercício 22//
int listToArray (LInt l, int v[], int n){
    int i = 0;
    for(; l && i<n; l = l->prox, i++){
        v[i] = l->valor;
    }
    return i;
}

//Exercício 23//
LInt arrayToList (int v[], int n){
    LInt l = NULL;
    while(n>0){
        l = malloc(sizeof(struct lligada));
        l->valor = v[0];
        l->prox = arrayToList(v+1, n-1); //"v+1" indica que o array começa a partir do segundo elemento
        n--;
    }
    return l;
}

//Exercício 24//
LInt somasAcL (LInt l){
    int soma = 0;
    LInt r, pt;
    if(l){
        r = malloc(sizeof(struct lligada));
        pt = r;
        while(l){
            soma += l->valor;
            pt->valor = soma;
            if(l->prox){
                pt->prox = malloc(sizeof(struct lligada));
                pt = pt->prox;
            }
            l = l->prox;
        }
        pt->prox = NULL;
    }
    return r;
}
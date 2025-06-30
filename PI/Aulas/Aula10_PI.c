//Ficha 10//

typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} * ABin;

//Exercício 1//
//Alínea a//
ABin removeMenor (ABin *a){
    if (*a == NULL) return NULL;
    else if ((*a)->esq == NULL){
        ABin temp = *a;
        *a = (*a)->dir;
        free(temp);
        return *a;
    } else return removeMenor(&((*a)->esq));
}

//Alínea b//
void removeRaiz (ABin *a){
    if (*a != NULL){
        ABin temp = removeMenor((*a)->dir);
        temp->esq = (*a)->esq;
        temp->dir = (*a)->dir;
        free(*a);
        *a = temp;
    }
}

//Alínea c//
int removeElem(ABin *a, int x) {
    if (*a == NULL) return 1;
    else if ((*a)->valor == x) {
        ABin temp = *a;
        if ((*a)->esq == NULL) *a = (*a)->dir;
        else if ((*a)->dir == NULL) *a = (*a)->esq;
        else {
            ABin temp = removeMenor(&((*a)->dir));
            (*a)->valor = temp->valor;
        }
        free(temp);
        return 0;
    }else if (x < (*a)->valor) return removeElem(&((*a)->esq), x);
    else return removeElem(&((*a)->dir), x);
}
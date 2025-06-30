#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAZIO -1
#define DELETADO -2
#define MAX_TENTATIVAS 100

typedef struct {
    int *array;
    int capacidade;
} TabelaHash;

typedef struct Node {
    int chave;
    struct Node *proximo;
} Node;

typedef struct {
    Node **array;
    int capacidade;
} TabelaHashLINK;

typedef struct {
    int *tabela1;
    int *tabela2;
    int capacidade;
} TabelaHashCUCKOO;

TabelaHash* criarTabelaHashOPEN(int capacidade) {
    TabelaHash *tabela = (TabelaHash*) malloc(sizeof(TabelaHash));
    tabela->capacidade = capacidade;
    tabela->array = (int*) malloc(capacidade * sizeof(int));
    for (int i = 0; i < capacidade; i++) {
        tabela->array[i] = VAZIO;
    }
    return tabela;
}

TabelaHashLINK* criarTabelaHashLINK(int capacidade) {
    TabelaHashLINK *tabela = (TabelaHashLINK*) malloc(sizeof(TabelaHashLINK));
    tabela->capacidade = capacidade;
    tabela->array = (Node**) malloc(capacidade * sizeof(Node*));
    for (int i = 0; i < capacidade; i++) {
        tabela->array[i] = NULL;
    }
    return tabela;
}

TabelaHashCUCKOO* criarTabelaHashCUCKOO(int capacidade) {
    TabelaHashCUCKOO* t = malloc(sizeof(TabelaHashCUCKOO));
    t->capacidade = capacidade;
    t->tabela1 = malloc(capacidade * sizeof(int));
    t->tabela2 = malloc(capacidade * sizeof(int));
    for (int i = 0; i < capacidade; i++) {
        t->tabela1[i] = VAZIO;
        t->tabela2[i] = VAZIO;
    }
    return t;
}

Node* criarNode(int chave) {
    Node *novoNode = (Node*) malloc(sizeof(Node));
    novoNode->chave = chave;
    novoNode->proximo = NULL;
    return novoNode;
}

int h1LINK(TabelaHashLINK *tabela, int chave) {
    return chave % tabela->capacidade;
}

int h1CUCKOO(int chave, int capacidade) {
    return chave % capacidade;
}

int h1(TabelaHash *tabela, int chave) {
    return chave % tabela->capacidade;
}

int h2(int chave, int capacidade) {
    return (chave / capacidade) % capacidade;
}

int existeChave(TabelaHash *tabela, int chave) {
    for (int i = 0; i < tabela->capacidade; i++) {
        if (tabela->array[i] == chave) {
            return 1;
        }
    }
    return 0;
}

int findKeyIndex(TabelaHash *tabela, int chave) {
    for (int i = 0; i < tabela->capacidade; i++) {
        if (tabela->array[i] == chave) {
            return i;
        }
    }
    return -1;
}

int isSlotAvailable(TabelaHash *tabela, int indice) {
    return tabela->array[indice] == DELETADO || tabela->array[indice] == VAZIO;
}

int moveOpen(TabelaHash *tabela, int chave) {
    int indiceHash = h1(tabela, chave);
    int indiceAtual = findKeyIndex(tabela, chave);

    if (indiceAtual == -1) {
        return 0;
    }

    if (indiceAtual == indiceHash) {
        return 1;
    }

    int indiceProcurado = indiceHash;
    do {
        if (isSlotAvailable(tabela, indiceProcurado)) {
            tabela->array[indiceProcurado] = chave;
            tabela->array[indiceAtual] = DELETADO;
            return 1;
        }
        indiceProcurado = (indiceProcurado + 1) % tabela->capacidade;
    } while (indiceProcurado != indiceAtual);

    return 0;
}

int inserirOPEN(TabelaHash *tabela, int chave) {
    if (existeChave(tabela, chave)) {
        printf("%d EXISTS\n", chave);
        if (!moveOpen(tabela, chave)) {
            printf("GIVING UP!\n");
            return 1;
        }
        return 0;
    } else {
        int indice = h1(tabela, chave);
        int inicial = indice;
        do {
            if (tabela->array[indice] == VAZIO || tabela->array[indice] == DELETADO) {
                tabela->array[indice] = chave;
                printf("%d -> %d\n", indice, chave);
                printf("OK\n");
                return 0;
            }
            indice = (indice + 1) % tabela->capacidade;
        } while (indice != inicial);
        printf("GIVING UP!\n");
        return 1;
    }
}

void deletarOPEN(TabelaHash *tabela, int chave) {
    int indice = -1;
    for (int i = 0; i < tabela->capacidade; i++) {
        if (tabela->array[i] == chave) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        tabela->array[indice] = DELETADO;
        printf("OK\n");
    } else {
        printf("NO\n");
    }
}

void checarOPEN(TabelaHash *tabela, int chave) {
    moveOpen(tabela, chave);

    int i = 0;
    while (i < tabela->capacidade && tabela->array[i] != chave) {
        i++;
    }

    if (i < tabela->capacidade) {
        printf("%d\n", i);
    } else {
        printf("NO\n");
    }
}

void imprimirTabelaOPEN(TabelaHash *tabela) {
    for (int i = 0; i < tabela->capacidade; i++) {
        if (tabela->array[i] != VAZIO && tabela->array[i] != DELETADO) {
            printf("%d\t%d\n", i, tabela->array[i]);
        } else if (tabela->array[i] == DELETADO) {
            printf("%d\tD\n", i);
        }
    }
}

void metodoOPEN(TabelaHash *tabela) {
    char comando[10];
    int chave;

    while (scanf("%s", comando) == 1) {
        if (strcmp(comando, "END") == 0) {
            break;
        } else if (strcmp(comando, "I") == 0) {
            if (scanf("%d", &chave) != 1) {
                continue;
            }
            if (inserirOPEN(tabela, chave) == 1) {
                break;
            }
        } else if (strcmp(comando, "D") == 0) {
            if (scanf("%d", &chave) != 1) {
                continue;
            }
            deletarOPEN(tabela, chave);
        } else if (strcmp(comando, "C") == 0) {
            if (scanf("%d", &chave) != 1) {
                continue;
            }
            checarOPEN(tabela, chave);
        } else if (strcmp(comando, "P") == 0) {
            imprimirTabelaOPEN(tabela);
        } else {
            printf("Comando desconhecido.\n");
        }
    }
}

void inserirLINK(TabelaHashLINK *tabela, int chave) {
    int indice = h1LINK(tabela, chave);
    Node *novoNode = criarNode(chave);

    novoNode->proximo = tabela->array[indice];
    tabela->array[indice] = novoNode;

    printf("%d -> %d\n", indice, chave);
    printf("OK\n");
}

void checarLINK(TabelaHashLINK *tabela, int chave) {
    int indice = h1LINK(tabela, chave);
    Node *current = tabela->array[indice];
    int encontrada = 0;

    while (current != NULL) {
        if (current->chave == chave) {
            encontrada = 1;
            break;
        }
        current = current->proximo;
    }

    if (encontrada) {
        printf("%d\n", indice);
    } else {
        printf("NO\n");
    }
}

void deletarLINK(TabelaHashLINK *tabela, int chave) {
    int indice = h1LINK(tabela, chave);
    Node *current = tabela->array[indice];
    Node *prev = NULL;

    // Procurar a chave na lista encadeada
    while (current != NULL && current->chave != chave) {
        prev = current;
        current = current->proximo;
    }

    if (current == NULL) {
        printf("NO\n");
        return;
    }

    if (prev == NULL) {
        tabela->array[indice] = current->proximo;
    } else {
        prev->proximo = current->proximo;
    }

    free(current);
    printf("OK\n");
}

void imprimirTabelaLINK(TabelaHashLINK *tabela) {
    int i = 0;
    while (i < tabela->capacidade) {
        Node *current = tabela->array[i];
        if (current != NULL) {
            printf("%d", i);
            printf(" %d", current->chave);
            current = current->proximo;
            while (current) {
                printf(" %d", current->chave);
                current = current->proximo;
            }
            printf("\n");
        }
        i++;
    }
}

void metodoLINK(TabelaHashLINK *tabela) {
    char comando[10];
    int chave;

    while (scanf("%s", comando) == 1) {
        if (strcmp(comando, "END") == 0) {
            break;
        } else if (strcmp(comando, "I") == 0) {
            if (scanf("%d", &chave) != 1) {
                continue;
            }
            inserirLINK(tabela, chave);
        } else if (strcmp(comando, "D") == 0) {
            if (scanf("%d", &chave) != 1) {
                continue;
            }
            deletarLINK(tabela, chave);
        } else if (strcmp(comando, "C") == 0) {
            if (scanf("%d", &chave) != 1) {
                continue;
            }
            checarLINK(tabela, chave);
        } else if (strcmp(comando, "P") == 0) {
            imprimirTabelaLINK(tabela);
        } else {
            printf("Comando desconhecido.\n");
        }
    }
}

void trocarValores(TabelaHashCUCKOO* t, int* chave_atual, int pos, int tabela) {
    int temp = tabela == 1 ? t->tabela1[pos] : t->tabela2[pos];
    if (tabela == 1) t->tabela1[pos] = *chave_atual;
    else t->tabela2[pos] = *chave_atual;
    printf("%d %d -> %d\n", tabela - 1, pos, *chave_atual);
    *chave_atual = temp;
}

int inserirCuckoo(TabelaHashCUCKOO* t, int chave) {
    int pos1 = h1CUCKOO(chave, t->capacidade);
    int pos2;
    int chave_atual = chave;
    int tabelaAtual = 1;

    for (int tentativas = 0; tentativas < 100; tentativas++) {
        if (tabelaAtual == 1) {
            pos2 = h1CUCKOO(chave_atual, t->capacidade);

            if (t->tabela1[pos1] == VAZIO) {
                t->tabela1[pos1] = chave_atual;
                printf("0 %d -> %d\n", pos1, chave_atual);
                printf("OK\n");
                return 1;
            } else {
                trocarValores(t, &chave_atual, pos1, 1);
                tabelaAtual = 2;
                pos1 = h1CUCKOO(chave_atual, t->capacidade);
            }
        } else {
            if (t->tabela2[pos2] == VAZIO) {
                t->tabela2[pos2] = chave_atual;
                printf("1 %d -> %d\n", pos2, chave_atual);
                printf("OK\n");
                return 1;
            } else {
                trocarValores(t, &chave_atual, pos2, 2);
                tabelaAtual = 1;
                pos1 = h1CUCKOO(chave_atual, t->capacidade);
            }
        }
    }

    printf("GIVING UP!\n");
    return 0;
}

void checarCUCKOO(TabelaHashCUCKOO *t, int chave) {
    for (int i = 0; i < t->capacidade; i++) {
        if (t->tabela1[i] == chave) {
            printf("0\t%d\n", i);
            return;
        }
    }

    for (int i = 0; i < t->capacidade; i++) {
        if (t->tabela2[i] == chave) {
            printf("1\t%d\n", i);
            return;
        }
    }

    printf("NO\n");
}

void deleteCUCKOO(TabelaHashCUCKOO *t, int chave) {
    int pos1 = h1CUCKOO(chave, t->capacidade);
    int pos2 = h2(chave, t->capacidade);
    
    if (t->tabela1[pos1] == chave || t->tabela2[pos2] == chave) {
        if (t->tabela1[pos1] == chave) t->tabela1[pos1] = VAZIO;
        else t->tabela2[pos2] = VAZIO;
        printf("OK\n");
    }else printf("NO\n");
}

void imprimirTabela(int *tabela, int indiceTabela, int capacidade) {
    for (int i = 0; i < capacidade; i++) {
        if (tabela[i] != VAZIO) {
            printf("%d\t%d\t%d\n", indiceTabela, i, tabela[i]);
        }
    }
}

void imprimirTabelaCUCKOO(TabelaHashCUCKOO *t) {
    imprimirTabela(t->tabela1, 0, t->capacidade);
    imprimirTabela(t->tabela2, 1, t->capacidade);
}

void metodoCUCKOO(TabelaHashCUCKOO *tabela) {
    char comando[10];
    int chave, res;

    while (1) {
        res = scanf("%s", comando);

        if (res != 1 || strcmp(comando, "END") == 0) {
            break;
        } else if (strcmp(comando, "I") == 0) {
            res = scanf("%d", &chave);
            if (res != 1) {
                continue;
            }
            inserirCuckoo(tabela, chave);
        } else if (strcmp(comando, "C") == 0) {
            res = scanf("%d", &chave);
            if (res != 1) {
                continue;
            }
            checarCUCKOO(tabela, chave);
        } else if (strcmp(comando, "D") == 0) {
            res = scanf("%d", &chave);
            if (res != 1) {
                continue;
            }
            deleteCUCKOO(tabela, chave);
        } else if (strcmp(comando, "P") == 0) {
            imprimirTabelaCUCKOO(tabela);
        } else {
            printf("Comando desconhecido.\n");
        }
    }
}

int main() {
    int capacidade, res;
    char tipoMetodo[10];

    res = scanf("%d %s", &capacidade, tipoMetodo);
    if (res != 2) return 1;

    TabelaHash *tabela = NULL;
    TabelaHashLINK *tabela1 = NULL;
    TabelaHashCUCKOO *tabela2 = NULL;

    if (strcmp(tipoMetodo, "OPEN") == 0) {
        tabela = criarTabelaHashOPEN(capacidade);
    } else if (strcmp(tipoMetodo, "CUCKOO") == 0) {
        tabela2 = criarTabelaHashCUCKOO(capacidade);
    } else if (strcmp(tipoMetodo, "LINK") == 0) {
        tabela1 = criarTabelaHashLINK(capacidade);
    } else {
        printf("Metodo desconhecido.\n");
        return 1;
    }

    if (tabela != NULL) {
        metodoOPEN(tabela);
        free(tabela->array);
        free(tabela);
    } else if (tabela1 != NULL) {
        metodoLINK(tabela1);
    } else if (tabela2 != NULL) {
        metodoCUCKOO(tabela2);
    }

    return 0;
}
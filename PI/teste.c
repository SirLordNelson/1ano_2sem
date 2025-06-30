///////////////////////////////////////////////Primeiras 50 questões///////////////////////////////////////////////

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

//30
int menosFreq (int v[], int N){
    int r = N;
    int im = v[0];
    for(int i = 0; i < N && r != 1; i++){
        int acc = 0;
        for(int j = 0; j < N; j++){
            if(v[i] == v[j]) acc++;
        }
        if(r > acc){
            r = acc;
            im = v[i];
        }
    }
    return im;
}

//32
int maxCresc (int v[], int N){
    int acc;
    for(int i = 0; i < N; i++){
        if(v[i] < v[i+1]) acc++;
    }
    return acc;
}

// outra resposta mais eficiente:
int maxCresc(int v[], int N){
    int nT = 0;
    int nA = 1;
    for(int r = 0; r < N; r++){
        if (v[r + 1] >= v[r]) nA++;
        else if(nA > nT) nT = nA;
        nA = 1;
    }
    return nT;
}

//33
int elimRep(int v[], int n) {
    int acc = 0;
    for(int i = 0; i < n - 1; i++) {
        if(v[i] == v[i+1]) {
            for(int j = i+1; j < n - 1; j++) {
                v[j] = v[j+1];
            }
            n--;
            acc++;
            i--;
        }
    }
    return acc;
}

//34
int elimRepOrd(int v[], int n) {
    int new = 0; // Inicializa o novo tamanho do array
    for(int i = 0; i < n - 1; i++){
        if(v[i] != v[i+1]) v[new++] = v[i];
    }
    v[new++] = v[n-1];
    return new;
}

//35
int comunsOrd (int a[], int na, int b[], int nb){
    int acc;
    for(int i = 0; i < na; i++){ //percorre a
        for(int j = 0; j < nb; j++){ //percorre b
            if(a[i] == b[j]) acc++;
        }
    }
    return acc;
}
//outra alternativa:

int comunsOrd(int a[], int na, int b[], int nb){
    int rb = 0;
    int ra = 0;
    int comuns = 0;
    while(ra < na && rb < nb){
        if(a[ra] > b[rb]) rb++;
        else if(a[ra] == b[rb]){
            ra++;
            rb++;
            comuns++;
        }else ra++;
    }
    return comuns;
}

//37
int minInd (int v[], int n){
    int acc;
    for(int i = 0; i < n; i++){
        if(v[i] < v[acc]) acc = i;
    }
    return acc;
}

//38
void somasAc (int v[], int Ac [], int N){
    int sum;
    for(int i = 0; i < N; i++){
        Ac[i] = sum += v[i];
    }
}

//structs usado nas próximas questões:
typedef enum movimento {Norte, Oeste, Sul, Este} Movimento;
typedef struct posicao {
    int x, y;
} Posicao;

//47
Posicao posFinal (Posicao inicial, Movimento mov[], int N){
    for(int i = 0; i < N; i++){
        if(mov[i] == Norte) inicial.y++;
        if(mov[i] == Sul) inicial.y--;
        if(mov[i] == Este) inicial.x++;
        else inicial.x--;
    }
    return inicial;
}

//48
int caminho(Posicao inicial, Posicao final, Movimento mov[], int N){
    int nmovX, nmovY, i;
    int movX = inicial.x - final.x;
    int movY = inicial.y - final.y;

    if (movX < 0) nmovX = -movX;
    else nmovX = movX;

    if(movY < 0) nmovY = -movY;
    else nmovY = movY;

    if(nmovX + nmovY > N) N -= nmovX + nmovY;
    else N = nmovX + nmovY;

    for(i = 0; i < nmovX && i < N; i++){
        if (movX < 0) mov[i] = Este;
        else if (movX > 0) mov[i] = Oeste;
    }
    for(; i < N; i++){
        if (movY > 0) mov[i] = Sul;
        else if (movY < 0) mov[i] = Norte;
    }
    return N;
}

//49
int maiscentral(Posicao pos[], int N){
    int ind = 0;
    float dist = sqrt(pos[0].x * pos[0].x + pos[0].y * pos[0].y);
    for(int i = 1; i < N; i++){
        if(dist > sqrt(pos[i].x * pos[i].x + pos[i].y * pos[i].y)){
            dist = sqrt(pos[i].x * pos[i].x + pos[i].y * pos[i].y);
            ind = i;
        }
    }
    return ind;
}

//50 
int vizinhos(Posicao p, Posicao pos[], int N){
    int r = 0;
    for(int i=0; i<N; i++){
        if(p.x == pos[i].x){
            if(p.y == pos[i].y + 1 || p.y == pos[i].y -1) r++;
        } else if(p.y == pos[i].y){
            if(p.x == pos[i].x + 1 || p.x == pos[i].x - 1) r++;
            }
    }
    return r;
}

///////////////////////////////////////////////Últimas 50 questões///////////////////////////////////////////////

typedef struct lligada {
    int valor;
    struct lligada *prox;
} *LInt;

//25
void remreps (LInt l){
    LInt pt;
    LInt pr;
    for(; pt && pt->prox; pt = pt->prox){
        pr = pt->prox;
        if(pt->valor == pr->valor){
            pt->prox = pr->prox;
            free(pr);
            pr = pt;
        }
    }
}

/////////////////////////////////////////////////////Testes//////////////////////////////////////////////////////

//Teste_2022//

//1
int nesimo(int a[], int N, int i){
    isort(a, N);
    for(; i > 0 0; i--);
    return a[i - 1];
}

void isort(int a[], int n) {
    int i, j, aux;
    for (i = 0; i < n; i++) {
        aux = a[i];
        for (j = i; j > 0 && a[j-1] > aux; j--) a[j] = a[j-1];
        a[j] = aux;
    }
}

//2
typedef struct LInt_nodo {
    int valor;
    struct LInt_nodo *prox;
} *LInt;

LInt removeMaiores(LInt l, int x) {
    LInt pt = l;
    LInt ant = NULL;
    while(pt != NULL){
        if(pt->valor > x){
            if(ant == NULL) l = pt->prox;
            else ant->prox = pt->prox;
            LInt temp = pt;
            pt = pt->prox;
            free(temp);
        }else{
            ant = pt;
            pt = pt->prox;
        }
    }
    return l;
}

//3
typedef struct ABin_nodo {
    int valor;
    struct ABin_nodo *esq, *dir;
} *ABin;

LInt caminho(ABin a, int x){
    if(a == NULL) return NULL;

    LInt pt = NULL;
    LInt left = a->esq;
    LInt right = a->dir;
    if(a->valor == x){
        pt = malloc(sizeof(struct LInt_nodo));
        pt->valor = a->valor;
        pt->prox = NULL;
    }else if(left != NULL && left->valor < x) pt = caminho(left, x);
    else if(rigth != NULL) pt = caminho(right,x);

    return pt;
}

//4
void inc(char s[]) {
    int tam = strlen(s);
    int carry = 1;

    for(int i = tam - 1; i >= 0; i--){
        if(s[i] == '9' && carry == 1) s[i] = '0';
        else{
            s[i] += carry;
            carry = 0;
        }
    }
    if(s[0] == '0'){
        memmove(s + 1, s, tam + 1); //"memmove" copia um bloco de bytes de uma localização de memória para outra
        s[0] = '1';
    }
}

//5
int sacos(int p[], int N, int C){
    int peso;
    int nsacos;
    
    for(int i = 0; i < N; i++){
        if(peso + p[i] <= C) peso = peso + p[i];
        else{
            nsacos++;
            peso = p[i];
        }
    }
    if(peso > 0) sacos++;

    return nsacos;
}


//Exame_2022

//1
int pesquisa (int a[], int N, int x){
    for(int i = 0; i < N; i++){
        if(a[i] == x) return i;
    }
    if(a[i] != x) return -1;
}

//esta alternativa será melhor:
int pesquisa(int a[], int N, int x) {
    int esquerda = 0;
    int direita = N - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        if (a[meio] == x) return meio;
        else if (a[meio] < x) esquerda = meio + 1;
        else direita = meio - 1;
    }

    return -1;
}

//2
typedef struct LInt_nodo {
    int valor;
    struct LInt_nodo *prox;
} *LInt;

void roda (LInt *l){
    if (*l == NULL || (*l)->prox == NULL) return; //numa "void" nunca só colocamos "return" sem mais nada a seguir

    LInt pt = *l;
    LInt ant = NULL;

    for(; pt->prox != NULL; pt = pt->prox){
        ant = pt;
    }
    if(ant != NULL) ant->prox = NULL;
    pt->prox = *l; //o "*l" simboliza o início da lista l
    *l = pt;
}

//3
typedef struct ABin_nodo {
    int valor;
    struct ABin_nodo *esq, *dir;
} *ABin;

int apaga(ABin *a, int n) {
    if(*a == NULL || n <= 0) return 0;
    ABin temp = *a;
    int count = 0;
    if(temp->esq != NULL && count < n) count += apaga(&(temp->esq), n - count);
    if(temp->dir != NULL && count < n) count += apaga(&(temp->dir), n - count);
    if(count < n) {
        *a = NULL;
        free(temp);
        count++;
    }
    return count;
}

//4
void checksum (char s[]){
    int tam = strlen(s);
    int soma = 0;

    // Calcular a soma de acordo com o método de Luhn
    for(int i = tam - 1; i >= 0; i--) {
        int digit = s[i] - '0'; // Converter caractere para dígito numérico
        if((tam - i) % 2 == 0){ // Posição par (a partir do final)
            digit *= 2;
            if (digit > 9) digit -= 9;
        }
        soma += digit;
    }
    // Calcular o dígito de controle
    int checkDigit = (10 - (soma % 10)) % 10;
    // Adicionar o dígito de controle ao final da string
    s[tam] = '0' + checkDigit;
    s[tam + 1] = '\0';
}

//5
int escolhe(int N, int valor[], int peso[], int C, int quant[]){
    memset(quant, 0, N * sizeof(int)); // Inicializar o array quant com 0
    int valor_total = 0;
    int capacidade_restante = C;

    // Usar uma abordagem gulosa baseada na razão valor/peso
    while(capacidade_restante > 0){
        int melhor_indice = -1;
        double melhor_valor_peso = 0.0;
        // Encontrar o item com a melhor razão valor/peso que ainda cabe na mochila
        for(int i = 0; i < N; i++){
            if(peso[i] <= capacidade_restante){
                double valor_peso = (double)valor[i] / peso[i];
                if(valor_peso > melhor_valor_peso){
                    melhor_valor_peso = valor_peso;
                    melhor_indice = i;
                }
            }
        }
        // Se nenhum item pode ser adicionado, sair do loop
        if (melhor_indice == -1) break;
        // Adicionar o item escolhido
        quant[melhor_indice]++;
        capacidade_restante -= peso[melhor_indice];
        valor_total += valor[melhor_indice];
    }
    return valor_total;
}


//Teste_2023

//1
int perfeito(int x){
    int div;

    for(int i; i < x; i++){
        if(x % i == 0) div = i + div;
    }
    if(div == x) return 1;
    else return 0;
}

//2
typedef struct {
    int x,y;
} Ponto;

int distancia(Ponto p){
    return (p.x * p.x) + (p.y * p.y);
}

int comparaPontos(const void *a, const void *b) {
    Ponto *pontoA = (Ponto *)a;
    Ponto *pontoB = (Ponto *)b;
    int distanciaA = distanciaQuadrada(*pontoA);
    int distanciaB = distanciaQuadrada(*pontoB);

    return distanciaA - distanciaB;
}

void ordena(Ponto pos[], int N) {
    qsort(pos, N, sizeof(Ponto), comparaPontos);
}

//3
typedef struct abin_nodo {
    int valor;
    struct abin_nodo *esq, *dir;
} *ABin;

int depth(ABin a, int x) {
    int acc = 0;

    if(a == NULL) return -1;
    if(a->valor == x) return acc;

    int esq, dir;

    if(a->esq != NULL){
        esq = depth(a->esq, x);
        if(esq != -1) return esq + 1; // Se encontrado, retorna o nível encontrado + 1
    }

    if(a->dir != NULL){
        dir = depth(a->dir, x);
        if(dir != -1) return dir + 1; // Se encontrado, retorna o nível encontrado + 1
    }

    return -1;
}

//4
int wordle(char secreta[], char tentativa[]){
    int acerto = 0;
    int length = 0;
    
    while(secreta[len] != '\0'){
        length++;
    }

    int usada[len];
    for (int i = 0; i < len; i++) {
        usada[i] = 0;
    }
    // Primeira passagem: letras corretas na posição correta
    for (int i = 0; i < len; i++) {
        if (tentativa[i] == secreta[i]) {
            tentativa[i] = toupper(tentativa[i]);
            usada[i] = 1;
            acertos++;
        }
    }
    // Segunda passagem: letras corretas em posição incorreta
    for (int i = 0; i < len; i++) {
        if (islower(tentativa[i])) {
            int encontrado = 0;
            for (int j = 0; j < len; j++) {
                if (!usada[j] && tentativa[i] == secreta[j]) {
                    encontrado = 1;
                    usada[j] = 1;
                    break;
                }
            }
            if (!encontrado) tentativa[i] = '*';
        }
    }
    return acertos;
}

//5
typedef struct lint_nodo {
    int valor;
    struct lint_nodo *prox;
} *LInt;

// Função para criar um novo nodo da lista
LInt novoNodo(int valor){
    LInt novo = (LInt)malloc(sizeof(struct lint_nodo));
    if(novo != NULL){
        novo->valor = valor;
        novo->prox = NULL;
    }
    return novo;
}

LInt periodica(char s[]){
    int len = strlen(s);
    int i, start = -1, end = -1;
    // Encontrar os parênteses que delimitam a parte periódica
    for(i = 0; i < len; i++){
        if(s[i] == '(') start = i + 1;
        if(s[i] == ')') end = i;
    }
    // Verificar se encontramos parênteses válidos
    if(start == -1 || end == -1 || start >= end) return NULL; // String inválida ou sem parte periódica
    // Construir a lista circular com os dígitos entre start e end
    LInt head = NULL, tail = NULL;
    for(i = start; i < end; i++){
        LInt novo = novoNodo(s[i] - '0'); // Converter caractere para inteiro
        if (head == NULL) head = novo;
        else tail->prox = novo;
        tail = novo;
    }
    // Tornar a lista circular
    if(tail != NULL) tail->prox = head;

    return head;
}


//Exame_2023

//1
// Função auxiliar para verificar se um número é um quadrado perfeito
int isPerfectSquare(int n) {
    int s = (int)sqrt(n);
    return (s * s == n);
}

// Função para verificar se um número é um número de Fibonacci
int isFib(int x) {
    // Aplicar a propriedade matemática
    int test1 = 5 * x * x + 4;
    int test2 = 5 * x * x - 4;

    // Verificar se qualquer um dos testes é um quadrado perfeito
    return isPerfectSquare(test1) || isPerfectSquare(test2);
}

//2
typedef struct {
    float teste, minis;
} Aluno;

// Função para arredondar a nota final
int arredondaNota(float nota) {
    return (int)round(nota);
}

// Função para calcular a moda das notas finais
int moda(Aluno turma[], int N) {
    int freq[21] = {0}; // Array para armazenar frequências das notas 0 a 20
    // Calcular a frequência das notas finais
    for(int i = 0; i < N; i++){
        float notaFinal = turma[i].teste * 0.8 + turma[i].minis * 0.2;
        int notaArredondada = arredondaNota(notaFinal);
        if(notaArredondada < 9.5) freq[0]++; //se não tiver passado adicionamos um 0 no array
        else freq[notaArredondada]++; //se não tiver passado adicionamos um 0 no array, senão 
    }
    // Encontrar a nota mais frequente (moda)
    int modaNota = 0;
    int maxFreq = freq[0];
    for(int i = 1; i < 21; i++){
        if(freq[i] > maxFreq){
            maxFreq = freq[i];
            modaNota = i;
        }
    }
    return modaNota;
}

//3
typedef struct lint_nodo {
    int valor;
    struct lint_nodo *prox;
} *LInt;

int take(int n, LInt *l) {
    if(n <= 0 || *l == NULL) return 0; // Não há nodos para remover

    LInt atual = *l;
    int count = 1; // Contador para o número de nodos removidos
    // Avança até o n-ésimo nodo ou até o fim da lista
    while(count < n && atual->prox != NULL){
        atual = atual->prox;
        count++;
    }
    // Verifica se chegamos ao n-ésimo nodo
    if(count == n){
        // Libera a memória dos nodos além do n-ésimo
        LInt prox = atual->prox;
        while(prox != NULL){
            LInt proximo = prox->prox;
            free(prox);
            prox = proximo;
            count++;
        }
        // Atualiza o ponteiro do último nodo para NULL
        atual->prox = NULL;
    }
    return count - n; // Retorna o número de nodos removidos
}

//4
int verifica(char frase[], int k) {
    int i = 0;
    int caracteres = 0;
    int todas_com_k = 1; //Inicialmente assume que todas as palavras têm pelo menos k caracteres

    while(frase[i] != '\0'){
        if(!isspace(frase[i])) caracteres++; //Conta caracteres
        else{
            if(caracteres < k) todas_com_k = 0; //Define todas_com_k para 0 se uma palavra tiver menos de k caracteres
            caracteres = 0; //Reinicia a contagem para a próxima palavra
        }
        i++;
    }
    //Verifica a última palavra
    if(caracteres < k) todas_com_k = 0;

    return todas_com_k;
}

//5
typedef struct abin_nodo {
    int valor;
    struct abin_nodo *esq, *dir;
} *ABin;

// Função auxiliar para criar um novo nodo da árvore
ABin novoNodo(int valor){
    ABin novo = (ABin)malloc(sizeof(struct abin_nodo));
    if(novo != NULL){
        novo->valor = valor;
        novo->esq = novo->dir = NULL;
    }
    return novo;
}

// Função para reconstruir a árvore a partir da string de travessia pré-ordem
ABin reconstroi_aux(char s[], int *pos) {
    if(s[*pos] == '*' || s[*pos] == '\0'){
        (*pos)++; // Avança para o próximo caractere
        return NULL;
    }

    // Converte o caractere para inteiro
    int valor = s[*pos] - '0';
    (*pos)++; // Avança para o próximo caractere
    // Cria um novo nodo com o valor atual
    ABin nodo = novoNodo(valor);
    // Reconstrói a subárvore esquerda
    nodo->esq = reconstroi_aux(s, pos);
    // Reconstrói a subárvore direita
    nodo->dir = reconstroi_aux(s, pos);

    return nodo;
}

// Função principal para reconstruir a árvore
ABin reconstroi(char s[]){
    int pos = 0;
    return reconstroi_aux(s, &pos);
}

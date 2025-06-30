#include <stdio.h>

void linha (int n) {
    int i = 0 ;
    while (i != n) {     // posso usar recursividade, mas sem o "while", pq o "while" é um ciclo e é estúpido usar recursividade num ciclo //
        putchar ('#');
        i++;
    }
    if (i == n)
    printf ("\n");
}


int main () {
    int n;
    scanf ("%d", &n);
    linha (n);
    return 0;
}

// Ficha 1 //

// Exercício 3 //

// Alínea 1 //

void quadrado (int n) {
    int i = n;
    while (i != 0) {
        linha (n);
        i--;
    }
}

int main () {
    int n;
    scanf ("%d", &n);
    quadrado (n);
    return 0;
}

// Alínea 2 //

void nop (int n, int l) { // "l" é a linha a ser desenhada //
    char par, impar, i;
    if (l % 2 == 0) {
        par = '#';
        impar = '_';
    } else {
        par = '_';
        impar = '#';
    }
    i = 0;
    while (i < n) {
        if (i % 2 == 0)
            putchar (par);
        else putchar (impar);
        i++;
    }
}

void xadrez (int n) {
    int i = 0; // número de linhas já desenhado //
    while (i < n) {
        nop (n, i);
        i++;
        putchar ('\n');
    }
}

int main () {
    int n;
    scanf ("%d", &n);
    xadrez (n);
    return 0;
}

// Alínea 3 //

// Triângulo Vertical //
void hip (int n) {
    int i, j;
    i = 1;
    while (i <= n) { //desenhar a linha i //
        j = 0; // número de caracteres na linha //
        while (j != i) {
            putchar ('#');
            j++;
        }
    putchar ('\n');
    i++;
    }
}

void cat (int n) {
    int i, j;
    i = n;
    while (i > 0) {
        j = 1;
        while (j < i) {
            putchar ('#');
            j++;
        }
    i--;
    putchar ('\n');
    }
}

int main () {
    int n = 4;
    hip (n);
    cat (n);
    return 0;
}

// Triângulo horizontal //
int main() {
    int altura;
    scanf("%d", &altura);
    // Loop para cada linha do triângulo
    for (int linha = 1; linha <= altura; linha++) {
        // Loop para imprimir os espaços em branco
        for (int espaco = 1; espaco <= altura - linha; espaco++) {
            printf(" ");
        }
        // Loop para imprimir os caracteres #
        for (int caractere = 1; caractere <= 2 * linha - 1; caractere++) {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}

// Exercício 4 //

int desenharCirculo(int raio) {
    int contador = 0; // Variável para contar o número de '#' impressos
    // Loop para percorrer as linhas do círculo
    for (int linha = -raio; linha <= raio; linha++) {
        // Loop para percorrer as colunas do círculo
        for (int coluna = -raio; coluna <= raio; coluna++) {
            // Verifica se o ponto está dentro do círculo usando a equação do círculo: x^2 + y^2 <= raio^2
            if (coluna * coluna + linha * linha <= raio * raio) {
                printf("#"); // Imprime '#' se estiver dentro do círculo
                contador++; // Incrementa o contador
            } else {
                printf(" "); // Imprime espaço em branco se estiver fora do círculo
            }
        }
        printf("\n"); // Move para a próxima linha após desenhar uma linha do círculo
    }
    return contador; // Retorna o número total de '#' impressos
}
/*
    O loop para desenhar o círculo é onde percorremos cada ponto dentro de um quadrado com lados de comprimento 2 * raio + 1, 
representando a área onde o círculo será desenhado. 
    O loop externo for percorre as linhas do quadrado. Começa de -raio e vai até raio, pois estamos considerando os pontos no intervalo [-raio, raio]. 
Isso nos dá o número correto de linhas para desenhar o círculo.
    O loop interno for percorre as colunas do quadrado. Também começa de -raio e vai até raio, 
cobrindo todas as colunas necessárias para desenhar o círculo em cada linha.
*/
#include <stdio.h>
#include <ctype.h>
#include <math.h>

// Primeiras 50 Questões //

// Exercício 1 //
int maior(){
    int n, big;
    scanf("%d", &n);

    while(n != 0){
        if(big < n) big = n;
        scanf("%d", &n);
    }

    printf("%d\n", big);
    return 0;
}

// Exercício 2 //
int media(){
    int n;
    int z = 0;
    int m = 0;
    scanf("%d", &n); //recebe um valor

    while(n != 0){
        m = n + m;
        z++;
        scanf("%d", &n); // vai lendo os valores recebidos
    }

    n = m / z;
    printf("%d\n", n);
    return 0;
}

// Exercício 3 //
int smaior(){
    int n, fst, snd;
    scanf("%d", &n);

    while(n != 0){
        if(fst < n){
            snd = fst;
            fst = n;
        }
        else if(snd == fst || n > snd){
            snd = n;
        }
        scanf("%d", &n);
    }

    printf("%d\n", snd);
    return 0;
}

// Exercício 4 //
int bitsUm (unsigned int n){
    int aux = 0;

    while(n != 0){
        if(n%2 == 1) aux++;
        n = n / 2; // n tem que ser dividido por 2 para poder voltar a dividir por 2
    }
    return aux;
}

// Exercício 5 //
int trailingZ (unsigned int n){
    int aux = -1;
    int m = 1;

    while(n%m == 0){
        aux++;
        m = m*2;
    }
    return aux;
}

// Exercício 6 //
int qDig (unsigned int n){
    int aux = 0;

    while(n != 0){
        n = n%10;
        aux++;
    }
    return aux;
}// primeiro exercício que fiz todo sozinho e todo bem à primeira

// Exercício 7 //
char *strcat (char s1[], char s2[]){
    for(int i = 0; s1[i]; i++);
    for(int j = 0; s2[j]; j++) s1[i+j] = s2[j]; // o s2[j] indica que "j" vem do array s2[]
    s1[i+j] = "\0"; //estamos a adicionar manualmente o final da frase
    return s1;
}

// Exercício 8 //
char *strcpy (char *dest, char source[]){
    for(int i = 0; source[i]; i++) *(dest + i) = source[i]; // na última parte do código, o "*(dest + i)" está a substituir cada elemento de dest pelos elementos de source, progressivamente
    *(dest + 1) = "\0";
    return dest;
}

// Exercício 9 //
int strcmp (char s1[], char s2[]){
    for(int i = 0; s1[i] == s2[i] && s1[i]; i++); // em "s1[i]" está a ver qnd acaba em "\0"
    return s1[i]-s2[i];
}

// Exercício 10 //
char *strstr (char s1[], char s2[]){
    int ps1 = 0;
    int ps2 = 0;
    char *pos = s1; // os elementos de "pos" são iguais aos de "s1"

    while(s1[ps1] && s2[ps2]){ // o que está dentro de parênteses confirma se os dois arrays não são diferentes
        if(s1[ps1] == s2[ps2]){
            ps2++;
            if(pos == NULL) pos = s1+ps1; // se não for encontrado, à primeira, avança-se para o próximo elemento
        }
        else{
            ps2 = 0;
            pos = NULL;
        }
        ps1++;
    }
    if(s2[ps2] == 0) pos = NULL;

    return pos;
}

// Exercício 11 //
void strrev (char s[]){
    char rs;

    for(int i=0; s[i]; i++); // indica o comprimento da string
    for(int j=0; j<i/2; j++){ // este loop percorre a primeira metade da string s, que será trocada com a segunda metade para reverter a string
        rs = s[j]; // atribui o caracter de s[j] a rs
        s[j] = s[i-j-1]; // substitui o caracter de s[j] com o seu simétrico
        s[i-j-1] = rs; // o rs serve só para guardar os valores que irão para s
    }
}

// Exercício 12 //
void strnoV (char s[]){
    int w = 0;

    for(int i = 0; s[i]; i++){
        if(!isVowel(s[i])) s[w++] = s[i]; // s[w++] recolhe o valor w em s e, de seguida, w+1
    s[w] = "\0";
    }
}

// Exercício 13 //
void truncW (char t[], int n){
    int i = 0; // contador de nº de caracteres numa palavra
    int r = 0; // percorre o array t
    int w = 0; // marca a posição atual de t

    while(t[r]){
        if(t[r] == ' '){
            t[w] = t[r];
            w++;
            r++;
        }else if(i < n){
            t[w] = t[r];
            i++;
            w++;
            r++;
        }else r++;
    }
    t[w] = '\0';
}

// Exercício 14 //
char charMaisfreq (char s[]){
    char freq;
    int r = 0;
    int w = 0;

    for(int i = 0; s[i]; i++){ // percorre cada caracter da string
        for(int j = 0; s[j]; j++){ // faz o mm que o for anterior enquanto conta as ocorrências de cada caracter
            if(s[i] == s[j]) w++; // vai contar o nº de vezes que um caracter aparece
        }
        if(w > r){ // serve para confirmar se o caracter atual é mais frequente que o outro mais frequente
            r = w;
            freq = s[i]; // estas duas linhas servem para atualizar o r com o valor de w e para armazenar o caracter atual em freq
        }
        w = 0; // fazemos reset no w para voltar a ser usado no primeiro for
    }
    if(!s[0]) freq = 0;

    return freq;
}

// Exercício 15 //
int iguaisConsecutivos (char s[]){
    int acc = 0;
    int t = 0;

    for(int i = 0; s[i] && s[i+1]; i++){
        if(s[i] == s[i+1]) acc++;
        }

    return acc;
} // segundo exercício que fiz que está todo bem à primeira
// alternativa:
int iguaisConsecutivos(char s[])
{
    int sum, sumA, i;
    sum = 0; // armazena o valor máx de caracteres consecutivos
    sumA = 1; // representa a quantidade atual de caracteres iguais
    i = 0;
    while (s[i])
        if (s[i] == s[i + 1])
        {
            sumA++;
            i++;
        }
        else
        {
            if (sumA > sum)
                sum = sumA; // neste if, confirma-se se sumA é maior que sum e, se for, damos o valor de sumA a sum
            sumA = 1;
            i++;
        }
    return sum;
}


// Exercício 16 //
int difConsecutivos (char s[]){
    int acc = 0;
    int t = 0;
    int ctl = 0; // controla o fluxo do loop interno

    for(int x = 0; s[x]; x++){ // cada iteração desse loop define o início de uma sequência de caracteres consecutivos
        ctl = 1;
        for(int i = x; s[i] && ctl; i++){ // cada iteração desse loop representa um ponto de partida para uma possível sequência de caracteres consecutivos
            t = 1;
            for(int j = x; s[j] && ctl; j++){ // este loop itera sobre os caracteres da string começando da posição atual x
                if(s[j] != s[i]) ctl = 0;
                else t++;
            }
        }
        if(t > acc) acc = t;
    }

    return acc;
}

// Exercício 17 //
int maiorPrefixo (char s1 [], char s2 []){
    int acc = 0;

    for(int i = 0; s1[i] && s2[i]; i++){
        if(s1[i] == s2[i]) acc++;
    }

    return ;
} // terceiro exercício que fiz que está todo bem
// alternativa:
int maiorPrefixo(char s1[], char s2[])
{
    int i;
    for (i = 0; s1[i] == s2[i] && s1[i]; i++)
        ;
    return i;
}

// Exercício 18 //
int maiorSufixo (char s1 [], char s2 []){
    int acc = 0;

    for(int i = 0; s1[i]; i++)
    for(int j = 0; s2[j]; j++)
    while(s1[i--] == s2[j--]) acc++;

    return acc;
}

// Exercício 19 //
int sufPref(char s1[], char s2[]){
    int r = 0;
    int t = 0;

    for (int i = 0; s1[i]; i++){
        if (s1[i] == s2[r++]) t++;
        else t = r = 0;
    }

    return t;
}

// Exercício 20 //
int contaPal (char s[]){
    int acc = 0;

    for(int i = 0; s[i]; i++){
        if(!isspace(s[i]) && s[i+1]) acc++;
        else if(!isspace(s[i]) && isspace(s[i+1])) acc++; // aqui está a ser indicado o final de uma palavra, pois se "isspace(s[i+1])" for V, então há um espaço
    }

    return acc;
}

// Exercício 21 //
int contaVogais (char s[]){
    int acc = 0;

    for(int i = 0; s[i]; i++){
        if(i = 'a' || i = 'e' || i = 'i' || i = 'o' || i = 'u' || i = 'A' || i = 'E' || i = 'I' || i = 'O' || i = 'U') acc++;
    }

    return acc;
} // quarta que fiz toda bem
// isVowel é uma função que existe

// Exercício 22 //
int contida (char a[], char b[]){
    int c = 1;

    for(int i = 0; a[i] && c; i++){
        c = 0;
        for(int j = 0; b[j] && !c; j++){
            if(a[i] == b[i]) c = 1;
        }
    }

    return c;
}

// Exercício 23 //
int palindorome (char s[]){
    int c = 1;

    for(int n = 0; s[n]; n++);
    for(int i = 0; i <= n && c; i++){
        if(s[i] == s[n - 1]){
            c;
            n--;
        }
        else c = 0;
    }

    return c;
}

// Exercício 24 //
int remRep(char x[]){
    int w = 1;
    for (int i = 0; x[i]; i++){
        if (x[i] != x[i + 1]){
            x[w] = x[i + 1]; // vai reajustar o array
            w++;
        }
    }
    return w - 1; // subtraimos por 1, por causa do "\0"
}

// Exercício 25 //
int limpaEspacos (char t[]){
    int acc = 0;

    for(int i = 0; t[i]; i++){
        if (!isspace(t[i])) t[acc++] = t[i]; // é feito "acc+" para reajustar o array
        else if (isspace(t[i]) && !isspace(t[i + 1])) t[acc++] = t[i];
        else if (!isspace(t[i]) && isspace(t[i + 1])) t[acc++] = t[i];
    }
    t[acc] = '\0';

    return acc;
}

// Exercício 26 //
void insere (int v[], int N, int x){ // é importante dizer que este array será percorrido da direita para a esquerda, adicionando o elemento x de forma ordenada
    for(int i = N-1; x < v[i]; i++) v[i+1] = v[i];
    v[i+1] = v[x];
}

// Exercício 27 //
void merge (int r [], int a[], int b[], int na, int nb){
    int i = 0, j = 0, k = 0;

    // Enquanto houver elementos nos dois arrays
    while (i < na && j < nb) {
        if (a[i] <= b[j]) {
            r[k++] = a[i++]; // copia o elemento atual de a para o próximo espaço disponível em r, enquanto avança para o próximo elemento em ambos a e r
        } else {
            r[k++] = b[j++];
        }
    }
    // Copia os elementos restantes de 'a' para 'r', se houver
    while (i < na) {
        r[k++] = a[i++];
    }
    // Copia os elementos restantes de 'b' para 'r', se houver
    while (j < nb) {
        r[k++] = b[j++];
    }
}

// Exercício 28 //
int crescente (int a[], int i, int j){
    int r = 1;
    for(;i<j && r;i++){ // não foi feita nenhuma inicialização, pois i já foi anunciado antes
        if(a[i]>a[i+1]) r = 0;
    }

    return r;
}

// Exercício 29 //
int retiraNeg (int v[], int N){
    int acc = N;
    int w = 0;

    for(int i = 0; i < N; i++){
        if(v[i] >= 0) v[w++] = v[i]; // atualização de v[w] e incrementação de w++
        else acc--;
    }

    return acc;
}
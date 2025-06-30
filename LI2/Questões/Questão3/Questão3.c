#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
//conversão de binário para decimal - mantissa //
double bindecmant(char Mant[], int M){
    double dec = 0.0;
    double pot = 0.5;
    for(int i = 0; i < M; i++){
        if(Mant[i] == '1'){
            dec = dec + pot;
        }
        pot = pot * 0.5;
    }
    return dec;
}

// conversão de binário para decimal - expoente //
double bindecexp(char Exp[], int E){
    double dec = 0;
    int h = E - 1;
    for(int i = 0; i < E; i++){
        if(Exp[i] == '1'){
            dec = dec + pow(2,h);
        }
        h--;
    }
    return dec;
}

// cálculo do excesso //
double excesso(int E){
    return pow(2, (E - 1)) - 1;
}

// cálculo dos nº normalizados //
double normal(double s, double m, double e, double x){
    return (pow(-1, s) * (1 + m) * pow(2, e - x));
}

// cálculo dos nº desnormalizados //
double desnormal(double s, double m, double e){
    return (pow(-1, s) * m * pow(2, 1 - e));
}

// este programa só lê uma linha e parte a string de bits em sinal, expoente e mantissa //
int main (){
int linhas;
char buf[BUFSIZ];

    if(fgets(buf, BUFSIZ, stdin) != NULL){
    sscanf(buf, "%d", &linhas);
    
    for (int i = 1; i <= linhas; i++) {
    
        assert(fgets(buf, BUFSIZ, stdin) != NULL);
        assert(buf[strlen(buf) - 1] == '\n');
        buf[strlen(buf) - 1] = '\0';
        
        int E, M;
        char bits[BUFSIZ] = {0};

        sscanf(buf, "%d %d %s", &E, &M, bits);

        char Sinal;
        char Exp[BUFSIZ] = {0};
        char Mant[BUFSIZ] = {0};
        char formato[BUFSIZ];

        sprintf(formato, "%%c%%%ds%%%ds", E, M);
        sscanf(bits, formato, &Sinal, Exp, Mant);
        //printf("%d %s %s\n", Sinal - '0', Exp, Mant);

        int nnumero = 1;
        int znumero = 1;
        int zmantissa = 1;
        for(int i = 0; i < M; i++){
            if(Mant[i] == '1'){
                zmantissa = 0;
            }
        }
        for(int i = 0; i < E; i++){
            if(Exp[i] == '0'){
                nnumero = 0;
            }else{
                znumero = 0;
            }
        }
        if(nnumero && zmantissa){
            if(Sinal == '1'){
                printf("-Infinity\n");
            }else{
                printf("+Infinity\n");
            }
        }else if(nnumero && !zmantissa){
            printf("NaN\n");
        }else if(znumero && zmantissa){
            if(Sinal == '1'){
                printf("-0\n");
            }else{
                printf("0\n");
            }
        }else if(znumero && !zmantissa){
            if(Sinal == '1'){
                printf("%lg\n", desnormal(-1, bindecmant(Mant, M), excesso(E)));
            }else
                printf("%lg\n", desnormal(0, bindecmant(Mant, M), excesso(E)));
        }else{
            if(Sinal == '1'){
                printf("%lg\n", normal(-1, bindecmant(Mant, M), bindecexp(Exp, E), excesso(E)));
            }else{
            printf("%lg\n", normal(0, bindecmant(Mant, M), bindecexp(Exp, E), excesso(E)));
            }
        }
    }
    }
    return 0;
}
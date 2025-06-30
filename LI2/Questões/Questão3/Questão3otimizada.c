#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

//conversão de binário para decimal - mantissa //
double bindecmant(char Mant[], int M){
    double dec = 0.0;
    double pot = 0.5;
    for(int i = 0; i < M; i++){
        if(Mant[i] == '1')
			dec += pot;
        pot = pot * 0.5;
    }
    return dec;
}

// conversão de binário para decimal - expoente //
double bindecexp(char Exp[], int E){
    double dec = 0;
    int h = E - 1;
    for(int i = 0; i < E; i++){
        if(Exp[i] == '1')
			dec += pow(2,h);
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

    // Lê o número de linhas
	assert(fgets(buf, BUFSIZ, stdin) != NULL);
    sscanf(buf, "%d", &linhas);
    
    for (int i = 0; i < linhas; i++) {
    
        assert(fgets(buf, BUFSIZ, stdin) != NULL);
        assert(buf[strlen(buf) - 1] == '\n');
        buf[strlen(buf) - 1] = '\0';
        
        int E, M;
        char bits[BUFSIZ] = {0};

		// Lê o conteudo da linha
        sscanf(buf, "%d %d %s", &E, &M, bits);

        char Sinal;
        char Exp[BUFSIZ] = {0};
        char Mant[BUFSIZ] = {0};
        char formato[BUFSIZ];
		
		// Separa a informação dos bits
        sprintf(formato, "%%c%%%ds%%%ds", E, M);
        sscanf(bits, formato, &Sinal, Exp, Mant);

        int nnumero = 1;
        int znumero = 1;
        int zmantissa = 1;
		int j;
		
		// Verifica se na Mantissa existe '1's
        for(j = 0; j < M; i++)
            if(Mant[j] == '1')
                zmantissa = 0;
        
		// Verifica se no Expoente existem '1's ou '0's
        for(j = 0; j < E; i++)
            if(Exp[j] == '0')
                nnumero = 0;
            else
                znumero = 0;
            
		// Impressão do resultado	
        if(nnumero && zmantissa)
            printf("%cInfinity\n",(Sinal == 1?'-':'+'));
        else if(nnumero && !zmantissa)
            printf("NaN\n");
        else if(znumero && zmantissa)
            printf("%c0\n",(Sinal == 1?'-':'+'));
        else if(znumero && !zmantissa)
            printf("%lg\n", desnormal(Sinal - '0', bindecmant(Mant, M), excesso(E)));
        else
            printf("%lg\n", normal(Sinal - '0', bindecmant(Mant, M), bindecexp(Exp, E), excesso(E)));  
    }
    return 0;
}
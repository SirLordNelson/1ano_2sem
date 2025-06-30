#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define BUFFERSIZE 10000

// Array's com a informação a ser usada
float expected[] = {43.31, 10.56, 23.13, 17.25, 56.88, 9.24, 12.59, 15.31, 38.45, 1.00, 5.61,
                     27.98, 15.36, 33.92, 36.51, 16.14, 1.00, 38.64, 29.23, 35.43, 18.51, 5.13,
                     6.57, 1.48, 9.06, 1.39};

float partial(float expected, int freqObtida) {
  return (pow((expected - freqObtida), 2)) / expected;
}

int main() {
  char texto[BUFFERSIZE];
  int freq[26] = {0};

  assert(fgets(texto, BUFFERSIZE, stdin) != NULL); // lê o input e guarda no array texto

  // aumenta a freq de cada letra à medida que vai percorrendo o array
  for (int i = 0; texto[i] != '\0'; i++) 
    if (texto[i] >= 'a' && texto[i] <= 'z')
      freq[texto[i] - 'a']++;
    else 
      freq[texto[i] - 'A']++;

  float Parcial = 100000;
  float somaparcial;
  int chave = 0;

  for(int i = 0; i < 26; i++){
        somaparcial = 0;
        for(int j = 0; j < 26; j++) // vai calcular a parte "Parcial" de cada letra
            somaparcial = somaparcial + partial(expected[j], freq[(26 + j - i) % 26]); // isto traduz o somatório da fórmula

        if(somaparcial < Parcial){
            Parcial = somaparcial; // definição da substituição mais pequena
            chave = i;
        }
  }
  printf("%d ", chave);

  // imprime a cifra depois de ter mudado o valor
  for(int i = 0; texto[i] != '\0'; i++) {
        if(texto[i] >= 'A' && texto[i] <= 'Z')
            printf("%c", (((texto[i] - 'A') + chave) % 26) + 'A');
        else if(texto[i] >= 'a' && texto[i] <= 'z')
            printf("%c", (((texto[i] - 'a') + chave) % 26) + 'a');
        else printf("%c", texto[i]);
  }
  return 0;
}
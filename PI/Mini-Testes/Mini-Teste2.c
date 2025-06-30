#include <stdio.h>

int somaFrequencias(const char *str) {
    int frequencia_e = 0, frequencia_h = 0, frequencia_v = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == 'e') {
            frequencia_e++;
        } else if (str[i] == 'h') {
            frequencia_h++;
        } else if (str[i] == 'v') {
            frequencia_v++;
        }
    }
    return frequencia_e + frequencia_h + frequencia_v;
}

int main() {
    char texto[] = "TrIOsDb3fvRpQWNIcaoBNbrwmHvxMgcfPbiZbWQNl6ejgmU4DjNm9MbQS6AzP648FHEhbj121ymhBgCy6Y2JsqrG62z5m3BHtZxCJTG8NUwg7VJLdhc6KLVI0PsQzojeicGSDQFtezjD9o5GmITNtxCyaF74LOcflPMGEkxWGKnt4gaJQtTK6qkNcgXZu5jzJi3xcTbJtFiKX2U9Zki10X38C7gm9WEw6OZzZPc9fBTkGgYuUtKv00wDFiK26iLHqGiszX2IpJdKMJVMVSfggY9CFiXRsDjjDGrAioXSSg9R9WoJjWpCANkJSr5WMvyM7HsyMNf9pwK9MVRT5P3eLQS7KPwTO8QydcvzAADkG3aNXyfuUAcebdBG50I1MNc5iNAPmQab358VWTF3oxDAOamuc5y9oU1MVDQI7LlWmpklEMOIhYjIEq8hJjXOOr3LHmy7dX98FCv5rOcorr2fTzNGGr7X1rBjeNBLwcPGJtTQtUC4B2II0cmAyNYwWjd2DfPtBFKCa7HRq3YhlR770U2lG5UDVTH1FOhTCdhEmAPaHANgn2mD1htrZAlFzBoeckekiFTbQfgauU6JPb5pxn5D6NGf7nTwLq8rvi8RZbuEASCh1iM4WLj8cNoGLXjbaZrNM3SeYPjT3uwICMeQW5MtYCO34xP8a0MxguHsQD3DdXEIa2fNf4l5f9f8MHtdaRt9MCj4iCvKecIActl8LF1hjHBzfzmQA4rmygBRrvcrMKutqv2OmJc3dA0vrX8x8WgoCylOUO0vq7SG7DXmUhAOGIDWxA94mCYwvzcmhZjMz7ovKLgn8su3guCExHKN1AIavpkJLEOJaphFqVg3Q6QoM8rISBMFNwIAyzwZQrixhtULVIiQlneFRYPDL2fDxNOcS31NUMPfejJpJbx30yx8huNKLJAUNnMsJu6aUNQBTqFtuRD9ctcgY4bVc8x5kTVZ9yflgvkO0ljdQsiGlji4yuJwsO0arnB6C41a67BKl418GUhu99DEYxlfZtmi";

    int soma = somaFrequencias(texto);
    printf("Soma das frequências de 'e', 'h' e 'v': %d\n", soma);

    return 0;
}

#include <stdio.h>
#include <string.h>

char *menorSubstring(char *sequencia) {
    char *menor = sequencia; // Começamos com a primeira substring como a menor
    int len = strlen(sequencia); // Calculamos o comprimento da sequência
    for (int i = 0; i < len - 3; i++) { // Iteramos sobre a sequência
        if (strncmp(&sequencia[i], menor, 4) < 0) { // Se a substring atual for menor
            menor = &sequencia[i]; // Atualizamos a substring mínima
        }
    }
    return menor; // Retornamos a menor substring encontrada
}

int main() {
    char *sequencia = "Lji3OzY0QByxy9ErRQ89V1ZgZuwfeHLPCyKZQg6rOwVLufgamILGPpDVwPm76SeP2ZtqyTGYC8kyVLZjBJ1fMhx1EBAqvn6Ro7KdN0hl23JipngOIJ10rONlU001TDLtt9hsodaQ2jcgcYEAFJRvaCefNIsH20G38hoAMlzfU7XWLvzlqIrJcVKpyT4Xrgkyc19RgTEudSq4AaFQ2H4pKjUkH35JSiJRhFrVwUN1uTvcAeY9fRy0YkUpMqlKcTsljWW8dCWx8gHyW5fBgkoiodCKAZP1UrlltSEwaoQOuY6KeYG28emr1eA33XGWpSDKrswRIbi60bKxyWrDSuKGXKqYeMS1sNprIBYeR5NSeGwfyoRT1TyrsKWCc6xd9skAWpA1O5VWZHmVj4UGYVgsgNsidZuqKk6dkU0zUyh0MHtxwK7wEpm29zZoYBe5fA3w8aioAipSDcp02yd2SCbbEM7T0SKu8RKt2jImbZu71NTL9t01rdtbAM52uXvUzFKEXK3zDi34nHrSDomLMKk3OkeaTLxx7hgc0crBdTltO5CFZDi4Bt1duu8gGb7K5dvhwUG1VTlleH51J4dhny7M2OOp4aZ3TzGxOmOeMCR9QQigAtb676onz2p93iLnf1azB3WQuYHRB21nCrfovAQonc7ahDl9CzRcYiegtrLgojavgYOmG7IkRPr2MPylmUtS16iK0Fm4eetqraw6uQobgJR6TCfZ99zwrTLkLb36kkrMNnXnWzUKgnOsrLTptcmNKGE5A6Gqcvcb1dHqJgolPrBTxIDPcicOi2H5GC1jXupXknZ7iCkWFXi2EioIRp2l1TEACnrb88vqFjII9gYvW9a1UOMo8EwUaKlrqyfXbrGKoP5qPxmfCJVI8Gy4Z7zApoQGvvJWNXijWdXd1SebapRU5Y3PJF1kaFo0tYyK4RyOGg1JRlilQp0r0poMthjqYtj5ZvYTWg2hTYR9ReuWWNMYYz8f5jzsvT2Cogib7irnTOHD6vSuUkOsJqRwvarR";
    printf("Menor substring lexicograficamente: %.4s\n", menorSubstring(sequencia));
    return 0;
}
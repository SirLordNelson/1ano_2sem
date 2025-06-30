- Dicas:
verificar que o primeiro número é o nº de bits do expoente, de seguida o nº de bits da mantissa, e, por fim, o nº em si

- Matéria:
expoente 0 ("000")= desnormalizado

normalizado: (-1)^(sinal) * 1.mantissa * 2^(expoente - excesso)
desnormalizado: (-1)^(sinal) * 0.mantissa * 2^(1 - excesso)

- Cálculo do Excesso:
(2 ^ (número de bits - 1)) - 1

- Input (explicação):
3 bits para o expoente
4 bits para mantissa

- Exemplo de Código:

int n;
scanf ("%d", &n);

for (i = 0; i < n; i++)
    {
    ler linha
    provar linha
    escrever nova linha
    }

// "sscanf" pega na string "buf" e verifica se o que se segue acontece
// "assert" = assegura algo;
// "fgets" lê strings (o que quero ler, quantos caracteres vai ler, onde vai ler)

Plano:
1) criar uma função para analisar o sinal;
2) criar uma função que analise a matissa, que trabalhe com o normalizado
3) criar uma função para analisar o expoente
    3.1) criar um if para analisar se o expoente é "111"
        3.1.1) se sim, verificar se a matissa é "0000"
            3.1.1.1) se sim, é "Infinito"
            3.1.1.2) se não, é "NaN" (Not a Number)
    3.2) criar um if para analisar se o expoente é "000"
        3.1.1) se sim, verificar se a matissa é "0000"
            3.1.1.1) se sim, é "0"
            3.1.1.2) se não, é desnormalizado
    3.3) criar um if para trabalhar com a função do ponto 2
4) criar uma função que converta de binário para decimal 

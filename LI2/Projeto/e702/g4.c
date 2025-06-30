#include <assert.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

// 0 - espadas; 1 - copas; 2 - ouros; 3 - paus
int verNaipe(wchar_t carta)
{
    wchar_t primeiraCarta = 0x1F0A1;
    return ((carta - primeiraCarta) / 16);
}

// 0 ás, etc...
int verValor(wchar_t carta)
{
    wchar_t primeiraCarta = 0x1F0A1;
    return (carta - primeiraCarta) % 16;
}

void swap(wchar_t v[], int i, int j)
{
    wchar_t temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int partition(wchar_t v[], int N, int x)
{
    wchar_t aux[N];
    int count = 0;
    int j = 0;
    int k = N - 1;

    // insere todos os elementos menores ou iguais
    for (int i = 0; i < N; i++)
    {
        if ((verValor(v[i]) < verValor(x)) ||
            (verValor(v[i]) == verValor(x) && verNaipe(v[i]) < verNaipe(x)))
        {
            aux[j++] = v[i];
            count++;
        }
        else
        {
            aux[k--] = v[i];
        }
    }

    // copia para o array original
    for (int i = 0; i < N; i++)
    {
        v[i] = aux[i];
    }
    return count;
}

void ordenaMao(wchar_t a[], int n)
{
    if (n < 2)
        return;
    int p = partition(a, n - 1, a[n - 1]);
    swap(a, p, n - 1);
    ordenaMao(a, p);
    ordenaMao(a + p + 1, n - p - 1);
}

int eDuplaSequencia(wchar_t mao[], int tm)
{
    if (tm < 6 || tm % 2 == 1)
    {
        return 0;
    }
    else
    {
        for (int i = 1; i < tm;
             i++) // se i impar ver se o da frente tem o mesmo valor, se i par ver
                  // se o de frente tem o valor a seguir
        {
            if (i % 2 == 1)
            {
                if (verValor(mao[i]) != verValor(mao[i - 1]))
                {
                    return 0;
                }
            }
            else
            {
                if (verValor(mao[i]) != verValor(mao[i - 1]) + 1)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int verIndFstCartaSeq(wchar_t mao[], wchar_t FstCartajogada)
{
    int i = 0;
    while (verValor(mao[i]) < verValor(FstCartajogada))
    {
        i++;
    }
    return i;
}

int eSequencia(wchar_t mao[], int tm)
{
    if (tm < 3 || tm > 14)
    {
        return 0;
    }
    else
    {
        for (int i = 1; i < tm; i++)
        {
            if (verValor(mao[i - 1]) != verValor(mao[i]) - 1)
            {
                return 0;
            }
        }
        return 1;
    }
}

int eConjunto(wchar_t mao[], int tm)
{
    if (tm > 4)
        return 0;
    for (int i = 1; i < tm; i++)
    {
        if (verValor(mao[i]) != verValor(mao[i - 1]))
            return 0;
    }
    return 1;
}

/*-------------------------------------------------------------------------*/
// Função que recebe duas mãos ordenadas verifica se são do mesmo tipo e têm o
// mesmo tamanho
int tamanhoETipoIgual(wchar_t mao1[], wchar_t mao2[], int t1, int t2)
{
    if ((t1 != t2) || (eSequencia(mao1, t1) != eSequencia(mao2, t2)) ||
        (eConjunto(mao1, t1) != eConjunto(mao2, t2)) ||
        (eDuplaSequencia(mao1, t1) != eDuplaSequencia(mao2, t2)))
        return 0;
    return 1;
}

// funcao que ordena uma "matriz" (array dos pointers do primeiro elemento de
// cada mao) atraves de swaps
void ordenaMatriz(wchar_t *matriz[], int linhas, int tamanho)
{
    for (int k = linhas; k > 0; k--)
    {
        for (int i = 1; i < linhas; i++)
        {
            if ((verValor(*(matriz[i] + tamanho - 1)) <
                 verValor(*(matriz[i - 1] + tamanho - 1))) ||
                (verValor(*(matriz[i] + tamanho - 1)) ==
                     verValor(*(matriz[i - 1] + tamanho - 1)) &&
                 verNaipe(*(matriz[i] + tamanho - 1)) <
                     verNaipe(*(matriz[i - 1] + tamanho - 1))))
            {
                wchar_t *temp = matriz[i];
                matriz[i] = matriz[i - 1];
                matriz[i - 1] = temp;
            }
        }
    }
}

// funcao que printa uma linha de values(uma mao)
void printLinha(wchar_t linha[], int tam)
{
    for (int i = 0; i < tam - 1; i++)
    {
        wprintf(L"%lc ", linha[i]);
    }
    wprintf(L"%lc", linha[tam - 1]);
    wprintf(L"\n");
}

// funcao que printa todas as linhas de values depois de cada mao estar ordenada
// e depois de serem ordenadas entre si
void printaMatrizPorOrdem(wchar_t *matriz[], int linhas, int tam)
{
    for (int i = 0; i < linhas; i++)
    {
        printLinha(matriz[i], tam);
    }
}

int Principal2(wchar_t *matriz[], int matrizTm[], int linhas)
{
    int continua = 1;
    for (int k = 1; k < linhas && continua; k++)
    {
        if (!tamanhoETipoIgual(matriz[0], matriz[k], matrizTm[0], matrizTm[k]))
        {
            wprintf(L"Combinações não iguais!\n");
            continua = 0; // Caso entre no if, printa e depois acaba direto o for
        }
    }
    if (continua)
    {
        ordenaMatriz(matriz, linhas, matrizTm[0]);
        printaMatrizPorOrdem(matriz, linhas, matrizTm[0]);
    }
    return 0;
}

/*---------------------------------------------------------------------------------------------------------*/
// Principal 3
typedef struct PossuimosCarta
{
    wchar_t mao[15];
    wchar_t carta;
} PossuimosCarta;

typedef struct Mao
{
    wchar_t mao[15];
    int arrayiado[14];
    wchar_t maiorCarta;
    PossuimosCarta carta;
    int nvalues;
    int eValida;
} Mao;

typedef struct staticQueue
{
    int front;
    int length;
    wchar_t *values[4];
} QUEUE, *SQueue;

int cartaPertence(wchar_t mao[], wchar_t c, int tmMao)
{
    for (int i = 0; i < tmMao; i++)
    {
        if (c == mao[i])
        {
            return 1;
        }
    }
    return 0;
}

int cPertenceM(wchar_t mao[], wchar_t c[], int tmNossaJogada, int tmMao) //c == nossaJogada
{
    for (int i = 0; i < tmNossaJogada; i++)
    {
        if (cartaPertence(mao, c[i], tmMao) == 0)
            return 0;
    }
    return 1;
}

void eRei(wchar_t ultComb[], int numReis)
{

    for (int i = 0; i < 1; i++)
    {
        if (ultComb[i] == 0x1F0AE || ultComb[i] == 0x1F0BE ||
            ultComb[i] == 0x1F0CE || ultComb[i] == 0x1F0DE)
            numReis++;
    }
}

int DizComb(wchar_t ultComb[], int tamanho)
{
    if (eConjunto(ultComb, tamanho) == 1)
        return 1;
    else if (eSequencia(ultComb, tamanho))
        return 2;
    else if (eDuplaSequencia(ultComb, tamanho))
        return 3;
    else
        return 0;
}

int compara(wchar_t nossaJogada[], wchar_t ultComb[], int numReis)
{
    size_t tamanho = wcslen(ultComb);
    size_t tmNossa = wcslen(nossaJogada);
    if (numReis == 0)
    {
        if (tamanhoETipoIgual(ultComb, nossaJogada, tamanho, tmNossa) == 0)
            return 0;
        else if (verValor(nossaJogada[tmNossa - 1]) <
                 verValor(ultComb[tamanho - 1]))
            return 0;
        else if (verValor(nossaJogada[tmNossa - 1]) ==
                 verValor(ultComb[tamanho - 1]))
        {
            if (verNaipe(nossaJogada[tmNossa - 1]) < verNaipe(ultComb[tamanho - 1]))
                return 0;
        }
        else
            return 1;
    }
    else if (numReis == 1)
    {
        if (tmNossa == 4 && eConjunto(nossaJogada, tmNossa) == 1)
            return 1;
        else if (tamanho == 6 && eDuplaSequencia(nossaJogada, tmNossa))
            return 1;
    }
    else if (numReis == 2)
    {
        if (tamanho == 8 && eDuplaSequencia(nossaJogada, tmNossa))
            return 1;
    }
    else if (numReis == 3)
    {
        if (tamanho == 10 && eDuplaSequencia(nossaJogada, tmNossa))
            return 1;
    }
    return 0;
}

int TresPasso(SQueue Jogadas, wchar_t *ultComb, int numJogadasAnteriores)
{
    if (Jogadas->length == 4)
    {
        for (int i = 3; i > 0; i--)
        {
            if (wcscmp(Jogadas->values[(numJogadasAnteriores - i) % 4], L"PASSO") !=
                0)
            {
                wcscpy(ultComb, Jogadas->values[(numJogadasAnteriores - i) % 4]);
                return 0;
            }
        }
        return 1;
    }
    else
    {
        for (int i = 0; i < Jogadas->length - 1; i++)
        {
            if (wcscmp(Jogadas->values[i], L"PASSO") != 0)
            {
                wcscpy(ultComb, Jogadas->values[i]);
                return 0;
            }
        }
        return 1;
    }
}

int valida(SQueue Jogadas, wchar_t nossaJogada[], int numJogadasAnteriores)
{
    wchar_t ultComb[15];
    int numReis = 0;

    if (TresPasso(Jogadas, ultComb, numJogadasAnteriores) == 1)
        return 1;
    else
    {
        eRei(ultComb, numReis);
        return compara(nossaJogada, ultComb, numReis);
    }
}

void limpaBuffer()
{
    wint_t c;
    while ((c = fgetwc(stdin)) != L'\n' && c != WEOF)
        ;
}

int eValida(wchar_t mao[], SQueue Jogadas, wchar_t *nossaJogada, int tmNossaJogada, int tmMao, int numJogadasAnteriores)
{
    if (cPertenceM(mao, nossaJogada, tmNossaJogada, tmMao) == 0)
        return 0;
    else
    {
        return valida(Jogadas, nossaJogada, numJogadasAnteriores);
    }
}

void gerarSequencias(wchar_t mao[], int IndFstCartaSeq, int tamanhoMao, wchar_t aux[], int i, int tamanhoSeq, wchar_t jogada[], int *trava) // IndFstCartaSeq é o indice da carta onde podem começar as sequencias / n TamanhoMAo / data é
{
    if (i == tamanhoSeq)
    {
        // Imprime a sequência atual
        if (verValor(aux[0]) == verValor(jogada[0]))
        {
            if (verNaipe(aux[tamanhoSeq - 1]) < verNaipe(jogada[tamanhoSeq - 1]))
            {
                return;
            }
        }
        for (int j = 0; j < tamanhoSeq - 1; j++)
        {
            wprintf(L"%lc ", aux[j]);
        }
        wprintf(L"%lc", aux[tamanhoSeq - 1]);
        wprintf(L"\n");
        *trava = 1;
        return;
    }

    // Quando não há mais elementos para selecionar
    if (IndFstCartaSeq >= tamanhoMao)
        return;

    // Inclui o elemento atual no conjunto, se for sequência
    if (i == 0 || verValor(mao[IndFstCartaSeq]) == verValor(aux[i - 1]) + 1)
    {
        aux[i] = mao[IndFstCartaSeq];
        gerarSequencias(mao, IndFstCartaSeq + 1, tamanhoMao, aux, i + 1, tamanhoSeq, jogada, trava);
    }

    // Tenta com os próximos elementos
    gerarSequencias(mao, IndFstCartaSeq + 1, tamanhoMao, aux, i, tamanhoSeq, jogada, trava);
}

void gerarDuplaSequencias(wchar_t mao[], int IndFstCartaSeq, int tamanhoMao, wchar_t aux[], int i, int tamanhoSeq, wchar_t jogada[], int *trava)
{
    if (i == tamanhoSeq)
    {
        // Imprime a sequência atual
        if (verValor(aux[0]) == verValor(jogada[0]))
        {
            if (verNaipe(aux[tamanhoSeq - 1]) < verNaipe(jogada[tamanhoSeq - 1]))
            {
                return;
            }
        }
        if (eDuplaSequencia(aux, i) == 0)
        {
            return;
        }
        for (int j = 0; j < tamanhoSeq - 1; j++)
        {
            wprintf(L"%lc ", aux[j]);
        }
        wprintf(L"%lc", aux[tamanhoSeq - 1]);
        wprintf(L"\n");
        *trava = 1;
        return;
    }

    // Quando não há mais elementos para selecionar
    if (IndFstCartaSeq >= tamanhoMao)
        return;

    // Inclui o elemento atual no conjunto, se for sequência
    if (i % 2 == 1 && verValor(mao[IndFstCartaSeq]) == verValor(aux[i - 1]))
    {
        aux[i] = mao[IndFstCartaSeq];
        gerarDuplaSequencias(mao, IndFstCartaSeq + 1, tamanhoMao, aux, i + 1, tamanhoSeq, jogada, trava);
    }
    else if (i == 0 || verValor(mao[IndFstCartaSeq]) == verValor(aux[i - 1]) + 1)
    {
        aux[i] = mao[IndFstCartaSeq];
        gerarDuplaSequencias(mao, IndFstCartaSeq + 1, tamanhoMao, aux, i + 1, tamanhoSeq, jogada, trava);
    }
    gerarDuplaSequencias(mao, IndFstCartaSeq + 1, tamanhoMao, aux, i, tamanhoSeq, jogada, trava);
}

/* Funções relacionadas ao conjunto */
void printaConjuntoIgual(wchar_t mao[], int tamanho, int *trava)
{
    int i = 1;
    if (wcslen(mao) == 0)
        return;
    else
    {
        *trava = 1;
        wprintf(L"%lc", mao[0]);
        for (; i < tamanho; i++)
        {
            wprintf(L" %lc", mao[i]);
        }
        wprintf(L"\n");
    }
}

void printaConjuntoDiferente(wchar_t mao[], int indices[], int tamanhoAnterior, int *trava)
{
    int i = 1;
    if (wcslen(mao) == 0)
        return;
    else
    {
        *trava = 1;
        wprintf(L"%lc", mao[indices[0]]);
        for (; i < tamanhoAnterior; i++)
        {
            wprintf(L" %lc", mao[indices[i]]);
        }
        wprintf(L"\n");
    }
}

void tamanhoAnteriorIgual3(wchar_t novo[], int *trava)
{
    int tamanhoAnterior = 3;
    int array[3] = {0, 1, 2};
    printaConjuntoDiferente(novo, array, tamanhoAnterior, trava);
    array[2] = 3;
    printaConjuntoDiferente(novo, array, tamanhoAnterior, trava);
    array[1] = 2;
    printaConjuntoDiferente(novo, array, tamanhoAnterior, trava);
    array[0] = 1;
    printaConjuntoDiferente(novo, array, tamanhoAnterior, trava);
}

void tamanhoAnteriorIgual2(wchar_t novo[], int tamanhoPossibilidades, wchar_t jogadaAnterior[], int *trava)
{
    int valorUltima = verValor(jogadaAnterior[1]), naipeUltima = verNaipe(jogadaAnterior[1]);
    int tamanhoAnterior = 2;
    int array[2] = {0, 1};
    if (!(verValor(novo[1]) == valorUltima && verNaipe(novo[1]) < naipeUltima))
        printaConjuntoDiferente(novo, array, tamanhoAnterior, trava);
    if (!(verValor(novo[2]) == valorUltima && verNaipe(novo[2]) < naipeUltima)){
        array[1] = 2;
        printaConjuntoDiferente(novo, array, tamanhoAnterior, trava);
    }
    if (tamanhoPossibilidades == 4 && (!(verValor(novo[3]) == valorUltima && verNaipe(novo[3]) < naipeUltima))){
        array[1] = 3;
        printaConjuntoDiferente(novo, array, tamanhoAnterior, trava);
    }
    array[0] = 1;
    if (!(verValor(novo[2]) == valorUltima && verNaipe(novo[2]) < naipeUltima)){
        array[1] = 2;
        printaConjuntoDiferente(novo, array, tamanhoAnterior, trava);
    }
    if (tamanhoPossibilidades == 4 && (!(verValor(novo[3]) == valorUltima && verNaipe(novo[3]) < naipeUltima)))
    {
        array[1] = 3;
        printaConjuntoDiferente(novo, array, tamanhoAnterior, trava);
        array[0] = 2;
        printaConjuntoDiferente(novo, array, tamanhoAnterior, trava);
    }
}

void printaConjunto(wchar_t possibilidades[], int inicial, int final, int tamanhoAnterior, wchar_t jogadaAnterior[], int *trava)
{
    wchar_t novo[final - inicial + 2];
    int tamanhoPoss = 0;
    for (int i = inicial; i <= final; i++, tamanhoPoss++)
    {
        novo[tamanhoPoss] = possibilidades[i];
    }
    if (tamanhoPoss == tamanhoAnterior)
    {
        if ((verValor(novo[tamanhoPoss - 1]) == verValor(jogadaAnterior[tamanhoAnterior - 1]) && verNaipe(novo[tamanhoPoss - 1]) < verNaipe(jogadaAnterior[tamanhoAnterior - 1]))) return;
        printaConjuntoIgual(novo, tamanhoAnterior, trava);
    }
    else if (tamanhoAnterior == 3)
    {   
        // o tamanhoPoss neste caso é sempre 4 porque se fosse 3 ja tinha entrado em cima
        tamanhoAnteriorIgual3(novo, trava);
    }
    else if (tamanhoAnterior == 2)
    {
        tamanhoAnteriorIgual2(novo, tamanhoPoss, jogadaAnterior, trava);
    }
    else if (tamanhoAnterior == 1)
    {
        for (int i = 0; i < tamanhoPoss; i++)
        {
            if (verValor(novo[i]) == verValor(jogadaAnterior[0]) && verNaipe(novo[i]) < verNaipe(jogadaAnterior[0]))
            {
                continue;
            }
            else
            {
                *trava = 1;
                wprintf(L"%lc\n", novo[i]);
            }
        }
    }
}

// Elimina todos os valores mais pequenos do que a menor carta da jogada
// anterior
int eliminaMaisPequenos(wchar_t mao[], wchar_t jogadaAnterior[], int tamanhoMao)
{
    wchar_t menorCartaAnterior = jogadaAnterior[0];
    int i;
    for (i = 0; i < tamanhoMao && verValor(menorCartaAnterior) > verValor(mao[i]); i++)
        ;
    return i;
}

void separaConjunto(wchar_t mao[], int indicesAPrintar[], int tamanhoMao, int tamanhoAnterior, int *numIndicesAPrintar)
{
    int i, tamanho = 1, inicial = 0, k = 0;
    for (i = 1; i < tamanhoMao; i++) // ver o que acontece quando tamanho da mao é 1
    {
        if (verValor(mao[i - 1]) == verValor(mao[i]))
        {
            tamanho++;
        }
        else
        {
            if (tamanho >= tamanhoAnterior)
            {
                indicesAPrintar[k] = inicial;
                k++;
                indicesAPrintar[k] = i - 1;
                k++;
            }
            inicial = i;
            tamanho = 1;
        }
    }
    if (tamanho >= tamanhoAnterior)
    {
        indicesAPrintar[k] = inicial;
        k++;
        indicesAPrintar[k] = i - 1;
        k++;
    }
    *numIndicesAPrintar = k;
}

// Conta quantos reis existem na jogadaAnterior
int quantoRei(wchar_t jogadaAnterior[], int tamanhoAnterior)
{
    int numReis = 0;
    for (int i = 0; i < tamanhoAnterior; i++)
    {
        if (verValor(jogadaAnterior[i]) == 13)
            numReis++;
    }
    return numReis;
}

void ImprimeTesteConjunto(wchar_t mao[], wchar_t jogadaAnterior[], int tamanhoMao, int tamanhoAnterior, int eRei, int *trava)
{
    int comeco = 0;
    if (eRei == -1)
    {
        int numReis;
        numReis = quantoRei(mao, tamanhoMao);
        if (numReis != 0)
        {
            for (int i = 0; i < tamanhoMao; i++)
            {
                if ((verValor(mao[i]) == 13) && verNaipe(mao[i]) > verNaipe(jogadaAnterior[0]))
                {
                    wprintf(L"%lc\n", mao[i]);
                    *trava = 1;
                }
            }
        }
    }
    else
    {
        comeco = eliminaMaisPequenos(mao, jogadaAnterior, tamanhoMao);
    }
    if (comeco < tamanhoMao)
    {
        int indicesAPrintar[56] = {0};
        tamanhoMao = tamanhoMao - comeco;
        int numIndicesAPrintar = 0;
        separaConjunto(mao + comeco, indicesAPrintar, tamanhoMao, tamanhoAnterior,
                       &numIndicesAPrintar);
        for (int k = 0; k < numIndicesAPrintar; k += 2)
            printaConjunto(mao + comeco, indicesAPrintar[k], indicesAPrintar[k + 1],
                           tamanhoAnterior, jogadaAnterior, trava);
    }
}

void gerarConjuntos(wchar_t maoInicial[], wchar_t jogadaAnterior[], int tamanhoMao, int tamanhoAnterior, wchar_t aux[], int *trava)
{
    int numReis = 0;
    wchar_t jogada[1] = {0x1F0A1};
    numReis = quantoRei(jogadaAnterior, tamanhoAnterior);
    if (numReis == 1)
    {
        ImprimeTesteConjunto(maoInicial, jogadaAnterior, tamanhoMao, 4, -1, trava); // testa se podemos jogar um conjunto de 4 cartas
        gerarDuplaSequencias(maoInicial, 0, tamanhoMao, aux, 0, 6, jogada, trava);  // testa se podemos jogar uma duplaSeqeuncia de tamanho 6
    }
    else if (numReis == 2)
    {
        int nReisNossos = quantoRei(maoInicial, tamanhoMao);
        if (nReisNossos == 2) // Testa se podemos jogar um par de reis em cima de outro par de reis
        {
            if (maoInicial[tamanhoMao - 1] - jogadaAnterior[1] > 0)
            {
                wprintf(L"%lc %lc\n", maoInicial[tamanhoMao - 2], maoInicial[tamanhoMao - 1]);
                *trava = 1;
            }
        }
        gerarDuplaSequencias(maoInicial, 0, tamanhoMao, aux, 0, 8, jogada, trava); // testa se podemos jogar uma duplaSeqeuncia de tamanho 8
    }
    else if (numReis == 3)
    {
        gerarDuplaSequencias(maoInicial, 0, tamanhoMao, aux, 0, 10, jogada, trava); // testa se podemos jogar uma duplaSeqeuncia de tamanho 10
    }
    /*else if (numReis == 4)
    {
        //
        //wprintf(L"PASSO\n"); // nao exite nenhuma jogada que se pode jogar depois de um conjunto de 4 reis
    }*/
    else if (numReis != 4)
        ImprimeTesteConjunto(maoInicial, jogadaAnterior, tamanhoMao, tamanhoAnterior, 0, trava); // testa se podemos jogar um conjunto com o mesmo tamanho que a jogada Anterior e maior(So se usa esta funçao caso a jogada anterior nao seja um conjunto de reis)
}

char detectaTipo(wchar_t jogadaAnterior[], int tamanhoAnterior)
{
    if (eConjunto(jogadaAnterior, tamanhoAnterior))
    {
        return 'C'; // Conjunto
    }
    else if (eSequencia(jogadaAnterior, tamanhoAnterior))
    {
        return 'S'; // Sequencia
    }
    else if (eDuplaSequencia(jogadaAnterior, tamanhoAnterior))
    {
        return 'D'; // duplaSequencia
    }
    else
    {
        return 'N'; // nada
    }
}

int main()
{
    setlocale(LC_CTYPE, "C.UTF-8");
    int nTestes = 0;

    assert(wscanf(L"%d", &nTestes) == 1);
    wchar_t maoInicial[56];
    wchar_t jogadaAnterior[56];
    wchar_t aux[56];
    int trava = 0;
    limpaBuffer();
    for (int i = 0; i < nTestes; i++)
    {
        assert(fgetws(jogadaAnterior, 56, stdin) != NULL);
        assert(fgetws(maoInicial, 56, stdin) != NULL);
        wprintf(L"Teste %d\n", i + 1);
        int tamanhoAnterior = wcslen(jogadaAnterior) - 1;
        int tamanhoMao = wcslen(maoInicial) - 1;
        ordenaMao(jogadaAnterior, tamanhoAnterior);
        ordenaMao(maoInicial, tamanhoMao);

        switch (detectaTipo(jogadaAnterior, tamanhoAnterior))
        {
        case 'C':
            gerarConjuntos(maoInicial, jogadaAnterior, tamanhoMao, tamanhoAnterior, aux, &trava);
            break;
        case 'S':
            gerarSequencias(maoInicial, verIndFstCartaSeq(maoInicial, jogadaAnterior[0]), tamanhoMao, aux, 0, tamanhoAnterior, jogadaAnterior, &trava);
            break;
        case 'D':
            gerarDuplaSequencias(maoInicial, verIndFstCartaSeq(maoInicial, jogadaAnterior[0]), tamanhoMao, aux, 0, tamanhoAnterior, jogadaAnterior, &trava);
            break;
        default:
            wprintf(L"PASSO\n");
            break;
        }

        if (trava == 0)
            wprintf(L"PASSO\n");
        trava = 0;
    }
    return 0;
}
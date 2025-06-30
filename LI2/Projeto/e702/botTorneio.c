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
        for (int i = 1; i < tm; i++)
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

typedef struct staticQueue
{
    int front;
    int length;
    wchar_t *values[3];
} QUEUE, *SQueue;

void limpaBuffer()
{
    wint_t c;
    while ((c = fgetwc(stdin)) != L'\n' && c != WEOF)
        ;
}

void gerarSequencias(
    wchar_t mao[], int IndFstCartaSeq, int tamanhoMao, wchar_t aux[], int i,
    int tamanhoSeq, wchar_t jogada[],
    int *trava) // IndFstCartaSeq é o indice da carta onde podem começar as
                // sequencias / n TamanhoMAo / data é
{
    if (*trava == 1)
        return;
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
        gerarSequencias(mao, IndFstCartaSeq + 1, tamanhoMao, aux, i + 1, tamanhoSeq,
                        jogada, trava);
    }

    // Tenta com os próximos elementos
    gerarSequencias(mao, IndFstCartaSeq + 1, tamanhoMao, aux, i, tamanhoSeq,
                    jogada, trava);
}

void gerarDuplaSequencias(wchar_t mao[], int IndFstCartaSeq, int tamanhoMao,
                          wchar_t aux[], int i, int tamanhoSeq,
                          wchar_t jogada[], int *trava)
{
    if (*trava == 1)
        return;
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
        gerarDuplaSequencias(mao, IndFstCartaSeq + 1, tamanhoMao, aux, i + 1,
                             tamanhoSeq, jogada, trava);
    }
    else if (i == 0 ||
             verValor(mao[IndFstCartaSeq]) == verValor(aux[i - 1]) + 1)
    {
        aux[i] = mao[IndFstCartaSeq];
        gerarDuplaSequencias(mao, IndFstCartaSeq + 1, tamanhoMao, aux, i + 1,
                             tamanhoSeq, jogada, trava);
    }
    gerarDuplaSequencias(mao, IndFstCartaSeq + 1, tamanhoMao, aux, i, tamanhoSeq,
                         jogada, trava);
}

/* Funções relacionadas ao conjunto */
void printaConjuntoIgual(wchar_t mao[], int tamanho, int *trava)
{
    int i = 1;
    if (wcslen(mao) == 0)
        return;
    else if (*trava == 0)
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

void printaConjuntoDiferente(wchar_t mao[], int indices[], int tamanhoAnterior,
                             int *trava)
{
    int i = 1;
    if (wcslen(mao) == 0)
        return;
    else if (*trava == 0)
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

void tamanhoAnteriorIgual2(wchar_t novo[], int tamanhoPossibilidades,
                           wchar_t jogadaAnterior[], int *trava)
{
    int valorUltima = verValor(jogadaAnterior[1]),
        naipeUltima = verNaipe(jogadaAnterior[1]);
    int tamanhoAnterior = 2;
    int array[2] = {0, 1};
    if (!(verValor(novo[1]) == valorUltima && verNaipe(novo[1]) < naipeUltima))
        printaConjuntoDiferente(novo, array, tamanhoAnterior, trava);
    if (!(verValor(novo[2]) == valorUltima && verNaipe(novo[2]) < naipeUltima))
    {
        array[1] = 2;
        printaConjuntoDiferente(novo, array, tamanhoAnterior, trava);
    }
    if (tamanhoPossibilidades == 4 && (!(verValor(novo[3]) == valorUltima &&
                                         verNaipe(novo[3]) < naipeUltima)))
    {
        array[1] = 3;
        printaConjuntoDiferente(novo, array, tamanhoAnterior, trava);
    }
    array[0] = 1;
    if (!(verValor(novo[2]) == valorUltima && verNaipe(novo[2]) < naipeUltima))
    {
        array[1] = 2;
        printaConjuntoDiferente(novo, array, tamanhoAnterior, trava);
    }
    if (tamanhoPossibilidades == 4 && (!(verValor(novo[3]) == valorUltima &&
                                         verNaipe(novo[3]) < naipeUltima)))
    {
        array[1] = 3;
        printaConjuntoDiferente(novo, array, tamanhoAnterior, trava);
        array[0] = 2;
        printaConjuntoDiferente(novo, array, tamanhoAnterior, trava);
    }
}

void printaConjunto(wchar_t possibilidades[], int inicial, int final,
                    int tamanhoAnterior, wchar_t jogadaAnterior[], int *trava)
{
    wchar_t novo[final - inicial + 2];
    int tamanhoPoss = 0;
    for (int i = inicial; i <= final; i++, tamanhoPoss++)
    {
        novo[tamanhoPoss] = possibilidades[i];
    }
    if (tamanhoPoss == tamanhoAnterior)
    {
        if ((verValor(novo[tamanhoPoss - 1]) ==
                 verValor(jogadaAnterior[tamanhoAnterior - 1]) &&
             verNaipe(novo[tamanhoPoss - 1]) <
                 verNaipe(jogadaAnterior[tamanhoAnterior - 1])))
            return;
        printaConjuntoIgual(novo, tamanhoAnterior, trava);
    }
    else if (tamanhoAnterior == 3)
    {
        // o tamanhoPoss neste caso é sempre 4 porque se fosse 3 ja tinha entrado em
        // cima
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
            if (verValor(novo[i]) == verValor(jogadaAnterior[0]) &&
                verNaipe(novo[i]) < verNaipe(jogadaAnterior[0]))
            {
                continue;
            }
            else if (*trava == 0)
            {
                *trava = 1;
                wprintf(L"%lc\n", novo[i]);
            }
        }
    }
}

// Elimina todos os valores mais pequenos do que a menor carta da jogada
// anterior
int eliminaMaisPequenos(wchar_t mao[], wchar_t jogadaAnterior[],
                        int tamanhoMao)
{
    wchar_t menorCartaAnterior = jogadaAnterior[0];
    int i;
    for (i = 0; i < tamanhoMao && verValor(menorCartaAnterior) > verValor(mao[i]);
         i++)
        ;
    return i;
}

void separaConjunto(wchar_t mao[], int indicesAPrintar[], int tamanhoMao,
                    int tamanhoAnterior, int *numIndicesAPrintar)
{
    int i, tamanho = 1, inicial = 0, k = 0;
    for (i = 1; i < tamanhoMao;
         i++) // ver o que acontece quando tamanho da mao é 1
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

void ImprimeTesteConjunto(wchar_t mao[], wchar_t jogadaAnterior[],
                          int tamanhoMao, int tamanhoAnterior, int eRei,
                          int *trava)
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
                if ((verValor(mao[i]) == 13) &&
                    verNaipe(mao[i]) > verNaipe(jogadaAnterior[0]) && *trava == 0)
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

void gerarConjuntos(wchar_t maoInicial[], wchar_t jogadaAnterior[],
                    int tamanhoMao, int tamanhoAnterior, wchar_t aux[],
                    int *trava)
{
    int numReis = 0;
    wchar_t jogada[1] = {0x1F0A1};
    numReis = quantoRei(jogadaAnterior, tamanhoAnterior);
    if (numReis == 1)
    {
        ImprimeTesteConjunto(
            maoInicial, jogadaAnterior, tamanhoMao, 4, -1,
            trava); // testa se podemos jogar um conjunto de 4 cartas
        gerarDuplaSequencias(
            maoInicial, 0, tamanhoMao, aux, 0, 6, jogada,
            trava); // testa se podemos jogar uma duplaSeqeuncia de tamanho 6
    }
    else if (numReis == 2)
    {
        int nReisNossos = quantoRei(maoInicial, tamanhoMao);
        if (nReisNossos ==
            2) // Testa se podemos jogar um par de reis em cima de outro par de reis
        {
            if (maoInicial[tamanhoMao - 1] - jogadaAnterior[1] > 0 && *trava == 0)
            {
                wprintf(L"%lc %lc\n", maoInicial[tamanhoMao - 2],
                        maoInicial[tamanhoMao - 1]);
                *trava = 1;
            }
        }
        gerarDuplaSequencias(
            maoInicial, 0, tamanhoMao, aux, 0, 8, jogada,
            trava); // testa se podemos jogar uma duplaSeqeuncia de tamanho 8
    }
    else if (numReis == 3)
    {
        gerarDuplaSequencias(
            maoInicial, 0, tamanhoMao, aux, 0, 10, jogada,
            trava); // testa se podemos jogar uma duplaSeqeuncia de tamanho 10
    }
    else if (numReis != 4)
        ImprimeTesteConjunto(
            maoInicial, jogadaAnterior, tamanhoMao, tamanhoAnterior, 0,
            trava); // testa se podemos jogar um conjunto com o mesmo tamanho que a
                    // jogada Anterior e maior(So se usa esta funçao caso a jogada
                    // anterior nao seja um conjunto de reis)
}

// Vê o tamanho de uma mão
int tamanho(wchar_t array[])
{
    int size = 0;
    for (int i = 0; array[i]; i++)
        size++;
    return size;
}

SQueue SinitQueue()
{
    SQueue q = malloc(sizeof(struct staticQueue));
    q->front = 0;
    q->length = 0;

    return q;
}

int Senqueue(SQueue q, wchar_t *x)
{
    if (q->length >= 3)
        return 1;
    q->values[(q->front + q->length) % 3] = x;
    q->length++;
    return 0;
}

int Sdequeue(SQueue q)
{
    if (q->length == 0)
        return 1;
    q->length--;
    if (q->front == 2)
        q->front = 0;
    else
        q->front++;

    return 0;
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

int ultimaJogada2(SQueue q, int posicaoFinal)
{
    if (wcscmp((q->values[posicaoFinal]), L"SSOPA") == 0)
    {
        if (posicaoFinal == 0)
        {
            if (wcscmp((q->values[posicaoFinal + 1]), L"SSOPA") == 0)
            {
                return -1;
            }
            else
                return 1;
        }
        else
        {
            if (wcscmp((q->values[posicaoFinal - 1]), L"SSOPA") == 0)
            {
                return -1;
            }
            else
                return 0;
        }
    }
    else
    {
        return posicaoFinal;
    }
}

// Pega na jogada anterior que seja diferente de passo. Se retornar o indice de
// um passo, é porque eram os 3 passos e pode-se jogar qualquer coisa
int ultimaJogada(SQueue q, int nJogadasAnt)
{
    int posicaoFinal = (((q->front + q->length) - 1) % 3);
    int verPassos = 0;
    int i = 0;
    if (nJogadasAnt >= 3)
    {
        while (wcscmp((q->values[posicaoFinal]), L"SSOPA") == 0 && i < 3)
        {
            if (posicaoFinal == 0)
            {
                posicaoFinal = 2;
                verPassos++;
                i++;
            }
            else
            {
                posicaoFinal--;
                verPassos++;
                i++;
            }
        }
        if (verPassos == 3)
            return -1;
        else
            return posicaoFinal;
    }
    else if (nJogadasAnt == 2)
    {
        return ultimaJogada2(q, posicaoFinal);
    }
    else if (nJogadasAnt == 1)
    {
        if (wcscmp((q->values[posicaoFinal]), L"SSOPA") == 0)
            return -1;
        else
            return 0;
    }
    else
        return -1;
}

void testa2(SQueue jogadasAnt, int nJogadasAnteriores, wchar_t maoInicial[])
{
    wchar_t aux[56];
    int trava = 0;
    // aqui fazer a parte do guiao 4
    int posicaoFinal = ultimaJogada(jogadasAnt, nJogadasAnteriores);
    wchar_t maoFinal[15];
    if (posicaoFinal == -1)
    {
        wprintf(L"%lc\n", maoInicial[0]);
    }
    else
    {
        wcscpy(maoFinal, jogadasAnt->values[posicaoFinal]);
        int tmMaoFinal = tamanho(maoFinal);
        int tamanhoMao = tamanho(maoInicial);
        switch (detectaTipo(maoFinal, tmMaoFinal))
        {
        case 'C':
            gerarConjuntos(maoInicial, maoFinal, tamanhoMao, tmMaoFinal, aux,
                           &trava);
            break;
        case 'S':
            gerarSequencias(maoInicial, verIndFstCartaSeq(maoInicial, maoFinal[0]), tamanhoMao, aux, 0, tmMaoFinal, maoFinal, &trava);
            break;
        case 'D':
            gerarDuplaSequencias(maoInicial,
                                 verIndFstCartaSeq(maoInicial, maoFinal[0]),
                                 tamanhoMao, aux, 0, tmMaoFinal, maoFinal, &trava);
            break;
        default:
            wprintf(L"PASSO\n");
            break;
        }

        if (trava == 0)
            wprintf(L"PASSO\n");
        trava = 0;
    }
}

void testa(wchar_t maoInicial[], SQueue jogadasAnt, int nJogadasAnteriores)
{
    // Lê as n jogadas anteriores
    for (int j = 0; j < nJogadasAnteriores + 1; j++)
    {
        if (j == 0)
        {
            assert(fgetws(maoInicial, BUFSIZ, stdin) != NULL);
            maoInicial[wcslen(maoInicial) - 1] = L'\0';

            ordenaMao(maoInicial, wcslen(maoInicial));
        }
        else
        {
            wchar_t *jogadaAtual = malloc(sizeof(wchar_t) * BUFSIZ);
            assert(fgetws(jogadaAtual, BUFSIZ, stdin) != NULL);
            jogadaAtual[wcslen(jogadaAtual) - 1] = L'\0';

            ordenaMao(jogadaAtual, wcslen(jogadaAtual));

            if (j > 3)
                Sdequeue(jogadasAnt);
            Senqueue(jogadasAnt, jogadaAtual);
        }
        if (j == nJogadasAnteriores)
        {
            testa2(jogadasAnt, nJogadasAnteriores, maoInicial);
        }
    }
}

int main()
{
    setlocale(LC_CTYPE, "C.UTF-8");
    int nJogadasAnteriores;
    assert(wscanf(L"%d", &nJogadasAnteriores) == 1);
    limpaBuffer();
    wchar_t maoInicial[BUFSIZ]; // Mão inicial do jogador
    SQueue jogadasAnt = SinitQueue();
    testa(maoInicial, jogadasAnt, nJogadasAnteriores);
    for (int j = 0; j < jogadasAnt->length; j++)
    {
        free(jogadasAnt->values[j]);
    }
    free(jogadasAnt);
}
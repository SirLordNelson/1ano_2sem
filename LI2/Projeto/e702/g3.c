#include <assert.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
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
    qsorte(a, p);
    qsorte(a + p + 1, n - p - 1);
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

int cartaPertence(wchar_t carta, wchar_t mao[])
{
    for (int i = 0; mao[i]; i++)
    {
        if (mao[i] == carta)
            return 1;
    }

    return 0;
}

void puxaTras(wchar_t maoInicial[], int tamanhoInicial, int posicao)
{
    for (int i = posicao; i < tamanhoInicial - 1; i++)
    {
        maoInicial[i] = maoInicial[i + 1];
    }
    maoInicial[tamanhoInicial - 1] = L'\0'; // Terminar a string corretamente
}

void deletarMao(wchar_t maoInicial[], int tamanhoInicial, wchar_t maoJogada[])
{
    for (int i = tamanhoInicial - 1; i >= 0; i--)
    {
        if (cartaPertence(maoInicial[i], maoJogada))
        {
            puxaTras(maoInicial, tamanhoInicial, i);
            tamanhoInicial--; // Reduzir o tamanho da mão após a remoção
        }
    }
}

void printMao(wchar_t maoInicial[], int tamanhoInicial, wchar_t maoJogada[])
{
    deletarMao(maoInicial, tamanhoInicial, maoJogada);
    int tamanho = wcslen(maoInicial);
    for (int i = 0; i < tamanho; i++)
    {
        if (i == tamanho - 1)
        {
            wprintf(L"%lc", maoInicial[i]);
        }
        else
        {
            wprintf(L"%lc ", maoInicial[i]);
        }
    }
}

typedef struct staticQueue
{
    int front;
    int length;
    wchar_t *values[4];
} QUEUE, *SQueue;

// Vê o tamanho de uma mão
int tamanho(wchar_t array[])
{
    int size = 0;
    for (int i = 0; array[i]; i++)
        size++;
    return size;
}

// Verifica se uma dada carta pertence a uma mão

int combinacaoValida(wchar_t mao[])
{

    if (eConjunto(mao, tamanho(mao)) || eSequencia(mao, tamanho(mao)) ||
        eDuplaSequencia(mao, tamanho(mao)))
        return 1;
    else
        return 0;
}
// Verifica se a combinação que vamos jogar pertence à mão inicial
int combinacaoPertence(wchar_t jogadaFinal[], wchar_t maoInicial[])
{
    for (int i = 0; jogadaFinal[i]; i++)
    {
        if (!cartaPertence(jogadaFinal[i], maoInicial))
            return 0;
    }

    return 1;
}

// Verifica se existem três PASSO consecutivos na queue
int tresPassoOuPrimeiroAJogar(int nJogadasAnteriores, SQueue q)
{
    if (nJogadasAnteriores == 0)
        return 1;
    int size = q->length;
    int count = 0;
    wchar_t comparar[] = L"SSOPA"; // "PASSO" organizado no ordenaMao
    for (int i = 0; i < size; i++)
    {
        if (wcscmp(comparar, q->values[i]) == 0)
            count++;
    }

    if (count == 3)
        return 1;
    return 0;
}

// Verifica se o valor da última carta da nossa jogada é superior ao último
// valor da jogada anterior
int maiorValor(wchar_t jogadaFinal[], wchar_t jogadaAnterior[])
{
    int tAnterior = tamanho(jogadaAnterior);
    int tAtual = tamanho(jogadaFinal);

    if (verValor(jogadaFinal[tAtual - 1]) >
        verValor(jogadaAnterior[tAnterior - 1]))
        return 1;
    if (verValor(jogadaFinal[tAtual - 1]) ==
        verValor(jogadaAnterior[tAnterior - 1]))
        return verNaipe(jogadaFinal[tAtual - 1]) >
               verNaipe(jogadaAnterior[tAnterior - 1]);

    return 0;
}

int mesmoTipo(wchar_t jogadaFinal[], wchar_t jogadaAnterior[])
{

    if ((eSequencia(jogadaFinal, tamanho(jogadaFinal)) &&
         eSequencia(jogadaAnterior, tamanho(jogadaAnterior))) ||
        (eDuplaSequencia(jogadaFinal, tamanho(jogadaFinal)) &&
         eDuplaSequencia(jogadaAnterior, tamanho(jogadaAnterior))) ||
        (eConjunto(jogadaFinal, tamanho(jogadaFinal)) &&
         eConjunto(jogadaAnterior, tamanho(jogadaAnterior))))
    {
        return 1;
    }

    return 0;
}

int contaReis(wchar_t maoFinal[])
{
    int count = 0;
    for (int i = 0; i < tamanho(maoFinal); i++)
    {
        if ((maoFinal[i] == 0x1F0AE || maoFinal[i] == 0x1F0BE ||
             maoFinal[i] == 0x1F0CE || maoFinal[i] == 0x1F0DE) &&
            eConjunto(maoFinal, tamanho(maoFinal)))
            count++;
    }

    return count;
}

void printaInicial(wchar_t mao[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        wprintf(L"%lc", mao[i]);
    }
    wprintf(L"\n");
}

void limpaBuffer()
{
    wint_t c;
    while ((c = fgetwc(stdin)) != L'\n' && c != WEOF)
        ;
}

SQueue SinitQueue() //iniciar uma queue
{
    SQueue q = malloc(sizeof(struct staticQueue));
    q->front = 0;
    q->length = 0;

    return q;
}

int Senqueue(SQueue q, wchar_t *x) //adiciona cenas até o tamanho da queue ser 4
{
    if (q->length >= 4)
        return 1;
    q->values[(q->front + q->length) % 4] = x;
    q->length++;
    return 0;
}

int Sdequeue(SQueue q) //tirar um elemento da queue
{
    if (q->length == 0)
        return 1;
    q->length--;
    if (q->front == 3)
        q->front = 0;
    else
        q->front++;

    return 0;
}

int tamanhoETipoIgual(wchar_t mao1[], wchar_t mao2[], int t1, int t2)
{
    if ((t1 != t2) || (eSequencia(mao1, t1) != eSequencia(mao2, t2)) ||
        (eConjunto(mao1, t1) != eConjunto(mao2, t2)) ||
        (eDuplaSequencia(mao1, t1) != eDuplaSequencia(mao2, t2)))
        return 0;
    return 1;
}
// Verifica se a nossa jogada é valida, tendo em conta as jogadas anteriores
int eValida(SQueue q, wchar_t *maoFinal, wchar_t maoInicial[],
            int nJogadasAnteriores)
{
    if (!combinacaoPertence(maoFinal, maoInicial) || !combinacaoValida(maoFinal))
        return 0;

    if (tresPassoOuPrimeiroAJogar(nJogadasAnteriores, q))
        return 1;

    // Depois de aplicar o ordenaMao, o PASSO passa a SSOPA
    wchar_t comparar[6] = L"SSOPA";
    wchar_t jogadaAnterior[15] = {0};
    if (wcscmp(q->values[(q->length + q->front - 2) % 4], comparar) != 0)
    {
        wcscpy(jogadaAnterior, q->values[(q->length + q->front - 2) % 4]);
    }
    else if (wcscmp(q->values[(q->length + q->front - 3) % 4], comparar) != 0)
    {
        wcscpy(jogadaAnterior, q->values[(q->length + q->front - 3) % 4]);
    }
    else
    {
        wcscpy(jogadaAnterior, q->values[(q->length + q->front - 4) % 4]);
    }

    if (contaReis(jogadaAnterior) == 1 &&
        eConjunto(maoFinal, tamanho(maoFinal)) && tamanho(maoFinal) == 4)
        return 1;
    else if (contaReis(jogadaAnterior) == 1 &&
             eDuplaSequencia(maoFinal, tamanho(maoFinal)) &&
             tamanho(maoFinal) == 6)
        return 1;
    else if (contaReis(jogadaAnterior) == 2 &&
             eDuplaSequencia(maoFinal, tamanho(maoFinal)) &&
             tamanho(maoFinal) == 8)
        return 1;

    else if (contaReis(jogadaAnterior) == 3 &&
             eDuplaSequencia(maoFinal, tamanho(maoFinal)) &&
             tamanho(maoFinal) == 10)
        return 1;

    else if (tamanhoETipoIgual(maoFinal, jogadaAnterior, tamanho(maoFinal),
                               tamanho(jogadaAnterior)) &&
             maiorValor(maoFinal, jogadaAnterior))
        return 1;

    return 0;
}

void printaMaoInicial(wchar_t maoInicial[], int tamanho)
{
    int k;
    for (k = 0; k < tamanho; k++)
    {
        if (k == tamanho - 1)
        {
            wprintf(L"%lc", maoInicial[k]);
        }
        else
        {
            wprintf(L"%lc ", maoInicial[k]);
        }
    }
}

void testa(wchar_t maoInicial[], SQueue maosAnteriores, int nJogadasAnteriores,
           int IndiceTeste)
{
    // Lê as n jogadas anteriores
    for (int j = 0; j < nJogadasAnteriores + 2; j++)
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

            if (j > 4)
                Sdequeue(maosAnteriores);
            Senqueue(maosAnteriores, jogadaAtual);
        }
        if (j == nJogadasAnteriores + 1)
        {
            wchar_t *maoFinal = maosAnteriores->values[(
                ((maosAnteriores->front + maosAnteriores->length) - 1) % 4)];
            wprintf(L"Teste %ld\n", IndiceTeste + 1);
            if ((eValida(maosAnteriores, maoFinal, maoInicial, nJogadasAnteriores) ==
                 0))
            {
                printaMaoInicial(maoInicial, tamanho(maoInicial));
            }
            else
                printMao(maoInicial, tamanho(maoInicial), maoFinal);
            wprintf(L"\n");
        }
    }
}

int main()
{
    setlocale(LC_CTYPE, "C.UTF-8");
    int nTestes = 0;

    assert(wscanf(L"%d", &nTestes) == 1);

    for (int i = 0; i < nTestes; i++)
    {
        int nJogadasAnteriores;
        assert(wscanf(L"%d", &nJogadasAnteriores) == 1);
        limpaBuffer();
        wchar_t maoInicial[BUFSIZ]; // Mão inicial do jogador
        SQueue maosAnteriores = SinitQueue();
        testa(maoInicial, maosAnteriores, nJogadasAnteriores, i);
        for (int j = 0; j < maosAnteriores->length; j++)
        {
            free(maosAnteriores->values[j]);
        }
        free(maosAnteriores);
    }

    return 0;
}
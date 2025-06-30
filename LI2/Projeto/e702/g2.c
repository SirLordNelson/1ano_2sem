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
void ordenaMatriz(wchar_t *matriz[], int linhas, int tamanho) //ordena a jogada
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

int main(){

    setlocale(LC_CTYPE, "C.UTF-8");
    int numtestes=0;
    assert(wscanf(L"%d", &numtestes) == 1);

    for (int i = 0; i < numtestes; i++){
        int nlinhas=0;
        assert(wscanf(L"%d", &nlinhas) == 1);
        //nlinhas++;
        wchar_t *matriz[nlinhas];                // guardar as maos
        int matrizTm[nlinhas];                // guardar os tamanhos das maos

        for (int j = 0; j <= nlinhas; j++){
            wchar_t mao[58];
            assert(fgetws(mao, 58, stdin) != NULL);
            if (mao[0] != L'\n'){
                int tamanho = wcslen(mao) - 1;   // saber o tamanho da mao
                ordenaMao(mao, tamanho);
                matriz[j-1] = wcsdup(mao);
                matrizTm[j-1] = tamanho;       // copia o tamanho da mao para a matrizTm
            }
        }
        //nlinhas--;
        wprintf(L"Teste %d\n", i + 1);
        Principal2(matriz, matrizTm, nlinhas); // vai ordenar as maos na matriz, e printá-las
    }
    return 0;
}


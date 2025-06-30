#include <assert.h>
#include <locale.h>
#include <stdio.h>
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

int partition(wchar_t v[], int N, int x) //organiza o deck
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


void Principal(wchar_t mao[], int tm) {
  ordenaMao(mao, tm);
  if (eConjunto(mao, tm))
    wprintf(L"conjunto com %d cartas onde a carta mais alta é %lc\n", tm,
            mao[tm - 1]);
  else if (eSequencia(mao, tm)) {
    wprintf(L"sequência com %d cartas onde a carta mais alta é %lc\n", tm,
            mao[tm - 1]);
  } else if (eDuplaSequencia(mao, tm))
    wprintf(L"dupla sequência com %d cartas onde a carta mais alta é %lc\n",
            tm / 2, mao[tm - 1]);
  else
    wprintf(L"Nada!\n");
}

int main() {
  setlocale(LC_CTYPE, "C.UTF-8");

  int linhas;
  assert(wscanf(L"%d", &linhas) == 1);
  for (int i = 0; i <= linhas; i++) {
    wchar_t mao[58]; // Array para armazenar a sequência

    // Ler a sequência de wchar_t
    if (*(fgetws(mao, 58, stdin)) != '\n') {

      size_t tamanho = wcslen(mao) - 1;

      Principal(mao, tamanho);
    }
  }

  return 0;
}
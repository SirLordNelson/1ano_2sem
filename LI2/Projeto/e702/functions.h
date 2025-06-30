#ifndef DECK_H
#define DECK_H

#include <assert.h>
#include <locale.h>
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>

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

void qsorte(wchar_t a[], int n)
{
  if (n < 2)
    return;
  int p = partition(a, n - 1, a[n - 1]);
  swap(a, p, n - 1);
  qsorte(a, p);
  qsorte(a + p + 1, n - p - 1);
}

void ordenaMao(wchar_t mao[], int tm) { qsorte(mao, tm); }

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
  int arrayIndexado[14];
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

// Faz parte da nossa mao (Feito)
// Se as tiver 4 ou mais jogadas antes: - Pegar nas ultimas quatro values. Se as ultimas tres forem passos. Printar a mao sem essas values
//                                                                         Senao Pegar na ultima combinaçao, e ver se é do mesmo tipo, do mesmo tamanho, e maior do que a outra
//                                                                                                          Se essa combinaçao, a carta mais alta for um REI, pode: - Jogar um conjunto de 4 values eguistas
//                                                                                                                                                                  - Jogar uma dupla sequencia de 6 values
//                                                                                                                              as values mais altas forem um par de REIS: - Jogar uma dupla sequencia de 8 values
//                                                                                                                                                         uma tripla de REIS: - Jogar uma dupla sequencia de 10 values
//                                      - Senao pegar em todas

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

int cPertenceM(wchar_t mao[], wchar_t c[], int tmNossaJogada, int tmMao)
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
  size_t tamanho = wcslen(ultComb);

  for (int i = 0; i < 1; i++)
  {
    if (ultComb[i] == 0x1F0AE || ultComb[i] == 0x1F0BE || ultComb[i] == 0x1F0CE || ultComb[i] == 0x1F0DE)
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
    else if (verValor(nossaJogada[tmNossa - 1]) < verValor(ultComb[tamanho - 1]))
      return 0;
    else if (verValor(nossaJogada[tmNossa - 1]) == verValor(ultComb[tamanho - 1]))
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
      if (wcscmp(Jogadas->values[(numJogadasAnteriores - i) % 4], L"PASSO") != 0)
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

#endif
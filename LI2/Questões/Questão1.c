#include <stdio.h>
#include <locale.h>
#include <wchar.h>

int main() {
    int dia, mes;

    /* Mudar para UTF8 */
    setlocale(LC_CTYPE, "C.UTF-8");

    if(scanf("%d%d", &dia, &mes) == 2) {
        wchar_t c;
        if ((mes == 3 && dia >= 21) || (mes == 4 && dia <= 20)) {
            c = 0x2648;
    	    wprintf(L"%lc\n", c);
        } else if ((mes == 4 && dia >= 21) || (mes == 5 && dia <= 20)) {
          c = 0x2649;
          wprintf(L"%lc\n", c);
        }else if ((mes == 5 && dia >= 21) || (mes == 6 && dia <= 20)) {
          c = 0x264a;
          wprintf(L"%lc\n", c);
        }else if ((mes == 6 && dia >= 21) || (mes == 7 && dia <= 22)) {
          c = 0x264b;
          wprintf(L"%lc\n", c);
        }else if ((mes == 7 && dia >= 23) || (mes == 8 && dia <= 22)) {
          c = 0x264c;
          wprintf(L"%lc\n", c);
        }else if ((mes == 8 && dia >= 23) || (mes == 9 && dia <= 22)) {
          c = 0x264d;
          wprintf(L"%lc\n", c);
        }else if ((mes == 9 && dia >= 23) || (mes == 10 && dia <= 22)) {
          c = 0x264e;
          wprintf(L"%lc\n", c);
        }else if ((mes == 10 && dia >= 23) || (mes == 11 && dia <= 21)) {
          c = 0x264f;
          wprintf(L"%lc\n", c);
        }else if ((mes == 11 && dia >= 22) || (mes == 12 && dia <= 21)) {
          c = 0x2650;
          wprintf(L"%lc\n", c);
        }else if ((mes == 12 && dia >= 22) || (mes == 1 && dia <= 19)) {
          c = 0x2651;
          wprintf(L"%lc\n", c);
        }else if ((mes == 1 && dia >= 20) || (mes == 2 && dia <= 18)) {
          c = 0x2652;
          wprintf(L"%lc\n", c);
        }else if ((mes == 2 && dia >= 19) || (mes == 3 && dia <= 20)) {
          c = 0x2653;
          wprintf(L"%lc\n", c);
        }
    }

    return 0;
}
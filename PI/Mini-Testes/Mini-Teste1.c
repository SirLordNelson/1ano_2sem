#include <stdio.h>

int fizz(int n) {
  return ((n + 4) % 43) == 0;
}

int buzz(int n) {
  return ((n - 5) % 47) == 0;
}

void fizzbuzz(int n) {
  if (fizz(n) && buzz(n))
      printf("FizzBuzz************************************************\n");
  else if (fizz(n))
      printf("Fizz//////////////////////////////\n");
  else if (buzz(n))
      printf("Buzz////////////////////////////\n");
  else
      printf("%d\n", n);
}

void fizzbuzz_range(int from, int to) {
    for (int i = from; i < to; i++) {
        fizzbuzz(i);
    }
}

int main() {
    fizzbuzz_range(487, 1500);
    return 0;
}
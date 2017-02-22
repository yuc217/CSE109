#include <stdio.h>

#define N 5

void fcn(int b[]) {
  printf("%d\n", sizeof(b) /sizeof (b[0]);
}

int main(int argc, char *argv[]) {
  int a[] = { 5, 6, 7, 8, 9 };
  int *b;

  printf("%d\n", sizeof(a)/sizeof(a[0]) );
  fcn(a);
  b = a;
  //b++;b--;b--;

  b = 3;
  *(b+1) = 3;
  
  printf("%d %d\n", sizeof(b)/sizeof (b[0]), *(b + 1), b[1] );
}

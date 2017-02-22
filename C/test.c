#include <stdio.h>


#ifndef HELLO
#define HELLO 1


#endif


int copyFile(char *fileName) {
  FILE *in;
  int ch;

  in = fopen(fileName, "r");

  if (!in)
    return 1;

  while ((ch = fgetc(in))) {
    printf("%d %c\n", ch, ch);
    if (ch == EOF) break;
  }

  fclose(in);
}

int main(int argc, char *argv[]) {

  int iarg;
  for (iarg = 1; iarg < argc; ++iarg) {
    copyFile(argv[iarg]);
  }

  return 0;
}

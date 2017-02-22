#include <stdio.h>

int copyFile(char *fileName) {
  FILE *in;
  int ch;

  in = fopen(fileName, "r");

  if (!in)
    return 1;

  while ((ch = fgetc(in)) != EOF) {
    putchar(ch);
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

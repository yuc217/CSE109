#include <stdio.h>

int copyFile(char *fileName) {
  FILE *in;
  char buf[1000];

  in = fopen(fileName, "r");

  if (!in)
    return 1;

  while (fgets(buf, 1000, in) != NULL) {
    puts(buf);
  }

  fclose(in);
  return 0;
}

int main(int argc, char *argv[]) {

  int iarg;
  for (iarg = 1; iarg < argc; ++iarg) {
    copyFile(argv[iarg]);
  }
  
  return 0;
}

#include <stdio.h>

int main(int argc, char *argv[]) {

  unsigned short ui; 
  for (ui = 0; ui <= 64535; ui += 1000) {
    short i = ui;
    printf("%6u %6i %6x\n", ui, i, ui);
  }

  return 0;
}

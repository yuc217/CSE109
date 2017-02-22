#include <stdio.h>
#include <string.h>

struct bytes {
  unsigned short b1:8, b2:8;
};

union Data
{
  int i;
  unsigned int ui;
  short si;
  unsigned short usi;
  struct bytes bb;
  float f;
  char str[20];
} stack[100];

int main( )
{
  union Data data;

  data.bb.b2 = 1;
  //data.usi = 65534;
  // data.f = 220.5;
  //  strcpy( data.str, "C Programming");

  printf( "data.i : %d\n", data.i);
  printf( "data.ui : %u\n", data.ui);
  printf( "data.si : %d\n", data.si);
  printf( "data.usi : %u\n", data.usi);
  printf( "data.f : %f\n", data.f);
  printf( "data.str : %s\n", data.str);

  return 0;
}

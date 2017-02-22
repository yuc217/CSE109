#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NSTUDENTS 5

struct person {
  char name[15];
  char email[6];
  int age;
} p = { "Jim Smith", "abc123", 29 };

struct person q;

int main(int argc, char *argv[]) {
  struct person *p2 = malloc(sizeof(struct person));
  strcpy(p2->name, "Sue Jones");
  strcpy(p2->email, "123abc");
  p2->age = 25;
  
  printf("%s %s %d\n", p.name, p.email, p.age);
  printf("%s %s %d\n", p2->name, p2->email, p2->age); 

  free(p2);
  
  return 0;
}

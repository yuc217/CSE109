#include <stdio.h>  
#include <stdlib.h>
struct Person {
  char* name;
  int age;
};

void printit(struct Person *person) {
	printf("%s %d \n",person->name,person->age);
}

int main(int argc, char** argv) {
  struct Person *p = malloc(sizeof(struct Person));
  p->name = malloc(sizeof(char *));
  printf("Enter name: ");
  scanf("%s", p->name);
  printf("Enter age: ");
  scanf("%d", &(p->age));
  printit(p);
  free(p);
}


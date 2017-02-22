#include <stdio.h>

int main()
{
  char fname[20];
  char lname[20];
  int age;
  
  printf("Enter lastname, firstname: ");
  scanf("%s %s", lname, fname);
  printf("Enter age: ");
  scanf("%d", &age);  

  printf("Entered Name: %s %s\n", fname, lname);
  printf("Entered Age: %-15d\n", age);

  return 0;
}

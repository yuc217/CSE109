#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

  char str1[] = "Hello";
  char str2[] = "Goodbye";
  char str[14];

  strcpy(str, str1);
  strcat(str, str2);

  printf("%s + %s = %s\n", str1, str2, str);
  printf("The length of %s is %d\n", str, strlen(str));

  char s1[] = "abc";
  char s2[] = "abd";
  
  int tmp = strcmp(s1, s2);
  if (tmp < 0)
    printf("%s < %s\n", s1, s2);
  else if (tmp > 0)
    printf("%s > %s\n", s1, s2);
  else
    printf("%s == %s\n", s1, s2);

  char s[] = "This is a test";

  char *token = strtok(s, " ");
  while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, " ");
  }
  
}

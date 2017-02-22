#include <stdio.h>
int main(int argc, char *arg[]) {
	char* str = "This is a string";
	while(*str){
		if(*str == ' ') printf("\n");
		else putchar(*str);
		*str++;
	}
	printf("\n");
	return 0;
}

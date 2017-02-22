/* 
CSE 109
Yuchen Cai
yuc217
Program #2 create shell works as a terminal
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
char ** getopts(char cmd[]); // prototype 

int main(int argc, char *arg[]) {
	char str[1000];
	char name[64];
	char **argv;
	char *newline;
	gethostname(name,64); // defined by 64
	// call gethostname
	printf("%s >",name);
	// replace new line by 0

	// get from input 
	fgets(str,1000,stdin); 
	newline = strstr(str,"\n");  // replace new line
	if(newline!=NULL){
		*newline = '\0'; // with 0 
	}

	// if exit is not typed 
	while(strcmp(str,"exit")!=0){
		// call the function 
		argv = getopts(str);
		if (fork() == 0) {
			execvp(argv[0], argv);
		} 
		else wait(NULL);
		// repeat 
		printf("%s >",name);
		fgets(str,1000,stdin); 
		newline = strstr(str,"\n");
		if(newline!=NULL){
			*newline = '\0';
		}
	}
	return 0;
}

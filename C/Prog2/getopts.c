/* 
CSE 109
Yuchen Cai
yuc217
Program #2: takes command string and divide the str 
getopts -> process the commd string 
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/** getopts function takes a string and returns array of str*/
char ** getopts(char cmd[]){
	int num1=0;  // intialize the counter for loop 
	int num2=0;  // initialze a second counter for loop 
	char** strArr;	// declare the array of str to be returned 
	char strCopy[100];   // create a str of size 100 to store cmd
	char* token;  // each different token is a word in string 

	// first step copy the str to the commd 
	strcpy(strCopy,cmd);
	token = strtok(strCopy," "); // seperathe first string 
	while(token!=NULL){  // if the string is not a NULL pointer 
		num1++; // increment counter 
		token = strtok(NULL," "); // subsequent use NULL
	}
	// allocate mem for the who array string
	strArr = (char**) malloc(num1*sizeof(char*)); 
	// copy again 
	strcpy(strCopy,cmd);
	// first token 
	token = strtok(strCopy," ");
	for (;token!=NULL;num2++){ // go throug the loop again 
		// allocate for every word 
		strArr[num2] = (char*) malloc(strlen(token)*sizeof(char)); 
		// copy to array 
		strcpy(strArr[num2],token);
		// update token 
		token = strtok(NULL," ");
	}
	
return strArr; // return the array 
}

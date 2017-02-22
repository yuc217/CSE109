/*
CSE 109
Yuchen Cai
yuc217
Program Description: stdin -> stdout
Program #1
*/

// include standard file to use  
#include <stdio.h>  
#include <ctype.h>  // for toupper() function 
#include <string.h> 

/*
   
    NEED TO ADD SPACE WHEN USING -r COMMAND

*/


/** reverse function */ 
void reverseFunc(char str[],int length){
  int i; // declare index number 
  for(i =length-1;i>=0;i--){ // decrement
    putchar(str[i]); //putchar from last to first
  }
}

/** main method */ 
int main(int argc,char *argv[]){
  
  // declare variable 
  int ch;int i; int upper=0; int reverse=0;
  char stack[100];
  int index=0;
  
  // go through for loop to look for -u 
  for (i =1; i<argc;i++) {
    // if command has -u then variable set to 1
    if (strcmp(argv[i],"-u")==0) upper =1;
    // else if command has -r then set reverse variable to 1
    else if (strcmp(argv[i],"-r")==0) reverse=1;
    // is illegal statment is used then print error message
    else{
      fprintf(stderr,"Invalid command line option!\n");
      return 0;
    }
  }

  // here to start go through the standard in 
  while ((ch = getchar()) != EOF) {
    // if encoutner blank space 
    if (ch == ' '){
      // if index is not zero which means has character in stack
      if(index) {
        // then call reverse function 
        reverseFunc(stack,index);
        index =0; // set index back to zero
      }
      putchar(ch); // output blank 
    }

    // if not blank space 
    else {
      // if upper case command is in input,
      // conver each char to upper case
      if (upper ==1) ch = toupper(ch); 

      // if reverse command is in input 
      if (reverse ==1){     
        stack[index]=ch;  // put char in the stack
        index++; // increment index to add stack
      }
      else putchar(ch); // output char
    }
  }
  return 0;
}


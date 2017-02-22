/*
CSE 109
Yuchen Cai
yuc217
Program description: parser
Program #6 */
#include <cstdlib>
#include <string>
#include "Token.h"

// constructor 
Token::Token(int t, string l, int line, int pos){
	tokenType = t; 
	lex = l;
	lineNum = line;
	charPos = pos; 
}
Token::Token(){
	Token(0,"",0,0);
}
// deconstructor 
Token::~Token(){}
int Token::type(){
	return tokenType;
}

string Token::lexeme(){
	return lex;
}

int Token::line(){
	return lineNum;
}

int Token::pos(){
	return charPos;
}
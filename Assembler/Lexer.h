/*
CSE 109
Yuchen Cai
yuc217
Program description: parser
Program #6 */
#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include <string>
#include "Token.h"
using namespace std;

class Lexer{

public:
	// constructors 
	Lexer(istream& input);
	istream& in;
	~Lexer();
	// functions 
	char nextChar();
	Token nextToken();

	unsigned int line;
	unsigned int pos;

	// char next();
	// constatn fileds 
	static const int INTLIT = 1;
	static const int FLOATLIT = 2;
	static const int STRLIT = 3;
	static const int IDENT = 4;

	static const int PLUS = 5;
	static const int MINUS = 6;
	static const int TIMES = 7;
	static const int DIVIDE = 8;
	static const int REM = 9;
	static const int ASSIGN = 10;
	static const int LPAREN = 11;
	static const int RPAREN = 12;
	static const int COMMA = 13;
	static const int EQ = 14;
	static const int LT = 15;
	static const int LE = 16;
	static const int GT = 17;
	static const int GE = 18;
	static const int NE = 19;

	static const int SET = 20;
	static const int PRINT = 21;
	static const int WHILE = 22;
	static const int DO = 23;
	static const int END = 24;
	static const int AND = 25;
	static const int OR = 26;
	static const int IF = 27;
	static const int THEN = 28;
	static const int ELSE = 29;
	static const int ENDIF = 30;
	static const int PROGRAM = 31;

	static const int ENDOFFILE = 32;
	static const int ERROR = 33;

static const int FOR = 34;	
static const int TO = 35;
	string str[60];
	// char c;

};

#endif
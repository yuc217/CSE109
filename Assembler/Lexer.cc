/*
CSE 109
Yuchen Cai
yuc217
Program description: parser
Program #6 */

#include <iostream>
#include <cstdio>
#include "Lexer.h"
#include "Token.h"
#include <string>
#include <cctype>
using namespace std;
// constructor 
Lexer::Lexer(istream& input):in(input){
	line = 0;
	pos =0;	
}
// deconstructor 
Lexer::~Lexer() {}
// next char function 
char Lexer::nextChar(){
	int mypos = 0; int myline = 0;string nline; int num=0;
	while (!in.eof()){
		getline(in,nline);
		str[num] = nline; 
		
		num++;
	}
	if(in.eof())  return '$';
	char ch = in.get(); mypos++;
	if (ch == '\n') { myline++; mypos = 0; ch = nextChar();}
	else if (ch == ' '){ mypos++; ch=nextChar();}
	if(ch!='#') return ch;
	else{  // with #
		do{ if(in.eof()) return '$'; ch = in.get();
		}while(ch!='\n');
		myline++; mypos =0;
		return in.get();}
	return ch;
}

Token Lexer::nextToken(){
	nextChar();
	string s = "";
	if (pos >  1000 ) {pos = 0;} // if pos = -1
	char c = str[line][pos];	 
	while (c=='#'|| c=='\0') {
	line++;pos=0;c=str[line][pos];
	}	// take care of space
	while(c==' '|| c=='\t'||c=='\0') {
		pos++;
		if(pos == str[line].size()) {line++;pos=0;}
		c = str[line][pos]; 
	}	
	int curpos=pos;
	int lin = line;
	if(pos == str[line].size()) {line++;pos=0;}
	

	if (line<=20){  
		if(isalpha(c)){
		s = "";
		do{
			s += c;
			if (pos == str[line].size()) {line++;pos=-1;break;}
			c = str[line][++pos];
		}while(isalpha(c)|| isdigit(c));
		if (s=="set") return Token(SET,s,lin,curpos);			
		else if (s== "print") return Token(PRINT,s,lin,curpos);
		else if (s== "while") return Token(WHILE,s,lin,curpos);
		else if (s== "do") return Token(DO,s,lin,curpos);
		else if (s== "end") return Token(END,s,lin,curpos);
		else if (s== "and") return Token(AND,s,lin,curpos);
		else if (s== "or") return Token(OR,s,lin,curpos);
		else if (s== "if") return Token(IF,s,lin,curpos);			
		else if (s== "then") return Token(THEN,s,lin,curpos);
		else if (s== "else") return Token(ELSE,s,lin,curpos);
		else if (s== "endif") return Token(ENDIF,s,lin,curpos);
		else if (s== "program") return Token(PROGRAM,s,lin,curpos);
		else return Token(IDENT,s,lin,curpos);
		}
	
		else if (isdigit(c)){
		s="";
		do{
			s += c; 		
			if (pos == str[line].size()) {
				line++;pos=-1;
				c = str[line][++pos]; break;}
			else c = str[line][++pos];
		}while(isdigit(c));
		// FLOAT
		if(c== '.') {
			do{
				s += c; 
				if (pos == str[line].size()) {line++;pos=-1;break;}
				c = str[line][++pos];
				if (c=='#'){line++;pos=0;}
			}while(isdigit(c));
		}
		else return Token(INTLIT,s,lin,curpos);			
		return Token(FLOATLIT,s,lin,curpos);
		}

		// STRLIT modified 
	else if (c=='"'){		
			do{
				
				if (pos == str[line].size()) {line++;pos=-1;}
				c = str[line][++pos];
				if (c== '"') break;
				s=s+c;
			}while(c!='"');
			
			//c = str[line][++pos];
			 // now is a '	
			
			if (pos == str[line].size()) {
				line++;pos=-1;}
			c = str[line][++pos];	
			return Token(STRLIT,s,lin,curpos);
		}
	
		else{
			switch(c){
			case ',':
				if (pos == str[line].size()) {line++;pos=-1;}
				c = str[line][++pos];
				return Token(COMMA,",",lin,curpos);
			case '+': 
				if (pos == str[line].size()) {line++;pos=-1;}
				c = str[line][++pos];
				return Token(PLUS,"+",lin,curpos);
			case '-':
				if (pos == str[line].size()) {line++;pos=-1;}
				c = str[line][++pos];
				 return Token(MINUS,"-",lin,curpos);
			case '*': 
				if (pos == str[line].size()) {line++;pos=-1;}
				c = str[line][++pos];
				return Token(TIMES,"*",lin,curpos);
			case '/': 
				if (pos == str[line].size()) {line++;pos=-1;}
				c = str[line][++pos];
				return Token(DIVIDE,"/",lin,curpos);
			case '%': 
				if (pos == str[line].size()) {line++;pos=-1;}
				c = str[line][++pos];
				s = " "; s+='%';
				return Token(REM,s,lin,curpos);
			case '=': 
				if (pos == str[line].size()) {
					line++;pos=-1;
					c = str[line][++pos];
					return Token(ASSIGN,"=",lin,curpos);
				}
				else c = str[line][++pos];
				if (c == '='){
					c = str[line][++pos];
					return Token(EQ,"==",lin,curpos);
				}
				else return Token(ASSIGN,"=",lin,curpos);
			case '(':
				if (pos == str[line].size()) {line++;pos=-1;}
				c = str[line][++pos];
				return Token(LPAREN,"(",lin,curpos);
			case ')':
				if (pos == str[line].size()) {line++;pos=-1;}
				c = str[line][++pos];
				if (c == ' ') {c = str[line][++pos]; }
				return Token(RPAREN,")",lin,curpos);
			case '<': 
				if (pos == str[line].size()) {
					line++;pos=-1;
					c = str[line][++pos];
					return Token(LT,"<",lin,curpos);
				}
				else c = str[line][++pos];
				if (c == '='){
					c = str[line][++pos];
					return Token(LE,"<=",lin,curpos);
				}
				else return Token(LT,"<",lin,curpos);
			case '>': 
				if (pos == str[line].size()) {
					line++;pos=-1;
					c = str[line][++pos];
					return Token(GT,">",lin,curpos);
				}
				else c = str[line][++pos];
				if (c == '='){
					c = str[line][++pos];
					return Token(GE,">=",lin,curpos);
				}
				else return Token(GT,">",lin,curpos);
			case '!': 
				if (pos == str[line].size()) {
					line++;pos=-1;
					c = str[line][++pos];}		
				else if (c == '='){
					c = str[line][++pos];
					return  Token(NE,"!=",lin,curpos);
				}
			case '$': return Token(ENDOFFILE,"$",lin,curpos);
			default: s+=c; 
			cout<< "error " <<c <<"E"<<endl;return  Token(ERROR,s,lin,curpos);
			}
		}
	}
	else return Token(ENDOFFILE,"$",lin,curpos);
}

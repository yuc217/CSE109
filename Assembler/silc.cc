/*
CSE 109
Yuchen Cai
yuc217
Program description: parser
Program #6 */
#include "Token.h"
#include "Lexer.h"
#include <iostream>
#include <fstream>
#include "parser.h"
using namespace std;

bool genCode=true;

void processFile(istream&in){
  Lexer lex(in);
  Token token;
  Parser parser(lex, cout);
  Parser::TreeNode* program=parser.program();
  if(genCode){
    parser.generateCode(program);
  }
  else{
    cout<<Parser::TreeNode::toString(program)<<endl;
  }
}

int main(int argc, char **argv) {
  ifstream in;
  
  if (argc > 1) {
    string a1 = argv[1];
    if (a1 == "-h") {
      cout << "Usage: silc [-h | -p ] [<filename>]\nOptions:\n  -h Display this message\n  -p Parse the file and display the tree (no code generation)\nThe compiler will read from standard input if no filename is given.\nAll output goes to standard output.\n";
      return 0;
    } else if (a1 == "-p") {
      genCode = false;
    } else {
      in.open(argv[1]);
      processFile(in);
      in.close();
      return 0;
    }
    if (argc > 2) {
      in.open(argv[2]);
      processFile(in);
      in.close();
      return 0;
    } else {
      processFile(cin);
    }
  } else {
    processFile(cin);
  }
  
}

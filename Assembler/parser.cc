/*
CSE 109
Yuchen Cai
yuc217
Program description: parser
Program #6 */
#include "parser.h"
#include <cstring>
#include <iostream>

const string Parser::ops[] = {"ADD", "SUB", "AND", "DIV", "REM", "ISEQ", "ISGE", "ISGT", "ISLE",
            "ISLT", "ISNE", "MULT", "OR", "LOADL", "LOADV", "STOREV", "JUMPF",
            "JUMP", "INSLABEL", "PRINT", "SEQ", "NULLX", "PRINTLN", "PRINTS"};

Parser::Parser(Lexer& lexerx, ostream& outx): lex(lexerx), out(outx), lindex(1), tindex(1) {
  token = lex.nextToken();
}

Parser::~Parser() {}

void Parser::genCode() {
  TreeNode* programNode = program();
  generateCode(programNode);
}

void Parser::gen(TreeNode* node) {
  switch (node->op) {
    case SEQ:
    case NULLX:
      break;
    case LOADL:
    case LOADV:
    case STOREV:
    case JUMPF:
    case JUMP:
      emit(node->op, node->val);
      break;
    case PRINTS:
      emit(node->op, "\"" + node->val + "\"");
      break;
    case INSLABEL:
      emit(node->val);
      break;
    default:
      emit(node->op);
  }
}

void Parser::generateCode(TreeNode* node) {
  if (node != NULL) {
    generateCode(node->leftChild);
    generateCode(node->rightChild);
    gen(node);
  }
}

Parser::TreeNode* Parser::optimize(TreeNode* node) {
    return NULL;
}

void Parser::error(string message) {
  cerr << message << " Found " << token.lexeme() << " at line " << token.line() << " position " << token.pos() << endl;
  exit(1);
}

void Parser::check(int tokenType, string message) {
  if (token.type() != tokenType)
    error(message);
}

Parser::TreeNode* Parser::factor() {
  TreeNode* factorNode = NULL; 
  int tokenType = token.type();
  switch(tokenType){
    case Token::LPAREN:
      token = lex.nextToken();
      factorNode = expression();
      check(Token::RPAREN,"Here needs a right parenthesis.");
      break;
    case Token::INTLIT:
    case Token::FLOATLIT:
      factorNode = new TreeNode(LOADL,token.lexeme());break;
    case Token::IDENT:
      factorNode = new TreeNode(LOADV,token.lexeme());break;
    default: error("expect ( int or float ot ident"); break;   
  }
  token = lex.nextToken();
  return factorNode;
}

Parser::TreeNode* Parser::term() {
  TreeNode* termNode = factor();
  TreeNode* factorNode;
  int tokenType = token.type();
  while (tokenType == Token::TIMES || tokenType == Token::DIVIDE || tokenType == Token::REM) {
    token = lex.nextToken();
    factorNode = factor();
    switch (tokenType) {
      case Token::TIMES:
        termNode = new TreeNode(MULT, termNode, factorNode);
        break;
      case Token::DIVIDE:
        termNode = new TreeNode(DIV, termNode, factorNode);
        break;
      case Token::REM:
        termNode = new TreeNode(REM, termNode, factorNode);
        break;
    }
    tokenType = token.type();
  }
  return termNode;
}

//<expression> = <term> { PLUS <term> | MINUS <term> }
Parser::TreeNode* Parser::expression() {
  TreeNode* expressionNode = term();
  TreeNode* termNode;
  int tokenType = token.type();
  while(tokenType==Token::PLUS || tokenType==Token::MINUS){
    token = lex.nextToken();
    termNode = term();
    switch(tokenType){
      case Token::PLUS:
        expressionNode = new TreeNode(ADD,expressionNode,termNode);break;
      case Token::MINUS:
        expressionNode = new TreeNode(SUB,expressionNode,termNode);break;
    }
    tokenType = token.type();
  }
  return expressionNode;
}

/* <relationalexpression> = <expression> ( EQ <expression> | 
LT <expression> | LE <expression> | GT <expression> | 
GE <expression> | NE <expression> ) */
Parser::TreeNode* Parser::relationalExpression(){
  TreeNode* leftNode = expression();
  if(token.type()==Token::EQ){
    token=lex.nextToken();
    TreeNode* rightNode=expression();
    return new TreeNode(ISEQ, leftNode, rightNode);
  }
  else if(token.type()==Token::LT){
    token=lex.nextToken();
    TreeNode* rightNode=expression();
    return new TreeNode(ISLT, leftNode, rightNode);
  }
  else if(token.type()==Token::LE){
    token=lex.nextToken();
    TreeNode* rightNode=expression();
    return new TreeNode(ISLE, leftNode, rightNode);
  }
  else if(token.type()==Token::GT){
    token=lex.nextToken();
    TreeNode* rightNode=expression();
    return new TreeNode(ISGT, leftNode, rightNode);
  }
  else if(token.type()==Token::GE){
    token=lex.nextToken();
    TreeNode* rightNode=expression();
    return new TreeNode(ISGE, leftNode, rightNode);
  }
  else if(token.type()==Token::NE){
    token=lex.nextToken();
    TreeNode* rightNode=expression();
    return new TreeNode(ISNE, leftNode, rightNode);
  }
  else{
    error("relation expression not found");
  }
  return leftNode;
}

// <logicalexpression> = <relationalexpression> { 
//AND <relationalexpression> | OR <relationalexpression> }
Parser::TreeNode* Parser::logicalExpression(){
  TreeNode* relationNode=relationalExpression();
  while(token.type()==Token::AND||token.type()==Token::OR){
    token=lex.nextToken();
    TreeNode* rightNode=relationalExpression();
    relationNode=new TreeNode(SEQ, relationNode, rightNode);
  }
  return relationNode;
}

// <setstatement> = SET IDENT ASSIGN <expression>
Parser::TreeNode* Parser::setStatement() {
  //cout << "set"<<endl;
  TreeNode* setNode = NULL;
  TreeNode* expressionNode;
  check(Token::SET,"Here should a SET.");
  token = lex.nextToken();
  check(Token::IDENT,"Here should be a identifier.");
  string l = token.lexeme();
  token = lex.nextToken();
  check(Token::ASSIGN,"Here should be an ASSIGN.");
  TreeNode* store = new TreeNode(STOREV,l);
  token = lex.nextToken();
  expressionNode = expression();
  setNode = new TreeNode(SEQ,expressionNode,store);
  return setNode;
}

// <printExpression> = ( <expression> | STRLIT )
Parser::TreeNode* Parser::parsePrintExpression(){
  TreeNode *printE = NULL;
  TreeNode *expressionNode;
  int tokenType = token.type();
  if (tokenType == Token::STRLIT){
    printE = new TreeNode(PRINTS,token.lexeme());
    token = lex.nextToken();
  }else {
    expressionNode = expression();
    printE = new TreeNode(SEQ,expressionNode,new TreeNode(PRINT));
  }
  return printE;
}

// <printstatement> = PRINT <printExpression> { COMMA <printExpression> } 
Parser::TreeNode* Parser::printStatement() {
  check(Token::PRINT,"Here should be print.");
  token = lex.nextToken();
  TreeNode* printNode = parsePrintExpression();
  TreeNode* printE;
  int tokenType = token.type();
  while (tokenType == Token::COMMA){
    token = lex.nextToken();
    if (token.type() == Token::STRLIT){
      printE = parsePrintExpression();
      printNode = new TreeNode(SEQ,printNode,printE);
    }
    else {
      printE = parsePrintExpression();
      printE->leftChild->leftChild = printNode;
      printNode = printE;
    }
    tokenType = token.type();
  }
  return new TreeNode(SEQ,printNode,new TreeNode(PRINTLN));
}

// <whilestatement> = WHILE <logicalexpression> 
// DO <compoundstatement> END 
// INSLABEL
Parser::TreeNode* Parser::whileStatement(){
  check(Token::WHILE, "expect while");
  token=lex.nextToken();

  TreeNode* leftNode=logicalExpression();
  string l1 = makeLabel();
  string l2 = makeLabel();

  leftNode = new TreeNode(SEQ,new TreeNode(INSLABEL,l1+":"),leftNode);
  TreeNode* JUMPNode = new TreeNode(JUMPF,l2);
  TreeNode* left  = new TreeNode(SEQ,leftNode,JUMPNode);
  check(Token::DO, "expect do");
  token=lex.nextToken();
  TreeNode* rightNode=compoundStatement();

  check(Token::END, "expect end");
  token=lex.nextToken();
  TreeNode* jumpto = new TreeNode(SEQ,new TreeNode(SEQ, left, rightNode),new TreeNode(INSLABEL,l2+":"));
  return jumpto;
}

// <forstatement> = FOR IDENT ASSIGN <expression> TO <expression>
// <compoundstatement> END 
Parser::TreeNode* Parser::forStatement(){
  TreeNode* forNode = NULL;
  check(Token::FOR, "expect for");
  token=lex.nextToken();
  check(Token::IDENT, "expect identifier");
  token=lex.nextToken();
  check(Token::ASSIGN, "expect assignment");
  token=lex.nextToken();
  TreeNode* leftNode=expression();
  check(Token::TO, "expect to");
  TreeNode* rightNode=expression();
  TreeNode* left = new TreeNode(SEQ, leftNode, rightNode);
  TreeNode* right =compoundStatement();
  leftNode=new TreeNode(SEQ, left, right);
  check(Token::END, "need end");
  token=lex.nextToken();
  return forNode;
}

// <ifstatement> = IF <logicalexpression> THEN <compoundstatement> 
// [ ELSE <compoundstatement> ] ENDIF
Parser::TreeNode* Parser::ifStatement(){
  
  TreeNode* ifnode = NULL;
  check(Token::IF, "expect if. ");
  token=lex.nextToken();
  string l1 = makeLabel();
  string l2 = makeLabel();
  TreeNode* logexp=logicalExpression();

  TreeNode* label1 = new TreeNode(INSLABEL,l1+":");
  TreeNode* label2 = new TreeNode(INSLABEL,l2+":");
  //TreeNode* JUMPNode = new TreeNode(JUMPF,l2);
  //TreeNode* leftNode = new TreeNode(SEQ,label1,new TreeNode(SEQ,logexp,JUMPNode));

  check(Token::THEN, "expect then. ");
  token=lex.nextToken();
  TreeNode* comp1=compoundStatement();
  
  if(token.type()==Token::ELSE){
    token=lex.nextToken();
    TreeNode* comp2=compoundStatement();
    comp2 = new TreeNode(SEQ,comp2,label2);
    TreeNode* elseNode = new TreeNode(SEQ,label1,comp2);
    TreeNode* jump = new TreeNode(SEQ,new TreeNode(JUMP,l2),elseNode);
    TreeNode* right = new TreeNode(SEQ,comp1,jump);
    ifnode = new TreeNode(SEQ,new TreeNode(JUMPF,l1),right);
  }

  else{
    //SEQ(logexp, SEQ(JUMPF(lab2), SEQ(cs, INSLABEL(lab2))))
    TreeNode* jump = new TreeNode(JUMPF,l2);
    TreeNode* right = new TreeNode(SEQ,comp1,label2);
    ifnode = new TreeNode(SEQ,jump,right);
  }

  check(Token::ENDIF, "expect endif. ");
  token=lex.nextToken();
  return new TreeNode(SEQ,logexp,ifnode);
}

/*<statement> = <setstatement> | <printstatement> | <whilestatement> |
<ifstatement> | <forstatement> */
Parser::TreeNode* Parser::statement() {
  
  //cout << "a:"<<endl;
  TreeNode* statement = NULL;
  //cout<<"in state " <<token.lexeme()<<endl;
  switch (token.type()) {
    case Token::SET:
      statement = setStatement(); break;
    case Token::PRINT:
      statement = printStatement(); break;
    case Token::WHILE:
      statement = whileStatement(); break;
    case Token::IF:
      statement = ifStatement(); break;
    case Token::FOR:
      statement = forStatement(); break;
    default:
      error("Statement:expected set,print,while,if and for. "); break;
  }
  return statement;
}

/*<compoundstatement> = <statement> { <statement> }*/
Parser::TreeNode* Parser::compoundStatement() {
  TreeNode* compoundNode = statement();
  TreeNode* statementNode;
  int tokenType = token.type();
  //cout<<"in compound " <<token.lexeme()<<endl;
  while(tokenType == Token::SET || tokenType == Token::PRINT
    || tokenType == Token::WHILE || tokenType == Token::IF
    || tokenType == Token::FOR)
  {
    statementNode = statement();
    compoundNode = new TreeNode(SEQ,compoundNode,statementNode);
    tokenType = token.type();
  }
  return compoundNode;
}

/*
<program> = PROGRAM IDENT <compoundstatement> END PROGRAM*/
Parser::TreeNode* Parser::program() {
  TreeNode* programNode;
  check(Token::PROGRAM,"PROGRAM:start program."); // program
  token = lex.nextToken(); // ident
  check(Token::IDENT,"PROGRAM: identifier.");
  string iden = token.lexeme();
  token = lex.nextToken();
  programNode = compoundStatement(); // compound statement 

  check(Token::END,"PROGRAM:END."); // end 
  //cout<< " end"<<endl;
  token = lex.nextToken();
  check(Token::PROGRAM,"PROGRAM: end program."); // program
  //cout<< " program"<<endl;
  //token = lex.nextToken();
  //cout << "last"<< endl;
  return programNode;
}

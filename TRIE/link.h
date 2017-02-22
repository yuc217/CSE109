/*
CSE 109
Yuchen Cai
yuc217
Program Description: implement trie strucutre 
Program #3 */

/* Link class */

#ifndef LINK_H
#define LINK_H

#include <iostream>

using namespace std;

class Node;

class Link{
public:
	//1) A char member variable to hold the character that takes you to the next Node.
	char var;
	//2) A Node* member variable that points to the next Node.
	Node *nextN;
	//3) A constructor
	Link();
	//4) A destructor
	~Link();
	
};   

#endif
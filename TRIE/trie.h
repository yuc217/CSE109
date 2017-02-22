/*
CSE 109
Yuchen Cai
yuc217
Program Description: implement trie strucutre 
Program #3 */

/* Trie class */

#ifndef TRIE_H
#define TRIE_H


#include <iostream>
#include <string.h>
#include "node.h"

using namespace std;


class Trie {
public:
	//1) A Node* member variable that holds a pointer to the start node.
	Node *first;
	//2) A member function:  for adding a new key and value to
	//the Trie.
	void put(string key, int value);
	//3) A member function:  for retrieving a value from the Trie using the
	//key.
	int get(string key);
	//4) A constructor
	Trie();
	//5) A destructor
	~Trie();


	// int find(Node *node, char c);
};

#endif
/*
CSE 109
Yuchen Cai
yuc217
Program Description: implement trie strucutre 
Program #3 */


/* class NODE */
#ifndef NODE_H
#define NODE_H

//#include <iostream>;
#include "link.h"
using namespace std;

class Node{
public:
	//Create a class Node that contains:
	//1) An int member variable to hold the value for the Node.
	int index;
	//2) An array member variable of 10 Link* to hold up to 10 Links to other Nodes
	Link* links[10];
	//3) An int member variable to hold the number of links being used by this Node.
	int num;
	//4) A constructor
	Node();
	// 5) A destructor
	~Node();


};


#endif
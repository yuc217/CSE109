/*
CSE 109
Yuchen Cai
yuc217
Program Description: Program #8
*/

#ifndef PROG8LIB_H
#define PROG8LIB_H

#include <iostream>
#include <queue>
#include <string>
#include <set>
using namespace std;


namespace prog8lib{
	
	

	class Node {
	public:
  	Node(string,Node*);
  	Node* pre;
  	string str;
	};


	class Search{
	public:
		queue<string> wordpath;
		queue<string> searchPath(string first,string end,set<string> dict);

	};
		
	
}

#endif
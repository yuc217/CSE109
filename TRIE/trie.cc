/*
CSE 109
Yuchen Cai
yuc217
Program Description: implement trie strucutre 
Program #3 */

/* trie */
#include <iostream>
#include <string.h>
#include "node.h"
#include "link.h"
#include "trie.h"

Trie::Trie() {
	first = new Node();
}

Trie::~Trie() {

}

// int Trie::find(Node *node,char c){
// 	for (int i=0; i<node->num;i++) {
// 		Link* tmp = node->links[i];
// 		if(tmp->var==c) {return i;}
// 	}
// 	return -1;
// }

void Trie::put(string key, int value) {
	Node *node = first;
	Link *nlink = NULL;
	int place = -1;
	unsigned int i=0;
	for(; i<key.length();i++){
		place = -1;
		for (int j=0; j<node->num;j++) {
			
			if(node->links[j]->var==key.at(i)) {
				place = j; 
				break;
			}
		}	
		//index =find(node,key.at(i));
		// for(int j=0;j<node->num;j++){
		// 	if(node -> links[j]->var == key.at(i)) 
		// 		link = node->links[i];
		// }
		// if(link == NULL){
		// 	link = new Link();
		// 	link->var = key.at(i);
		// 	node ->links[node->num] = link;
		// 	node -> num++;
		// 	link -> nextN = new Node();
		// }
		if(place !=-1 ) {
			nlink = node -> links[place];
			node = nlink->nextN;
			// if(nlink->nextN != NULL){
			// 	node = node ->links[place] ->nextN;
			// }
		}
		else {
			nlink = new Link();
			
			// link = tmp;
			nlink -> var = key.at(i);
			
			node -> links[node->num] = nlink;
			node ->num +=1;
			// node -> links[node->num] = link;
			// node -> num++;
			Node *newNode = new Node();
			nlink -> nextN = newNode;
			node = nlink->nextN;
		}
	}
	// set the value to the last node 
	node -> index = value;
}

/* get the string and return an correspoinding number */
int Trie::get(string key){
	Node *node = first;
	bool ifFound = false;
	/* go through a loop to find that string */
	for(unsigned int i=0; i<key.length();i++){
		for(int j=0; j<node->num; j++){
			if(node->links[j]->var == key.at(i)){
				node = node -> links[j] -> nextN;				
				ifFound = true;
				break;
			}
			ifFound = false;
		}
		// return -1 if not found the string
		if (ifFound == false) return -1;
	}
	return node->index;
}


/*
CSE 109
Yuchen Cai
yuc217
Program Description: implement trie strucutre 
Program #3 */

#include <iostream>
#include <string.h>
#include "trie.h"
#include "link.h"
#include "node.h"

/* main method for testing */
int main(int argc, char **argv){
	Trie t;
	// put three values 
	t.put("LEMON", 10);
	t.put("LEHIGH",11);
	t.put("LEMUNE",12);

	// get three 
	int x = t.get("LEHIGH");
	int y = t.get("LEMON");
	int z = t.get("LEMUNE");
	// out put to testtrie 
	cout << x << endl;
	cout << y << endl;
	cout << z << endl;
	cout << t.get("NON") << endl;

	return 0;
}
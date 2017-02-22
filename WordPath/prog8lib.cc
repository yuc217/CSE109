/*
CSE 109
Yuchen Cai
yuc217
Program Description: Program #8
*/

#include "prog8lib.h"

// git remote add origin __URL_ 
// git push --set ----- 

// git clone addsresswithID to some other folder

namespace prog8lib{

	Node::Node(string s,Node* n):pre(n){str = s;}

	queue<string> Search::searchPath(string first,string end,set<string> dict){	
		// the queue use as a possible path
 		queue<Node*> temp;
 		
		temp.push(new Node(first,NULL));
		// if not empty, pop out the first one in queue
		while(!temp.empty()){
			Node* top = temp.front();	
			temp.pop();
			string word = top->str;
			if(word==end) {
				wordpath.push(top->str);
				while(top->pre!=NULL){
					wordpath.push(top->pre->str);
					top=top->pre;
				}
				return wordpath;
			}// need implemenation
			
			for(unsigned int i=0;i<word.length();i++){
				for(char c='A'; c<='Z';c++){
					char tmp = word[i];
					word[i]=c;
					// if contains 
					if(dict.count(word)!=0){
						temp.push(new Node(word,top));
						//temp.push(word);
						dict.erase(word);
					}
					word[i]= tmp;
				}

			}	

		}
		queue<string> notfound; notfound.push("$");
		return notfound;
	}

}	

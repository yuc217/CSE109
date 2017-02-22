/*
CSE 109
Yuchen Cai
yuc217
Program Description: Program #8
*/
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include "prog8lib.h"
using namespace std;

int main(int argc, char** argv){
	ifstream file;
    file.open("words");
    ifstream list;
    list.open("classwords.txt");
    // checking if can open file
    if (file.fail()||list.fail()){
        cout<<"Cannot open file"<<endl;
        exit(1);
    }

    // loading dictionary
    set<string> dict;
    string line;
    while(!file.eof()){
    	getline(file,line);
    	dict.insert(line);
    }

    // read classwords
    string wordpair;
    while(!list.eof()){
    	getline(list,wordpair);

    	string list[3];
	    string s = "";
	    int num = 0; 
	    for(unsigned int i=0;i<wordpair.length();i++){	

			if(wordpair[i]==' '){
				if(num==3) break;
				list[num++]=s;s="";	

			}
			else s+=wordpair[i];
		}
		if(num<3) list[num]=s;

		if(list[1].size()==0||list[2].size()==0||list[1]=="aaaa") continue;
		else {
			cout<< list[0]<< "["<< list[1]<<","<<list[2]<<"]:";
		}



    


    using prog8lib::Search;
    Search search;
    queue<string> path = search.searchPath(list[1],list[2],dict);
    
    if(path.front()=="$") {cout << "not found" <<endl;exit(1);}

    while(!path.empty()){

    	cout << path.front() << " ";
    	path.pop();
    	
    }


    cout << "."<<endl;
    }

	return 0;
}

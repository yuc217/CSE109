/*
CSE 109
Yuchen
yuc217
Program Description: Program #7
*/
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include "hashTable.h"

using namespace std;

void processLine(string line, int index);
void token(string list[],int index);
void error(string msg);
void checkArgMap(string argument,int index);
void checkLabMap(string label,int index);
void genhex(string,string,string);
void finishtmp();
void writeFile(char*);
string tostring(int);
//string argMapOut();
//string labelMapOut();

HashTable labelMap(257);int labIndex=1;
HashTable argMap(257);int argIndex=1;
string tmp[10];int tmpIndex=0;
string program[255]; int progIndex=1; 
string orig[255]; 

int main(int argc, char **argv){
	program[0] = "CAFEBE";

	int index=0;
	// open file 
	int h =0; int in = 0; int lab = 0;
	int arg = 0; int p = 0; string line;
	//string str[255];
	for(int i=1;i<argc;i++){
		if(strcmp(argv[i],"-h")==0) h = 1;
		else if(strcmp(argv[i],"-i")==0) in = 1;
		else if(strcmp(argv[i],"-l")==0) lab = 1;
		else if(strcmp(argv[i],"-a")==0) arg = 1;
		else if(strcmp(argv[i],"-p")==0) p=1;
		else {
			ifstream file;
			file.open(argv[i]);
			while(!file.eof()){
				getline(file,line);
				orig[index]=line;
				index++;

				if(line.length()>0)
				processLine(line,index);
			}
			finishtmp();
			writeFile(argv[i]);
		}
	}
	if(h==1) {
		cout << "To pipe in a file: cat myfile.sasm | ./assemble"<<"\n";
		cout <<"Piping in a file requires the output of this program to be piped into the Linker."<<"\n";
		cout <<"To assemble 1 or more files: ./assemble file1.sasm file2.sasm ..."<<"\n";
		cout <<"Passing in file names as command line args saves them as *.s files to pass into the Linker. Command line arguments:"<<"\n";
		cout <<"-h display this usage information"<< endl;
		cout <<"-i prints all the .sasm instructions as well as their bytecode representation."<<endl;
		cout <<"-l prints the label map. The decimal value of the 1 byte hex string on the left and the respective label on the right."<<endl;
		cout <<"-a prints the instruction arguments. The decimal value of the 1 byte hex string on the left and the respective argument on the right."<<endl;
		cout <<"-p prints the bytecode of the .sasm program. It prints every instruction on its own line, mirroring the .sasm that was input."<< endl;
	}
	if(in){
		for(int i=0;i<255;i++){
  			if(program[i].length()>0){
  				cout<< program[i]<<"    "<< orig[i]<<endl;
  			}
  		}
		cout << "\n";
	}
	if(lab){
		cout << "The labels are:"<< endl; 
		cout<< labelMap <<endl;
		cout << "Bytecode:"<< endl; 
		for(int i=0;i<255;i++){
		if(labelMap.allInfo[i].length()>0)
		cout << labelMap.allInfo[i]<<endl;
	}	
		cout << "\n";
	}
	if(arg){
		cout << "The args are:(not in order)"<< endl; 
		cout<< argMap <<endl;
		cout << "Bytecode:"<< endl; 
		for(int i=1;i<255;i++){
		if(argMap.allInfo[i].length()>0)
		cout << argMap.allInfo[i]<<endl;
	}
		cout << "\n";
	}
	if(p){
		for(int i=0;i<255;i++){
  			if(program[i].length()>0){
  				cout<< program[i]<<endl;
  			}
  		}
		cout << "\n";
	}

	// finish map; forward reference 
	
	// put all information in to arrays
/**	argMap.hasharray(argMap);
	labelMap.hasharray(labelMap);
	argMap.argaddExtension();
	labelMap.labaddExtension();	
cout<< argMap<<endl;

	for(int i=0;i<255;i++){
		if(labelMap.allInfo[i].length()>0)
		cout << labelMap.allInfo[i] << endl;
	}	

	for(int i=1;i<255;i++){
		if(argMap.allInfo[i].length()>0)
		cout << argMap.allInfo[i] << endl;
	}	


	for(int i=0;i<255;i++){
		if(program[i].length()>0)
		cout << program[i]<< endl;
	}
*/
}

void processLine(string line, int index){ 

	// take care of "#" comment 
	for(unsigned int i =0;i<line.length();i++){
		if(line[i]=='#') {
			line = line.substr(0,i);
			break;
		}
	}

	// process each token seperate by space
	string list[10];
	string s = "";
	int num = 0; 
	for(unsigned i=0;i<line.length();i++){	
		if(line[i]==' '){
			list[num++] = s;s="";		
		}
		else s+=line[i];
	}
	list[num]=s;
	token(list,index);
}

void token(string list[],int index){
	//cout << index<<":" <<index << " content:"<< list[0]<<"\n"; 
	string label="$";
	string inst="$";
	string argm="$";
	int counter = 0;
	string first = list[counter];

	if(first[first.length()-1]==':') {
		label = first;
		if(list[++counter].length()>0) inst = list[1];
		if(list[++counter].length()>0) argm = list[2];
	}
	else {
		inst = first;
		if(list[++counter].length()>0) argm = list[1];
	}


	// check label 
	if(label!="$"){
		if(labelMap.inTable(label)){
			error("Label already exit.");
		}
		else {
			label = label.substr(0,label.length()-1);
			labelMap[label]=index;
		}
	}

	if(inst=="ADD"){
		if(list[++counter].length()>0) error("ADD doesn't need argument.");
		inst = "a0";
	}
	else if(inst == "SUB"){
		if(list[++counter].length()>0) error("SUB doesn't need argument.");
		inst = "a1";
	}
	else if(inst == "MULT"){
		if(list[++counter].length()>0) error("MULT doesn't need argument.");
		inst = "a2";
	}
	else if(inst == "DIV"){
		if(list[++counter].length()>0) error("DIV doesn't need argument.");
		inst = "a3";
	}
	else if(inst == "REM"){
		if(list[++counter].length()>0) error("REM doesn't need argument.");
		inst = "a4";
	}
	else if(inst == "DUP"){
		if(list[++counter].length()>0) error("DUP doesn't need argument.");
		inst = "a5";
	}
	else if(inst == "AND"){
		if(list[++counter].length()>0) error("AND doesn't need argument.");
		inst = "b0";
	}
	else if(inst == "OR"){
		if(list[++counter].length()>0) error("OR doesn't need argument.");
		inst = "b1";
	}
	else if(inst == "NOT"){
		if(list[++counter].length()>0) error("NOT doesn't need argument.");
		inst = "b2";
	}
	else if(inst == "ISEQ"){
		if(list[++counter].length()>0) error("ISEQ doesn't need argument.");
		inst = "b3";
	}
	else if(inst == "ISNE"){
		if(list[++counter].length()>0) error("ISNE doesn't need argument.");
		inst = "b4";
	}
	else if(inst == "ISGT"){
		if(list[++counter].length()>0) error("ISGT doesn't need argument.");
		inst = "b5";
	}
	else if(inst == "ISGE"){
		if(list[++counter].length()>0) error("ISGE doesn't need argument.");
		inst = "b6";
	}
	else if(inst == "ISLT"){
		if(list[++counter].length()>0) error("ISLT doesn't need argument.");
		inst = "b7";
	}
	else if(inst == "ISLE"){
		if(list[++counter].length()>0) error("ISLE doesn't need argument.");
		inst = "b8";
	}
	else if(inst == "LOADL"){
		list[++counter] = argm; inst = "c0";
		checkArgMap(argm,index);
		if(list[++counter].length()>0) error("Error.");
	}
	else if(inst == "LOADV"){
		list[++counter] = argm; inst = "c1";
		checkArgMap(argm,index);
		if(list[++counter].length()>0) error("Error.");
	}
	else if(inst == "STOREV"){
		list[++counter] = argm; inst = "c2";
		checkArgMap(argm,index);
		if(list[++counter].length()>0) error("Error.");
	}
	else if(inst == "JUMP"){
		list[++counter] = argm; inst = "d0";
		checkLabMap(argm,index);
		if(list[++counter].length()>0) error("Error.");
	}
	else if(inst == "JUMPF"){
		list[++counter] = argm; inst = "d1";
		checkLabMap(argm,index);
		if(list[++counter].length()>0) error("Error.");
	}
	else if(inst == "PRINT"){
		if(list[++counter].length()>0) error("Error. No arguments needed.");
		inst = "e0";
	}
	else if(inst == "PRINTLN"){
		if(list[++counter].length()>0) error("Error. No arguments needed.");
		inst = "e1";
	}
	else if(inst == "PRINTS"){
		list[++counter] = argm;inst = "e2";
		argm = argm.substr(1,argm.length()-2);
		checkArgMap(argm,index);
		if(list[++counter].length()>0) error("Error. No arguments needed.");
		
	}
	else if (inst == "$"){

	}
	else error("Instruction not recognized."+inst);
//	cout << "label:" << label << " inst:"<<inst
//	<< " argm:"<<argm<<endl;
	genhex(label,inst,argm);


}
void checkLabMap(string label,int index){

	if(!labelMap.inTable(label)){
		//cout << label << " int "<< index << endl;
		tmp[tmpIndex++] = label;
		tmp[tmpIndex++] = tostring(index); //tmpIndex++;
	}
}

void checkArgMap(string argument,int index){
	if(argument=="$"){
		error("should have argument here. ");
	}
	if(!argMap.inTable(argument)){
		argMap.add(argument,argIndex++);
	}
	
}
void error(string msg){
	cerr << msg << endl; exit(1);
}

void genhex(string label,string inst, string argm){
	string prog;
	// process label
	if(label == "$") label ="00";
	else {
		int labeLine= labelMap[label];
		stringstream ss;
		ss<< hex << labeLine; // int decimal value
		string hexValab (ss.str());
		if(hexValab.length()<2) label= "0"+hexValab;
		else label = hexValab;
		
	}
	int line;
	// process instruction
	if(inst == "$") inst = "00";
	else if(inst == "d0"|| inst == "d1"){//jump instruction
		line = labelMap[argm];
	}
	else line = argMap[argm];

	// process arguments 
	if(argm == "$") argm = "00";
	else{
		
		stringstream ss;
		ss<< hex << line; // int decimal value
		string hexVal (ss.str());
		if(hexVal.length()<2) argm= "0"+hexVal;
		else argm = hexVal;
	}

	//bytecode by each line
	program[progIndex++]=label+inst+argm;



}
void finishtmp(){
for(int i=0;i<10;i+=2){
		// has a label 
		if(tmp[i].length()>0){
			//cout << tmp[i+1] << endl;
			int whichLine = atoi(tmp[i+1].c_str());
			if(labelMap.inTable(tmp[i])){
			//	cout << tmp[i] << endl;
				int realLine = labelMap[tmp[i]];
				stringstream ss;ss<< hex << realLine; // int decimal value
				string change (ss.str());
				if(change.length()<2) {
					program[whichLine][4]='0';
					program[whichLine][5]= change[0];
				}
				else {
					program[whichLine][4]=change[0];
					program[whichLine][5]=change[1];
				}
				//cout << program[whichLine] << endl;
			}
			else {
				cout << tmp[i] << endl;
				error("no label found.");
			}
		}
		else break;
		}
	program[224]="000000";
}
void writeFile(char* f){
	int countfile =0;
	string fname;
	while (f[countfile]!='.'){
		fname+=f[countfile];
		countfile++;
	}
	fname+=".s";

//	cout<< fname<< endl;
	ofstream myfile;
  	myfile.open(fname.c_str());
  	for(int i=0;i<255;i++){
  		if(program[i].length()>0){
  			myfile << program[i];
  		}
  	}
  	argMap.ahasharray(argMap);
	labelMap.hasharray(labelMap);
	argMap.argaddExtension();
	labelMap.labaddExtension();	

  	for(int i=0;i<255;i++){
		if(labelMap.allInfo[i].length()>0)
		myfile << labelMap.allInfo[i];
	}	

	for(int i=1;i<255;i++){
		if(argMap.allInfo[i].length()>0)
		myfile << argMap.allInfo[i];
	}	

myfile.close();

}

string tostring(int number){
ostringstream ss;
     ss << number;
     return ss.str();

}

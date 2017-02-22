#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main(int argc, char **argv){

	// if commande line 
	if (argc > 1) {

		// open file 
		for(int i=1;i<argc;i++){
			ifstream file;
			file.open(argv[i]);
		}

	}


	// if standard in 
	else {
		// use cin as file
	}


	string[] program = new string[255]; 
	program[0] = "CAFEBE";
}

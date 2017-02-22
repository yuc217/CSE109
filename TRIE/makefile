# make file 
#/*
#CSE 109
#Yuchen Cai
#yuc217
#Program Description: implement trie strucutre 
#Program #3 */

OBJ = prog3.o trie.o node.o link.o 
OPTS = -g -c -Wall -Werror

prog3: $(OBJ)
	g++ -o testtrie $(OBJ)

prog3.o: node.h prog3.cc  trie.h link.h
	g++ $(OPTS) prog3.cc

trie.o: trie.cc trie.h node.h link.h 
	g++ $(OPTS) trie.cc

node.o: node.h node.cc
	g++ $(OPTS) node.cc

link.o: link.cc link.h
	g++ $(OPTS) link.cc

clean: 
	rm -f *.o testtrie *~ 
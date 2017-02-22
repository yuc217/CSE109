OBJ= assembler.o hashTable.o link.o hash.o
OPTS= -g -c -Wall -Werror

assemble: $(OBJ)
	g++ -o assemble $(OBJ)

assembler.o: assembler.cc hash.h hashTable.h link.h
	g++ $(OPTS) assembler.cc

hashTable.o: hashTable.cc hashTable.h link.h hash.h
	g++ $(OPTS) hashTable.cc

hash.o: hash.h hash.cc
	g++ $(OPTS) hash.cc

link.o: link.cc link.h
	g++ $(OPTS) link.cc

clean:
	rm -f *.o assemble *~

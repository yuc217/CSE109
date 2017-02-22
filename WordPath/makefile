OBJ= prog8.o prog8lib.o
OPTS= -g -c -Wall -Werror

wordlist: $(OBJ)
	g++ -o wordlist $(OBJ)

prog8.o: prog8.cc prog8lib.h
	g++ $(OPTS) prog8.cc

prog8lib.o: prog8lib.h
	g++ $(OPTS) prog8lib.cc

clean:
	rm -f *.o wordlist *~
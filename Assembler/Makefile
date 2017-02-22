OBJ=parser.o Lexer.o Token.o silc.o
OPTS=-g -c -Wall -Werror

silc:$(OBJ)
	g++ -o silc $(OBJ)

parser.o: parser.cc Lexer.h Token.h
	g++ $(OPTS) parser.cc

Lexer.o: Lexer.h Lexer.cc Token.h
	g++ $(OPTS) Lexer.cc

silc.o: Token.h Lexer.h parser.h silc.cc
	g++ $(OPTS) silc.cc

Token.o: Token.cc Token.h
	g++ $(OPTS) Token.cc

clean: 
	rm -f *.o silc *~ 

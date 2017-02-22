OPTS= -g -xc -Wall -Werror 

copy: copy.c
	gcc $(OPTS) -o copy copy.c 

cat: cat.c
	gcc $(OPTS) -o cat cat.c

linecat: linecat.c
	gcc $(OPTS) -o linecat linecat.c

demo: scanfprintfdemo.c
	gcc $(OPTS) -o demo scanfprintfdemo.c

struct: struct.c
	gcc $(OPTS) -o struct struct.c

unions: unions.c
	gcc $(OPTS) -o unions unions.c

clean:
	rm -f *.o *~ a.out cat copy linecat demo struct unions

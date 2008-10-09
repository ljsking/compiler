all: lex yacc
	gcc lex.yy.c y.tab.c -lfl
	
lex: simple.l
	flex simple.l

yacc: simple.y
	bison -yd simple.y
	
clean:
	rm -f lex.yy.c
	rm -f y.tab.c
	rm -f y.tab.h
	rm -f a.out
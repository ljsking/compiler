TARGET = compiler
CC = gcc

$(TARGET): lex.yy.c simple.tab.c
	$(CC) -o $(TARGET) lex.yy.c simple.tab.c -lfl

clean:
	rm $(TARGET) lex.yy.c simple.tab.c simple.tab.h

lex.yy.c: simple.l
	flex simple.l
	
simple.tab.c: simple.y
	bison simple.y -d
	


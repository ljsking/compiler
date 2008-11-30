TARGET = compiler
CC = gcc

$(TARGET): lex.yy.c simple.tab.c simple.h intList.c intList.h node.h node.c type.h type.c statementList.h statementList.c interpreter.h interpreter.c symbol.h symbol.c vector.h vector.c meschach.a
	$(CC) -o $(TARGET) lex.yy.c simple.tab.c intList.c node.c type.c statementList.c interpreter.c symbol.c vector.c -lfl meschach.a -lm

clean:
	rm $(TARGET) lex.yy.c simple.tab.c simple.tab.h meschach.a

lex.yy.c: simple.l
	flex simple.l
	
simple.tab.c: simple.y
	bison simple.y -d
	
meschach.a:
	cd mesch && make
	cp mesch/meschach.a ./
	cd mesch && make clean 

#ifndef SIMPLE_H
#define SIMPLE_H

#define TypeInfo 		-1
#define IDList			-2
#define FunctionCall	-3
#define NumberList		-4
#define NUMBER			-5
#define ScalarAssign	-6
#define VectorAssign	-7
#define MatrixAssign	-8
#define FuncInfo		-9
#define PARAM			-10
#define PARAMS			-11
#define ArgList			-12

char *convertTag(int , char *);
#endif

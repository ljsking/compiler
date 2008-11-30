#ifndef SIMPLE_H
#define SIMPLE_H

#define TypeInfo 		-1
#define IDList			-2
#define Vector			-3
#define NumberList		-4
#define ScalarID		-5
#define ScalarAssign	-6
#define ScalarAdd		-7
#define ScalarSub		-8
#define ScalarMul		-9
#define ScalarDiv		-10
#define ScalarLes		-11
#define ScalarGrt		-12
#define ScalarLE		-13
#define ScalarGE		-14
#define ScalarEq		-15
#define ScalarNE		-16
#define ScalarAnd		-17
#define ScalarOr		-18
#define ScalarData		-19
#define VectorAssign	-20
#define MatrixAssign	-21
#define VectorAdd		-22
#define MatrixAdd		-23

char *convertTag(int , char *);
#endif

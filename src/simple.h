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
#define ScalarMod		-11
#define ScalarPow		-12
#define ScalarLes		-13
#define ScalarGrt		-14
#define ScalarLE		-15
#define ScalarGE		-16
#define ScalarEq		-17
#define ScalarNE		-18
#define ScalarAnd		-19
#define ScalarOr		-20
#define ScalarData		-21
#define VectorAssign	-22
#define MatrixAssign	-23

char *convertTag(int , char *);
#endif

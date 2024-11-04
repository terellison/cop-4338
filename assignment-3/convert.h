#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define error(m, c) do{fprintf(stderr, "%s\n", m);exit(c);}while(0)

typedef enum{
	NONE = 0,//no flags are passed in CLAs
	CLEAR = 1,//-c
	HEX = 1<<1, //-x
	SCIENTIFIC = 1<<2,//-e
	TRUNCATED = 1<<3,//-s
}flags;

int is_double(char*);
int is_int(char*);
char* strip(char * input);
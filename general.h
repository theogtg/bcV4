#ifndef gen_h
#define gen_h
#define TABLE_SIZE 211
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

typedef union {
   int ivalue;
   char cvalue;
   double dvalue;
} VALUE;

/* Global declarations */
/* Variables */
extern char lexeme[100];
extern char nextChar;
extern int lexLen;
extern FILE *in_fp, *fopen();
extern char peek;
extern string input;
extern int num;

/* Function declarations */

int getString();
void addChar();
void getChar();
void getNonBlank();
extern int lex();

int stmts();
int stmt();
bool cond();
int optelse();
int expr();
int term();
int unary();
int expo();
int factor();
void error(const char *);

/* Character classes */
extern int charClass;
#define LETTER 0
#define DIGIT 1
#define OPERATOR 99
#define IF_STMT 60
#define THEN_STMT 61
#define ELSE_STMT 62
#define FI_STMT 63
#define WHILE_STMT 64
#define DO_STMT 65
#define DONE_STMT 66

/* Token codes */
extern int token;
extern int nextToken;
#define QUIT 8
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define MOD_OP 25
#define LEFT_PAREN 26
#define RIGHT_PAREN 27
#define EXPO_OP 28
#define UNARY_MINUS 29
#define PRINT 44
#define COMMENT 45
#define EQ_OP 50
#define NOTEQ_OP 51
#define LESSEQ_OP 52
#define GREATEQ_OP 53
#define GREAT_OP 54
#define LESS_OP 55
#define NEWLINE 96
#define DUMP 900

#define DEBUG

#endif
%{
#include "parser.h"

int yylex();
int yyerror(char *s);

%}

%token INSTRUCTION STRING IDENTIFIER COLON REFERENCE NUM OTHER NEWLINE

%type <name> STRING
%type <number> NUM

%union{
	  char name[32];
      int number;
}

%%

prog:
  stmts
;

stmts:
		| stmt NEWLINE stmts

stmt:
		OTHER
;

%%

int yyerror(char *s)
{
	return 0;
}
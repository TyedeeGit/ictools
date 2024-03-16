%{
#include "syntax.tab.h"
#include "parser.h"

void showError();
YY_BUFFER_STATE yy_scan_string(const char *str);
%}


numbers     ([0-9])+
alpha       ([a-zA-Z])+

%%

%%

int yywrap(){
    return 1;
}

int yyparse_string(const char *str) {
    yy_scan_string(str);
    return yyparse();
}
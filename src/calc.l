
%{
#include<string>
#include "parser.hpp"
void yyerror(std::string);
%}
%option noyywrap
%%
"exit"		return QUIT;
[0-9]*\.[0-9]+|[0-9]+ { yylval.value = new std::string(yytext); return DOUBLE_NUM; }
[_a-zA-Z][_a-zA-Z0-9]* { yylval.value = new std::string(yytext); return IDENTIFIER; }
[-(){}<>=+*/%;,] return *yytext;
">=" return GEQ;
"<=" return LEQ;
"==" return EQ;
"!=" return NE;
[ \t\n]+ ;
%%

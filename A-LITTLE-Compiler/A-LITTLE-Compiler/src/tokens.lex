
%top{
#include <iostream>
#include <stdio.h>
}

%option noyywrap

identifier [a-zA-Z_][a-zA-Z_0-9]*
constant   [0-9]+
whitespace ( |\t)+
other	   .

%%
{identifier}  *yyout << "Found an identifier" << YYText() <<std::endl;
{constant}    printf("Found a constant %s\n", yytext);
{other}	      printf("ERROR UNRECOGNIZED INPUT\n");
%%

int main(){
  FlexLexer* lexer = new yyFlexLexer();
  while (lexer->yylex(&std::cin, &std::cout)!=0);
  return 0;
}


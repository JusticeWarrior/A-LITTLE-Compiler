
%top{
#include <iostream>
#include <stdio.h>
#define PRINT_INFO(name, value)				\
  do {							\
    *yyout << "Token type: " << (name) << std::endl <<	\
    "Value: " << (value);				\
  }while(0)
}

%option noyywrap

identifier [a-zA-Z_][a-zA-Z_0-9]*
constant   [0-9]+
whitespace ( |\t)+
other	   .

%%
{identifier}  PRINT_INFO("IDENTIFIER", YYText());
{constant}    PRINT_INFO("CONSTANT", YYText());
{other}	      PRINT_INFO("OTHER", YYText());
%%

int main(){
  FlexLexer* lexer = new yyFlexLexer();
  while (lexer->yylex(&std::cin, &std::cout)!=0){
    std::cout<<"Wee!"<<std::endl;
  }
  return 0;
}


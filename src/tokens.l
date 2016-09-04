
%top{
#include <iostream>
#include <stdio.h>
#define PRINT_INFO(name, value)				\
  do {							\
    *yyout << "Token type: " << (name) << std::endl <<	\
    "Value: " << (value) << std::endl;			\
  }while(0)
}

%option noyywrap


identifier    [a-zA-Z_][a-zA-Z_0-9]*
intliteral    [0-9]+
stringliteral \".*\"
keyword       BEGIN|END
whitespace    \(\ |\t\)+
other	      .

%%
{identifier}	  PRINT_INFO("IDENTIFIER", YYText());
{intliteral}	  PRINT_INFO("INTLITERAL", YYText());
{stringliteral}	  PRINT_INFO("STRINGLITERAL",YYText());
{keyword}	  PRINT_INFO("KEYWORD",YYText());
%%

int main(){
  FlexLexer* lexer = new yyFlexLexer();
  while (lexer->yylex(&std::cin, &std::cout)!=0){
  }
  return 0;
}


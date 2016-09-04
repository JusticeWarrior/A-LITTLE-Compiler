
%top{
#include <iostream>
#include <stdio.h>
#define PRINT_INFO(name, value)				\
  do {							\
    *yyout << "Token Type: " << (name) << std::endl <<	\
    "Value: " << (value) << std::endl;			\
  }while(0)
}

%option noyywrap

keyword PROGRAM|BEGIN|END|FUNCTION|READ|WRITE|IF|ELSIF|ENDIF|DO|WHILE|CONTINUE|BREAK|RETURN|INT|VOID|STRING|FLOAT|TRUE|FALSE
identifier    [a-zA-Z_][a-zA-Z_0-9]*
floatliteral  [0-9]*[.][0-9]+
intliteral    [0-9]+
stringliteral \"[^"]{0,80}\"
comment       [-]{2}.*
operator [:][=]|[+]|[-]|[*]|[/]|[=]|[<]|[>]|[(]|[)]|[;]|[,]|[;]|[<][=]|[>][=]|[!][=]
whitespace    [ \n\t\r]+
other	      .

%%
{keyword}	  PRINT_INFO("KEYWORD",YYText());
{identifier}	  PRINT_INFO("IDENTIFIER", YYText());
{floatliteral}	  PRINT_INFO("FLOATLITERAL", YYText());
{intliteral}	  PRINT_INFO("INTLITERAL", YYText());
{stringliteral}	  PRINT_INFO("STRINGLITERAL",YYText());
{comment}	  ;
{operator}	  PRINT_INFO("OPERATOR", YYText());
{whitespace}	  ;
%%

int main(){
  FlexLexer* lexer = new yyFlexLexer();
  while (lexer->yylex(&std::cin, &std::cout)!=0){
  }
  delete lexer;
  return 0;
}



%top{
#include <iostream>
#include <stdio.h>
#include "tokens.hpp"
#include "scanner.hpp"
#define PRINT_INFO(name, value)				\
  do {							\
    *yyout << "Token Type: " << (name) << std::endl <<	\
    "Value: " << (value) << std::endl;			\
  }while(0)

#define yyterminate() return(token::END)
}

%option noyywrap
%option nodefault
%option yyclass="LittleScanner"
%option c++

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
{keyword}	  {PRINT_INFO("KEYWORD",YYText()); return(token::KEYWORD);}
{identifier}	  {PRINT_INFO("IDENTIFIER", YYText()); return(token::IDENTIFIER);}
{floatliteral}	  {PRINT_INFO("FLOATLITERAL", YYText()); return(token::FLOATLITERAL);}
{intliteral}	  {PRINT_INFO("INTLITERAL", YYText()); return (token::INTLITERAL);}
{stringliteral}	  {PRINT_INFO("STRINGLITERAL",YYText()); return (token::STRINGLITERAL);}
{comment}	  ;
{operator}	  {PRINT_INFO("OPERATOR", YYText()); return (token::OPERATOR);}
{whitespace}	  ;
{other} {return (token::TRASH);}
%%

int main(){
  //FlexLexer* lexer = new yyFlexLexer(&std::cin, &std::cout);
  LittleScanner* lexer = new LittleScanner(&std::cin, &std::cout);
  while (lexer->yylex()!=token::END){
  }
  delete lexer;
  return 0;
}


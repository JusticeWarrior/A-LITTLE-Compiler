
%top{
#include <iostream>
#include <stdio.h>
#include "grammar.tab.hpp"
#include "scanner.hpp"
  
// Move this to anothe file
#include "parser.hpp"

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
{keyword}	  {PRINT_INFO("KEYWORD",YYText()); return(KEYWORD);}
{identifier}	  {PRINT_INFO("IDENTIFIER", YYText()); return(IDENTIFIER);}
{floatliteral}	  {PRINT_INFO("FLOATLITERAL", YYText()); return(FLOATLITERAL);}
{intliteral}	  {PRINT_INFO("INTLITERAL", YYText()); return (INTLITERAL);}
{stringliteral}	  {PRINT_INFO("STRINGLITERAL",YYText()); return (STRINGLITERAL);}
{comment}	  ;
{operator}	  {PRINT_INFO("OPERATOR", YYText()); return (OPERATOR);}
{whitespace}	  ;
{other} {return (TRASH);}
%%

int main(){
  /*
  LittleScanner* lexer = new LittleScanner(&std::cin, &std::cout);
  while (lexer->yylex()!=token::END){
  }
  delete lexer;
  return 0;
  */

  LittleParser parser = LittleParser(&std::cin);
  parser.parse();
  if (parser.accepted())
    std::cout << "Accepted!" << std::endl;
  else
    std::cout << "Not Accepted!" << std::endl;
}


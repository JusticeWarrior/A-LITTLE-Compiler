#ifndef _TOKENS_HPP_
#define _TOKENS_HPP_

namespace token{
  typedef enum token_t{
    END,
    KEYWORD,
    IDENTIFIER,
    FLOATLITERAL,
    INTLITERAL,
    STRINGLITERAL,
    OPERATOR,
    TRASH
  } token_t;
};

#endif

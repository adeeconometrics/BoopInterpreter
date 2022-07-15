#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "TokenType.h"
#include "Types.h"

#include <string>

namespace boop {
    
class Token {
    const TokenType m_type;
    const std::string m_lexeme;
    OptionalLiteral m_literal {std::nullopt};
    const int m_line;

public:
    Token(const TokenType& _type, const std::string& _lexeme, 
        const OptionalLiteral& _literal, int _line ); // uncertain how to parse std::any
    
    auto to_string(void) const noexcept -> std::string;
    auto get_lexeme(void) const noexcept -> std::string; // not final
};

}

#endif // __TOKEN_H__

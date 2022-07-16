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
    
    auto to_string() const noexcept -> std::string;
    auto get_type() const noexcept -> TokenType;
    auto get_lexeme() const noexcept -> std::string; // not final
    auto get_line() const noexcept -> int; 
    const auto get_optional_literal() const noexcept -> OptionalLiteral&;
    
};

}

#endif // __TOKEN_H__

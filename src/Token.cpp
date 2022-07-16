#include "Token.h"

namespace boop {
    
Token::Token(const TokenType type, const std::string &lexeme,
             const std::string &literal, const int line)
    : m_type(type), m_lexeme(lexeme), m_literal(literal), m_line(line) {}

auto Token::to_string() const -> std::string {
  std::ostringstream os;
  const int width = 80;

  switch (m_type) {
  case TokenType::LEFT_PAREN:
  case TokenType::RIGHT_PAREN:
  case TokenType::RIGHT_BRACE:
  case TokenType::LEFT_BRACE:
  case TokenType::COMMA:
  case TokenType::DOT:
  case TokenType::MINUS:
  case TokenType::PLUS:
  case TokenType::SEMI_COLON:
  case TokenType::SLASH:
  case TokenType::STAR:
    os << m_lexeme << std::setw(width - m_lexeme.size()) << "is punctuator";
    return os.str();

  case TokenType::BANG:
  case TokenType::BANG_EQUAL:
  case TokenType::EQUAL:
  case TokenType::EQUAL_EQUAL:
  case TokenType::GREATER:
  case TokenType::GREATER_EQUAL:
  case TokenType::LESS:
  case TokenType::LESS_EQUAL:
    os << m_lexeme << std::setw(width - m_lexeme.size())
       << "is a relational operator";
    return os.str();

  case TokenType::STRING:
    os << m_literal << std::setw(width - m_literal.size())
       << "is a string literal";
    return os.str();

  case TokenType::NUMBER:
    os << m_literal << std::setw(width - m_literal.size()) << "is a number";
    return os.str();

  case TokenType::IDENTIFIER:
    os << m_lexeme << std::setw(width - m_lexeme.size()) << "is an identifier";
    return os.str();

  case TokenType::END_OF_FILE:
    os << m_lexeme << std::setw(width - m_lexeme.size()) << "is end of file";
    return os.str();

  default:
    std::ostringstream os;
    os << m_lexeme << std::setw(width - m_lexeme.size()) << "is a keyword";
    return os.str();
  };
}
}
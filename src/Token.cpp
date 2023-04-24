#include "../include/Token.h"
#include "../include/TokenType.h"

namespace boop {

namespace {
auto TokenTypeString(const TokenType value) -> const std::string & {
  static const std::map<TokenType, std::string> lookup_table{
      {TokenType::LEFT_PAREN, "LEFT_PAREN"},
      {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
      {TokenType::LEFT_BRACE, "LEFT_BRACE"},
      {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
      {TokenType::COMMA, "COMMA"},
      {TokenType::COLON, "COLON"},
      {TokenType::DOT, "DOT"},
      // {TokenType::QUESTION, "QUESTION"},
      {TokenType::SEMICOLON, "SEMICOLON"},
      {TokenType::SLASH, "SLASH"},
      {TokenType::STAR, "STAR"},
      {TokenType::BANG, "BANG"},
      {TokenType::BANG_EQUAL, "BANG_EQUAL"},
      {TokenType::EQUAL, "EQUAL"},
      {TokenType::EQUAL_EQUAL, "EQUAL_EQUAL"},
      {TokenType::GREATER, "GREATER"},
      {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
      {TokenType::LESS, "LESS"},
      {TokenType::LESS_EQUAL, "LESS_EQUAL"},
      {TokenType::MINUS, "MINUS"},
      {TokenType::MINUS_MINUS, "MINUS_MINUS"},
      {TokenType::PLUS, "PLUS"},
      {TokenType::PLUS_PLUS, "PLUS_PLUS"},
      {TokenType::IDENTIFIER, "IDENTIFIER"},
      {TokenType::STRING, "STRING"},
      {TokenType::NUMBER, "NUMBER"},
      {TokenType::AND, "AND"},
      {TokenType::CLASS, "CLASS"},
      {TokenType::ELSE, "ELSE"},
      {TokenType::LOX_FALSE, "FALSE"},
      {TokenType::FUN, "FUN"},
      {TokenType::FOR, "FOR"},
      {TokenType::IF, "IF"},
      {TokenType::NIL, "NIL"},
      {TokenType::OR, "OR"},
      {TokenType::PRINT, "PRINT"},
      {TokenType::RETURN, "RETURN"},
      {TokenType::SUPER, "SUPER"},
      {TokenType::THIS, "THIS"},
      {TokenType::LOX_TRUE, "TRUE"},
      {TokenType::VAR, "VAR"},
      {TokenType::WHILE, "WHILE"},
      {TokenType::LOX_EOF, "EOF"}};

  return lookup_table.find(value)->second;
}
} // namespace

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

auto Token::get_line() const noexcept -> int { return m_line; }

auto Token::get_lexeme() const noexcept -> std::string { return m_lexeme; }

auto Token::get_type() const noexcept -> TokenType { return m_type; }

const auto Token::get_optional_literal() const noexcept -> OptionalLiteral & {
  m_literal;
}

auto Token::get_type_string() const noexcept -> std::string {
  return TokenTypeString(this->m_type);
}

} // namespace boop
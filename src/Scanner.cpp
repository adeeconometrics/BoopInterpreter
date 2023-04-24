#include "../include/Scanner.h"
#include "../include/TokenType.h"

#include <string_view>
#include <unordered_map>

namespace boop {
const std::unordered_map<std::string_view, TokenType> Scanner::m_keywords{
    {"and", TokenType::AND},       {"class", TokenType::CLASS},
    {"else", TokenType::ELSE},     {"false", TokenType::FALSE},
    {"fun", TokenType::FUN},       {"for", TokenType::FOR},
    {"if", TokenType::IF},         {"nil", TokenType::NIL},
    {"or", TokenType::OR},         {"print", TokenType::PRINT},
    {"return", TokenType::RETURN}, {"super", TokenType::SUPER},
    {"this", TokenType::THIS},     {"true", TokenType::TRUE},
    {"var", TokenType::VAR},       {"while", TokenType::WHILE},
};

Scanner::Scanner(std::string_view source, ErrorHandler &error)
    : m_source(source), m_error_handler(error) {}

auto Scanner::scan_and_get_tokens() -> vector<Token> {
  while (!is_at_end()) {
    m_start = m_current;
    scan_and_add_token();
  }

  m_tokens.push_back(
      Token(TokenType::END_OF_FILE, "", "", m_line)); // what is eof
  return m_tokens;
}

auto Scanner::is_keyword(std::string_view token) const -> bool {
  return std::any_of(
      m_keywords.cbegin(), m_keywords.cend(),
      [&token](const auto &i) -> bool { return token == i.first; });
}

auto Scanner::scan_and_add_token() -> void {
  const char c = advance();
  switch (c) {
  case '(':
    add_token(TokenType::LEFT_PAREN);
    break;
  case ')':
    add_token(TokenType::RIGHT_PAREN);
    break;
  case '{':
    add_token(TokenType::LEFT_BRACE);
    break;
  case '}':
    add_token(TokenType::RIGHT_BRACE);
    break;
  case ',':
    add_token(TokenType::COMMA);
    break;
  case '.':
    add_token(TokenType::DOT);
    break;
  case '-':
    add_token(TokenType::MINUS);
    break;
  case '+':
    add_token(TokenType::PLUS);
    break;
  case ';':
    add_token(TokenType::SEMI_COLON);
    break;
  case '*':
    add_token(TokenType::STAR);
    break;
  case '!':
    add_token(match_and_advance('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
    break;
  case '=':
    add_token(match_and_advance('=') ? TokenType::EQUAL_EQUAL
                                     : TokenType::EQUAL);
    break;
  case '<':
    add_token(match_and_advance('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
    break;
  case '>':
    add_token(match_and_advance('=') ? TokenType::GREATER_EQUAL
                                     : TokenType::GREATER);
    break;
  case '/':
    if (match_and_advance('/')) {
      // a comment goes until the end of the line.
      while (peek() != '\n' && !is_at_end())
        static_cast<void>(advance());
    } else {
      add_token(TokenType::SLASH);
    }
    break;
  case '"':
    string();
    break;
  case ' ':
  case '\r':
  case '\t':
    break;
  case '\n':
    m_line += 1;
    break;
  default: {
    if (is_digit(c)) {
      number();
    } else if (is_alpha(c)) {
      identifier();
    } else {
      std::string error_msg{"Unexpectd character: "};
      error_msg += c;
      error_handler.add(m_line, "", error_msg);
      break;
    }
  }
  }
}

// get the set of string literal in the source code
auto Scanner::string() -> void {
  while (peek() != '"' && !is_at_end()) {
    if (peek() == '\n')
      m_line += 1;
    static_cast<void>(
        advance()); // look into why we need to convert char to void
  }

  // handle unterminated std::string
  if (is_at_end()) {
    error_handler.add(m_line, "", "Unterminated string.");
    return;
  }

  static_cast<void>(advance());
  const size_t string_size = m_current - m_start;
  const std::string string_literal =
      m_source.substr(m_start + 1, string_size - 2);
  add_token(TokenType::STRING, string_literal);
}

// gets the set of numbers in the source code
auto Scanner::number() -> void {
  while (is_digit(peek()))
    static_cast<void>(advance());

  if (peek() == '.' && is_digit(peek_next())) {
    static_cast<void>(advance());

    while (is_digit(peek()))
      static_cast<void>(advance());
  }

  const size_t number_length = m_current - m_start;
  const std::string number_literal = m_source.substr(m_start, number_length);

  add_token(TokenType::NUMBER, number_literal);
}

// gets the set of identifiers in the source code
auto Scanner::identifier() -> void {
  while (is_alphanum(peek()))
    static_cast<void>(advance());

  const size_t identifier_length = m_current - m_start;
  const std::string identifier = m_source.substr(m_start, identifier_length);
  const bool is_reserved_key = is_keyword(identifier);

  if (is_reserved_key) {
    add_token(m_keywords.at(identifier));
  } else {
    add_token(TokenType::IDENTIFIER); // will be prompted to symbol table
  }
}

auto Scanner::match_and_advance(const char c) -> bool {
  if (is_at_end() || m_source[m_current] != c)
    return false;

  m_current += 1;

  return true;
}

auto Scanner::add_token(const TokenType type, const std::string &token)
    -> void {
  const size_t lexeme_size = m_current - m_start;
  const std::string lexeme = m_source.substr(m_start, lexeme_size);

  m_tokens.push_back(Token(type, lexeme, token, m_line));
}

auto Scanner::add_token(TokenType type) -> void { add_token(type, ""); }

auto Scanner::advance() -> char {
  m_current += 1;
  return m_source[m_current - 1];
}

auto Scanner::peek() const -> char {
  if (is_at_end())
    return '\0';
  return m_source[m_current];
}

auto Scanner::peek_next() const -> char {
  if (m_current + 1 >= m_source.length())
    return '\0';
  return m_source[m_current + 1];
}

auto Scanner::is_at_end() const -> bool { return m_current >= m_source.size(); }

auto Scanner::is_digit(const char c) const -> bool {
  return c >= '0' && c <= '9';
}

auto Scanner::is_alpha(const char c) const -> bool {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

auto Scanner::is_alphanum(const char c) const -> bool {
  return is_alpha(c) || is_digit(c);
}
}; // namespace boop
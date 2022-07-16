#ifndef __PARSER_H__
#define __PARSER_H__

#include "ASTNodes.h"
#include "ErrorHandler.h"
#include "Token.h"
#include "TokenType.h"
#include "Types.h"

#include <exception>
#include <function>
#include <initializer_list>
#include <iterator>
#include <vector>

namespace boop {

class Parser {
private:
  static const int MAX_ARGS = 255;
  const std::vector<Token> &m_tokens;
  std::vector<Token>::const_iterator m_current_iter;
  std::vector<AST::StmtPtrVariant> m_stmts;
  ErrorHandler &m_error_handler;


public:
  explicit Parser(const std::vector<Token> &_tokens, ErrorHandler &_error);

  struct ParseError : public std::exception {}; // parse exception

private:
  // apply production rules for stmts
  auto program() -> void;
  auto declaration() -> std::optional<AST::StmtPtrVariant>;
  auto var_declaration() -> AST::StmtPtrVariant;
  auto function_declaration(const std::string &kind) -> AST::StmtPtrVariant;
  auto function_body(const std::string &kind) -> AST::ExprPtrVariant;
  auto parameters() -> std::vector<Token>;
  auto class_declaration() -> AST::StmtPtrVariant;
  auto statement() -> AST::StmtPtrVariant;
  auto print_stmt() -> AST::StmtPtrVariant;
  auto block_stmt() -> AST::StmtPtrVariant;
  auto if_stmt() -> AST::StmtPtrVariant;
  auto while_stmt() -> AST::StmtPtrVariant;
  auto for_stmt() -> AST::StmtPtrVariant;
  auto return_stmt() -> AST::StmtPtrVariant;
  auto expr_stmt() -> AST::StmtPtrVariant;

  // apply production rules for expr
  auto expression() -> AST::ExprPtrVariant;
  auto comma() -> AST::ExprPtrVariant;
  auto assignment() -> AST::ExprPtrVariant;
  auto conditional() -> AST::ExprPtrVariant;
  auto logical_or() -> AST::ExprPtrVariant;
  auto logical_and() -> AST::ExprPtrVariant;
  auto equality() -> AST::ExprPtrVariant;
  auto comparison() -> AST::ExprPtrVariant;
  auto addition() -> AST::ExprPtrVariant;
  auto multiplication() -> AST::ExprPtrVariant;
  auto unary() -> AST::ExprPtrVariant;
  auto postfix() -> AST::ExprPtrVariant;
  auto call() -> AST::ExprPtrVariant;
  auto arguments() -> std::vector<AST::ExprPtrVariant>;
  auto primary() -> AST::ExprPtrVariant;

private:
  using parse_fn = AST::ExprPtrVariant (Parser::*)();
  // helper functions to consume tokens
  auto advance() -> void;
  auto report_error(const std::string &msg) -> void;
  auto synchronize() -> void;
  auto throw_on_error_productions(const std::initializer_list<TokenType> &types,
                                  const parse_fn &f) -> void;
  auto throw_on_error_productions() -> void;

  auto consume_or_error(Token type, const std::string &_error);
  auto consume_binary_expr(const std::initializer_list<TokenType> &types,
                           AST::ExprPtrVariant expr, const parse_fn &f)
      -> AST::ExprPtrVariant;
  auto consume_one_literal() -> AST::ExprPtrVariant;
  auto consume_one_literal(const std::string &str) -> AST::ExprPtrVariant;
  auto consume_grouping_expr() -> AST::ExprPtrVariant;
  auto consume_postfix_expr(AST::ExprPtrVariant expr) -> AST::ExprPtrVariant;
  auto consume_semicolon_or_error() -> void;
  auto consume_super() -> AST::ExprPtrVariant;
  auto consume_unary_expr() -> AST::ExprPtrVariant;
  auto consume_variable_expr() -> AST::ExprPtrVariant;
  auto error(const std::string &msg) -> ParseError;

  auto get_current_token_type() const noexcept -> TokenType;
  auto get_token_and_advance() noexcept -> Token;
  auto peek() const noexcept -> Token;

  auto is_at_end() const noexcept -> bool;
  auto is_match(const std::initializer_list<TokenType> &types) const noexcept
      -> bool;
  auto is_match(TokenType type) const noexcept -> bool;
  auto is_match_next(TokenType type) const noexcept -> bool;
};

} // namespace boop

#endif // __PARSER_H__

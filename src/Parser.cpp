#include "../include/Parser.h"
#include "../include/ASTNodes.h"
#include "../include/Token.h"
#include "../include/TokenType.h"
#include "../include/Types.h"

#include <exception>
#include <function>
#include <initializer_list>
#include <iterator>
#include <optional>
#include <string>
#include <vector>

namespace boop {

Parser::Parser(const std::vector<Token> &_tokens, ErrorHandler &_error)
    : m_tokens(_tokens), m_error_handler(_error) {
  this->m_current_iter;
}

auto Parser::program() -> void {
  try {
    while (!is_at_end()) {
      std::optional<AST::StmtPtrVariant> opt_stmt = declaration();
      if (opt_stmt.has_value()) {
        m_stmts.push_back(std::move(opt_stmt.value()));
      }
    }
  } catch (const std::exception &e) {
    m_error_handler.add(peek.get_line(),
                        "Caught unhandled exception: " + e.what());
  }
}

auto Parser::declaration() -> std::optional<AST::StmtPtrVariant> {
  try {
    if (is_match(TokenType::VAR)) {
      advance();
      return var_declaration();
    }

    if (is_match(TokenType::FUN) && is_match_next(TokenType::IDENTIFIER)) {
      advance();
      return function_declaration("function");
    }

    if (is_match(TokenType::CLASS)) {
      advance();
      return class_declaration();
    }

    return statement();

  } catch (const ParseError &e) {
    m_error_handler.add(
        "Caught ParseError; Calling synchronize. Current Token: " +
        peek().to_string());
    synchronize();
    return std::nullopt;
  }
}

auto Parser::var_declaration() -> std::optional<AST::StmtPtrVariant> {
  if (is_match(TokenType::IDENTIFIER)) {
    Token var_name = get_token_and_advance();
    std::optional<AST::ExprPtrVariant> initializer{std::nullopt};
    if (is_match(TokenType::EQUAL)) {
      advance();
      initializer = expression();
    }
    consume_semicolon_or_error();
    return AST::make_variable_stmt(var_name, std::move(initializer));
  }
  throw error("Expected a variable name after the `var` keyword");
}

auto Parser::function_declaration(const std::string &kind)
    -> AST::StmtPtrVariant {
  if (is_match(TokenType::IDENTIFIER)) {
    Token function_name = get_token_and_advance();
    return AST::make_function_stmt(
        function_name, std::get<AST::ExprFunctionPtr>(function_body(kind)));
  }
  throw error("Expected a " + kind + " name after the fun keyword");
}

auto Parser::function_body(const string &kind) -> AST::ExprPtrVariant {
  consume_or_error(TokenType::LEFT_PAREN,
                   "Expected '(' after " + kind + " declaration.");
  std::vector<Token> params{
      is_match(TokenType::RIGHT_PAREN) ? std::vector<Token>() : parameters()};

  consume_or_error(TokenType::RIGHT_PAREN,
                   "Expected ')' after " + kind + " declaration.");
  consume_or_error(TokenType::LEFT_BRACE,
                   "Expected '{' after " + kind + " declaration.");
  std::vector<AST::StmtPtrVariant> body{}; // checkout if this changes behavior
  while (!is_match(TokenType::RIGHT_BRACE) && !is_at_end()) {
    auto opt_stmt = declaration();
    if (opt_stmt.has_value()) {
      body.push_back(std::move(opt_stmt.value()));
    }
  }
  consume_or_error(TokenType::LEFT_BRACE,
                   "Expected '}' after " + kind + " declaration.");
}
// parameter := id::param | id::param , [parameter]
auto Parser::parameters() -> std::vector<Token> {
  std::vector<Tokens> params;
  auto flag = [this]() -> bool {
    if (is_match(TokenType::COMMA)) {
      advance();
      return true;
    }
    return false;
  }

  while (flag()) {
    if (peek().get_type() != TokenType::IDENTIFIER) {
      throw error("Expected an identifier for parameter");
      params.emplace_back(get_token_and_advance());
    }
  }

  return params;
}

auto Parser::class_declaration() -> AST::StmtPtrVariant {
  if (is_match(TokenType::IDENTIFIER)) {
    Token class_name = get_token_and_advance();

    auto get_super_type = [&]() -> std::optional<AST::ExprPtrVariant> {
      if (is_match(TokenType::LESS)) {
        advance();

        if (is_match(TokenType::IDENTIFIER)) {
          auto super_class_var = consume_variable_expr();
          if ((std::get<AST::ExprVariablePtr>(super_class_var)
                   ->var_name.get_lexeme() == class_name.get_lexeme())) {
            throw error("A class can't inherit from itself, silly.");
          }

          return super_class_var;
        }
        throw error("Expected a superclass name after '<' ");
      }
      return std::nullopt;
    }();
  }
}
// stmt := [stmt::print] | [stmt::block] | [stmt::block] | [stmt::if]
//          [stmt::while] | [stmt::for] | [stmt::return] | [stmt::expr]
auto Parser::statement() -> AST::StmtPtrVariant {
  if (is_match(TokenType::PRINT)) {
    return print_stmt();
  };
  if (is_match(TokenType::LEFT_BRACE)) {
    return block_stmt();
  };
  if (is_match(TokenType::IF)) {
    return if_stmt();
  };
  if (is_match(TokenType::WHILE)) {
    return while_stmt();
  };
  if (is_match(TokenType::FOR)) {
    return for_stmt();
  };
  if (is_match(TokenType::RETURN)) {
    return return_stmt;
  };
  return expr_stmt();
}

auto Parser::print_stmt() -> AST::StmtPtrVariant {
  advance();
  auto print_expr = expression();
  consume_semicolon_or_error();
  return AST::make_print_stmt(std::move(print_expr));
}
// block := { [stmt] }
auto Parser::block_stmt() -> AST::StmtPtrVariant {
  advance();
  std::vector<AST::StmtPtrVariant> stmt;

  while (!is_match(TokenType::RIGHT_BRACE) && !is_at_end()) {
    auto opt_stmt = declaration();
    if (opt_stmt.has_value()) {
      stmt.push_back(std::move(opt_stmt.value()));
    }
  }
  consume_or_error(TokenType::RIGHT_BRACE, "Expect '}' after block");
  return AST::make_block_stmt(std::move(stmt));
}
// if := ( [exp::conditional] ) { [stmt] }
auto Parser::if_stmt() -> AST::StmtPtrVariant {
  advance();
  consume_or_error(TokenType::LEFT_PAREN, "Expecte '(' after if.");
  AST::ExprPtrVariant condition = expression();
  consume_or_error(TokenType::RIGHT_PAREN, "Expecte ')' after if condition.");

  auto then_branch = statement();

  std::optional<AST::StmtPtrVariant> else_branch = std::nullopt;
  if (match(TokenType::ELSE)) {
    advance();
    else_branch = std::make_optional(statement());
  }

  return AST::make_if_stmt(std::move(condition), std::move(then_branch),
                           std::move(else_branch));
}
// while := while([expr:conditional])
auto Parser::while_stmt() -> AST::StmtPtrVariant {
  advance();
  consume_or_error(TokenType::LEFT_PARENT, "Expected '(' after while.");
  auto condition = expression();
  consume_or_error(TokenType::RIGHT_PARENT, "Expected ')' after while.");
  return AST::make_while_stmt(std::move(condition), statement());
}
// for := for([expr:initialize]; [expr:conditional]; [expr:increment])
auto Parser::for_stmt() -> AST::StmtPtrVariant {
  advance();
  consume_or_error(TokenType::LEFT_PAREN, "Expected '(' after for.");

  std::optional<AST::StmtPtrVariant> initializer = std::nullopt;
  if (match(TokenType::SEMICOLON)) {
    advance();
  } else if (match(TokenType::VAR)) {
    advance();
    initializer = std::make_optional(var_declaration());
  } else {
    initializer = std::make_optional(expr_stmt());
  }

  std::optional<AST::ExprPtrVariant> condition = std::nullopt;
  if (!is_match(TokenType::SEMICOLON))
    condition = std::make_optional(expression());

  consume_semicolon_or_error();

  std::optional<AST::ExprPtrVariant> increment = std::nullopt;
  if (!is_match(TokenType::RIGHT_PAREN))
    increment = std::make_optional(expression());

  consume_or_error(TokenType::RIGHT_PAREN, "Expected ')' after 'for' clauses.");

  AST::StmtPtrVariant loopBody = statement();

  return AST::make_for_stmt(std::move(initializer), std::move(condition),
                            std::move(increment), std::move(loopBody));
}

auto Parser::return_stmt() -> AST::StmtPtrVariant {
  auto ret = get_token_and_advance();
  std::optional<AST::ExprPtrVariant> value = std::nullopt;
  if (!is_match(TokenType::SEMICOLON)) {
    value = expression();
  }
  consume_semicolon_or_error();
  return AST::make_return_stmt(std::move(ret), std::move(value));
}

auto Parser::expr_stmt() -> AST::StmtPtrVariant {
  auto expr = expression();
  consume_semicolon_or_error();
  return AST::make_expr_stmt(std::move(expr));
}

auto Parser::expression() -> AST::ExprPtrVariant { return comma(); }

auto comma() -> AST::ExprPtrVariant {
  return consume_binary_expr({TokenType::COMMA}, assignment(),
                             &Parser::assignment);
}

auto Parser::assignment() -> AST::ExprPtrVariant {
  AST::ExprPtrVariant expr = conditional();

  if (match(TokenType::EQUAL)) {
    advance();
    if (std::holds_alternative<AST::ExprVariablePtr>(expr)) {
      Token var_name = std::get<AST::ExprVariablePtr>(expr)->var_name;
      return AST::make_assignment_expr(var_name, assignment());
    }
    if (std::holds_alternative<AST::ExprGetPtr>(expr)) {
      auto &get_expr = std::get<AST::ExprGetPtr>(expr);
      return AST::make_set_expr(std::move(get_expr->expr),
                                std::move(get_expr->name), assignment());
    }
    throw error("Invalid assignment target");
  }

  return expr;
}
// implement QUESTION in token and scanner
// auto Parser::conditional() ->AST::ExprPtrVariant {
//  AST::ExprPtrVariant expr = logical_or();
//   if (match(TokenType::QUESTION)) {
//     Token op = get_token_and_advance();
//    AST::ExprPtrVariant thenBranch = expression();
//     consume_or_error(TokenType::COLON, "Expected a colon after ternary
//     operator"); return AST::make_conditional_expr(std::move(expr),
//     std::move(thenBranch),
//                                      conditional());
//   }
//   return expr;
// }

auto Parser::logical_or() -> AST::ExprPtrVariant {
  AST::ExprPtrVariant expr = logical_and();
  while (match(TokenType::OR)) {
    Token op = get_token_and_advance();
    expr = AST::make_logical_expr(std::move(expr), op, logical_and());
  }
  return expr;
}

auto Parser::logical_and() -> AST::ExprPtrVariant {
  AST::ExprPtrVariant expr = equality();
  while (match(TokenType::AND)) {
    Token op = get_token_and_advance();
    expr = AST::make_logical_expr(std::move(expr), op, equality());
  }
  return expr;
}

auto Parser::equality() -> AST::ExprPtrVariant {
  auto eq_types = {TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL};
  return consume_binary_expr(eq_types, comparison(), &Parser::comparison);
}

auto Parser::comparison() -> AST::ExprPtrVariant {
  auto comp_types = {TokenType::GREATER, TokenType::GREATER_EQUAL,
                     TokenType::LESS, TokenType::LESS_EQUAL};
  return consume_binary_expr(comp_types, addition(), &Parser::addition);
}

auto Parser::addition() -> AST::ExprPtrVariant {
  auto add_types = {TokenType::PLUS, TokenType::MINUS};
  return consume_binary_expr(add_types, multiplication(),
                             &Parser::multiplication);
}

auto Parser::multiplication() -> AST::ExprPtrVariant {
  auto mult_types = {TokenType::SLASH, TokenType::STAR};
  return consume_binary_expr(mult_types, unary(), &Parser::unary);
}

auto Parser::unary() -> AST::ExprPtrVariant {
  auto unary_types = {TokenType::BANG, TokenType::MINUS, TokenType::PLUS_PLUS,
                      TokenType::MINUS_MINUS};
  if (match(unary_types)) {
    return consume_unary_expr();
  }
  return postfix();
}

auto Parser::postfix() -> AST::ExprPtrVariant {
  return consume_postfix_expr(call());
}

auto Parser::call() -> AST::ExprPtrVariant {
  auto expr = primary();
  while (true) {
    if (match(TokenType::LEFT_PAREN)) {
      advance();
      std::vector<AST::ExprPtrVariant> args;
      if (!is_match(TokenType::RIGHT_PAREN)) {
        args = arguments();
      }
      if (!is_match(TokenType::RIGHT_PAREN)) {
        throw error("Expected ')' after function invocation.");
      }
      expr = make_call_expr(std::move(expr), get_token_and_advance(),
                            std::move(args));
    } else if (match(TokenType::DOT)) {
      advance();
      Token name = match(TokenType::IDENTIFIER)
                       ? get_token_and_advance()
                       : throw error("Expected a name after '.'.");
      expr = make_call_expr(std::move(expr), std::move(name));
    } else {
      break;
    }
  }
  return expr;
}

auto Parser::arguments() -> std::vector<AST::ExprPtrVariant> {
  std::vector<AST::ExprPtrVariant> args;
  args.push_back(assignment());
  while (match(TokenType::COMMA)) {
    advance();
    if (args.size() >= MAX_ARGS) {
      throw error("A function can't be invoked with more than 255 arguments");
    }
    args.push_back(assignment());
  }
  return args;
}

auto Parser::primary() -> AST::ExprPtrVariant { // transform into match case
  if (match(TokenType::LOX_FALSE))
    return consume_one_literal("false");
  if (match(TokenType::LOX_TRUE))
    return consume_one_literal("true");
  if (match(TokenType::NIL))
    return consume_one_literal("nil");
  if (match(TokenType::NUMBER))
    return consume_one_literal();
  if (match(TokenType::STRING))
    return consume_one_literal();
  if (match(TokenType::LEFT_PAREN))
    return consume_grouping_expr();
  if (match(TokenType::THIS))
    return AST::make_this_expr(get_token_and_advance());
  if (match(TokenType::IDENTIFIER))
    return consume_variable_expr();
  if (match(TokenType::FUN))
    return funcBody("Anon-Function");
  if (match(TokenType::SUPER))
    return consume_super();

  throw_on_error_productions();

  // if none of the known error productions match,
  // give up and throw generic ParseError;
  throw error("Expected an expression; Got something else.");
}

auto Parse::parse() -> std::vector<AST::StmtPtrVariant> {
  program();
  return std::move(m_stmts);
}

auto advance() -> void {
  if (!is_at_end()) {
    ++m_current_iter;
  }
}

auto Parser::report_error(const std::string &msg) -> void {
  const Token &token = peek();
  std::string error = msg;
  if (token.get_type() == TokenType::EOF) {
    error = " at end: " + error;
  } else {
    error = " at '" + token.get_lexeme() + "': " + error;
  }

  m_error_handler.add(token.get_line(), error);
}

auto Parser::synchronize() -> void {
  while (!is_at_end()) {
    switch (get_current_token_type()) {
    case TokenType::SEMICOLON:
      advance();
      return;
    case TokenType::CLASS:
    case TokenType::FUN:
    case TokenType::VAR:
    case TokenType::FOR:
    case TokenType::IF:
    case TokenType::WHILE:
    case TokenType::PRINT:
    case TokenType::RETURN:
      return;
    default:
      m_error_handler.add("Discarding extranuous token:" + peek().get_lexeme());
      advance();
    }
  }
}

auto Parser::throw_on_error_productions(
    const std::initializer_list<TokenType> &types, const parse_fn &f) -> void {
  if (is_match(types)) {
    auto err_obj = error("Missing left hand operand");
    advance();
    ExprPtrVariant expr = std::invoke(f, this);
    throw err_obj;
  }
}

auto Parser::throw_on_error_productions() -> void {
  throw_on_error_productions({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL},
                             &Parser::equality);
  throw_on_error_productions({TokenType::GREATER, TokenType::GREATER_EQUAL,
                              TokenType::LESS, TokenType::LESS_EQUAL},
                             &Parser::comparison);
  throw_on_error_productions({TokenType::PLUS}, &Parser::addition);
  throw_on_error_productions({TokenType::STAR, TokenType::SLASH},
                             &Parser::multiplication);
}

auto Parser::consume_or_error(Token type, const std::string &_error) {
  if (get_current_token_type() == type)
    return advance();
  throw error(_error + " Got: " + peek().to_string());
}

auto Parser::consume_binary_expr(const std::initializer_list<TokenType> &types,
                                 AST::ExprPtrVariant expr, const parse_fn &f)
    -> AST::ExprPtrVariant {

  while (is_match(types)) {
    Token op = get_token_and_advance();
    expr = AST::make_binary_expr(std::move(expr), op, std::invoke(f, this));
  }
  return expr;
}

auto Parser::consume_one_literal() -> AST::ExprPtrVariant {
  return AST::make_literal_expr(get_token_and_advance().get_optional_literal());
}

auto Parser::consume_one_literal(const std::string &str)
    -> AST::ExprPtrVariant {
  advance();
  return AST::make_literal_expr(make_optional_literal(str));
}

auto Parser::consume_grouping_expr() -> AST::ExprPtrVariant {
  advance();
  ExprPtrVariant expr = expression();
  consume_or_error(TokenType::RIGHT_PAREN,
                   std::to_string(peek().get_line()) +
                       " Expected a closing parenthesis after expression.");
  return AST::make_grouping_expr(std::move(expr));
}

auto Parser::consume_postfix_expr(AST::ExprPtrVariant expr)
    -> AST::ExprPtrVariant {
  while (is_match({TokenType::PLUS_PLUS, TokenType::MINUS_MINUS})) {
    expr = AST::make_postfix_expr(std::move(expr), get_token_and_advance());
  }
  return expr;
}

auto Parser::consume_semicolon_or_error() -> void {
  consume_or_error(TokenType::SEMI_COLON, "Expected a ';'");
}

auto Parser::consume_super() -> AST::ExprPtrVariant {
  Token super = get_token_and_advance();
  consume_or_error(TokenType::DOT, "Expected a '.' after 'super' keyword");
  if (!is_match(TokenType::IDENTIFIER)) {
    throw error("Expected an identifier after 'super.' ");
  }
  Token method = get_token_and_advance();
  return AST::make_super_expr(std::move(super), std::move(method));
}

auto Parser::consume_unary_expr() -> AST::ExprPtrVariant{
    return AST::make_unary_expr(get_token_and_advance(), unary());
}

auto Parser::consume_variable_expr() -> AST::ExprPtrVariant{
    auto name = get_token_and_advance();
    return AST::make_variable_expr(name);
}

auto Parser::error(const std::string &msg) -> ParseError{
    report_error(msg);
    return ParseError(); //checkout
}

auto get_current_token_type() const noexcept -> TokenType {
    return m_current_iter->get_type();
}

auto get_token_and_advance() noexcept -> Token{
    Token token = peek();
    advance();
    return token;
}

auto peek() const noexcept -> Token {
    return *m_current_iter;
}

auto is_at_end() const noexcept -> bool {
    return peek().get_type() == TokenType::EOF;
}

auto is_match(const std::initializer_list<TokenType> &types) const noexcept
    -> bool{

  bool result{false};
  for (const auto &i : types) {
    result = (result || is_match(type));
  }
  return result;
}

auto is_match(TokenType type) const noexcept -> bool{
    if(is_at_end()) return false;
    return (type == get_current_token_type());
}

auto is_match_next(TokenType type) const noexcept -> bool {
    advance();
    bool result = match(type);
    --m_current_iter;
    return result;
}

} // namespace boop
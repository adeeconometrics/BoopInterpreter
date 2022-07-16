#ifndef __PARSER_H__
#define __PARSER_H__

#include "ASTNodes.h"
#include "ErrorHandler.h"
#include "Token.h"

#include <initializer_list>
#include <exception>
#include <function>
#include <iterator>
#include <vector>

namespace boop {

class Parser {
private: 
    static const int MAX_ARGS = 255;
    const std::vector<Token>& m_tokens;
    ErrorHandler & m_error_handler;
    std::vector<StmtPtrVariant> m_stmts;
    
public:

    explicit Parser(const std::vector<Token>& _tokens,
                    ErrorHandler& _error);

    struct ParseError: public std::exception {}; // parse exception

private:
    // apply production rules for stmts 
    auto program() -> void;
    auto declaration() -> std::optional<StmtPtrVariant>;
    auto var_declaration() -> StmtPtrVariant;
    auto class_declaration() -> StmtPtrVariant;
    auto function_declaration(const std::string &kind) -> StmtPtrVariant;
    auto function_body(const std::string &kind) -> ExprPtrVariant;
    auto parameters() -> std::vector<Types::Token>;
    auto statement() -> StmtPtrVariant;
    auto expr_stmt() -> StmtPtrVariant;
    auto print_stmt() -> StmtPtrVariant;
    auto block_stmt() -> StmtPtrVariant;
    auto if_stmt() -> StmtPtrVariant;
    auto while_stmt() -> StmtPtrVariant;
    auto for_stmt() -> StmtPtrVariant;
    auto return_stmt() -> StmtPtrVariant;

    // apply production rules for expr
    auto expression() -> ExprPtrVariant;
    auto comma() -> ExprPtrVariant;
    auto assignment() -> ExprPtrVariant;
    auto conditional() -> ExprPtrVariant;
    auto logical_or() -> ExprPtrVariant;
    auto logical_and() -> ExprPtrVariant;
    auto equality() -> ExprPtrVariant;
    auto comparison() -> ExprPtrVariant;
    auto addition() -> ExprPtrVariant;
    auto multiplication() -> ExprPtrVariant;
    auto unary() -> ExprPtrVariant;
    auto postfix() -> ExprPtrVariant;
    auto call() -> ExprPtrVariant;
    auto arguments() -> std::vector<ExprPtrVariant>;
    auto primary() -> ExprPtrVariant;

private:
    using parse_fn = ExprPtrVariant(Parser::*)();
    // helper functions to consume tokens
    auto advance() -> void;
    auto report_error(const std::string& msg) -> void;
    auto synchronize() -> void;
    auto throw_on_error_productions(const std::initializer_list<TokenType>& types, const parse_fn& f) -> void;
    auto throw_on_error_productions() -> void;

    
    auto consume_or_error(Token type, const std::string& error);
    auto consume_binary_expr(const std::initializer_list<TokenType>& types,
                            ExprPtrVariant expr, const parse_fn& f) -> ExprPtrVariant;
    auto consume_one_literal() -> ExprPtrVariant;
    auto consume_one_literal(const std::string& str) -> ExprPtrVariant;
    auto consume_grouping_expr() -> ExprPtrVariant;
    auto consume_postfix_expr(ExprPtrVariant expr) -> ExprPtrVariant;
    auto consume_semicolon_or_error() -> void;
    auto consume_super() -> ExprPtrVariant;
    auto consume_unary_expr() -> ExprPtrVariant;
    auto consume_variable_expr() -> ExprPtrVariant;
    auto error(const std::string& msg) -> ParseError;

    auto get_current_token_type() const noexcept -> TokenType;
    auto get_token_and_advance() noexcept -> Token;
    auto peek() const noexcept -> Token;
    
    auto is_at_end() const noexcept -> bool;
    auto is_match(const std::initializer_list<TokenType>& types) const noexcept -> bool;
    auto is_match(TokenType type) const noexcept -> bool;
    auto is_mathc_next(TokenType type) const noexcept -> bool;  

};

}

#endif // __PARSER_H__

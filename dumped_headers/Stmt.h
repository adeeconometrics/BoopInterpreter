#ifndef __STMT_H__
#define __STMT_H__

#include "Expr.h"
#include "Token.h"

#include <vector>

namespace boop {

class Stmt: public Uncopyable {
  template <typename T> class Visitor {
    virtual auto visit_block_stmt(const Block &stmt) -> T = 0;
    virtual auto visit_class_stmt(const Class &stmt) -> T = 0;
    virtual auto visit_expr_stmt(const Expression &stmt) -> T = 0;
    virtual auto visit_function_stmt(const Function &stmt) -> T = 0;
    virtual auto visit_if_stmt(const If &stmt) -> T = 0;
    virtual auto visit_print_stmt(const Print &stmt) -> T = 0;
    virtual auto visit_return_stmt(const Return &stmt) -> T = 0;
    virtual auto visit_var_stmt(const Var &stmt) -> T = 0;
    virtual auto visit_while_stmt(const While &stmt) -> T = 0;
  };

  template <typename T> virtual auto accept(const Visitor<T> &visitor) -> T = 0;

  struct Block final : public Stmt {
    Block(const std::vector<Stmt> &_stmt) : m_stmt(_stmt) {}
    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const std::vector<Stmt> m_stmt;
  };

  struct Class final : public Stmt {
    Class(const Token &_name, const Expr.Variable &_superclass,
          const std::vector<Stmt.Function> &_methods)
        : m_name(_name), m_superclass(_superclass), m_methods(_methods) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Token m_name;
    const Expr.Variable m_superclass;
    const std::vector<Stmt.Function> m_methods;
  };

  struct Expression final : public Stmt {
    Expression(const Expr &_expr) : m_expr(_expr) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Expr m_expr;
  };

  struct Function final : public Stmt {
    Function(const Token &_name, const std::vector<Token> &_params,
             const std::vector<Stmt> &_body)
        : m_name(_name), m_params(_params), m_body(_body) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Token m_name;
    const std::vector<Token> m_params;
    const std::vector<Stmt> m_body;
  };

  struct If final : public Stmt {
    If(const Expr &_condition, const _then, const _else)
        : m_condition(_condition), m_then(_then), m_else(_else) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Expr m_condition;
    const Stmt m_then;
    const Stmt m_else;
  };

  struct Print final : public Stmt {
    Print(const Expr &_expr) : m_expr(_expr) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Expr m_expr;
  };

  struct Return final : public Stmt {
    Return(const Token &_keyword, const Expr &_value)
        : m_keyword(_keyword), m_value(_value) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Token m_keyword;
    const Expr value;
  };

  struct Var final : public Stmt {
    Var(const Token &_name, const Expr &_initializer)
        : m_name(_name), m_initializer(_initializer) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Token m_name;
    const Expr m_initializer;
  };

  struct While final : public Stmt {
    While(const Expr &_condition, const Stmt &_body)
        : m_condition(_condition), m_body(_body) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Expr m_condition;
    const Stmt m_body;
  };
};
}

#endif // __STMT_H__

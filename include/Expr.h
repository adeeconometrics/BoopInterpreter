#ifndef __EXPR_H__
#define __EXPR_H__

#include "Token.h"
#include "Types.h"

namespace boop {

class Expr: Uncopyable {
  template <typename T> class Visitor {
    virtual auto visit_assign_expr(const Assign &expr) -> T = 0;
    virtual auto visit_binary_expr(const Binary &expr) -> T = 0;
    virtual auto visit_call_expr(const Call &expr) -> T = 0;
    virtual auto visit_get_expr(const Get &expr) -> T = 0;
    virtual auto visit_grouping_expr(const Grouping &expr) -> T = 0;
    virtual auto visit_literal_expr(const Literal &expr) -> T = 0;
    virtual auto visit_logical_expr(const Logical &expr) -> T = 0;
    virtual auto visit_set_expr(const Set &expr) -> T = 0;
    virtual auto visit_super_expr(const Super &expr) -> T = 0;
    virtual auto visit_this_expr(const This &expr) -> T = 0;
    virtual auto visit_unary_expr(const Unary &expr) -> T = 0;
    virtual auto visit_variable_expr(const Variable &expr) -> T = 0;
  };

  template <typename T> virtual auto accept(const Visitor<T> &visitor) -> T = 0;
  // should be static
  struct Assign final : public Expr {
    Assign(const Token &_name, const Expr &_value)
        : m_name(_name), m_value(_value) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Token m_name;
    const Expr m_value;
  };

  struct Binary final : public Expr {
    Binary(const Expr &_left, const Token &_op, const Expr &_right)
        : m_left(_left), m_op(_op), m_right(_right) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Expr m_left;
    const Token m_op;
    const Expr m_right;
  };

  struct Call final : public Expr {
    Call(const Expr &_callee, const Token &_paren,
         const std::vector<Expr> &_args)
        : m_callee(_callee), m_paren(_paren), m_args(_args) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Expr m_callee;
    const Token m_paren;
    const std::vector<Expr> m_args;
  };

  struct Get final : public Expr {
    Get(const Expr &_obj, const Token &_name) : m_obj(_obj), m_name(_name) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Expr m_obj;
    const Token m_name;
  };

  struct Grouping final : public Expr {
    Grouping(const Expr &_expr) : m_expr(_expr) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Expr m_expr;
  };

  struct Literal final : public Expr {
    Literal(const LiteralType &_value) : m_value(_value) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const LiteralType m_value;
  };

  struct Logical final : public Expr {
    Logical(const Expr &_left, const Token &_op, const Expr &_right)
        : m_left(_left), m_op(_op), m_right(_right) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Expr m_left;
    const Token m_op;
    const Expr m_right;
  };

  struct Set final : public Expr {
    Set(const Expr &_obj, const Token &_name, const Expr &_value)
        : m_obj(_obj), m_name(_name), m_value(_value) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Expr m_obj;
    const Token m_name;
    const Expr m_value;
  };

  struct Super final : public Expr {
    Super(const Token &_keyword, const Token &_method)
        : m_keyword(_keyword), m_method(_method) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Token m_keyword;
    const Token m_method;
  };

  struct This final : public Expr {
    This(const Token &_keyword) : m_keyword(_keyword) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Token m_keyword;
  };

  struct Unary final : public Expr {
    Unary(const Token &_op, const Expr &_right) : m_op(_op), m_right(_right) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Token m_op;
    const Expr m_right;
  };

  struct Variable final : public Expr {
    Variable(const Token &_name) : m_name(_name) {}

    template <typename T> auto accept(const Visitor<T> &visitor) -> T override;

    const Token m_name;
  };
};

}

#endif // __EXPR_H__
